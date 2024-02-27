#include "LIS2DW12.h"
#include <stdio.h>
#include "math.h"

/* Device ID Set */
uint8_t LIS2DW12_DeviceID = LIS2DW12_DeviceID1;
int z_array_val[25];


/*
   @Brief         Custom Initialization
   @Description   Custom Parameters for Sensor
   @Parameter     I2C_HandleTypeDef ->  HAL_I2C Handle
   @Return value  void
 */
void LIS2DW12_Initialization               (I2C_HandleTypeDef i2c)
{
	uint8_t buf[5];

	// Control Register 1 //
	buf[0]  = LIS2DW12_CTRL1;
	uint8_t ODR = 0b0010;								// Low Power Mode 12.5Hz
	uint8_t MODE = 0b00;								// Low-Power Mode (12/14bit reso)
	uint8_t LP_MODE = 0b11;								// Low-Power Mode 4 (14-bit reso)
	buf[1]  = (ODR << 4) | (MODE << 2) | LP_MODE;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);

	// Control Register 6 //
	buf[0] = LIS2DW12_CTRL6;
    uint8_t BW_FILT = 0b01;								// ODR/4
    uint8_t FS = 0b01;									// +-4g
    uint8_t FDS = 0b0;									// Low Pass Filter
	uint8_t LOW_NOISE = 0b1;							// Enable Low Noise Configuration
	buf[1] = (BW_FILT << 6) | (FS << 4) | (FDS << 3) | (LOW_NOISE << 2);
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);

    // FIFO CTRL //
    buf[0] = LIS2DW12_FIFO_CTRL;
    uint8_t FMode = 0b001;								// Set to FIFO mode: Stop collecting data when FIFO is full
    uint8_t FTH = 0b11000;								// FIFO threshold (0-31) -> set to be 24 -> to get 1s
    buf[1] = (FMode << 5) | FTH;
    HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);

    // Control Register 4 INT1_PAD_CTRL//
    buf[0] = LIS2DW12_CTRL4_INT1_PAD_CTRL;
    uint8_t INT1_FTH = 0b1;								// FIFO threshold interrupt routed to INT1
    buf[1] = (INT1_FTH << 1);
    HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);

    // Control Register 7 //
    buf[0] = LIS2DW12_CTRL7;
    uint8_t INT_EN = 0b1;								// Enable interrupts
    buf[1] = (INT_EN << 5);
    HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);

	return;

}

void LIS2DW12_Set_ODR					   (I2C_HandleTypeDef i2c, uint8_t odr){

	uint8_t buf[2];

	buf[0] = LIS2DW12_CTRL1;
	buf[1] = (odr << 4) | 0b11;				// set ODR while keeping Low Power Mode 4

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);
	HAL_Delay(1);

	return;

}

uint8_t LIS2DW12_Get_ODR				   (I2C_HandleTypeDef i2c){

	uint8_t buf;

	buf = LIS2DW12_CTRL1;

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_Delay(1);

	return (buf >> 4);
}

void LIS2DW12_Set_Sensitivity			   (I2C_HandleTypeDef i2c, uint8_t sensitivity){

	uint8_t buf[2];

	buf[0] = LIS2DW12_CTRL6;
	buf[1] = (sensitivity << 4) | 0b1;		// set sensitivity while keeping Low Noise Config

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);
	HAL_Delay(1);

	return;
}



uint8_t LIS2DW12_Get_Reg(I2C_HandleTypeDef i2c, uint8_t regName){


				uint8_t buf;

					buf = regName;

						HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
						HAL_Delay(1);
						HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&buf,1,100);
						HAL_Delay(1);

						return buf;

}

void LIS2DW12_Set_HP (I2C_HandleTypeDef i2c){


	uint8_t buf[2];
		buf[0] = LIS2DW12_CTRL6;
				buf[1] = 0b00001000 | LIS2DW12_Get_Reg(i2c,LIS2DW12_CTRL6);		// set sensitivity while keeping Low Noise Config

				HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);
				HAL_Delay(1);

				return;



}




void LIS2DW12_Set_Offset (I2C_HandleTypeDef i2c, uint8_t xoffset, uint8_t yoffset,uint8_t zoffset)
{
	uint8_t buf[2];

	buf[0] = LIS2DW12_CTRL7;
	buf[1] = 0b00011100 | 0b1;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);
	HAL_Delay(1);

	buf[0] = LIS2DW12_X_OFS_USR;
	buf[1] = xoffset;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);		HAL_Delay(1);
	HAL_Delay(1);

	buf[0] = LIS2DW12_Y_OFS_USR;
		buf[1] = yoffset;
		HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);		HAL_Delay(1);
		HAL_Delay(1);

		buf[0] = LIS2DW12_Z_OFS_USR;
			buf[1] = zoffset;
			HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);		HAL_Delay(1);
			HAL_Delay(1);


}

uint8_t LIS2DW12_Get_Sensitivity		   (I2C_HandleTypeDef i2c){

	uint8_t buf;

	buf = LIS2DW12_CTRL6;

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_Delay(1);

	return (buf >> 4);
}

void LIS2DW12_Set_FIFO					   (I2C_HandleTypeDef i2c, uint8_t FMode){

	uint8_t buf[2];

	buf[0] = LIS2DW12_FIFO_CTRL;
	buf[1] = (FMode << 5) | LIS2DW12_Get_Reg(i2c,LIS2DW12_FIFO_CTRL);

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);
	HAL_Delay(1);

	return;
}

void LIS2DW12_Set_Int_Fth			   (I2C_HandleTypeDef i2c, uint8_t intMode){

	uint8_t buf[2];

		buf[0] = LIS2DW12_CTRL4_INT1_PAD_CTRL;
		buf[1] = intMode;

		HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);
		HAL_Delay(1);

		return;


}

void LIS2DW12_Set_FIFO_Threshold			   (I2C_HandleTypeDef i2c, uint8_t threshold){

	uint8_t buf[2];

		buf[0] = LIS2DW12_FIFO_CTRL;
		buf[1] = threshold | LIS2DW12_Get_Reg(i2c,LIS2DW12_FIFO_CTRL);

		HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);
		HAL_Delay(1);

		return;


}

uint8_t LIS2DW12_ReadID					   (I2C_HandleTypeDef  i2c){

	uint8_t buf;

	buf = LIS2DW12_WHO_AM_I;

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_Delay(1);

	return buf;
}

float LIS2DW12_ReadX					    (I2C_HandleTypeDef i2c){

	uint8_t buf;
	uint8_t high = 0;
	uint8_t low = 0;

	buf = LIS2DW12_OUT_X_LOW;

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&low,1,100);

	buf = LIS2DW12_OUT_X_HIGH;

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&high,1,100);;

	int16_t value = (high << 8) | low;

	float acceleration = ((value / 4) * LIS2DW12_scale_4g) * 9.806;

	return acceleration;
}

float LIS2DW12_ReadY					    (I2C_HandleTypeDef i2c){

	uint8_t buf;
	uint8_t high = 0;
	uint8_t low = 0;

	buf = LIS2DW12_OUT_Y_LOW;

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&low,1,100);

	buf = LIS2DW12_OUT_Y_HIGH;

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&high,1,100);

	int16_t value = (high << 8) | low;

	float acceleration = ((value / 4) * LIS2DW12_scale_4g) * 9.806;

	return acceleration;
}

float LIS2DW12_ReadZ					    (I2C_HandleTypeDef i2c){

	uint8_t buf;
	uint8_t high = 0;
	uint8_t low = 0;

	buf = LIS2DW12_OUT_Z_LOW;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&low,1,100);

	buf = LIS2DW12_OUT_Z_HIGH;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&high,1,100);

	int16_t value = (int16_t) (high << 8) | low;

	float acceleration = ((value / 4) * LIS2DW12_scale_4g) * 9.806;

	return acceleration;
}



void LIS2DW12_Reset_FIFO (I2C_HandleTypeDef i2c){

	uint8_t buf[5];
	buf[0] = LIS2DW12_FIFO_CTRL;
    buf[1] = 0x00;											// Bypass mode: Reset FIFO
    HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);

    uint8_t FMode = 0b001;									// FIFO mode
    uint8_t FTH = 0b11000;									// FIFO threshold (0-31) -> set to be 24 -> to get 1s
    buf[1] = (FMode << 5) | FTH;
    HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);

	return;
}




void LIS2DW12_Wait_for_Data				   (I2C_HandleTypeDef i2c){

	uint8_t buf;
	uint8_t status = 0;
	buf = LIS2DW12_STATUS;

	while(status == 0){
		HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
		HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&status,1,100);
		status = status & 0x01;
	}
	return;
}

void LIS2DW12_Self_Test					   (I2C_HandleTypeDef i2c){

	uint8_t buf[2];
	float data[3];
	uint8_t ST = 0b01;

	printf("Starting Self Test, Initial Values: \r\n");

	data[0] = LIS2DW12_ReadX(i2c);
	data[1] = LIS2DW12_ReadY(i2c);
	data[2] = LIS2DW12_ReadZ(i2c);

	printf("%2.3f  ", data[0]);
	printf("%2.3f  ", data[1]);
	printf("%2.3f\r\n", data[2]);

	buf[0] = LIS2DW12_CTRL3;
	buf[1] = (ST << 6);

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);
	HAL_Delay(1);

	printf("Positive Self Test Applied, Values:\r\n");

	data[0] = LIS2DW12_ReadX(i2c);
	data[1] = LIS2DW12_ReadY(i2c);
	data[2] = LIS2DW12_ReadZ(i2c);

	printf("%2.3f  ", data[0]);
	printf("%2.3f  ", data[1]);
	printf("%2.3f\r\n", data[2]);

	ST = 0b10;
	buf[1] = (ST << 6);

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);
	HAL_Delay(1);

	printf("Negative Self Test Applied, Values:\r\n");

	data[0] = LIS2DW12_ReadX(i2c);
	data[1] = LIS2DW12_ReadY(i2c);
	data[2] = LIS2DW12_ReadZ(i2c);

	printf("%2.3f  ", data[0]);
	printf("%2.3f  ", data[1]);
	printf("%2.3f\r\n", data[2]);

	printf("Self Test Complete\r\n");

	ST = 0b00;
	buf[1] = (ST << 6);

	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,buf,2,100);
	HAL_Delay(1);

	return;
}

uint8_t LIS2DW12_Get_FIFO_SAMPLES (I2C_HandleTypeDef i2c) {

	uint8_t buf = LIS2DW12_FIFO_SAMPLES;
    uint8_t DIFF = 0;								// Number of unread samples stored in FIFO
    HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
    HAL_Delay(1);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&DIFF,1,100);
	HAL_Delay(1);

	DIFF = DIFF & 0b00011111;

	return DIFF;
}

uint8_t LIS2DW12_Get_FIFO_FTH (I2C_HandleTypeDef i2c) {

	uint8_t buf = LIS2DW12_FIFO_SAMPLES;
    uint8_t FTH = 0;													// FIFO threshold status flag
    HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&FTH,1,100);

	FTH = FTH & 0x80;

	return FTH;
}

void LIS2DW12_Get_FIFO_Z (I2C_HandleTypeDef i2c, float * z_array) {

	for (int i = 0; i < 25; i++) {
		z_array[i] = LIS2DW12_ReadZ(i2c);
	}
	return;
}

uint8_t LIS2DW12_Get_STATUS (I2C_HandleTypeDef i2c) {
	uint8_t buf = LIS2DW12_STATUS;
	uint8_t status;
    HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&status,1,100);

	return status;
}

void LIS2DW12_ReadXYZ (I2C_HandleTypeDef i2c, float * destination) {
	uint8_t buf;
	uint8_t high = 0;
	uint8_t low = 0;
	uint16_t value;

	// Read X //
	buf = LIS2DW12_OUT_X_LOW;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&low,1,100);

	buf = LIS2DW12_OUT_X_HIGH;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&high,1,100);;

	value = (high << 8) | low;
	destination[0] = ((value / 4) * LIS2DW12_scale_4g) * 9.806;

	// Read Y //
	buf = LIS2DW12_OUT_Y_LOW;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&low,1,100);

	buf = LIS2DW12_OUT_Y_HIGH;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&high,1,100);

	value = (high << 8) | low;
	destination[1] = ((value / 4) * LIS2DW12_scale_4g) * 9.806;

	// Read Z //
	buf = LIS2DW12_OUT_Z_LOW;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&low,1,100);

	buf = LIS2DW12_OUT_Z_HIGH;
	HAL_I2C_Master_Transmit(&i2c,LIS2DW12_DeviceID,&buf,1,100);
	HAL_I2C_Master_Receive(&i2c,LIS2DW12_DeviceID,&high,1,100);

	value = (int16_t) (high << 8) | low;
	destination[2] = ((value / 4) * LIS2DW12_scale_4g) * 9.806;

	return;
}










