################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32WBxx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/NUCLEO-WB15CC/subdir.mk
-include Application/User/subdir.mk
-include Application/Startup/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := ADC_SingleConversion_TriggerTimer_DMA
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ADC_SingleConversion_TriggerTimer_DMA.elf \

MAP_FILES += \
ADC_SingleConversion_TriggerTimer_DMA.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ADC_SingleConversion_TriggerTimer_DMA.list \


# All Target
all: main-build

# Main-build Target
main-build: ADC_SingleConversion_TriggerTimer_DMA.elf secondary-outputs

# Tool invocations
ADC_SingleConversion_TriggerTimer_DMA.elf ADC_SingleConversion_TriggerTimer_DMA.map: $(OBJS) $(USER_OBJS) C:\Users\mjm17h\Documents\RF-Wireless-Sensors-main\STM32Cube_FW_WB_V1.17.0\Projects\NUCLEO-WB15CC\Examples\ADC\ADC_SingleConversion_TriggerTimer_DMA\STM32CubeIDE\STM32WB15CCUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ADC_SingleConversion_TriggerTimer_DMA.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\mjm17h\Documents\RF-Wireless-Sensors-main\STM32Cube_FW_WB_V1.17.0\Projects\NUCLEO-WB15CC\Examples\ADC\ADC_SingleConversion_TriggerTimer_DMA\STM32CubeIDE\STM32WB15CCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ADC_SingleConversion_TriggerTimer_DMA.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ADC_SingleConversion_TriggerTimer_DMA.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ADC_SingleConversion_TriggerTimer_DMA.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ADC_SingleConversion_TriggerTimer_DMA.elf ADC_SingleConversion_TriggerTimer_DMA.list ADC_SingleConversion_TriggerTimer_DMA.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
