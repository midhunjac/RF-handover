################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/mjm17h/Documents/RF-Wireless-Sensors-main/STM32Cube_FW_WB_V1.17.0/Projects/NUCLEO-WB15CC/Applications/BLE/BLE_p2pClient/STM32_WPAN/App/app_ble.c \
C:/Users/mjm17h/Documents/RF-Wireless-Sensors-main/STM32Cube_FW_WB_V1.17.0/Projects/NUCLEO-WB15CC/Applications/BLE/BLE_p2pClient/STM32_WPAN/App/p2p_client_app.c 

OBJS += \
./Application/User/STM32_WPAN/App/app_ble.o \
./Application/User/STM32_WPAN/App/p2p_client_app.o 

C_DEPS += \
./Application/User/STM32_WPAN/App/app_ble.d \
./Application/User/STM32_WPAN/App/p2p_client_app.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/STM32_WPAN/App/app_ble.o: C:/Users/mjm17h/Documents/RF-Wireless-Sensors-main/STM32Cube_FW_WB_V1.17.0/Projects/NUCLEO-WB15CC/Applications/BLE/BLE_p2pClient/STM32_WPAN/App/app_ble.c Application/User/STM32_WPAN/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_STM32WBXX_NUCLEO -DUSE_HAL_DRIVER -DSTM32WB15xx -c -I../../Core/Inc -I../../STM32_WPAN/App -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/NUCLEO-WB15CC -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/STM32_WPAN/App/p2p_client_app.o: C:/Users/mjm17h/Documents/RF-Wireless-Sensors-main/STM32Cube_FW_WB_V1.17.0/Projects/NUCLEO-WB15CC/Applications/BLE/BLE_p2pClient/STM32_WPAN/App/p2p_client_app.c Application/User/STM32_WPAN/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_STM32WBXX_NUCLEO -DUSE_HAL_DRIVER -DSTM32WB15xx -c -I../../Core/Inc -I../../STM32_WPAN/App -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/NUCLEO-WB15CC -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-STM32_WPAN-2f-App

clean-Application-2f-User-2f-STM32_WPAN-2f-App:
	-$(RM) ./Application/User/STM32_WPAN/App/app_ble.cyclo ./Application/User/STM32_WPAN/App/app_ble.d ./Application/User/STM32_WPAN/App/app_ble.o ./Application/User/STM32_WPAN/App/app_ble.su ./Application/User/STM32_WPAN/App/p2p_client_app.cyclo ./Application/User/STM32_WPAN/App/p2p_client_app.d ./Application/User/STM32_WPAN/App/p2p_client_app.o ./Application/User/STM32_WPAN/App/p2p_client_app.su

.PHONY: clean-Application-2f-User-2f-STM32_WPAN-2f-App

