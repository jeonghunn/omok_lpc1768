################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FreeRTOS/list.c \
../src/FreeRTOS/queue.c \
../src/FreeRTOS/tasks.c 

OBJS += \
./src/FreeRTOS/list.o \
./src/FreeRTOS/queue.o \
./src/FreeRTOS/tasks.o 

C_DEPS += \
./src/FreeRTOS/list.d \
./src/FreeRTOS/queue.d \
./src/FreeRTOS/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
src/FreeRTOS/%.o: ../src/FreeRTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -DPACK_STRUCT_END=__attribute\(\(packed\)\) -DALIGN_STRUCT_END=__attribute\(\(aligned\(4\)\)\) -D__CODE_RED -D__REDLIB__ -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/FreeRTOS/include" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/LPCUSB" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/webserver" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/Common Demo Tasks/include" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/FreeRTOS/portable/GCC/ARM_CM3" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/inc" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/inc" -I"/Users/jhrunning/Documents/MCUXpressoIDE_10.3.1/workspace/CMSIS_CORE_LPC17xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -Wextra -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


