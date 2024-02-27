#include "main.h"


#ifndef      _LIS2DW12_H_
#define      _LIS2DW12_H_

/*
Check the model of your MCU model
*/
#ifndef     __STM32WBxx_HAL_I2C_H
#define     __STM32WBxx_HAL_I2C_H
#endif

/* I2C Address Pin */
#define     LIS2DW12_DeviceID0 0x30     //	GND
#define     LIS2DW12_DeviceID1 0x32    //	Vdd (Default)

/*
Pointer Registers
*/
#define     LIS2DW12_TEMPERATURE_OUTPUT_LOW    0x0D
#define     LIS2DW12_TEMPERATURE_OUTPUT_HIGH   0x0E
#define     LIS2DW12_WHO_AM_I				   0x0F

#define     LIS2DW12_CTRL1					   0x20
#define     LIS2DW12_CTRL2					   0x21
#define     LIS2DW12_CTRL3					   0x22
#define     LIS2DW12_CTRL4_INT1				   0x23
#define     LIS2DW12_CTRL5_INT2				   0x24
#define     LIS2DW12_CTRL6					   0x25
#define     LIS2DW12_CTRL7					   0x3F
#define		LIS2DW12_CTRL4_INT1_PAD_CTRL	   0x23


#define     LIS2DW12_STATUS					   0x27

#define     LIS2DW12_OUT_X_LOW				   0x28
#define     LIS2DW12_OUT_X_HIGH				   0x29

#define     LIS2DW12_OUT_Y_LOW				   0x2A
#define     LIS2DW12_OUT_Y_HIGH				   0x2B

#define     LIS2DW12_OUT_Z_LOW				   0x2C
#define     LIS2DW12_OUT_Z_HIGH				   0x2D

#define     LIS2DW12_FIFO_CTRL				   0x2E
#define     LIS2DW12_FIFO_SAMPLES			   0x2F

#define     LIS2DW12_WAKE_UP_THS			   0x34
#define     LIS2DW12_WAKE_UP_DUR			   0x35
#define     LIS2DW12_FREE_FALL				   0x36
#define     LIS2DW12_STATUS_DUP				   0x37

/*
ODR Values
*/
#define		LIS2DW12_ODR_0Hz				   0x00
#define		LIS2DW12_ODR_1_6Hz				   0x01
#define		LIS2DW12_ODR_12_5Hz				   0x02
#define		LIS2DW12_ODR_25Hz				   0x03
#define		LIS2DW12_ODR_50Hz				   0x04
#define		LIS2DW12_ODR_100Hz				   0x05
#define		LIS2DW12_ODR_200Hz				   0x06
#define		LIS2DW12_ODR_400Hz				   0x07
#define		LIS2DW12_ODR_800Hz				   0x08
#define		LIS2DW12_ODR_1600Hz				   0x09

/*
Sensitivity Register Values
*/

#define LIS2DW12_Sensitivity_2g				   0x00
#define LIS2DW12_Sensitivity_4g				   0x01
#define LIS2DW12_Sensitivity_8g				   0x02
#define LIS2DW12_Sensitivity_16g			   0x03

/*
 * offset registers
 */

#define LIS2DW12_X_OFS_USR					   0X3C
#define LIS2DW12_Y_OFS_USR					   0X3D
#define LIS2DW12_Z_OFS_USR					   0X3E

/*
 * Sensitivity Scale Factors (unit g/LSB)
 */
#define LIS2DW12_scale_2g_LP1				   0.000976f	// Low Power 1 Mode
#define LIS2DW12_scale_2g					   0.000244f	// All other power modes

#define LIS2DW12_scale_4g_LP1				   0.001952f	// Low Power 1 Mode
#define LIS2DW12_scale_4g					   0.000488f	// All other power modes

#define LIS2DW12_scale_8g_LP1				   0.003904f	// Low Power 1 Mode
#define LIS2DW12_scale_8g					   0.000976f	// All other power modes

#define LIS2DW12_scale_16g_LP1				   0.007808f	// Low Power 1 Mode
#define LIS2DW12_scale_16g					   0.001952f	// All other power modes

/*
 * FIFO FMode Values
 */
#define LIS2DW12_FIFO_Bypass_Mode				   0x00		// Bypass Mode (FIFO off)
#define LIS2DW12_FIFO_FIFO_Mode					   0x01		// FIFO Mode
#define LIS2DW12_FIFO_Cont_to_FIFO_Mode			   0x00		// Continuous to FIFO Mode
#define LIS2DW12_FIFO_Bypass_to_FIFO_Mode		   0x00		// Bypass to FIFO Mode
#define LIS2DW12_FIFO_Cont_Mode					   0x06		// Continuous Mode
#define LIS2DW12_IF_ADD_INC						   0x02

/*
 * Interupt modes
 */

#define LIS2DW12_INT_FTH				   0x02


/*
 * Private Define
 */


/*
   @Brief         Custom Initialization
   @Description   Custom Parameters for Sensor
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  void
 */
void LIS2DW12_Initialization               (I2C_HandleTypeDef i2c);
void LIS2DW12_Set_ODR					   (I2C_HandleTypeDef i2c, uint8_t odr);
uint8_t LIS2DW12_Get_ODR				   (I2C_HandleTypeDef i2c);
void LIS2DW12_Set_Sensitivity			   (I2C_HandleTypeDef i2c, uint8_t sensitivity);
uint8_t LIS2DW12_Get_Sensitivity		   (I2C_HandleTypeDef i2c);
void LIS2DW12_Set_FIFO					   (I2C_HandleTypeDef i2c, uint8_t FMode);
uint8_t LIS2DW12_ReadID					   (I2C_HandleTypeDef i2c);
float LIS2DW12_ReadX					   (I2C_HandleTypeDef i2c);
float LIS2DW12_ReadY					   (I2C_HandleTypeDef i2c);
float LIS2DW12_ReadZ					   (I2C_HandleTypeDef i2c);
void LIS2DW12_Wait_for_Data				   (I2C_HandleTypeDef i2c);
void LIS2DW12_Self_Test					   (I2C_HandleTypeDef i2c);
void LIS2DW12_Set_Offset (I2C_HandleTypeDef i2c, uint8_t xoffset, uint8_t yoffset,uint8_t zoffset);
void LIS2DW12_Set_Int_Fth			   (I2C_HandleTypeDef i2c, uint8_t intMode);
void LIS2DW12_Set_FIFO_Threshold			   (I2C_HandleTypeDef i2c, uint8_t threshold);
void LIS2DW12_Offload_FIFO (I2C_HandleTypeDef i2c, float * data);
uint8_t LIS2DW12_Get_Reg(I2C_HandleTypeDef i2c, uint8_t regName);
void LIS2DW12_Reset_FIFO (I2C_HandleTypeDef i2c);
uint8_t LIS2DW12_Get_FIFO_SAMPLES (I2C_HandleTypeDef i2c);
uint8_t LIS2DW12_Get_FIFO_FTH (I2C_HandleTypeDef i2c);
void LIS2DW12_Get_FIFO_Z (I2C_HandleTypeDef i2c, float * z_array);
uint8_t LIS2DW12_Get_STATUS (I2C_HandleTypeDef i2c);
void LIS2DW12_ReadXYZ (I2C_HandleTypeDef i2c, float * destination);
#endif



















