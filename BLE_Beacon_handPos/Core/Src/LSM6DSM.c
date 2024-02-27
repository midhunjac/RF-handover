#include "LSM6DSM.h"
#include <stdio.h>

uint8_t LSM6DSM_DeviceID = LSM6DSM_DeviceID0;

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
void LSM6DSM_init(I2C_HandleTypeDef i2c, uint8_t Ascale, uint8_t Gscale, uint8_t AODR, uint8_t GODR){

	uint8_t buf[3];

	// Control Register 1 Linear Acceleration Sensor //
	buf[0]  = LSM6DSM_CTRL1_XL;
	buf[1]  = (AODR << 4) | (Ascale << 2);			// Set Accelerometer data rate | Sensitivity
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);


	// Control Register 2 Angular Rate Sensor //
	buf[0]  = LSM6DSM_CTRL2_G;
	if(Gscale == GFS_125DPS){
		buf[1]  = (GODR << 4) | 0b10;				// Set Gyroscope data rate | Sensitivity is 125dps
	}else{
		buf[1]  = (GODR << 4) | (Gscale << 2);		// Set Gyroscope data rate | Sensitivity more than 125dps
	}
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);


	// Control Register 6 //
	uint8_t XL_HM_MODE = 0b1;						// Disable High performance mode for Accelerometer
	buf[0]  = LSM6DSM_CTRL6_C;
	buf[1]  = (XL_HM_MODE << 4);
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);


	// Control Register 7//
	uint8_t G_HM_MODE = 0b1;						// Disable High performance mode for gyroscope
	buf[0]  = LSM6DSM_CTRL7_G;
	buf[1]  = (G_HM_MODE << 7);
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);

	// INT2 pad Control Register //
//	uint8_t INT2_DRDY_G = 0b1;						// Enable Data Ready on INT2 pad
//	buf[0] = LSM6DSM_INT2_CTRL;
//	buf[1] = (INT2_DRDY_G << 1);
//	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);

	return;
}

void LSM6DSM_start_gyro(I2C_HandleTypeDef i2c, uint8_t Gscale, uint8_t GODR) {
	// Control Register 2 Angular Rate Sensor //
	uint8_t buf[2];
	buf[0]  = LSM6DSM_CTRL2_G;
	if(Gscale == GFS_125DPS){
			buf[1]  = (GODR << 4) | 0b10;				// Set Gyroscope data rate | Sensitivity is 125dps
		}else{
			buf[1]  = (GODR << 4) | (Gscale << 2);		// Set Gyroscope data rate | Sensitivity more than 125dps
		}
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);

	// Control Register 7//
	uint8_t G_HM_MODE = 0b1;						// Disable High performance mode for gyroscope
	buf[0]  = LSM6DSM_CTRL7_G;
	buf[1]  = (G_HM_MODE << 7);
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);

	return;
}

void LSM6DSM_stop_gyro(I2C_HandleTypeDef i2c, uint8_t GODR) {
	// Control Register 2 Angular Rate Sensor //
	uint8_t buf[2];
	buf[0]  = LSM6DSM_CTRL2_G;
	buf[1]  = (GODR << 4) | (0b01 << 2);					  // Set Gyroscope data rate
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);

	return;
}

void LSM6DSM_stop_acc(I2C_HandleTypeDef i2c, uint8_t AODR) {
	// Control Register 1 Linear Acceleration Sensor //
	uint8_t buf[2];
	buf[0]  = LSM6DSM_CTRL1_XL;
	buf[1]  = (AODR << 4);					// Set Accelerometer data rate
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);

	return;
}

/*
   @Brief         Get Chip ID
   @Description   Read the permanent Address of the Chip
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint8_t
 */
uint8_t LSM6DSM_ReadID(I2C_HandleTypeDef i2c){

	uint8_t buf;

	buf = LSM6DSM_WHO_AM_I;

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_Delay(1);

	return buf;
}

/*
   @Brief         Get Sensitivity of Accelerometer
   @Description   Check Sensitivity range of Accelerometer
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint8_t
 */
uint8_t LSM6DSM_getAscale(I2C_HandleTypeDef i2c){

	uint8_t buf;

	buf = LSM6DSM_CTRL1_XL;			// Read CTRL1_XL

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_Delay(1);

	uint8_t Ascale = (buf >> 2) % 4;	// Extract Full-scale sensitivity selection

	switch(Ascale){

		case AFS_2G  : return 2;
		case AFS_4G  : return 4;
		case AFS_8G  : return 8;
		case AFS_16G : return 16;

		default : return 0;
	}
}

/*
   @Brief         Get ODR of Accelerometer
   @Description   Check Output Data Rate of Accelerometer
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t LSM6DSM_getAODR(I2C_HandleTypeDef i2c){

	uint8_t buf;

	buf = LSM6DSM_CTRL1_XL;			// Read CTRL1_XL

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_Delay(1);

	uint8_t AODR = (buf >> 4);	// Extract ODR selection

	switch(AODR){

		case AODR_POWER_DOWN	: return 0;
		case AODR_1_6Hz 		: return 1;
		case AODR_12_5Hz  		: return 12;
		case AODR_26Hz  		: return 26;
		case AODR_52Hz 			: return 52;
		case AODR_104Hz 		: return 104;
		case AODR_208Hz 		: return 208;
		case AODR_416Hz 		: return 416;
		case AODR_833Hz 		: return 833;
		case AODR_1660Hz 		: return 1660;
		case AODR_3330Hz 		: return 3330;
		case AODR_6660Hz 		: return 6660;

		default: return 5;
	}
}

/*
   @Brief         Set Sensitivity and ODR of Accelerometer
   @Description   Change Sensitivity range and Output Data Rate of Accelerometer
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Parameter     Ascale ->  Accelerometer Sensitivity
   @Parameter	  AODR   ->  Accelerometer Output Data Rate
   @Return value  void
 */
void LSM6DSM_setAinfo(I2C_HandleTypeDef i2c, uint8_t Ascale, uint8_t AODR){

	uint8_t buf[2];

	buf[0]  = LSM6DSM_CTRL1_XL;
	buf[1]  = (AODR << 4) | (Ascale << 2);		// Set Accelerometer ODR and Sensitivity
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);
    HAL_Delay(1);

	return;
}

/*
   @Brief         Get Sensitivity of Gyroscope
   @Description   Check Sensitivity range of Gyroscope
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t LSM6DSM_getGscale(I2C_HandleTypeDef i2c){

	uint8_t buf = LSM6DSM_CTRL2_G;				// Read CTRL2_G
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&buf,1,100);

	uint8_t Gscale = (buf >> 1) % 8;	// Extract Full-scale sensitivity selection
	if((Gscale % 2)){					// Check for FS_125 bit
		return 125;
	}else{
		Gscale = Gscale >> 1;
	}

	switch(Gscale){
		case GFS_250DPS  : return 250;
		case GFS_500DPS  : return 500;
		case GFS_1000DPS : return 1000;
		case GFS_2000DPS : return 2000;
		default : return 0;
	}
}

/*
   @Brief         Get ODR of Gyroscope
   @Description   Check Output Data Rate of Gyroscope
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  uint16_t
 */
uint16_t LSM6DSM_getGODR(I2C_HandleTypeDef i2c){

	uint8_t buf;

	buf = LSM6DSM_CTRL2_G;			// Read CTRL2_G

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_Delay(1);


	uint8_t GODR = buf >> 4;	// Extract ODR selection

	switch(GODR){

		case GODR_POWER_DOWN	: return 0;
		case GODR_12_5Hz  		: return 12;
		case GODR_26Hz  		: return 26;
		case GODR_52Hz 			: return 52;
		case GODR_104Hz 		: return 104;
		case GODR_208Hz 		: return 208;
		case GODR_416Hz 		: return 416;
		case GODR_833Hz 		: return 833;
		case GODR_1660Hz 		: return 1660;
		case GODR_3330Hz 		: return 3330;
		case GODR_6660Hz 		: return 6660;

		default: return 5;
	}
}

/*
   @Brief         Set Sensitivity and ODR of Gyroscope
   @Description   Change Sensitivity range and Output Data Rate of Gyroscope
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Parameter     Gscale ->  Gyroscope Sensitivity
   @Parameter	  GODR	 ->  Gyroscope Output Data Rate
   @Return value  void
 */
void LSM6DSM_setGinfo(I2C_HandleTypeDef i2c, uint8_t Gscale, uint8_t GODR){

	uint8_t buf[2];

	buf[0]  = LSM6DSM_CTRL2_G;
	if(Gscale == GFS_125DPS){
		buf[1]  = (GODR << 4) | 0b10;		// Set Accelerometer ODR and Sensitivity
	}
	else{
		buf[1]  = (GODR << 4) | (Gscale << 2);		// Set Accelerometer ODR and Sensitivity
	}
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);
    HAL_Delay(1);

	return;
}

/*
   @Brief         Reset LSM6DSM Chip
   @Description   Reset the chip registers
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  void
 */
void LSM6DSM_reset(I2C_HandleTypeDef i2c){

	uint8_t buf[2];

	buf[0] = LSM6DSM_CTRL3_C;

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,1,100);	// Read CTRL3_C to preserve any other selections
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&buf[1],1,100);
	HAL_Delay(1);

	buf[1] = buf[1] | 0b1;

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);
	HAL_Delay(100);												// Wait for registers to reset

	return;
}

/*
   @Brief         Read Gyroscope Values
   @Description   Read Angular acceleration from each axis
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Parameter     destination ->  pointer to array to store values
   @Return value  void
 */
void LSM6DSM_readGyro(I2C_HandleTypeDef i2c, float * destination){

	uint8_t buf = 0;
	uint8_t high = 0;
	uint8_t low = 0;
	int16_t value[3];

	float scale = 0.0f;
	uint16_t Gscale = LSM6DSM_getGscale(i2c);
	switch (Gscale){
		case 125  :	scale = LSM6DSM_SCALE_125DPS;
					break;
		case 250  : scale = LSM6DSM_SCALE_250DPS;
					break;
		case 500  : scale = LSM6DSM_SCALE_500DPS;
					break;
		case 1000 : scale = LSM6DSM_SCALE_1000DPS;
					break;
		case 2000 : scale = LSM6DSM_SCALE_2000DPS;
					break;
		default : 	printf("Error in Gscale\r\n");
					return;
	}


	// Get X Axis Value -> Pitch axis
	buf = LSM6DSM_OUTX_L_G;
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&low,1,100);

	buf = LSM6DSM_OUTX_H_G;
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&high,1,100);

	value[0] = (int16_t) ((high << 8) | low);
	destination[0] = (value[0] * scale);



	//Get Y Axis Value -> Roll axis
	buf = LSM6DSM_OUTY_L_G;
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&low,1,100);

	buf = LSM6DSM_OUTY_H_G;
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&high,1,100);

	value[1] = (int16_t) ((high << 8) | low);
	destination[1] = (value[1] * scale);



	//Get Z Axis Value -> Yaw axis
	buf = LSM6DSM_OUTZ_L_G;
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&low,1,100);

	buf = LSM6DSM_OUTZ_H_G;
	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&high,1,100);

	value[2] = (int16_t) ((high << 8) | low);
	destination[2] = (value[2] * scale);


	return;
}

/*
   @Brief         Self Test the Accelerometer and Gyroscope
   @Description   Test if Accelerometer and Gyroscope working correctly
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  void
 */
void LSM6DSM_selfTest(I2C_HandleTypeDef i2c){

	uint8_t buf[2];

	float data[3];

	printf("Starting Self Test in 2s, place IMU on stable, motionless surface \r\n\r\n");

	HAL_Delay(2000);

	//Get Initial Gyro Values
	LSM6DSM_readGyro(i2c, data);

	printf("Initial Values    : %3.3f   %3.3f   %3.3f\r\n", data[0], data[1], data[2]);

	//Get Positive Self Test Values
	buf[0] = LSM6DSM_CTRL5_C;
	buf[1] = 0b0100;			// set ST_G to positive self test

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);
    HAL_Delay(10);

	LSM6DSM_readGyro(i2c, data);
	printf("Positive Self Test: %3.3f   %3.3f   %3.3f\r\n", data[0], data[1], data[2]);

	//Get Negative Self Test Values
	buf[1] = 0b1100;			// set ST_G to negative self test

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);
    HAL_Delay(10);

	LSM6DSM_readGyro(i2c, data);
	printf("Negative Self Test: %3.3f   %3.3f   %3.3f\r\n\r\n", data[0], data[1], data[2]);

	printf("Self Test Complete. Values should be within 20dps and 80dps\r\n\r\n");

	buf[1] = 0;						// reset ST_G to stop self test

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);
    HAL_Delay(1);

	return;

}

/*
   @Brief         Setup chip for use of INT1 flag
   @Description   Route Gyro Data Ready flag to INT1 Pad
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  void
 */
void LSM6DSM_setup_int1(I2C_HandleTypeDef i2c){

	// read STATUS Register to confirm data ready flag is high

	uint8_t buf[2];
	buf[0] = LSM6DSM_STATUS_REG;
	buf[1] = 0b00;

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,buf,1,100);
	HAL_Delay(1);

	if(!(buf[0] & 0b010)){
		printf("ERROR: data not ready\r\n");
		return;
	}

	//enable DRDY_MASK flag in CTRL4_C Register

	buf[0] = LSM6DSM_CTRL4_C;
	buf[1] = 0b0100;

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);
	HAL_Delay(1);

	// route int1 pad to the gyro data ready flag

	buf[0] = LSM6DSM_INT1_CTRL;
	buf[1] = 0b010;

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,buf,2,100);
	HAL_Delay(1);

//	if(HAL_GPIO_ReadPin(INT1_GPIO_Port, INT1_Pin) == GPIO_PIN_SET){
//		printf("INT1 successfully routed!\r\n");
//		return;
//	}
//	else{
//		printf("INT1 not routed!\r\n");
//		return;
//	}
}

/*
   @Brief         Wait until next set of Gyro data is ready
   @Description   Wait for status
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  void
 */
void LSM6DSM_wait_for_Data(I2C_HandleTypeDef i2c){

	uint8_t data = LSM6DSM_read_status(i2c);
	while(!(data & 0b010)){
		data = LSM6DSM_read_status(i2c);
	}
	return;
}

uint8_t LSM6DSM_read_status(I2C_HandleTypeDef i2c){

	uint8_t buf = LSM6DSM_STATUS_REG;
	uint8_t data = 0;

	HAL_I2C_Master_Transmit(&i2c,LSM6DSM_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LSM6DSM_DeviceID,&data,1,100);

	return data;
}


