################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_LIB/Src/usb_bsp.c \
../USB_LIB/Src/usb_core.c \
../USB_LIB/Src/usb_dcd.c \
../USB_LIB/Src/usbd_cdc_if.c \
../USB_LIB/Src/usbd_core.c \
../USB_LIB/Src/usbd_desc.c \
../USB_LIB/Src/usbd_ioreq.c \
../USB_LIB/Src/usbd_req.c \
../USB_LIB/Src/usbd_usr.c 

OBJS += \
./USB_LIB/Src/usb_bsp.o \
./USB_LIB/Src/usb_core.o \
./USB_LIB/Src/usb_dcd.o \
./USB_LIB/Src/usbd_cdc_if.o \
./USB_LIB/Src/usbd_core.o \
./USB_LIB/Src/usbd_desc.o \
./USB_LIB/Src/usbd_ioreq.o \
./USB_LIB/Src/usbd_req.o \
./USB_LIB/Src/usbd_usr.o 

C_DEPS += \
./USB_LIB/Src/usb_bsp.d \
./USB_LIB/Src/usb_core.d \
./USB_LIB/Src/usb_dcd.d \
./USB_LIB/Src/usbd_cdc_if.d \
./USB_LIB/Src/usbd_core.d \
./USB_LIB/Src/usbd_desc.d \
./USB_LIB/Src/usbd_ioreq.d \
./USB_LIB/Src/usbd_req.d \
./USB_LIB/Src/usbd_usr.d 


# Each subdirectory must supply rules for building sources it contributes
USB_LIB/Src/%.o USB_LIB/Src/%.su USB_LIB/Src/%.cyclo: ../USB_LIB/Src/%.c USB_LIB/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32F429xx -DRELEASE -DUSE_HAL_DRIVER -c -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/STM32F4xx_HAL_Driver/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/User/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/USB_LIB/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/CDC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/Composite/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/UVC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-USB_LIB-2f-Src

clean-USB_LIB-2f-Src:
	-$(RM) ./USB_LIB/Src/usb_bsp.cyclo ./USB_LIB/Src/usb_bsp.d ./USB_LIB/Src/usb_bsp.o ./USB_LIB/Src/usb_bsp.su ./USB_LIB/Src/usb_core.cyclo ./USB_LIB/Src/usb_core.d ./USB_LIB/Src/usb_core.o ./USB_LIB/Src/usb_core.su ./USB_LIB/Src/usb_dcd.cyclo ./USB_LIB/Src/usb_dcd.d ./USB_LIB/Src/usb_dcd.o ./USB_LIB/Src/usb_dcd.su ./USB_LIB/Src/usbd_cdc_if.cyclo ./USB_LIB/Src/usbd_cdc_if.d ./USB_LIB/Src/usbd_cdc_if.o ./USB_LIB/Src/usbd_cdc_if.su ./USB_LIB/Src/usbd_core.cyclo ./USB_LIB/Src/usbd_core.d ./USB_LIB/Src/usbd_core.o ./USB_LIB/Src/usbd_core.su ./USB_LIB/Src/usbd_desc.cyclo ./USB_LIB/Src/usbd_desc.d ./USB_LIB/Src/usbd_desc.o ./USB_LIB/Src/usbd_desc.su ./USB_LIB/Src/usbd_ioreq.cyclo ./USB_LIB/Src/usbd_ioreq.d ./USB_LIB/Src/usbd_ioreq.o ./USB_LIB/Src/usbd_ioreq.su ./USB_LIB/Src/usbd_req.cyclo ./USB_LIB/Src/usbd_req.d ./USB_LIB/Src/usbd_req.o ./USB_LIB/Src/usbd_req.su ./USB_LIB/Src/usbd_usr.cyclo ./USB_LIB/Src/usbd_usr.d ./USB_LIB/Src/usbd_usr.o ./USB_LIB/Src/usbd_usr.su

.PHONY: clean-USB_LIB-2f-Src

