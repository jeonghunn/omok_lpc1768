################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/TCP/FreeRTOS_DHCP.c \
../src/TCP/FreeRTOS_DNS.c \
../src/TCP/FreeRTOS_IP.c \
../src/TCP/FreeRTOS_Stream_Buffer.c \
../src/TCP/FreeRTOS_TCP_IP.c \
../src/TCP/FreeRTOS_TCP_WIN.c \
../src/TCP/FreeRTOS_UDP_IP.c 

OBJS += \
./src/TCP/FreeRTOS_DHCP.o \
./src/TCP/FreeRTOS_DNS.o \
./src/TCP/FreeRTOS_IP.o \
./src/TCP/FreeRTOS_Stream_Buffer.o \
./src/TCP/FreeRTOS_TCP_IP.o \
./src/TCP/FreeRTOS_TCP_WIN.o \
./src/TCP/FreeRTOS_UDP_IP.o 

C_DEPS += \
./src/TCP/FreeRTOS_DHCP.d \
./src/TCP/FreeRTOS_DNS.d \
./src/TCP/FreeRTOS_IP.d \
./src/TCP/FreeRTOS_Stream_Buffer.d \
./src/TCP/FreeRTOS_TCP_IP.d \
./src/TCP/FreeRTOS_TCP_WIN.d \
./src/TCP/FreeRTOS_UDP_IP.d 


# Each subdirectory must supply rules for building sources it contributes
src/TCP/%.o: ../src/TCP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -DPACK_STRUCT_END=__attribute\(\(packed\)\) -DALIGN_STRUCT_END=__attribute\(\(aligned\(4\)\)\) -D__CODE_RED -D__REDLIB__ -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/FreeRTOS/include" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/LPCUSB" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/webserver" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/Common Demo Tasks/include" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/FreeRTOS/portable/GCC/ARM_CM3" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/inc" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/inc" -I"/Users/jhrunning/Documents/MCUXpressoIDE_10.3.1/workspace/CMSIS_CORE_LPC17xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -Wextra -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


