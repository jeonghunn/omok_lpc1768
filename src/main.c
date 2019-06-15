/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the standard demo application tasks
 * (which just exist to test the kernel port and provide an example of how to use
 * each FreeRTOS API function).
 *
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "Check" hook -  This only executes fully every five seconds from the tick
 * hook.  Its main function is to check that all the standard demo tasks are
 * still operational.  The status can be viewed using on the Task Stats page
 * served by the WEB server.
 *
 * "uIP" task -  This is the task that handles the uIP stack.  All TCP/IP
 * processing is performed in this task.
 *
 * "USB" task - Enumerates the USB device as a CDC class, then echoes back all
 * received characters with a configurable offset (for example, if the offset
 * is 1 and 'A' is received then 'B' will be sent back).  A dumb terminal such
 * as Hyperterminal can be used to talk to the USB task.
 */

/* Standard includes. */
#include "stdio.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo app includes. */
#include "BlockQ.h"
#include "integer.h"
#include "blocktim.h"
#include "flash.h"
#include "partest.h"
#include "semtest.h"
#include "PollQ.h"
#include "GenQTest.h"
#include "QPeek.h"
#include "recmutex.h"
#include "GLCD.h"
#include "LED.h"
#include "gamed.h"
#include "Keypad.H"


#include "LPC1768_utility.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"



/*-----------------------------------------------------------*/

/* The time between cycles of the 'check' functionality (defined within the
tick hook. */
#define mainCHECK_DELAY						( ( TickType_t ) 5000 / portTICK_PERIOD_MS )

/* Task priorities. */
#define mainQUEUE_POLL_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainSEM_TEST_PRIORITY				( tskIDLE_PRIORITY + 1 )
#define mainBLOCK_Q_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainUIP_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define mainINTEGER_TASK_PRIORITY           ( tskIDLE_PRIORITY )
#define mainGEN_QUEUE_TASK_PRIORITY			( tskIDLE_PRIORITY )
#define mainFLASH_TASK_PRIORITY				( tskIDLE_PRIORITY + 2 )

/* The WEB server has a larger stack as it utilises stack hungry string
handling library calls. */
#define mainBASIC_WEB_STACK_SIZE            ( configMINIMAL_STACK_SIZE * 4 )

/* The message displayed by the WEB server when all tasks are executing
without an error being reported. */
#define mainPASS_STATUS_MESSAGE				"All tasks are executing without error."

/* Bit definitions. */
#define PCONP_PCGPIO    0x00008000
#define PLLFEED_FEED1   0x000000AA
#define PLLFEED_FEED2   0x00000055
/*-----------------------------------------------------------*/


/*
 * Configure the hardware for the demo.
 */
static void prvSetupHardware( void );

/*
 * The task that handles the uIP stack.  Al조ㅑㅣl TCP/IP processing is performed in
 * this task.
 */
extern void vuIP_Task( void *pvParameters );

/*
 * The task that handles the USB stack.
 */
extern void vUSBTask( void *pvParameters );

/*
 * Simply returns the current status message for display on served WEB pages.
 */
char *pcGetTaskStatusMessage( void );

/*-----------------------------------------------------------*/

/* Holds the status message displayed by the WEB server. */
static char *pcStatusMessage = mainPASS_STATUS_MESSAGE;

/*-----------------------------------------------------------*/

int keypadTask(void *args){





}



int joyStickTask(void *args){

	uint8_t Keypad_Value=20;

	while(1)
	  {
		unsigned int oldx = selector_x;
		unsigned int oldy = selector_y;
			//	Áö¼ÓÀûÀ¸·Î ¹öÆ°ÀÇ »óÅÂ¸¦ ReadÇÏ¿© »óÅÂ°ªÀ» Button_Status¿¡ ÀúÀåÇÏ°í ÆÇº°ÇÑ´Ù.
			int okbutton = (GPIO_ReadValue(GPIO_PORT_1) & (1<<20)); //	GPIO_ReadValue´Â ÇØ´ç PORTÀÇ 32 Bit °ªÀ» ¹ÝÈ¯ÇÑ´Ù.
			int leftb = (GPIO_ReadValue(GPIO_PORT_1) & (1<<23)); //	GPIO_ReadValue´Â ÇØ´ç PORTÀÇ 32 Bit °ªÀ» ¹ÝÈ¯ÇÑ´Ù.
			int topb = (GPIO_ReadValue(GPIO_PORT_1) & (1<<24)); //	GPIO_ReadValue´Â ÇØ´ç PORTÀÇ 32 Bit °ªÀ» ¹ÝÈ¯ÇÑ´Ù.
			int rightb = (GPIO_ReadValue(GPIO_PORT_1) & (1<<25)); //	GPIO_ReadValue´Â ÇØ´ç PORTÀÇ 32 Bit °ªÀ» ¹ÝÈ¯ÇÑ´Ù.
			int bottomb = (GPIO_ReadValue(GPIO_PORT_1) & (1<<26)); //	GPIO_ReadValue´Â ÇØ´ç PORTÀÇ 32 Bit °ªÀ» ¹ÝÈ¯ÇÑ´Ù.


			if(okbutton == 0)	//	INT ButtonÀ» ´­·¶À» ¶§
			{

			 putSelector(selector_x,selector_y, oldx,oldy);
			}
			if(leftb == 0)	//	INT ButtonÀ» ´­·¶À» ¶§
						{
						selector_x--;
						 putSelector(selector_x,selector_y, oldx,oldy);
						}
			if(rightb == 0)	//	INT ButtonÀ» ´­·¶À» ¶§
								{
				selector_x++;
				 putSelector(selector_x,selector_y, oldx,oldy);
								}
			if(topb == 0)	//	INT ButtonÀ» ´­·¶À» ¶§
								{
				selector_y--;
				 putSelector(selector_x,selector_y, oldx,oldy);
								}
			if(bottomb == 0)	//	INT ButtonÀ» ´­·¶À» ¶§
								{
				selector_y++;
				 putSelector(selector_x,selector_y, oldx,oldy);
								}

			 Keypad_Value = Keypad('C');
				if(Keypad_Value != 20){

					unsigned int placex = 0;
					unsigned int placey = 0;

					unsigned int sy = (Keypad_Value+1)/4;
					unsigned int sx = (Keypad_Value+1)%4 ;

					if(sx > 0) {
			sx  = sx -1;
					}else{
						sy = sy -1;
						sx = 3;
					}

					//if(okbutton == 0 || leftb == 0 || topb ==  0 || rightb ==0 || bottomb == 0) {



		//	putDol(selector_x + sx , selector_y + sy, 2, 1);
			if(selector_x + sx > 9){
				VCOM_putchar('1');
				VCOM_putchar('0' + (selector_x + sx - 10));
			}else{
				VCOM_putchar('0' + selector_x + sx);
			}
			VCOM_putchar('/');
			if(selector_y + sy > 9){
						VCOM_putchar('1');
						VCOM_putchar('0' + (selector_y + sy- 10));
					}else{
						VCOM_putchar('0' + selector_y + sy);
					}
			VCOM_putchar('/');
			//VCOM_putchar(EOF);

			putDol(selector_x + sx , selector_y + sy , 2, 1);

				}


		}
}


int main( void )
{
char cIPAddress[ 16 ]; /* Enough space for "xxx.xxx.xxx.xxx\0". */

	/* Configure the hardware for use by this demo. */
	prvSetupHardware();

	/* Start the standard demo tasks.  These are just here to exercise the
	kernel port and provide examples of how the FreeRTOS API can be used. */
//	vStartBlockingQueueTasks( mainBLOCK_Q_PRIORITY );
 //   vCreateBlockTimeTasks();
  //  vStartSemaphoreTasks( mainSEM_TEST_PRIORITY );
  //  vStartPolledQueueTasks( mainQUEUE_POLL_PRIORITY );
 //   vStartIntegerMathTasks( mainINTEGER_TASK_PRIORITY );
//    vStartGenericQueueTasks( mainGEN_QUEUE_TASK_PRIORITY );
  //  vStartQueuePeekTasks();eeww
    //vStartRecursiveMutexTasks()d;

    /* Create the USB task. */

enemy_x = -1;
enemy_y = -1;
sendUSBCDC=0;
    xTaskCreate( vUSBTask, "USB", mainBASIC_WEB_STACK_SIZE, ( void * ) NULL, tskIDLE_PRIORITY+3 , NULL );

	/* Display the IP address, then create the uIP task.  The WEB server runs
	in this task.  --- Due to tool changes since this demo was created the LCD
	is no longer used.
	LCDdriver_initialisation();
	LCD_PrintString( 5, 10, "FreeRTOS.org", 14, COLOR_GREEN);
	sprintf( cIPAddress, "%d.%d.%d.%d", configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3 );
	LCD_PrintString( 5, 30, cIPAddress, 14, COLOR_RED);
    xTaskCreate( vuIP_Task, "uIP", mainBASIC_WEB_STACK_SIZE, ( void * ) NULL, mainUIP_TASK_PRIORITY, NULL ); */

   // sprintf( cIPAddress, "%d.%d.%d.%d", configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3 );

    //
                           /* Initialize the MCU clocks     */

        	LED_init ();                              /* Initialize the LEDs           */

        	GLCD_init();                              /* Initialize the GLCD           */
        	GLCD_clear(White);                        /* Clear the GLCD                */
        	GLCD_displayStringLn(Line0, "Cortex M3 LPC 1768");
        	GLCD_displayStringLn(Line1, "(C) 2019, JHRunning");
        //	GLCD_setBackColor(Blue);                           /* Set the Text Color */
        			//GLCD_setTextColor(White);                          /* Set the Text Color */


        	  LPC_GPIO1->FIODIR   &= ~((1UL<<20)|(1UL<<23)|(1UL<<24)|(1UL<<25)|(1UL<<26));
        	  EXT_IO_init();
        	    Keypad_DIR_Input();
        	//		GLCD_displayStringLn(0, "   www.huins.com    ");


        //	os_sys_init(init);                        /* Initialize RTX and start init */
        	  xTaskCreate(joyStickTask, NULL, mainBASIC_WEB_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL); //테스크1
        //	  xTaskCreate(keypadTask, NULL, configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL); //테스크1
       // 	  xTaskCreate( vuIP_Task, "uIP", mainBASIC_WEB_STACK_SIZE, ( void * ) NULL, mainUIP_TASK_PRIORITY, NULL );
        		//

    /* Start the scheduler. */
	vTaskStartScheduler();

    /* Will only get here if there was insufficient memory to create the idle
    task.  The idle task is created within vTaskStartScheduler(). */
	for( ;; );
}
/*-----------------------------------------------------------*/




void vApplicationTickHook( void )
{
static unsigned long ulTicksSinceLastDisplay = 0;

	/* Called from every tick interrupt as described in the comments at the top
	of this file.

	Have enough ticks passed to make it	time to perform our health status
	check again? */
	ulTicksSinceLastDisplay++;
	if( ulTicksSinceLastDisplay >= mainCHECK_DELAY )
	{
		/* Reset the counter so these checks run again in mainCHECK_DELAY
		ticks time. */
		ulTicksSinceLastDisplay = 0;

		/* Has an error been found in any task? */
		if( xAreGenericQueueTasksStillRunning() != pdTRUE )
		{
			pcStatusMessage = "An error has been detected in the Generic Queue test/demo.";
		}
		else if( xAreQueuePeekTasksStillRunning() != pdTRUE )
		{
			pcStatusMessage = "An error has been detected in the Peek Queue test/demo.";
		}
		else if( xAreBlockingQueuesStillRunning() != pdTRUE )
		{
			pcStatusMessage = "An error has been detected in the Block Queue test/demo.";
		}
		else if( xAreBlockTimeTestTasksStillRunning() != pdTRUE )
		{
			pcStatusMessage = "An error has been detected in the Block Time test/demo.";
		}
	    else if( xAreSemaphoreTasksStillRunning() != pdTRUE )
	    {
	        pcStatusMessage = "An error has been detected in the Semaphore test/demo.";
	    }
	    else if( xArePollingQueuesStillRunning() != pdTRUE )
	    {
	        pcStatusMessage = "An error has been detected in the Poll Queue test/demo.";
	    }
	    else if( xAreIntegerMathsTaskStillRunning() != pdTRUE )
	    {
	        pcStatusMessage = "An error has been detected in the Int Math test/demo.";
	    }
	    else if( xAreRecursiveMutexTasksStillRunning() != pdTRUE )
	    {
	    	pcStatusMessage = "An error has been detected in the Mutex test/demo.";
	    }
	}
}
/*-----------------------------------------------------------*/

char *pcGetTaskStatusMessage( void )
{
	/* Not bothered about a critical section here. */
	return pcStatusMessage;
}
/*-----------------------------------------------------------*/

void prvSetupHardware( void )
{
	/* Disable peripherals power. */
	LPC_SC->PCONP = 0;

	/* Enable GPIO power. */
	LPC_SC->PCONP = PCONP_PCGPIO;

	/* Disable TPIU. */
	LPC_PINCON->PINSEL10 = 0;

	if ( LPC_SC->PLL0STAT & ( 1 << 25 ) )
	{
		/* Enable PLL, disconnected. */
		LPC_SC->PLL0CON = 1;
		LPC_SC->PLL0FEED = PLLFEED_FEED1;
		LPC_SC->PLL0FEED = PLLFEED_FEED2;
	}

	/* Disable PLL, disconnected. */
	LPC_SC->PLL0CON = 0;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;

	/* Enable main OSC. */
	LPC_SC->SCS |= 0x20;
	while( !( LPC_SC->SCS & 0x40 ) );

	/* select main OSC, 12MHz, as the PLL clock source. */
	LPC_SC->CLKSRCSEL = 0x1;

	LPC_SC->PLL0CFG = 0x20031;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;

	/* Enable PLL, disconnected. */
	LPC_SC->PLL0CON = 1;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;

	/* Set clock divider. */
	LPC_SC->CCLKCFG = 0x03;

	/* Configure flash accelerator. */
	LPC_SC->FLASHCFG = 0x403a;

	/* Check lock bit status. */
	while( ( ( LPC_SC->PLL0STAT & ( 1 << 26 ) ) == 0 ) );

	/* Enable and connect. */
	LPC_SC->PLL0CON = 3;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;
	while( ( ( LPC_SC->PLL0STAT & ( 1 << 25 ) ) == 0 ) );




	/* Configure the clock for the USB. */
	if( LPC_SC->PLL1STAT & ( 1 << 9 ) )
	{
		/* Enable PLL, disconnected. */
		LPC_SC->PLL1CON = 1;
		LPC_SC->PLL1FEED = PLLFEED_FEED1;
		LPC_SC->PLL1FEED = PLLFEED_FEED2;
	}

	/* Disable PLL, disconnected. */
	LPC_SC->PLL1CON = 0;
	LPC_SC->PLL1FEED = PLLFEED_FEED1;
	LPC_SC->PLL1FEED = PLLFEED_FEED2;

	LPC_SC->PLL1CFG = 0x23;
	LPC_SC->PLL1FEED = PLLFEED_FEED1;
	LPC_SC->PLL1FEED = PLLFEED_FEED2;

	/* Enable PLL, disconnected. */
	LPC_SC->PLL1CON = 1;
	LPC_SC->PLL1FEED = PLLFEED_FEED1;
	LPC_SC->PLL1FEED = PLLFEED_FEED2;
	while( ( ( LPC_SC->PLL1STAT & ( 1 << 10 ) ) == 0 ) );

	/* Enable and connect. */
	LPC_SC->PLL1CON = 3;
	LPC_SC->PLL1FEED = PLLFEED_FEED1;
	LPC_SC->PLL1FEED = PLLFEED_FEED2;
	while( ( ( LPC_SC->PLL1STAT & ( 1 << 9 ) ) == 0 ) );

	/*  Setup the peripheral bus to be the same as the CPU output (100 MHz). */
	LPC_SC->PCLKSEL0 = 0x05555555;

	/* Configure the LEDs. */
	vParTestInitialise();
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	/* This function will get called if a task overflows its stack. */

	( void ) pxTask;
	( void ) pcTaskName;

	for( ;; );
}
/*-----------------------------------------------------------*/

void vConfigureTimerForRunTimeStats( void )
{
const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;

	/* This function configures a timer that is used as the time base when
	collecting run time statistical information - basically the percentage
	of CPU time that each task is utilising.  It is called automatically when
	the scheduler is started (assuming configGENERATE_RUN_TIME_STATS is set
	to 1). */

	/* Power up and feed the timer. */
	LPC_SC->PCONP |= 0x02UL;
	LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & (~(0x3<<2))) | (0x01 << 2);

	/* Reset Timer 0 */
	LPC_TIM0->TCR = TCR_COUNT_RESET;

	/* Just count up. */
	LPC_TIM0->CTCR = CTCR_CTM_TIMER;

	/* Prescale to a frequency that is good enough to get a decent resolution,
	but not too fast so as to overflow all the time. */
	LPC_TIM0->PR =  ( configCPU_CLOCK_HZ / 10000UL ) - 1UL;

	/* Start the counter. */
	LPC_TIM0->TCR = TCR_COUNT_ENABLE;
}
/*-----------------------------------------------------------*/

