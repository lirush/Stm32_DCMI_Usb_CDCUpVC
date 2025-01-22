################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fmc.c 

OBJS += \
./Driver/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fmc.o 

C_DEPS += \
./Driver/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fmc.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/STM32F4xx_HAL_Driver/Inc/%.o Driver/STM32F4xx_HAL_Driver/Inc/%.su Driver/STM32F4xx_HAL_Driver/Inc/%.cyclo: ../Driver/STM32F4xx_HAL_Driver/Inc/%.c Driver/STM32F4xx_HAL_Driver/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32F429xx -DRELEASE -DUSE_HAL_DRIVER -c -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/STM32F4xx_HAL_Driver/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/User/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/USB_LIB/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/CDC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/Composite/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/UVC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-STM32F4xx_HAL_Driver-2f-Inc

clean-Driver-2f-STM32F4xx_HAL_Driver-2f-Inc:
	-$(RM) ./Driver/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fmc.cyclo ./Driver/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fmc.d ./Driver/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fmc.o ./Driver/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fmc.su

.PHONY: clean-Driver-2f-STM32F4xx_HAL_Driver-2f-Inc

