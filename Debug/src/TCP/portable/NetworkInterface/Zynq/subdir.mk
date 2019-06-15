################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/TCP/portable/NetworkInterface/Zynq/NetworkInterface.c \
../src/TCP/portable/NetworkInterface/Zynq/uncached_memory.c \
../src/TCP/portable/NetworkInterface/Zynq/x_emacpsif_dma.c \
../src/TCP/portable/NetworkInterface/Zynq/x_emacpsif_hw.c \
../src/TCP/portable/NetworkInterface/Zynq/x_emacpsif_physpeed.c 

OBJS += \
./src/TCP/portable/NetworkInterface/Zynq/NetworkInterface.o \
./src/TCP/portable/NetworkInterface/Zynq/uncached_memory.o \
./src/TCP/portable/NetworkInterface/Zynq/x_emacpsif_dma.o \
./src/TCP/portable/NetworkInterface/Zynq/x_emacpsif_hw.o \
./src/TCP/portable/NetworkInterface/Zynq/x_emacpsif_physpeed.o 

C_DEPS += \
./src/TCP/portable/NetworkInterface/Zynq/NetworkInterface.d \
./src/TCP/portable/NetworkInterface/Zynq/uncached_memory.d \
./src/TCP/portable/NetworkInterface/Zynq/x_emacpsif_dma.d \
./src/TCP/portable/NetworkInterface/Zynq/x_emacpsif_hw.d \
./src/TCP/portable/NetworkInterface/Zynq/x_emacpsif_physpeed.d 


# Each subdirectory must supply rules for building sources it contributes
src/TCP/portable/NetworkInterface/Zynq/%.o: ../src/TCP/portable/NetworkInterface/Zynq/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -DPACK_STRUCT_END=__attribute\(\(packed\)\) -DALIGN_STRUCT_END=__attribute\(\(aligned\(4\)\)\) -D__CODE_RED -D__REDLIB__ -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/FreeRTOS/include" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/LPCUSB" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/webserver" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/Common Demo Tasks/include" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/FreeRTOS/portable/GCC/ARM_CM3" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -Wextra -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


