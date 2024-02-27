#include "main.h"

#ifndef      _MAX30003_H_
#define      _MAX30003_H_

/*
Check the model of your MCU model
*/
#ifndef     __STM32WBxx_HAL_SPI_H
#define     __STM32WBxx_HAL_SPI_H
#endif

#ifndef		__STM32WBxx_HAL_GPIO_H
#define		__STM32WBxx_HAL_GPIO_H
#endif


/*
Pointer Registers
*/
#define MAX30003_REG_WRITE			0x00
#define MAX30003_REG_READ			0x01

#define	MAX30003_STATUS				0x01
#define MAX30003_EN_INT				0x02
#define MAX30003_EN_INT2         	0x03
#define MAX30003_MNGR_INT			0x04
#define MAX30003_MNGR_DYN			0x05

#define MAX30003_SW_RST          	0x08
#define MAX30003_SYNCH           	0x09
#define MAX30003_FIFO_RST        	0x0A
#define MAX30003_INFO				0x0F

#define MAX30003_CNFG_GEN    		0x10
#define MAX30003_CNFG_CAL			0x12
#define MAX30003_CNFG_EMUX     		0x14
#define	MAX30003_CNFG_ECG			0x15
#define MAX30003_CNFG_RTOR1      	0x1D
#define MAX30003_CNFG_RTOR2			0x1E

#define MAX30003_ECG_BURST_FIFO  	0x20
#define	MAX30003_ECG_FIFO			0x21
#define	MAX30003_RTOR_FIFO			0x25

/*
   @Description   Get MAX30003's register value
   @Parameter     SPI_HandleTypeDef ->  HAL_SPI Handle
                  GPIO_TypeDef  	->  SPI GPIO_Port
                  uint16_t      	->  SPI GPIO_Pin
                  uint16_t 			->	Register address
   @Return value  uint32_t			-> 	Register value
 */
uint32_t MAX30003_get_reg(SPI_HandleTypeDef spi, GPIO_TypeDef * port, uint16_t pin, uint8_t reg_addr);
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
		uint8_t first_byte, uint8_t second_byte, uint8_t third_byte);

/*
   @Description   Set MAX30003's register value to zero
   @Parameter     SPI_HandleTypeDef ->  HAL_SPI Handle
                  GPIO_TypeDef  	->  SPI GPIO_Port
                  uint16_t      	->  SPI GPIO_Pin
   @Return value  void
 */
void MAX30003_set_reg_to_zero(SPI_HandleTypeDef spi, GPIO_TypeDef * port, uint16_t pin, uint8_t reg_addr);


#endif
