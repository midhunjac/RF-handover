################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/mjm17h/Documents/RF-Wireless-Sensors-main/STM32Cube_FW_WB_V1.17.0/Drivers/BSP/NUCLEO-WB15CC/nucleo_wb15cc.c 

OBJS += \
./Drivers/BSP/NUCLEO-WB15CC/nucleo_wb15cc.o 

C_DEPS += \
./Drivers/BSP/NUCLEO-WB15CC/nucleo_wb15cc.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/NUCLEO-WB15CC/nucleo_wb15cc.o: C:/Users/mjm17h/Documents/RF-Wireless-Sensors-main/STM32Cube_FW_WB_V1.17.0/Drivers/BSP/NUCLEO-WB15CC/nucleo_wb15cc.c Drivers/BSP/NUCLEO-WB15CC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_STM32WBXX_NUCLEO -DUSE_HAL_DRIVER -DSTM32WB15xx -c -I../../Core/Inc -I../../STM32_WPAN/App -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/lhci -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/vcp -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/NUCLEO-WB15CC -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-NUCLEO-2d-WB15CC

clean-Drivers-2f-BSP-2f-NUCLEO-2d-WB15CC:
	-$(RM) ./Drivers/BSP/NUCLEO-WB15CC/nucleo_wb15cc.cyclo ./Drivers/BSP/NUCLEO-WB15CC/nucleo_wb15cc.d ./Drivers/BSP/NUCLEO-WB15CC/nucleo_wb15cc.o ./Drivers/BSP/NUCLEO-WB15CC/nucleo_wb15cc.su

.PHONY: clean-Drivers-2f-BSP-2f-NUCLEO-2d-WB15CC

