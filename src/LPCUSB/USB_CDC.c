/*
	LPCUSB, an USB device driver for LPC microcontrollers	
	Copyright (C) 2006 Bertrik Sikken (bertrik@sikken.nl)

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, 
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
	Minimal implementation of a USB serial port, using the CDC class.
	This example application simply echoes everything it receives right back
	to the host.

	Windows:
	Extract the usbser.sys file from .cab file in C:\WINDOWS\Driver Cache\i386
	and store it somewhere (C:\temp is a good place) along with the usbser.inf
	file. Then plug in the LPC176x and direct windows to the usbser driver.
	Windows then creates an extra COMx port that you can open in a terminal
	program, like hyperterminal. [Note for FreeRTOS users - the required .inf
	file is included in the project directory.]

	Linux:
	The device should be recognised automatically by the cdc_acm driver,
	which creates a /dev/ttyACMx device file that acts just like a regular
	serial port.

*/

#include <game_res.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <stdio.h>
#include <string.h>

#include "usbapi.h"
#include "usbdebug.h"
#include "usbstruct.h"



#include "LPC17xx.h"
#include "GLCD.h"
#include "gamed.h"


#define usbMAX_SEND_BLOCK		( 20 / portTICK_PERIOD_MS )
#define usbBUFFER_LEN			( 20 )

#define INCREMENT_ECHO_BY 1
#define BAUD_RATE	115200

#define INT_IN_EP		0x81
#define BULK_OUT_EP		0x05
#define BULK_IN_EP		0x82

#define MAX_PACKET_SIZE	64

#define LE_WORD(x)		((x)&0xFF),((x)>>8)

// CDC definitions
#define CS_INTERFACE			0x24
#define CS_ENDPOINT				0x25

#define	SET_LINE_CODING			0x20
#define	GET_LINE_CODING			0x21
#define	SET_CONTROL_LINE_STATE	0x22

// data structure for GET_LINE_CODING / SET_LINE_CODING class requests
typedef struct {
	unsigned long		dwDTERate;
	unsigned char		bCharFormat;
	unsigned char		bParityType;
	unsigned char		bDataBits;
} TLineCoding;

static TLineCoding LineCoding = {115200, 0, 0, 8};
static unsigned char abBulkBuf[64];
static unsigned char abClassReqData[8];

static QueueHandle_t xRxedChars = NULL, xCharsForTx = NULL;

// forward declaration of interrupt handler
void USBIntHandler(void);

static const unsigned char abDescriptors[] = {

// device descriptor
	0x12,
	DESC_DEVICE,
	LE_WORD(0x0101),			// bcdUSB
	0x02,						// bDeviceClass
	0x00,						// bDeviceSubClass
	0x00,						// bDeviceProtocol
	MAX_PACKET_SIZE0,			// bMaxPacketSize
	LE_WORD(0xFFFF),			// idVendor
	LE_WORD(0x0005),			// idProduct
	LE_WORD(0x0100),			// bcdDevice
	0x01,						// iManufacturer
	0x02,						// iProduct
	0x03,						// iSerialNumber
	0x01,						// bNumConfigurations

// configuration descriptor
	0x09,
	DESC_CONFIGURATION,
	LE_WORD(67),				// wTotalLength
	0x02,						// bNumInterfaces
	0x01,						// bConfigurationValue
	0x00,						// iConfiguration
	0xC0,						// bmAttributes
	0x32,						// bMaxPower
// control class interface
	0x09,
	DESC_INTERFACE,
	0x00,						// bInterfaceNumber
	0x00,						// bAlternateSetting
	0x01,						// bNumEndPoints
	0x02,						// bInterfaceClass
	0x02,						// bInterfaceSubClass
	0x01,						// bInterfaceProtocol, linux requires value of 1 for the cdc_acm module
	0x00,						// iInterface
// header functional descriptor
	0x05,
	CS_INTERFACE,
	0x00,
	LE_WORD(0x0110),
// call management functional descriptor
	0x05,
	CS_INTERFACE,
	0x01,
	0x01,						// bmCapabilities = device handles call management
	0x01,						// bDataInterface
// ACM functional descriptor
	0x04,
	CS_INTERFACE,
	0x02,
	0x02,						// bmCapabilities
// union functional descriptor
	0x05,
	CS_INTERFACE,
	0x06,
	0x00,						// bMasterInterface
	0x01,						// bSlaveInterface0
// notification EP
	0x07,
	DESC_ENDPOINT,
	INT_IN_EP,					// bEndpointAddress
	0x03,						// bmAttributes = intr
	LE_WORD(8),					// wMaxPacketSize
	0x0A,						// bInterval
// data class interface descriptor
	0x09,
	DESC_INTERFACE,
	0x01,						// bInterfaceNumber
	0x00,						// bAlternateSetting
	0x02,						// bNumEndPoints
	0x0A,						// bInterfaceClass = data
	0x00,						// bInterfaceSubClass
	0x00,						// bInterfaceProtocol
	0x00,						// iInterface
// data EP OUT
	0x07,
	DESC_ENDPOINT,
	BULK_OUT_EP,				// bEndpointAddress
	0x02,						// bmAttributes = bulk
	LE_WORD(MAX_PACKET_SIZE),	// wMaxPacketSize
	0x00,						// bInterval
// data EP in
	0x07,
	DESC_ENDPOINT,
	BULK_IN_EP,					// bEndpointAddress
	0x02,						// bmAttributes = bulk
	LE_WORD(MAX_PACKET_SIZE),	// wMaxPacketSize
	0x00,						// bInterval
	
	// string descriptors
	0x04,
	DESC_STRING,
	LE_WORD(0x0409),

	0x0E,
	DESC_STRING,
	'L', 0, 'P', 0, 'C', 0, 'U', 0, 'S', 0, 'B', 0,

	0x14,
	DESC_STRING,
	'U', 0, 'S', 0, 'B', 0, 'S', 0, 'e', 0, 'r', 0, 'i', 0, 'a', 0, 'l', 0,

	0x12,
	DESC_STRING,
	'D', 0, 'E', 0, 'A', 0, 'D', 0, 'C', 0, '0', 0, 'D', 0, 'E', 0,

// terminating zero
	0
};


/**
	Local function to handle incoming bulk data
		
	@param [in] bEP
	@param [in] bEPStatus
 */
static void BulkOut(unsigned char bEP, unsigned char bEPStatus)
{
	int i, iLen;
	long lHigherPriorityTaskWoken = pdFALSE;

	( void ) bEPStatus;
	
	// get data from USB into intermediate buffer
	iLen = USBHwEPRead(bEP, abBulkBuf, sizeof(abBulkBuf));
	for (i = 0; i < iLen; i++) {
		// put into queue
		xQueueSendFromISR( xRxedChars, &( abBulkBuf[ i ] ), &lHigherPriorityTaskWoken ); 
	}
	
	portEND_SWITCHING_ISR( lHigherPriorityTaskWoken );
}


/**
	Local function to handle outgoing bulk data
		
	@param [in] bEP
	@param [in] bEPStatus
 */
static void BulkIn(unsigned char bEP, unsigned char bEPStatus)
{
	int i, iLen;
	long lHigherPriorityTaskWoken = pdFALSE;

	( void ) bEPStatus;
	
	if (uxQueueMessagesWaitingFromISR( xCharsForTx ) == 0) {
		// no more data, disable further NAK interrupts until next USB frame
		USBHwNakIntEnable(0);
		return;
	}

	// get bytes from transmit FIFO into intermediate buffer
	for (i = 0; i < MAX_PACKET_SIZE; i++) {
		if( xQueueReceiveFromISR( xCharsForTx, ( &abBulkBuf[i] ), &lHigherPriorityTaskWoken ) != pdPASS )
		{
			break;
		}
	}
	iLen = i;
	
	// send over USB
	if (iLen > 0) {
		USBHwEPWrite(bEP, abBulkBuf, iLen);
	}
	
	portEND_SWITCHING_ISR( lHigherPriorityTaskWoken );
}


/**
	Local function to handle the USB-CDC class requests
		
	@param [in] pSetup
	@param [out] piLen
	@param [out] ppbData
 */
static BOOL HandleClassRequest(TSetupPacket *pSetup, int *piLen, unsigned char **ppbData)
{
	switch (pSetup->bRequest) {

	// set line coding
	case SET_LINE_CODING:
DBG("SET_LINE_CODING\n");
		memcpy((unsigned char *)&LineCoding, *ppbData, 7);
		*piLen = 7;
DBG("dwDTERate=%u, bCharFormat=%u, bParityType=%u, bDataBits=%u\n",
	LineCoding.dwDTERate,
	LineCoding.bCharFormat,
	LineCoding.bParityType,
	LineCoding.bDataBits);
		break;

	// get line coding
	case GET_LINE_CODING:
DBG("GET_LINE_CODING\n");
		*ppbData = (unsigned char *)&LineCoding;
		*piLen = 7;
		break;

	// set control line state
	case SET_CONTROL_LINE_STATE:
		// bit0 = DTR, bit = RTS
DBG("SET_CONTROL_LINE_STATE %X\n", pSetup->wValue);
		break;

	default:
		return FALSE;
	}
	return TRUE;
}


/**
	Writes one character to VCOM port
	
	@param [in] c character to write
	@returns character written, or EOF if character could not be written
 */
int VCOM_putchar(int c)
{
char cc = ( char ) c;

	if( xQueueSend( xCharsForTx, &cc, usbMAX_SEND_BLOCK ) == pdPASS )
	{
		return c;
	}
	else
	{
		return EOF;
	}
}


/**
	Reads one character from VCOM port
	
	@returns character read, or EOF if character could not be read
 */
int VCOM_getchar(void)
{
	unsigned char c;
	
	/* Block the task until a character is available. */
	xQueueReceive( xRxedChars, &c, portMAX_DELAY );
	return c;
}


/**
	Interrupt handler
	
	Simply calls the USB ISR
 */
//void USBIntHandler(void)
void USB_IRQHandler(void)
{
	USBHwISR();
}


static void USBFrameHandler(unsigned short wFrame)
{
	( void ) wFrame;
	
	if( uxQueueMessagesWaitingFromISR( xCharsForTx ) > 0 )
	{
		// data available, enable NAK interrupt on bulk in
		USBHwNakIntEnable(INACK_BI);
	}
}

// CodeRed - added CPUcpsie

unsigned long CPUcpsie(void)
{
    unsigned long ulRet;

    //
    // Read PRIMASK and enable interrupts.
    //
    __asm("    mrs     %0, PRIMASK\n"
          "    cpsie   i\n"
          "    bx      lr\n"
          : "=r" (ulRet));

    //
    // The return is handled in the inline assembly, but the compiler will
    // still complain if there is not an explicit return here (despite the fact
    // that this does not result in any code being produced because of the
    // naked attribute).
    //
    return(ulRet);
}



void vUSBTask( void *pvParameters )
{
	int c;
	
	/* Just to prevent compiler warnings about the unused parameter. */
	( void ) pvParameters;
	DBG("Initialising USB stack\n");

	xRxedChars = xQueueCreate( usbBUFFER_LEN, sizeof( char ) );
	xCharsForTx = xQueueCreate( usbBUFFER_LEN, sizeof( char ) );

	if( ( xRxedChars == NULL ) || ( xCharsForTx == NULL ) )
	{
		/* Not enough heap available to create the buffer queues, can't do
		anything so just delete ourselves. */
		vTaskDelete( NULL );
	}
	
	
	// initialise stack
	USBInit();

	// register descriptors
	USBRegisterDescriptors(abDescriptors);

	// register class request handler
	USBRegisterRequestHandler(REQTYPE_TYPE_CLASS, HandleClassRequest, abClassReqData);

	// register endpoint handlers
	USBHwRegisterEPIntHandler(INT_IN_EP, NULL);
	USBHwRegisterEPIntHandler(BULK_IN_EP, BulkIn);
	USBHwRegisterEPIntHandler(BULK_OUT_EP, BulkOut);
	
	// register frame handler
	USBHwRegisterFrameHandler(USBFrameHandler);

	// enable bulk-in interrupts on NAKs
	USBHwNakIntEnable(INACK_BI);

	DBG("Starting USB communication\n");
	GLCD_displayStringLn(144,  "USB Communication...");

	NVIC_SetPriority( USB_IRQn, configUSB_INTERRUPT_PRIORITY );
	NVIC_EnableIRQ( USB_IRQn );
		
	// connect to bus
		
	DBG("Connecting to USB bus\n");
	GLCD_displayStringLn(168, "Connecting USB Bus...");
	USBHwConnect(TRUE);
	int line = 0;
	int i =0;
	int mode = 0;
	int init = 0;

	unsigned int  xy[4];


	// echo any character received (do USB stuff in interrupt)
	for( ;; )
	{


		c = VCOM_getchar();
		if (c != EOF) 
		{
			if(init == 0){
				init++;
				GLCD_displayStringLn(192, "Connected.");
				GLCD_clear(0xFFFF);
			}

		//	VCOM_putchar(c);
			// Echo character back with INCREMENT_ECHO_BY offset, so for example if
			// INCREMENT_ECHO_BY is 1 and 'A' is received, 'B' will be echoed back.
//			if(sendUSBCDC == 1 && c == 'p'){
//
//			if(selector_x + selectedx_s > 9){
//					VCOM_putchar('1');
//					VCOM_putchar('0' + (selector_x + selectedx_s - 10));
//				}else{
//					VCOM_putchar('0' + selector_x + selectedx_s);
//				}
//				VCOM_putchar('/');
//				if(selector_y + selectedy_s > 9){
//							VCOM_putchar('1');
//							VCOM_putchar('0' + (selector_y + selectedy_s- 10));
//						}else{
//							VCOM_putchar('0' + selector_y + selectedy_s);
//						}
//
//				sendUSBCDC = 0;
//
//			}

// `1 : String mode `2 Dot mode `3 fnd mode '4 clear lcd
if(c == '\''){
	mode = 0;
	continue;
}

if(mode == 0){
	if(c == '1') mode = 1;
	if(c == '2') mode = 2;
	if(c == '3') mode = 3;
	if(c == '4') {
		GLCD_clear(0xFFFF);
		i=0;
		line =0;

	}
	//Enter
	if(c == '5') {

			i=0;
			line++;

		}
	//map
	if(c == '8') {
		GLCD_setBackColor(0xFFFF);
		GLCD_bitmap2X( 40 ,0,240,240,omok_map);
	//	GLCD_bitmap_transparent(0,0,16,16,black_dol);
	//	putDol(4,4 ,1);
		//putSelector(2,2);

	}



	//PUT DOL
if(c== '7'){
	i=0;
	mode = 7;


}


	if(c == '9') {
		GLCD_clear(0xFFFF);
		i=0;
		line =0;
		GLCD_bitmap2X(0,0,320,240,omok_startup);



	}


	continue;
}

			if(mode == 1) {

				if(i >= 20) {
					i = 0;
					line++;
				}

				GLCD_displayChar(i*16,  line*24, c);
			}
if(mode == 2) {

	if(i >= 352) {
						i = 0;
						line++;
					}

	if(c == '1') GLCD_putPixel(i, line);
}

if(mode == 7){
	if(i < 4){
		xy[i] = c;
	}else{
		unsigned int x = (xy[0]- '0')*10 + (xy[1]- '0');
	unsigned int	y  =(xy[2]- '0')*10 + (xy[3]- '0');

i=0;
		putDol(x, y, 1, 1);
		//if(sendUSBCDC == 0) xTaskResumeAll();
	}


}

		i++;

		}
	}
}

