################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/Src/subdir.mk
-include USB_LIB/Src/subdir.mk
-include USB_LIB/Inc/subdir.mk
-include Startup/subdir.mk
-include Middlewares/Class/UVC/Src/subdir.mk
-include Middlewares/Class/Composite/Src/subdir.mk
-include Middlewares/Class/CDC/Src/subdir.mk
-include Driver/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Driver/STM32F4xx_HAL_Driver/Inc/subdir.mk
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


BUILD_ARTIFACT_NAME := stm32f429_kpvc_m
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
stm32f429_kpvc_m.elf \

MAP_FILES += \
stm32f429_kpvc_m.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
stm32f429_kpvc_m.list \


# All Target
all: main-build

# Main-build Target
main-build: stm32f429_kpvc_m.elf secondary-outputs

# Tool invocations
stm32f429_kpvc_m.elf stm32f429_kpvc_m.map: $(OBJS) $(USER_OBJS) D:\mlh\projects\07_kpvc_m_new\stm32f429_kpvc_m\STM32F429IITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "stm32f429_kpvc_m.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\mlh\projects\07_kpvc_m_new\stm32f429_kpvc_m\STM32F429IITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="stm32f429_kpvc_m.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

stm32f429_kpvc_m.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "stm32f429_kpvc_m.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout stm32f429_kpvc_m.elf stm32f429_kpvc_m.list stm32f429_kpvc_m.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
