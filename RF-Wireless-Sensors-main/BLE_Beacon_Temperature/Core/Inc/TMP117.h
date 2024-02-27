/*
 * tmp117.h
 *
 *  Created on: Aug 5, 2023
 *      Author: MATT.C
 */

#ifndef INC_TMP117_H_
#define INC_TMP117_H_

#include "main.h"

/*
Check the model of your MCU model
*/
#ifndef     __STM32WBxx_HAL_I2C_H
#define     __STM32WBxx_HAL_I2C_H
#endif

#define     TMP117_DeviceID1 0x48<<1    //	GND
#define     TMP117_DeviceID2 0x49<<1    //	Vcc
#define     TMP117_DeviceID3 0x4A<<1    //	SDA
#define     TMP117_DeviceID4 0x4B<<1    //	SCL


/*
Pointer Registers
*/
#define     TMP117_TemperatureRegister     0x00
#define     TMP117_ConfigurationRegister   0x01
#define     TMP117_TemperatureHighLimit    0x02
#define     TMP117_TemperatureLowLimit     0x03

#define     TMP117_EEPROM_Uclock           0x04
#define     TMP117_EEPROM1                 0x05
#define     TMP117_EEPROM2                 0x06
#define     TMP117_EEPROM3                 0x08

#define     TMP117_Temperature_Offset      0x07
#define     TMP117_ID_Register             0x0F

/*
   @Brief         Get temperature basically
   @Description   Function gives to us ambient temperature
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  Float
 */
uint16_t TMP117_get_Temperature             (I2C_HandleTypeDef i2c, uint8_t device_ID);

/*
   @Brief         Get Configuration
   @Description   Get Configuration Register Value
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t TMP117_get_Configuration     (I2C_HandleTypeDef i2c, uint8_t device_ID);

/*
   @Brief         Set Configuration
   @Description   Set Configuration Register for Features
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
                  uint8_t first     ->  [15:8]
                  uint8_t second    ->  [7:0]
   @Return value  void
 */
void TMP117_set_Configuration            (I2C_HandleTypeDef i2c,uint8_t first,uint8_t second, uint8_t device_ID);

/*
   @Brief         Set HighLimit
   @Description   Set HighLimit for Alert
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
                  uint8_t first     ->  [15:8]
                  uint8_t second    ->  [7:0]
   @Return value  void
 */
void TMP117_set_HighLimit                (I2C_HandleTypeDef i2c,uint8_t first,uint8_t second, uint8_t device_ID);

/*
   @Brief         Get Highlimit
   @Description   Get Highlimit Register Value
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t TMP117_get_HighLimit         (I2C_HandleTypeDef i2c, uint8_t device_ID);

/*
   @Brief         Set LowLimit
   @Description   Set LowLimit for Alert
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
                  uint8_t first     ->  [15:8]
                  uint8_t second    ->  [7:0]
   @Return value  void
 */
void TMP117_set_LowLimit                 (I2C_HandleTypeDef i2c,uint8_t first,uint8_t second, uint8_t device_ID);

/*
   @Brief         Get LowLimit
   @Description   Get Lowlimit Register Value
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t TMP117_get_LowLimit          (I2C_HandleTypeDef i2c, uint8_t device_ID);

/*
   @Brief         Get EEPROM Unlock Register Value
   @Description   Check EEPROM for Unlock/Lock
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t TMP117_get_EEPROM_Unclock    (I2C_HandleTypeDef i2c, uint8_t device_ID);

/*
   @Brief         Set EEPROM Unlock Register Value
   @Description   Active/Inactive for EEPROM read/write situation
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
                  uint8_t first     ->  [15:8]
                  uint8_t second    ->  [7:0]
   @Return value  void
 */
void TMP117_set_EEPROM_Unlock            (I2C_HandleTypeDef i2c,uint8_t first,uint8_t second, uint8_t device_ID);

/*
   @Brief
   @Description
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
                  uint8_t first     ->  [15:8]
                  uint8_t second    ->  [7:0]
   @Return value  void
 */
void TMP117_set_EEPROM1                  (I2C_HandleTypeDef i2c,uint8_t first,uint8_t second, uint8_t device_ID);

/*
   @Brief
   @Description
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t TMP117_get_EEPROM1           (I2C_HandleTypeDef i2c, uint8_t device_ID);

/*
   @Brief
   @Description
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
                  uint8_t first     ->  [15:8]
                  uint8_t second    ->  [7:0]
   @Return value  void
 */
void TMP117_set_EEPROM2                  (I2C_HandleTypeDef i2c,uint8_t first,uint8_t second, uint8_t device_ID);

/*
   @Brief
   @Description
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t TMP117_get_EEPROM2           (I2C_HandleTypeDef i2c, uint8_t device_ID);

/*
   @Brief
   @Description
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
                  uint8_t first     ->  [15:8]
                  uint8_t second    ->  [7:0]
   @Return value  void
 */
void TMP117_set_EEPROM3                  (I2C_HandleTypeDef i2c,uint8_t first,uint8_t second, uint8_t device_ID);

/*
   @Brief         Get EEPROM3 Value
   @Description
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t TMP117_get_EEPROM3           (I2C_HandleTypeDef i2c, uint8_t device_ID);

/*
   @Brief         Set Temperature Offset Value
   @Description   Set Temperature Offset Value for Calibrating
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
                  uint8_t first     ->  [15:8]
                  uint8_t second    ->  [7:0]
   @Return value  void
 */
void TMP117_set_Temperature_Offset       (I2C_HandleTypeDef i2c,uint8_t first,uint8_t second, uint8_t device_ID);

/*
   @Brief         Get Temperature Offset Value
   @Description   Get Temperature Offset Value for Calibrating
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t TMP117_get_Temperature_Offset (I2C_HandleTypeDef i2c, uint8_t device_ID);

/*
   @Brief         Get ID Register
   @Description   Check Device ID for Error Handler
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t TMP117_get_ID_Register       (I2C_HandleTypeDef i2c, uint8_t device_ID);


#endif /* INC_TMP117_H_ */
