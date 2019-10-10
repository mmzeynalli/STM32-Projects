################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
016.\ ADC_Regular_Channel.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
016.\ ADC_Regular_Channel.list \


# All Target
all: 016.\ ADC_Regular_Channel.elf secondary-outputs

# Tool invocations
016.\ ADC_Regular_Channel.elf: $(OBJS) $(USER_OBJS) D:\OneDrive\ -\ ADA\ University\Projects\STM32\016.\ ADC_Regular_Channel\STM32F407VGTX_FLASH.ld
	arm-none-eabi-gcc -o "016. ADC_Regular_Channel.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\OneDrive - ADA University\Projects\STM32\016. ADC_Regular_Channel\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="016. ADC_Regular_Channel.map" -Wl,--gc-sections -static -u _printf_float --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

016.\ ADC_Regular_Channel.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "016. ADC_Regular_Channel.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
