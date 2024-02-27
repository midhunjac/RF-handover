#include "MAX30003.h"

#include <stdio.h>

/*
   @Description   Get MAX30003's register value
   @Parameter     SPI_HandleTypeDef ->  HAL_SPI Handle
                  GPIO_TypeDef  	->  SPI GPIO_Port
                  uint16_t      	->  SPI GPIO_Pin
                  uint16_t 			->	Register address
   @Return value  uint32_t			-> 	Register value
 */
uint32_t MAX30003_get_reg(SPI_HandleTypeDef spi, GPIO_TypeDef * port, uint16_t pin, uint8_t reg_addr)
{
	static uint8_t buf[3];
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
	buf[0] = (reg_addr << 1) | MAX30003_REG_READ;
	HAL_SPI_Transmit(&spi, buf, 1, 1);
	HAL_SPI_Receive(&spi, buf, 3, 1);
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);

	return ((buf[0]<<16)|(buf[1]<<8)|buf[2]);
}

/*
   @Description   Set MAX30003's register value; operate three bytes at a time
   @Parameter     SPI_HandleTypeDef ->  HAL_SPI Handle
                  GPIO_TypeDef  	->  SPI GPIO_Port
                  uint16_t      	->  SPI GPIO_Pin
                  uint8_t       	->  First data byte
                  uint8_t       	->  Second data byte
                  uint8_t       	->  Third data byte
   @Return value  void
 */
void MAX30003_set_reg(SPI_HandleTypeDef spi, GPIO_TypeDef * port, uint16_t pin, uint8_t reg_addr,
		uint8_t first_byte, uint8_t second_byte, uint8_t third_byte)
{
	uint8_t buf[4];
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
	buf[0] = (reg_addr << 1) | MAX30003_REG_WRITE;
	buf[1] = first_byte;
	buf[2] = second_byte;
	buf[3] = third_byte;
	HAL_SPI_Transmit(&spi, buf, 4, 1);
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);

	return;
}

/*
   @Description   Set MAX30003's register value to zero
   @Parameter     SPI_HandleTypeDef ->  HAL_SPI Handle
                  GPIO_TypeDef  	->  SPI GPIO_Port
                  uint16_t      	->  SPI GPIO_Pin
   @Return value  void
 */
void MAX30003_set_reg_to_zero(SPI_HandleTypeDef spi, GPIO_TypeDef * port, uint16_t pin, uint8_t reg_addr)
{
	MAX30003_set_reg(spi, port, pin, reg_addr, 0x00, 0x00, 0x00);
	return;
}

