################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
../Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c 

OBJS += \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.o 

C_DEPS += \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.d \
./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/STM32F4xx_HAL_Driver/Src/%.o Driver/STM32F4xx_HAL_Driver/Src/%.su Driver/STM32F4xx_HAL_Driver/Src/%.cyclo: ../Driver/STM32F4xx_HAL_Driver/Src/%.c Driver/STM32F4xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/User/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/STM32F4xx_HAL_Driver/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/USB_LIB/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/CDC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/Composite/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Middlewares/Class/UVC/Inc" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/mlh/projects/07_kpvc_m_new/stm32f429_kpvc_m/Driver/CMSIS/Include" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-STM32F4xx_HAL_Driver-2f-Src

clean-Driver-2f-STM32F4xx_HAL_Driver-2f-Src:
	-$(RM) ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.su ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.cyclo ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.d ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.o ./Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.su

.PHONY: clean-Driver-2f-STM32F4xx_HAL_Driver-2f-Src

