################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Class/Composite/Src/usbd_composite.c 

OBJS += \
./Middlewares/Class/Composite/Src/usbd_composite.o 

C_DEPS += \
./Middlewares/Class/Composite/Src/usbd_composite.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Class/Composite/Src/%.o Middlewares/Class/Composite/Src/%.su Middlewares/Class/Composite/Src/%.cyclo: ../Middlewares/Class/Composite/Src/%.c Middlewares/Class/Composite/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/User/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/STM32F4xx_HAL_Driver/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/USB_LIB/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/CDC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/Composite/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/UVC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Class-2f-Composite-2f-Src

clean-Middlewares-2f-Class-2f-Composite-2f-Src:
	-$(RM) ./Middlewares/Class/Composite/Src/usbd_composite.cyclo ./Middlewares/Class/Composite/Src/usbd_composite.d ./Middlewares/Class/Composite/Src/usbd_composite.o ./Middlewares/Class/Composite/Src/usbd_composite.su

.PHONY: clean-Middlewares-2f-Class-2f-Composite-2f-Src

