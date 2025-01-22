################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_LIB/Inc/usb_dcd_int.c 

OBJS += \
./USB_LIB/Inc/usb_dcd_int.o 

C_DEPS += \
./USB_LIB/Inc/usb_dcd_int.d 


# Each subdirectory must supply rules for building sources it contributes
USB_LIB/Inc/%.o USB_LIB/Inc/%.su USB_LIB/Inc/%.cyclo: ../USB_LIB/Inc/%.c USB_LIB/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32F429xx -DRELEASE -DUSE_HAL_DRIVER -c -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/STM32F4xx_HAL_Driver/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/User/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/USB_LIB/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/CDC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/Composite/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/UVC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-USB_LIB-2f-Inc

clean-USB_LIB-2f-Inc:
	-$(RM) ./USB_LIB/Inc/usb_dcd_int.cyclo ./USB_LIB/Inc/usb_dcd_int.d ./USB_LIB/Inc/usb_dcd_int.o ./USB_LIB/Inc/usb_dcd_int.su

.PHONY: clean-USB_LIB-2f-Inc

