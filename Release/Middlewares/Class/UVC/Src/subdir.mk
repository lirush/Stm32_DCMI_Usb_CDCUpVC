################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Class/UVC/Src/usbd_uvc.c 

OBJS += \
./Middlewares/Class/UVC/Src/usbd_uvc.o 

C_DEPS += \
./Middlewares/Class/UVC/Src/usbd_uvc.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Class/UVC/Src/%.o Middlewares/Class/UVC/Src/%.su Middlewares/Class/UVC/Src/%.cyclo: ../Middlewares/Class/UVC/Src/%.c Middlewares/Class/UVC/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32F429xx -DRELEASE -DUSE_HAL_DRIVER -c -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/STM32F4xx_HAL_Driver/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/User/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/USB_LIB/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/CDC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/Composite/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/UVC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Class-2f-UVC-2f-Src

clean-Middlewares-2f-Class-2f-UVC-2f-Src:
	-$(RM) ./Middlewares/Class/UVC/Src/usbd_uvc.cyclo ./Middlewares/Class/UVC/Src/usbd_uvc.d ./Middlewares/Class/UVC/Src/usbd_uvc.o ./Middlewares/Class/UVC/Src/usbd_uvc.su

.PHONY: clean-Middlewares-2f-Class-2f-UVC-2f-Src

