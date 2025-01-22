################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Src/camera.c \
../User/Src/dcmi.c \
../User/Src/err.c \
../User/Src/gpio.c \
../User/Src/main.c \
../User/Src/sdram.c \
../User/Src/stm32f4xx_hal_msp.c \
../User/Src/stm32f4xx_it.c \
../User/Src/syscalls.c \
../User/Src/sysmem.c \
../User/Src/system_stm32f4xx.c \
../User/Src/uart.c \
../User/Src/usb_device.c 

OBJS += \
./User/Src/camera.o \
./User/Src/dcmi.o \
./User/Src/err.o \
./User/Src/gpio.o \
./User/Src/main.o \
./User/Src/sdram.o \
./User/Src/stm32f4xx_hal_msp.o \
./User/Src/stm32f4xx_it.o \
./User/Src/syscalls.o \
./User/Src/sysmem.o \
./User/Src/system_stm32f4xx.o \
./User/Src/uart.o \
./User/Src/usb_device.o 

C_DEPS += \
./User/Src/camera.d \
./User/Src/dcmi.d \
./User/Src/err.d \
./User/Src/gpio.d \
./User/Src/main.d \
./User/Src/sdram.d \
./User/Src/stm32f4xx_hal_msp.d \
./User/Src/stm32f4xx_it.d \
./User/Src/syscalls.d \
./User/Src/sysmem.d \
./User/Src/system_stm32f4xx.d \
./User/Src/uart.d \
./User/Src/usb_device.d 


# Each subdirectory must supply rules for building sources it contributes
User/Src/%.o User/Src/%.su User/Src/%.cyclo: ../User/Src/%.c User/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/User/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/STM32F4xx_HAL_Driver/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/USB_LIB/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/CDC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/Composite/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/UVC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User-2f-Src

clean-User-2f-Src:
	-$(RM) ./User/Src/camera.cyclo ./User/Src/camera.d ./User/Src/camera.o ./User/Src/camera.su ./User/Src/dcmi.cyclo ./User/Src/dcmi.d ./User/Src/dcmi.o ./User/Src/dcmi.su ./User/Src/err.cyclo ./User/Src/err.d ./User/Src/err.o ./User/Src/err.su ./User/Src/gpio.cyclo ./User/Src/gpio.d ./User/Src/gpio.o ./User/Src/gpio.su ./User/Src/main.cyclo ./User/Src/main.d ./User/Src/main.o ./User/Src/main.su ./User/Src/sdram.cyclo ./User/Src/sdram.d ./User/Src/sdram.o ./User/Src/sdram.su ./User/Src/stm32f4xx_hal_msp.cyclo ./User/Src/stm32f4xx_hal_msp.d ./User/Src/stm32f4xx_hal_msp.o ./User/Src/stm32f4xx_hal_msp.su ./User/Src/stm32f4xx_it.cyclo ./User/Src/stm32f4xx_it.d ./User/Src/stm32f4xx_it.o ./User/Src/stm32f4xx_it.su ./User/Src/syscalls.cyclo ./User/Src/syscalls.d ./User/Src/syscalls.o ./User/Src/syscalls.su ./User/Src/sysmem.cyclo ./User/Src/sysmem.d ./User/Src/sysmem.o ./User/Src/sysmem.su ./User/Src/system_stm32f4xx.cyclo ./User/Src/system_stm32f4xx.d ./User/Src/system_stm32f4xx.o ./User/Src/system_stm32f4xx.su ./User/Src/uart.cyclo ./User/Src/uart.d ./User/Src/uart.o ./User/Src/uart.su ./User/Src/usb_device.cyclo ./User/Src/usb_device.d ./User/Src/usb_device.o ./User/Src/usb_device.su

.PHONY: clean-User-2f-Src

