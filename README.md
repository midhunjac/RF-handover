# RF-Wireless-Sensors

Getting started with STM32

Download STM32CubeProgrammer and STM32CubeIDE. Also download the STM drivers for Windows.
Use the FTDI cable to flash images.
FTDI cable to board connections.
To flash the image, the MCU must be in bootloader mode. To put it in bootloader mode, connect FTDI cable according to the schematics as shown below.

Red         ----        Power
Black       ----        Ground
Yellow      ----        TX
Orange      ----        RX
Red         ----        Boot0

Boot0 must be pulled high. Additionally, press down the RESET button while plugging in the FTDI cable. Once plugged in, release the RESET button. AT this point, the device is in bootloader mode and the MCU should not be advertising.
In the STM32CubeProgrammer, change connect mode to UART. Choose the new COM port from the dropdown. Keep everything else at default.If everything is set properly, the programmer should be able to connect to the device properly.
On the left-hand menu, go to 'Erasing and Programming' section. Customize the options as needed. Set the start address as 0x8000000. Choose the binary file from browser. Start programming. The new file should be transferred and the device will be disconnected. Disconnect the BOOT0 pin from power and power the device.