################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/LPC1768_fnd.c \
../lib/LPC1768_motor.c \
../lib/LPC1768_utility.c \
../lib/debug_frmwrk.c \
../lib/lpc17xx_adc.c \
../lib/lpc17xx_can.c \
../lib/lpc17xx_clkpwr.c \
../lib/lpc17xx_dac.c \
../lib/lpc17xx_emac.c \
../lib/lpc17xx_exti.c \
../lib/lpc17xx_gpdma.c \
../lib/lpc17xx_gpio.c \
../lib/lpc17xx_i2c.c \
../lib/lpc17xx_i2s.c \
../lib/lpc17xx_iap.c \
../lib/lpc17xx_libcfg_default.c \
../lib/lpc17xx_mcpwm.c \
../lib/lpc17xx_nvic.c \
../lib/lpc17xx_pinsel.c \
../lib/lpc17xx_pwm.c \
../lib/lpc17xx_qei.c \
../lib/lpc17xx_rit.c \
../lib/lpc17xx_rtc.c \
../lib/lpc17xx_spi.c \
../lib/lpc17xx_ssp.c \
../lib/lpc17xx_systick.c \
../lib/lpc17xx_timer.c \
../lib/lpc17xx_uart.c \
../lib/lpc17xx_wdt.c 

OBJS += \
./lib/LPC1768_fnd.o \
./lib/LPC1768_motor.o \
./lib/LPC1768_utility.o \
./lib/debug_frmwrk.o \
./lib/lpc17xx_adc.o \
./lib/lpc17xx_can.o \
./lib/lpc17xx_clkpwr.o \
./lib/lpc17xx_dac.o \
./lib/lpc17xx_emac.o \
./lib/lpc17xx_exti.o \
./lib/lpc17xx_gpdma.o \
./lib/lpc17xx_gpio.o \
./lib/lpc17xx_i2c.o \
./lib/lpc17xx_i2s.o \
./lib/lpc17xx_iap.o \
./lib/lpc17xx_libcfg_default.o \
./lib/lpc17xx_mcpwm.o \
./lib/lpc17xx_nvic.o \
./lib/lpc17xx_pinsel.o \
./lib/lpc17xx_pwm.o \
./lib/lpc17xx_qei.o \
./lib/lpc17xx_rit.o \
./lib/lpc17xx_rtc.o \
./lib/lpc17xx_spi.o \
./lib/lpc17xx_ssp.o \
./lib/lpc17xx_systick.o \
./lib/lpc17xx_timer.o \
./lib/lpc17xx_uart.o \
./lib/lpc17xx_wdt.o 

C_DEPS += \
./lib/LPC1768_fnd.d \
./lib/LPC1768_motor.d \
./lib/LPC1768_utility.d \
./lib/debug_frmwrk.d \
./lib/lpc17xx_adc.d \
./lib/lpc17xx_can.d \
./lib/lpc17xx_clkpwr.d \
./lib/lpc17xx_dac.d \
./lib/lpc17xx_emac.d \
./lib/lpc17xx_exti.d \
./lib/lpc17xx_gpdma.d \
./lib/lpc17xx_gpio.d \
./lib/lpc17xx_i2c.d \
./lib/lpc17xx_i2s.d \
./lib/lpc17xx_iap.d \
./lib/lpc17xx_libcfg_default.d \
./lib/lpc17xx_mcpwm.d \
./lib/lpc17xx_nvic.d \
./lib/lpc17xx_pinsel.d \
./lib/lpc17xx_pwm.d \
./lib/lpc17xx_qei.d \
./lib/lpc17xx_rit.d \
./lib/lpc17xx_rtc.d \
./lib/lpc17xx_spi.d \
./lib/lpc17xx_ssp.d \
./lib/lpc17xx_systick.d \
./lib/lpc17xx_timer.d \
./lib/lpc17xx_uart.d \
./lib/lpc17xx_wdt.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o: ../lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -DPACK_STRUCT_END=__attribute\(\(packed\)\) -DALIGN_STRUCT_END=__attribute\(\(aligned\(4\)\)\) -D__CODE_RED -D__REDLIB__ -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/FreeRTOS/include" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/LPCUSB" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/webserver" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/Common Demo Tasks/include" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/src/FreeRTOS/portable/GCC/ARM_CM3" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/inc" -I"/Users/jhrunning/Documents/freertos-code-r2664-trunk/FreeRTOS/Demo/CORTEX_LPC1768_GCC_RedSuite/inc" -I"/Users/jhrunning/Documents/MCUXpressoIDE_10.3.1/workspace/CMSIS_CORE_LPC17xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -Wextra -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


