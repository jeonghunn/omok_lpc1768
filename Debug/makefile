################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/webserver/subdir.mk
-include src/TCP/subdir.mk
-include src/LPCUSB/subdir.mk
-include src/FreeRTOS/portable/MemMang/subdir.mk
-include src/FreeRTOS/portable/GCC/ARM_CM3/subdir.mk
-include src/FreeRTOS/subdir.mk
-include src/Common\ Demo\ Tasks/subdir.mk
-include src/subdir.mk
-include lib/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: RTOSDemo_RDB1768.axf

# Tool invocations
RTOSDemo_RDB1768.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker --gc-sections -Xlinker -Map=RTOSDemo_RDB1768.map -mcpu=cortex-m3 -mthumb -T RTOSDemo_RDB1768.ld -o "RTOSDemo_RDB1768.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) RTOSDemo_RDB1768.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size RTOSDemo_RDB1768.axf; # arm-none-eabi-objdump -h -S RTOSDemo_RDB1768.axf >RTOSDemo_RDB1768.lss
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
