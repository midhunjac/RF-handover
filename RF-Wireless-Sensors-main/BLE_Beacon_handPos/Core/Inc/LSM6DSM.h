#include "main.h"

#ifndef      _LSM6DSM_H_
#define      _LSM6DSM_H_

/*
Check the model of your MCU model
*/
#ifndef     __STM32WBxx_HAL_I2C_H
#define     __STM32WBxx_HAL_I2C_H
#endif

/* I2C Address Pin */
#define     LSM6DSM_DeviceID0 0xD4     //	GND (Default), 0x6B << 1
#define     LDSM6DSM_DeviceID1 0xD6    //	Vdd, 0x6A << 1

/*
Pointer Registers
*/
#define     LSM6DSM_FUNC_CFG_ACCESS			    0x01

#define     LSM6DSM_SENSOR_SYNC_TIME_FRAME		0x04
#define     LSM6DSM_SENSOR_SYNC_RES_RATIO  	 	0x05

#define     LSM6DSM_FIFO_CTRL1					0x06
#define     LSM6DSM_FIFO_CTRL2					0x07
#define     LSM6DSM_FIFO_CTRL3					0x08
#define     LSM6DSM_FIFO_CTRL4					0x09
#define     LSM6DSM_FIFO_CTRL5					0x0A

#define     LSM6DSM_DRDY_PULSE_CFG				0x0B

#define     LSM6DSM_INT1_CTRL					0x0D
#define     LSM6DSM_INT2_CTRL					0x0E

#define     LSM6DSM_WHO_AM_I					0x0F

#define     LSM6DSM_CTRL1_XL					0x10
#define     LSM6DSM_CTRL2_G						0x11
#define     LSM6DSM_CTRL3_C						0x12
#define     LSM6DSM_CTRL4_C						0x13
#define     LSM6DSM_CTRL5_C						0x14
#define     LSM6DSM_CTRL6_C						0x15
#define     LSM6DSM_CTRL7_G						0x16
#define     LSM6DSM_CTRL8_XL					0x17
#define     LSM6DSM_CTRL9_XL					0x18
#define     LSM6DSM_CTRL10_C					0x19

#define     LSM6DSM_MASTER_CONFIG				0x1A
#define     LSM6DSM_WAKE_UP_SRC					0x1B
#define     LSM6DSM_TAP_SRC						0x1C
#define     LSM6DSM_D6D_SRC						0x1D
#define     LSM6DSM_STATUS_REG					0x1E

#define     LSM6DSM_OUT_TEMP_L					0x20
#define     LSM6DSM_OUT_TEMP_H					0x21

#define     LSM6DSM_OUTX_L_G					0x22
#define     LSM6DSM_OUTX_H_G					0x23
#define     LSM6DSM_OUTY_L_G					0x24
#define     LSM6DSM_OUTY_H_G					0x25
#define     LSM6DSM_OUTZ_L_G					0x26
#define     LSM6DSM_OUTZ_H_G					0x27

#define     LSM6DSM_OUTX_L_XL					0x28
#define     LSM6DSM_OUTX_H_XL					0x29
#define     LSM6DSM_OUTY_L_XL					0x2A
#define     LSM6DSM_OUTY_H_XL					0x2B
#define     LSM6DSM_OUTZ_L_XL					0x2C
#define     LSM6DSM_OUTZ_H_XL					0x2D

#define     LSM6DSM_SENSORHUB1_REG				0x2E
#define     LSM6DSM_SENSORHUB2_REG				0x2F
#define     LSM6DSM_SENSORHUB3_REG				0x30
#define     LSM6DSM_SENSORHUB4_REG				0x31
#define     LSM6DSM_SENSORHUB5_REG				0x32
#define     LSM6DSM_SENSORHUB6_REG				0x33
#define     LSM6DSM_SENSORHUB7_REG				0x34
#define     LSM6DSM_SENSORHUB8_REG				0x35
#define     LSM6DSM_SENSORHUB9_REG				0x36
#define     LSM6DSM_SENSORHUB10_REG				0x37
#define     LSM6DSM_SENSORHUB11_REG				0x38
#define     LSM6DSM_SENSORHUB12_REG				0x39

#define     LSM6DSM_FIFO_STATUS1				0x3A
#define     LSM6DSM_FIFO_STATUS2				0x3B
#define     LSM6DSM_FIFO_STATUS3				0x3C
#define     LSM6DSM_FIFO_STATUS4				0x3D
#define     LSM6DSM_FIFO_DATA_OUT_L				0x3E
#define     LSM6DSM_FIFO_DATA_OUT_H				0x3F

#define     LSM6DSM_TIMESTAMP0_REG				0x40
#define     LSM6DSM_TIMESTAMP1_REG				0x41
#define     LSM6DSM_TIMESTAMP2_REG				0x42

#define     LSM6DSM_STEP_TIMESTAMP_L			0x49
#define     LSM6DSM_STEP_TIMESTAMP_H			0x4A
#define     LSM6DSM_STEP_COUNTER_L				0x4B
#define     LSM6DSM_STEP_COUNTER_H				0x4C

#define     LSM6DSM_SENSORHUB13_REG				0x4D
#define     LSM6DSM_SENSORHUB14_REG				0x4E
#define     LSM6DSM_SENSORHUB15_REG				0x4F
#define     LSM6DSM_SENSORHUB16_REG				0x50
#define     LSM6DSM_SENSORHUB17_REG				0x51
#define     LSM6DSM_SENSORHUB18_REG				0x52

#define     LSM6DSM_FUNC_SRC1					0x53
#define     LSM6DSM_FUNC_SRC2					0x54
#define     LSM6DSM_WRIST_TILT_IA				0x55

#define     LSM6DSM_TAP_CFG						0x58
#define     LSM6DSM_TAP_THS_6D					0x59
#define     LSM6DSM_INT_DUR2					0x5A

#define LSM6DSM_WAKE_UP_THS               		0x5B
#define LSM6DSM_WAKE_UP_DUR               		0x5C
#define LSM6DSM_FREE_FALL                 		0x5D
#define LSM6DSM_MD1_CFG                   		0x5E
#define LSM6DSM_MD2_CFG                   		0x5F
#define LSM6DSM_MASTER_MODE_CODE          		0x60
#define LSM6DSM_SENS_SYNC_SPI_ERROR_CODE  		0x61
#define LSM6DSM_OUT_MAG_RAW_X_L           		0x66
#define LSM6DSM_OUT_MAG_RAW_X_H           		0x67
#define LSM6DSM_OUT_MAG_RAW_Y_L           		0x68
#define LSM6DSM_OUT_MAG_RAW_Y_H           		0x69
#define LSM6DSM_OUT_MAG_RAW_Z_L           		0x6A
#define LSM6DSM_OUT_MAG_RAW_Z_H           		0x6B
#define LSM6DSM_INT_OIS                   		0x6F
#define LSM6DSM_CTRL1_OIS                 		0x70
#define LSM6DSM_CTRL2_OIS                 		0x71
#define LSM6DSM_CTRL3_OIS                 		0x72
#define LSM6DSM_X_OFS_USR                 		0x73
#define LSM6DSM_Y_OFS_USR                 		0x74
#define LSM6DSM_Z_OFS_USR                 		0x75

//Sensitivity Bit Patterns
#define AFS_2G  0x00
#define AFS_4G  0x02
#define AFS_8G  0x03
#define AFS_16G 0x01

#define GFS_125DPS  0xFF
#define GFS_250DPS  0x00
#define GFS_500DPS  0x01
#define GFS_1000DPS 0x02
#define GFS_2000DPS 0x03

//ODR Bit Patterns
#define AODR_POWER_DOWN		0x00	// same for accel and gyro in normal mode
#define AODR_1_6Hz			0x0B
#define AODR_12_5Hz  		0x01
#define AODR_26Hz    		0x02
#define AODR_52Hz    		0x03
#define AODR_104Hz   		0x04
#define AODR_208Hz   		0x05
#define AODR_416Hz   		0x06
#define AODR_833Hz   		0x07
#define AODR_1660Hz  		0x08
#define AODR_3330Hz  		0x09
#define AODR_6660Hz  		0x0A

#define GODR_POWER_DOWN		0x00
#define GODR_12_5Hz  		0x01
#define GODR_26Hz    		0x02
#define GODR_52Hz    		0x03
#define GODR_104Hz   		0x04
#define GODR_208Hz   		0x05
#define GODR_416Hz   		0x06
#define GODR_833Hz   		0x07
#define GODR_1660Hz  		0x08
#define GODR_3330Hz  		0x09
#define GODR_6660Hz  		0x0A

// resolution for each Gyro Sensitivity. Unit: dps/LSB
# define LSM6DSM_SCALE_125DPS 	0.004375f
# define LSM6DSM_SCALE_250DPS 	0.00875f
# define LSM6DSM_SCALE_500DPS 	0.0175f
# define LSM6DSM_SCALE_1000DPS 	0.035f
# define LSM6DSM_SCALE_2000DPS 	0.075f

// FIFO Mode Bit Patterns
#define LSM6DSM_FIFO_MODE_BYPASS  					0x00
#define LSM6DSM_FIFO_MODE_FIFO  					0x01
#define LSM6DSM_FIFO_MODE_CONTINUOUS_TO_FIFO  		0x03
#define LSM6DSM_FIFO_MODE_BYPASS_TO_CONTINUOUS  	0x04
#define LSM6DSM_FIFO_MODE_CONTINUOUS  				0x06

// Gyro Sleep
#define LSM6DSM_SLEEP_DISABLE						0x00
#define LSM6DSM_SLEEP_ENABLE						0x01
/*
   @Brief         Custom Initialization
   @Description   Custom Parameters for Sensor
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Parameter     Ascale -> Accelerometer Sensitivity
   @Parameter     Gscale -> Gyroscope Sensitivity
   @Parameter     AODR -> Accelerometer Output Data Rate
   @Parameter     GODR -> Gyroscope Output Data Rate
   @Return value  void
 */
void LSM6DSM_init(I2C_HandleTypeDef i2c, uint8_t Ascale, uint8_t Gscale, uint8_t AODR, uint8_t GODR);

void LSM6DSM_start_gyro(I2C_HandleTypeDef i2c, uint8_t Gscale, uint8_t GODR);
void LSM6DSM_stop_gyro(I2C_HandleTypeDef i2c, uint8_t GODR);
void LSM6DSM_stop_acc(I2C_HandleTypeDef i2c, uint8_t AODR);

/*
   @Brief         Get Chip ID
   @Description   Read the permanent Address of the Chip
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint8_t
 */
uint8_t LSM6DSM_ReadID(I2C_HandleTypeDef i2c);

/*
   @Brief         Get Sensitivity of Accelerometer
   @Description   Check Sensitivity range of Accelerometer
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint8_t
 */
uint8_t LSM6DSM_getAscale(I2C_HandleTypeDef i2c);

/*
   @Brief         Get ODR of Accelerometer
   @Description   Check Output Data Rate of Accelerometer
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t LSM6DSM_getAODR(I2C_HandleTypeDef i2c);

/*
   @Brief         Set Sensitivity and ODR of Accelerometer
   @Description   Change Sensitivity range and Output Data Rate of Accelerometer
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Parameter     Ascale ->  Accelerometer Sensitivity
   @Parameter	  AODR   ->  Accelerometer Output Data Rate
   @Return value  void
 */
void LSM6DSM_setAinfo(I2C_HandleTypeDef i2c, uint8_t Ascale, uint8_t AODR);

/*
   @Brief         Get Sensitivity of Gyroscope
   @Description   Check Sensitivity range of Gyroscope
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t LSM6DSM_getGscale(I2C_HandleTypeDef i2c);

/*
   @Brief         Get ODR of Gyroscope
   @Description   Check Output Data Rate of Gyroscope
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t LSM6DSM_getGODR(I2C_HandleTypeDef i2c);

/*
   @Brief         Set Sensitivity and ODR of Gyroscope
   @Description   Change Sensitivity range and Output Data Rate of Gyroscope
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Parameter     Gscale ->  Gyroscope Sensitivity
   @Parameter	  GODR	 ->  Gyroscope Output Data Rate
   @Return value  void
 */
void LSM6DSM_setGinfo(I2C_HandleTypeDef i2c, uint8_t Gscale, uint8_t GODR);

/*
   @Brief         Reset LSM6DSM Chip
   @Description   Reset the chip registers
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  void
 */
void LSM6DSM_reset(I2C_HandleTypeDef i2c);

/*
   @Brief         Read Gyroscope ValuesGscale
   @Description   Test if Accelerometer and Gyroscope working correctly
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Parameter     destination ->  pointer to where to store values
   @Return value  void
 */
void LSM6DSM_readGyro(I2C_HandleTypeDef i2c, float * destination);

/*
   @Brief         Self Test the Accelerometer and Gyroscope
   @Description   Test if Accelerometer and Gyroscope working correctly
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  void
 */
void LSM6DSM_selfTest(I2C_HandleTypeDef i2c);

/*
   @Brief         Setup chip for use of INT1 flag
   @Description   Route Gyro Data Ready flag to INT1 Pad
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  void
 */
void LSM6DSM_setup_int1(I2C_HandleTypeDef i2c);

/*
   @Brief         Wait until next set of Gyro data is ready
   @Description   Check if INT2 is indicating data is ready
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  void
 */
void LSM6DSM_wait_for_Data(I2C_HandleTypeDef i2c);

uint8_t LSM6DSM_read_status(I2C_HandleTypeDef i2c);

#endif
