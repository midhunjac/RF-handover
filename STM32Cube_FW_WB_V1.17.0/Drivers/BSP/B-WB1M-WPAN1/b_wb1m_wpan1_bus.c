/**
  ******************************************************************************
  * @file    b_wb1m_wpan1_bus.c
  * @author  MCD Application Team
  * @brief   This file provides a set of firmware functions to manage bus
  *          available on B-WB1M-WPAN1 board (MB1868) from
  *          STMicroelectronics.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "b_wb1m_wpan1_bus.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup B_WB1M_WPAN1
  * @{
  */

/** @defgroup B_WB1M_WPAN1_BUS B-WB1M-WPAN1 BUS
  * @{
  */

/** @defgroup B_WB1M_WPAN1_BUS_Private_Defines B-WB1M-WPAN1 BUS Private Defines
  * @{
  */
#define I2C_SPEED_FREQ_STANDARD         0U   /* 100 kHz */
#define I2C_SPEED_FREQ_FAST             1U   /* 400 kHz */
#define I2C_SPEED_FREQ_FAST_PLUS        2U   /* 1 MHz */
#define I2C_ANALOG_FILTER_DELAY_MIN     50U  /* ns */
#define I2C_ANALOG_FILTER_DELAY_MAX     260U /* ns */
#define I2C_USE_ANALOG_FILTER           1U
#define I2C_DIGITAL_FILTER_COEF         0U
#define I2C_VALID_TIMING_NBR            128U
#define I2C_PRESC_MAX                   16U
#define I2C_SCLDEL_MAX                  16U
#define I2C_SDADEL_MAX                  16U
#define I2C_SCLH_MAX                    256U
#define I2C_SCLL_MAX                    256U
#define SEC2NSEC                        1000000000UL
/**
  * @}
  */

/** @defgroup B_WB1M_WPAN1_BUS_Private_Types B-WB1M-WPAN1 BUS Private Types
  * @{
  */
typedef struct
{
  uint32_t freq;       /* Frequency in Hz */
  uint32_t freq_min;   /* Minimum frequency in Hz */
  uint32_t freq_max;   /* Maximum frequency in Hz */
  uint32_t hddat_min;  /* Minimum data hold time in ns */
  uint32_t vddat_max;  /* Maximum data valid time in ns */
  uint32_t sudat_min;  /* Minimum data setup time in ns */
  uint32_t lscl_min;   /* Minimum low period of the SCL clock in ns */
  uint32_t hscl_min;   /* Minimum high period of SCL clock in ns */
  uint32_t trise;      /* Rise time in ns */
  uint32_t tfall;      /* Fall time in ns */
  uint32_t dnf;        /* Digital noise filter coefficient */
} I2C_Charac_t;

typedef struct
{
  uint32_t presc;      /* Timing prescaler */
  uint32_t tscldel;    /* SCL delay */
  uint32_t tsdadel;    /* SDA delay */
  uint32_t sclh;       /* SCL high period */
  uint32_t scll;       /* SCL low period */
} I2C_Timings_t;

/**
  * @}
  */

/** @defgroup B_WB1M_WPAN1_BUS_Private_Constants B-WB1M-WPAN1 BUS Private Constants
  * @{
  */
static const I2C_Charac_t I2C_Charac[] =
{
  [I2C_SPEED_FREQ_STANDARD] =
  {
    .freq = 100000,
    .freq_min = 80000,
    .freq_max = 120000,
    .hddat_min = 0,
    .vddat_max = 3450,
    .sudat_min = 250,
    .lscl_min = 4700,
    .hscl_min = 4000,
    .trise = 640,
    .tfall = 20,
    .dnf = I2C_DIGITAL_FILTER_COEF,
  },
  [I2C_SPEED_FREQ_FAST] =
  {
    .freq = 400000,
    .freq_min = 320000,
    .freq_max = 480000,
    .hddat_min = 0,
    .vddat_max = 900,
    .sudat_min = 100,
    .lscl_min = 1300,
    .hscl_min = 600,
    .trise = 250,
    .tfall = 100,
    .dnf = I2C_DIGITAL_FILTER_COEF,
  },
  [I2C_SPEED_FREQ_FAST_PLUS] =
  {
    .freq = 1000000,
    .freq_min = 800000,
    .freq_max = 1200000,
    .hddat_min = 0,
    .vddat_max = 450,
    .sudat_min = 50,
    .lscl_min = 500,
    .hscl_min = 260,
    .trise = 60,
    .tfall = 100,
    .dnf = I2C_DIGITAL_FILTER_COEF,
  },
};

/**
  * @}
  */

/** @defgroup B_WB1M_WPAN1_BUS_Private_Variables B-WB1M-WPAN1 BUS Private Variables
  * @{
  */
static uint32_t I2c1InitCounter = 0U;
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1U)
static uint32_t Bus_IsI2c1MspCbValid = 0U;
#endif /* (USE_HAL_I2C_REGISTER_CALLBACKS == 1) */
static I2C_Timings_t I2c_valid_timing[I2C_VALID_TIMING_NBR];
static uint32_t      I2c_valid_timing_nbr = 0U;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
static uint32_t IsSpi1MspCbValid = 0U;
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup B_WB1M_WPAN1_BUS_Exported_Variables B-WB1M-WPAN1 BUS Exported Variables
  * @{
  */
I2C_HandleTypeDef hbus_i2c1 = {0};
SPI_HandleTypeDef hbus_spi1 = {0};

/**
  * @}
  */

/** @defgroup B_WB1M_WPAN1_BUS_Private_Function_Prototypes B-WB1M-WPAN1 BUS Private Function Prototypes
  * @{
  */
static void     I2C1_MspInit(I2C_HandleTypeDef *hI2c);
static void     I2C1_MspDeInit(I2C_HandleTypeDef *hI2c);
static int32_t  I2C1_WriteReg(uint16_t DevAddr, uint16_t MemAddSize, uint16_t Reg, uint8_t *pData, uint16_t Length);
static int32_t  I2C1_ReadReg(uint16_t DevAddr, uint16_t MemAddSize, uint16_t Reg, uint8_t *pData, uint16_t Length);
static uint32_t I2C_GetTiming(uint32_t clock_src_freq, uint32_t i2c_freq);
static uint32_t I2C_Compute_SCLL_SCLH(uint32_t clock_src_freq, uint32_t I2C_speed);
static void     I2C_Compute_PRESC_SCLDEL_SDADEL(uint32_t clock_src_freq, uint32_t I2C_speed);

static void SPI1_MspInit(SPI_HandleTypeDef *hspi);
static void SPI1_MspDeInit(SPI_HandleTypeDef *hspi);
static uint32_t SPI_GetPrescaler(uint32_t clk_src_hz, uint32_t baudfreq_mbps);
/**
  * @}
  */

/** @defgroup B_WB1M_WPAN1_BUS_Exported_Functions B-WB1M-WPAN1 BUS Exported Functions
  * @{
  */

/**
  * @brief  Initialize BSP I2C1.
  * @retval BSP status.
  */
int32_t BSP_I2C1_Init(void)
{
  int32_t status = BSP_ERROR_NONE;

  hbus_i2c1.Instance = BUS_I2C1;

  if (I2c1InitCounter == 0U)
  {
    if (HAL_I2C_GetState(&hbus_i2c1) == HAL_I2C_STATE_RESET)
    {
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 0)
      /* Init the I2C1 Msp */
      I2C1_MspInit(&hbus_i2c1);

      if (MX_I2C1_Init(&hbus_i2c1, I2C_GetTiming(HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C1),
                                                 BUS_I2C1_FREQUENCY)) != HAL_OK)
      {
        status = BSP_ERROR_BUS_FAILURE;
      }
#else
      if (Bus_IsI2c1MspCbValid == 0U)
      {
        if (BSP_I2C1_RegisterDefaultMspCallbacks() != BSP_ERROR_NONE)
        {
          status = BSP_ERROR_MSP_FAILURE;
        }
      }

      if (status == BSP_ERROR_NONE)
      {
        if (MX_I2C1_Init(&hbus_i2c1, I2C_GetTiming(HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2C1),
                                                   BUS_I2C1_FREQUENCY)) != HAL_OK)
        {
          status = BSP_ERROR_BUS_FAILURE;
        }
      }
#endif /* (USE_HAL_I2C_REGISTER_CALLBACKS == 0) */
    }
  }
  if (I2c1InitCounter < 0xFFFFFFFFU)
  {
    I2c1InitCounter++;
  }
  return status;
}

/**
  * @brief  DeInitialize BSP I2C1.
  * @retval BSP status.
  */
int32_t BSP_I2C1_DeInit(void)
{
  int32_t status = BSP_ERROR_NONE;

  if (I2c1InitCounter > 0U)
  {
    I2c1InitCounter--;
    if (I2c1InitCounter == 0U)
    {
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 0)
      I2C1_MspDeInit(&hbus_i2c1);
#endif /* (USE_HAL_I2C_REGISTER_CALLBACKS == 0) */

      /* De-Init the I2C */
      if (HAL_I2C_DeInit(&hbus_i2c1) != HAL_OK)
      {
        status = BSP_ERROR_PERIPH_FAILURE;
      }
    }
  }

  return status;
}

/**
  * @brief  Write 8bit values in registers of the device through BUS.
  * @param  DevAddr Device address on Bus.
  * @param  Reg     The target register start address to write.
  * @param  pData   Pointer to data buffer.
  * @param  Length  Number of data.
  * @retval BSP status.
  */
int32_t BSP_I2C1_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  return I2C1_WriteReg(DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length);
}

/**
  * @brief  Read a 8bit values in registers of the device through BUS.
  * @param  DevAddr Device address on Bus.
  * @param  Reg     The target register start address to read.
  * @param  pData   Pointer to data buffer.
  * @param  Length  Number of data.
  * @retval BSP status
  */
int32_t BSP_I2C1_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  return I2C1_ReadReg(DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length);
}

/**
  * @brief  Write 16bit values in registers of the device through BUS.
  * @param  DevAddr Device address on Bus.
  * @param  Reg     The target register start address to write.
  * @param  pData   Pointer to data buffer.
  * @param  Length  Number of data.
  * @retval BSP status.
  */
int32_t BSP_I2C1_WriteReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  return I2C1_WriteReg(DevAddr, Reg, I2C_MEMADD_SIZE_16BIT, pData, Length);
}

/**
  * @brief  Read a 16bit values in registers of the device through BUS.
  * @param  DevAddr Device address on Bus.
  * @param  Reg     The target register start address to read.
  * @param  pData   Pointer to data buffer.
  * @param  Length  Number of data.
  * @retval BSP status
  */
int32_t BSP_I2C1_ReadReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  return I2C1_ReadReg(DevAddr, Reg, I2C_MEMADD_SIZE_16BIT, pData, Length);
}

/**
  * @brief  Checks if target device is ready for communication.
  * @param  DevAddr  Target device address.
  * @param  Trials   Number of trials.
  * @retval BSP status
  */
int32_t BSP_I2C1_IsReady(uint16_t DevAddr, uint32_t Trials)
{
  int32_t status = BSP_ERROR_NONE;

  if (HAL_I2C_IsDeviceReady(&hbus_i2c1, DevAddr, Trials, BUS_I2C1_TIMEOUT) != HAL_OK)
  {
    status = BSP_ERROR_BUSY;
  }

  return status;
}

/**
  * @brief  Initializes SPI HAL.
  * @retval BSP status
  */
int32_t BSP_SPI1_Init(void)
{
  int32_t ret = BSP_ERROR_NONE;

  hbus_spi1.Instance  = BUS_SPI1_INSTANCE;

  if (HAL_SPI_GetState(&hbus_spi1) == HAL_SPI_STATE_RESET)
  {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0)
    /* Init the SPI Msp */
    SPI1_MspInit(&hbus_spi1);
#else
    if (IsSpi1MspCbValid == 0U)
    {
      if (BSP_SPI1_RegisterDefaultMspCallbacks() != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif /* (USE_HAL_SPI_REGISTER_CALLBACKS == 0) */

    /* Init the SPI */
    if (MX_SPI1_Init(&hbus_spi1, SPI_GetPrescaler(HAL_RCC_GetPCLK1Freq(), BUS_SPI1_BAUDRATE)) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  DeInitializes SPI HAL.
  * @retval BSP status
  */
int32_t BSP_SPI1_DeInit(void)
{
  int32_t ret  = BSP_ERROR_NONE;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0)
  SPI1_MspDeInit(&hbus_spi1);
#endif /* (USE_HAL_SPI_REGISTER_CALLBACKS == 0) */

  /* DeInit the SPI*/
  if (HAL_SPI_DeInit(&hbus_spi1) == HAL_OK)
  {
    ret = BSP_ERROR_BUS_FAILURE;
  }

  return ret;
}

/**
  * @brief  Initializes MX SPI1 HAL.
  * @param  phspi             SPI handler
  * @param  BaudratePrescaler prsecaler to set for SPI baudrate
  * @retval HAL status
  */
__weak HAL_StatusTypeDef MX_SPI1_Init(SPI_HandleTypeDef *phspi, uint32_t BaudratePrescaler)
{
  HAL_StatusTypeDef ret = HAL_OK;

  phspi->Init.Mode              = SPI_MODE_MASTER;
  phspi->Init.Direction         = SPI_DIRECTION_2LINES;
  phspi->Init.DataSize          = SPI_DATASIZE_8BIT;
  phspi->Init.CLKPolarity       = SPI_POLARITY_HIGH;
  phspi->Init.CLKPhase          = SPI_PHASE_1EDGE;
  phspi->Init.NSS               = SPI_NSS_SOFT;
  phspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  phspi->Init.FirstBit          = SPI_FIRSTBIT_MSB;
  phspi->Init.TIMode            = SPI_TIMODE_DISABLE;
  phspi->Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  phspi->Init.CRCPolynomial     = 7;

  if (HAL_SPI_Init(phspi) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

  return ret;
}

/**
  * @brief  Write Data through SPI BUS.
  * @param  pData  Pointer to data buffer to send
  * @param  Length Length of data in byte
  * @retval BSP status
  */
int32_t BSP_SPI1_Send(uint8_t *pData, uint16_t Length)
{
  int32_t ret = BSP_ERROR_NONE;

  if (HAL_SPI_Transmit(&hbus_spi1, pData, Length, BUS_SPI1_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  return ret;
}

/**
  * @brief  Receive Data from SPI BUS
  * @param  pData  Pointer to data buffer to receive
  * @param  Length Length of data in byte
  * @retval BSP status
  */
int32_t  BSP_SPI1_Recv(uint8_t *pData, uint16_t Length)
{
  int32_t ret = BSP_ERROR_UNKNOWN_FAILURE;
  uint32_t tx_data = 0xFFFFFFFFU;

  if (HAL_SPI_TransmitReceive(&hbus_spi1, (uint8_t *)&tx_data, pData, Length, BUS_SPI1_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  return ret;
}

/**
  * @brief  Send and Receive data to/from SPI BUS (Full duplex)
  * @param  pTxData  Pointer to data buffer to send
  * @param  pRxData  Pointer to data buffer to receive
  * @param  Length   Length of data in byte
  * @retval BSP status
  */
int32_t BSP_SPI1_SendRecv(uint8_t *pTxData, uint8_t *pRxData, uint16_t Length)
{
  int32_t ret = BSP_ERROR_UNKNOWN_FAILURE;

  if (HAL_SPI_TransmitReceive(&hbus_spi1, pTxData, pRxData, Length, BUS_SPI1_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register Default I2C1 Bus Msp Callbacks
  * @retval BSP status
  */
int32_t BSP_I2C1_RegisterDefaultMspCallbacks(void)
{
  int32_t ret = BSP_ERROR_NONE;

  __HAL_I2C_RESET_HANDLE_STATE(&hbus_i2c1);

  /* Register default MspInit/MspDeInit Callback */
  if (HAL_I2C_RegisterCallback(&hbus_i2c1, HAL_I2C_MSPINIT_CB_ID, I2C1_MspInit) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else if (HAL_I2C_RegisterCallback(&hbus_i2c1, HAL_I2C_MSPDEINIT_CB_ID, I2C1_MspDeInit) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else
  {
    Bus_IsI2c1MspCbValid = 1U;
  }

  /* BSP status */
  return ret;
}

/**
  * @brief Register I2C1 Bus Msp Callback registering
  * @param Callbacks     pointer to I2C1 MspInit/MspDeInit callback functions
  * @retval BSP status
  */
int32_t BSP_I2C1_RegisterMspCallbacks(BSP_I2C_Cb_t *Callback)
{
  int32_t ret = BSP_ERROR_NONE;

  __HAL_I2C_RESET_HANDLE_STATE(&hbus_i2c1);

  /* Register MspInit/MspDeInit Callbacks */
  if (HAL_I2C_RegisterCallback(&hbus_i2c1, HAL_I2C_MSPINIT_CB_ID, Callback->pMspI2cInitCb) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else if (HAL_I2C_RegisterCallback(&hbus_i2c1, HAL_I2C_MSPDEINIT_CB_ID, Callback->pMspI2cDeInitCb) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else
  {
    Bus_IsI2c1MspCbValid = 1U;
  }

  /* BSP status */
  return ret;
}
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */

/**
  * @brief  Return system tick in ms
  * @retval Current HAL time base time stamp
  */
int32_t BSP_GetTick(void)
{
  return HAL_GetTick();
}

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
/**
  * @brief Register Default SPI1 Bus Msp Callbacks
  * @retval BSP status
  */
int32_t BSP_SPI1_RegisterDefaultMspCallbacks(void)
{
  __HAL_SPI_RESET_HANDLE_STATE(&hbus_spi1);

  /* Register MspInit Callback */
  if (HAL_SPI_RegisterCallback(&hbus_spi1, HAL_SPI_MSPINIT_CB_ID, SPI1_MspInit) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if (HAL_SPI_RegisterCallback(&hbus_spi1, HAL_SPI_MSPDEINIT_CB_ID, SPI1_MspDeInit) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  IsSpi1MspCbValid = 1;

  return BSP_ERROR_NONE;
}

/**
  * @brief Register SPI1 Bus Msp Callback registering
  * @param Callbacks     pointer to SPI1 MspInit/MspDeInit callback functions
  * @retval BSP status
  */
int32_t BSP_SPI1_RegisterMspCallbacks(BSP_SPI1_Cb_t *Callbacks)
{
  __HAL_SPI_RESET_HANDLE_STATE(&hbus_spi1);

  /* Register MspInit Callback */
  if (HAL_SPI_RegisterCallback(&hbus_spi1, HAL_SPI_MSPINIT_CB_ID, Callbacks->pMspSpiInitCb) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if (HAL_SPI_RegisterCallback(&hbus_spi1, HAL_SPI_MSPDEINIT_CB_ID, Callbacks->pMspSpiDeInitCb) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  IsSpi1MspCbValid = 1;

  return BSP_ERROR_NONE;
}

#endif /* (USE_HAL_SPI_REGISTER_CALLBACKS == 1) */

/**
  * @brief  MX I2C1 initialization.
  * @param  hI2c I2C handle.
  * @param  timing I2C timing.
  * @retval HAL status.
  */
__weak HAL_StatusTypeDef MX_I2C1_Init(I2C_HandleTypeDef *hI2c, uint32_t timing)
{
  HAL_StatusTypeDef status = HAL_OK;

  hI2c->Init.Timing           = timing;
  hI2c->Init.OwnAddress1      = 0;
  hI2c->Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
  hI2c->Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
  hI2c->Init.OwnAddress2      = 0;
  hI2c->Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hI2c->Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
  hI2c->Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

  if (HAL_I2C_Init(hI2c) != HAL_OK)
  {
    status = HAL_ERROR;
  }
  else
  {
    uint32_t analog_filter;

    analog_filter = (I2C_USE_ANALOG_FILTER == 1U) ? I2C_ANALOGFILTER_ENABLE : I2C_ANALOGFILTER_DISABLE;
    if (HAL_I2CEx_ConfigAnalogFilter(hI2c, analog_filter) != HAL_OK)
    {
      status = HAL_ERROR;
    }
    else
    {
      if (HAL_I2CEx_ConfigDigitalFilter(hI2c, I2C_DIGITAL_FILTER_COEF) != HAL_OK)
      {
        status = HAL_ERROR;
      }
    }
  }

  return status;
}

/**
  * @brief  Initializes SPI MSP.
  * @param  hspi  SPI handler
  * @retval None
  */
static void SPI1_MspInit(SPI_HandleTypeDef *hspi)
{
  UNUSED(hspi);

  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable SPIx clock  */
  BUS_SPI1_CLOCK_ENABLE();

  /* enable SPIx gpio clock */
  BUS_SPI1_GPIO_CLKA_ENABLE();

  /* configure SPIx SCK, MOSI */
  GPIO_InitStructure.Pin       = BUS_SPI1_MOSI_PIN;
  GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull      = GPIO_PULLDOWN;
  GPIO_InitStructure.Speed     = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStructure.Alternate = BUS_SPI1_AF;
  HAL_GPIO_Init(BUS_SPI1_GPIO_PORTA, &GPIO_InitStructure);

  GPIO_InitStructure.Pin       = BUS_SPI1_SCK_PIN;
  GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull      = GPIO_PULLDOWN;
  GPIO_InitStructure.Speed     = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStructure.Alternate = BUS_SPI1_AF;
  HAL_GPIO_Init(BUS_SPI1_GPIO_PORTA, &GPIO_InitStructure);
}

/**
  * @brief  DeInitializes SPI MSP.
  * @param  hspi  SPI handler
  * @retval None
  */
static void SPI1_MspDeInit(SPI_HandleTypeDef *hspi)
{
  UNUSED(hspi);

  GPIO_InitTypeDef gpio_init_structure;

  /* Peripheral clock disable */
  __HAL_RCC_SPI1_CLK_DISABLE();

  /* DeInitialize Peripheral GPIOs */
  /* SCK GPIO */
  gpio_init_structure.Pin = BUS_SPI1_SCK_PIN;
  HAL_GPIO_DeInit(BUS_SPI1_GPIO_PORTA, gpio_init_structure.Pin);

  /* MOSI GPIO */
  gpio_init_structure.Pin = BUS_SPI1_MOSI_PIN;
  HAL_GPIO_DeInit(BUS_SPI1_GPIO_PORTA, gpio_init_structure.Pin);
}

/**
  * @}
  */

/** @defgroup B_WB1M_WPAN1_BUS_Private_Functions B-WB1M-WPAN1 BUS Private Functions
  * @{
  */

/**
  * @brief  Initialize I2C1 MSP.
  * @param  hI2c  I2C handler
  * @retval None
  */
static void I2C1_MspInit(I2C_HandleTypeDef *hI2c)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* Prevent unused argument(s) compilation warning */
  UNUSED(hI2c);

  /*** Configure the GPIOs ***/
  /* Enable GPIO clock */
  BUS_I2C1_GPIO_CLK_ENABLE();

  /* Configure I2C SCL as alternate function */
  gpio_init_structure.Pin       = BUS_I2C1_SCL_GPIO_PIN;
  gpio_init_structure.Mode      = GPIO_MODE_AF_OD;
  gpio_init_structure.Pull      = GPIO_NOPULL;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;
  gpio_init_structure.Alternate = BUS_I2C1_SCL_GPIO_AF;
  HAL_GPIO_Init(BUS_I2C1_SCL_GPIO_PORT, &gpio_init_structure);

  /* Configure I2C SDA as alternate function */
  gpio_init_structure.Pin       = BUS_I2C1_SDA_GPIO_PIN;
  gpio_init_structure.Alternate = BUS_I2C1_SDA_GPIO_AF;
  HAL_GPIO_Init(BUS_I2C1_SDA_GPIO_PORT, &gpio_init_structure);

  /*** Configure the I2C peripheral ***/
  /* Enable I2C clock */
  BUS_I2C1_CLK_ENABLE();

  /* Force the I2C peripheral clock reset */
  BUS_I2C1_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  BUS_I2C1_RELEASE_RESET();
}

/**
  * @brief  DeInitialize I2C MSP.
  * @param  hI2c  I2C handler
  * @retval None
  */
static void I2C1_MspDeInit(I2C_HandleTypeDef *hI2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hI2c);

  /* De-initialiaze I2C SCL and SDA */
  HAL_GPIO_DeInit(BUS_I2C1_SCL_GPIO_PORT, BUS_I2C1_SCL_GPIO_PIN);
  HAL_GPIO_DeInit(BUS_I2C1_SDA_GPIO_PORT, BUS_I2C1_SDA_GPIO_PIN);

  /* Disable I2C clock */
  BUS_I2C1_CLK_DISABLE();
}

/**
  * @brief  Write values in registers of the device through BUS.
  * @param  DevAddr    Device address on Bus.
  * @param  Reg        The target register start address to write.
  * @param  MemAddSize Size of internal memory address.
  * @param  pData      The target register values to be written.
  * @param  Length     Number of data.
  * @retval BSP status.
  */
static int32_t I2C1_WriteReg(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length)
{
  int32_t  status = BSP_ERROR_NONE;
  uint32_t hal_error;

  if (HAL_I2C_Mem_Write(&hbus_i2c1, DevAddr, Reg, MemAddSize, pData, Length, BUS_I2C1_TIMEOUT) != HAL_OK)
  {
    hal_error = HAL_I2C_GetError(&hbus_i2c1);
    if ((hal_error & HAL_I2C_ERROR_BERR) != 0U)
    {
      status = BSP_ERROR_BUS_PROTOCOL_FAILURE;
    }
    else if ((hal_error & HAL_I2C_ERROR_ARLO) != 0U)
    {
      status = BSP_ERROR_BUS_ARBITRATION_LOSS;
    }
    else if ((hal_error & HAL_I2C_ERROR_AF) != 0U)
    {
      status = BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE;
    }
    else if (((hal_error & HAL_I2C_ERROR_TIMEOUT) != 0U) || ((hal_error & HAL_I2C_ERROR_SIZE) != 0U))
    {
      status = BSP_ERROR_BUS_TRANSACTION_FAILURE;
    }
    else
    {
      status = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return status;
}

/**
  * @brief  Read values in registers of the device through BUS.
  * @param  DevAddr    Device address on Bus.
  * @param  Reg        The target register start address to read.
  * @param  MemAddSize Size of internal memory address.
  * @param  pData      The target register values to be read.
  * @param  Length     Number of data.
  * @retval BSP status.
  */
static int32_t I2C1_ReadReg(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length)
{
  int32_t  status = BSP_ERROR_NONE;
  uint32_t hal_error;

  if (HAL_I2C_Mem_Read(&hbus_i2c1, DevAddr, Reg, MemAddSize, pData, Length, BUS_I2C1_TIMEOUT) != HAL_OK)
  {
    hal_error = HAL_I2C_GetError(&hbus_i2c1);
    if ((hal_error & HAL_I2C_ERROR_BERR) != 0U)
    {
      status = BSP_ERROR_BUS_PROTOCOL_FAILURE;
    }
    else if ((hal_error & HAL_I2C_ERROR_ARLO) != 0U)
    {
      status = BSP_ERROR_BUS_ARBITRATION_LOSS;
    }
    else if ((hal_error & HAL_I2C_ERROR_AF) != 0U)
    {
      status = BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE;
    }
    else if (((hal_error & HAL_I2C_ERROR_TIMEOUT) != 0U) || ((hal_error & HAL_I2C_ERROR_SIZE) != 0U))
    {
      status = BSP_ERROR_BUS_TRANSACTION_FAILURE;
    }
    else
    {
      status = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return status;
}

/**
  * @brief  Compute I2C timing according current I2C clock source and required I2C clock.
  * @param  clock_src_freq I2C clock source in Hz.
  * @param  i2c_freq Required I2C clock in Hz.
  * @retval I2C timing or 0 in case of error.
  */
static uint32_t I2C_GetTiming(uint32_t clock_src_freq, uint32_t i2c_freq)
{
  uint32_t ret = 0;
  uint32_t speed;
  uint32_t idx;

  if ((clock_src_freq != 0U) && (i2c_freq != 0U))
  {
    for (speed = 0U ; speed <= (uint32_t)I2C_SPEED_FREQ_FAST_PLUS ; speed++)
    {
      if ((i2c_freq >= I2C_Charac[speed].freq_min) &&
          (i2c_freq <= I2C_Charac[speed].freq_max))
      {
        I2C_Compute_PRESC_SCLDEL_SDADEL(clock_src_freq, speed);
        idx = I2C_Compute_SCLL_SCLH(clock_src_freq, speed);

        if (idx < I2C_VALID_TIMING_NBR)
        {
          ret = ((I2c_valid_timing[idx].presc  & 0x0FU) << 28) | \
                ((I2c_valid_timing[idx].tscldel & 0x0FU) << 20) | \
                ((I2c_valid_timing[idx].tsdadel & 0x0FU) << 16) | \
                ((I2c_valid_timing[idx].sclh & 0xFFU) << 8) | \
                ((I2c_valid_timing[idx].scll & 0xFFU) << 0);
        }
        break;
      }
    }
  }

  return ret;
}

/**
  * @brief  Compute PRESC, SCLDEL and SDADEL.
  * @param  clock_src_freq I2C source clock in HZ.
  * @param  I2C_speed I2C frequency (index).
  * @retval None.
  */
static void I2C_Compute_PRESC_SCLDEL_SDADEL(uint32_t clock_src_freq, uint32_t I2C_speed)
{
  uint32_t prev_presc = I2C_PRESC_MAX;
  uint32_t ti2cclk;
  int32_t  tsdadel_min;
  int32_t  tsdadel_max;
  int32_t  tscldel_min;
  uint32_t presc;
  uint32_t scldel;
  uint32_t sdadel;
  uint32_t tafdel_min;
  uint32_t tafdel_max;

  ti2cclk   = (SEC2NSEC + (clock_src_freq / 2U)) / clock_src_freq;

  tafdel_min = (I2C_USE_ANALOG_FILTER == 1U) ? I2C_ANALOG_FILTER_DELAY_MIN : 0U;
  tafdel_max = (I2C_USE_ANALOG_FILTER == 1U) ? I2C_ANALOG_FILTER_DELAY_MAX : 0U;

  /* tDNF = DNF x tI2CCLK
     tPRESC = (PRESC+1) x tI2CCLK
     SDADEL >= {tf +tHD;DAT(min) - tAF(min) - tDNF - [3 x tI2CCLK]} / {tPRESC}
     SDADEL <= {tVD;DAT(max) - tr - tAF(max) - tDNF- [4 x tI2CCLK]} / {tPRESC} */

  tsdadel_min = (int32_t)I2C_Charac[I2C_speed].tfall + (int32_t)I2C_Charac[I2C_speed].hddat_min -
                (int32_t)tafdel_min - (int32_t)(((int32_t)I2C_Charac[I2C_speed].dnf + 3) * (int32_t)ti2cclk);

  tsdadel_max = (int32_t)I2C_Charac[I2C_speed].vddat_max - (int32_t)I2C_Charac[I2C_speed].trise -
                (int32_t)tafdel_max - (int32_t)(((int32_t)I2C_Charac[I2C_speed].dnf + 4) * (int32_t)ti2cclk);


  /* {[tr+ tSU;DAT(min)] / [tPRESC]} - 1 <= SCLDEL */
  tscldel_min = (int32_t)I2C_Charac[I2C_speed].trise + (int32_t)I2C_Charac[I2C_speed].sudat_min;

  if (tsdadel_min <= 0)
  {
    tsdadel_min = 0;
  }

  if (tsdadel_max <= 0)
  {
    tsdadel_max = 0;
  }

  for (presc = 0U; presc < I2C_PRESC_MAX; presc++)
  {
    for (scldel = 0U; scldel < I2C_SCLDEL_MAX; scldel++)
    {
      /* TSCLDEL = (SCLDEL+1) * (PRESC+1) * TI2CCLK */
      uint32_t tscldel = (scldel + 1U) * (presc + 1U) * ti2cclk;

      if (tscldel >= (uint32_t)tscldel_min)
      {
        for (sdadel = 0; sdadel < I2C_SDADEL_MAX; sdadel++)
        {
          /* TSDADEL = SDADEL * (PRESC+1) * TI2CCLK */
          uint32_t tsdadel = (sdadel * (presc + 1U)) * ti2cclk;

          if ((tsdadel >= (uint32_t)tsdadel_min) && (tsdadel <= (uint32_t)tsdadel_max))
          {
            if (presc != prev_presc)
            {
              I2c_valid_timing[I2c_valid_timing_nbr].presc = presc;
              I2c_valid_timing[I2c_valid_timing_nbr].tscldel = scldel;
              I2c_valid_timing[I2c_valid_timing_nbr].tsdadel = sdadel;
              prev_presc = presc;
              I2c_valid_timing_nbr ++;

              if (I2c_valid_timing_nbr >= I2C_VALID_TIMING_NBR)
              {
                return;
              }
            }
          }
        }
      }
    }
  }
}

/**
  * @brief  Calculate SCLL and SCLH and find best configuration.
  * @param  clock_src_freq I2C source clock in HZ.
  * @param  I2C_speed I2C frequency (index).
  * @retval config index (0 to I2C_VALID_TIMING_NBR], 0xFFFFFFFF for no valid config.
  */
static uint32_t I2C_Compute_SCLL_SCLH(uint32_t clock_src_freq, uint32_t I2C_speed)
{
  uint32_t ret = 0xFFFFFFFFU;
  uint32_t ti2cclk;
  uint32_t ti2cspeed;
  uint32_t prev_error;
  uint32_t dnf_delay;
  uint32_t clk_min;
  uint32_t clk_max;
  uint32_t scll;
  uint32_t sclh;
  uint32_t tafdel_min;

  ti2cclk   = (SEC2NSEC + (clock_src_freq / 2U)) / clock_src_freq;
  ti2cspeed   = (SEC2NSEC + (I2C_Charac[I2C_speed].freq / 2U)) / I2C_Charac[I2C_speed].freq;

  tafdel_min = (I2C_USE_ANALOG_FILTER == 1U) ? I2C_ANALOG_FILTER_DELAY_MIN : 0U;

  /* tDNF = DNF x tI2CCLK */
  dnf_delay = I2C_Charac[I2C_speed].dnf * ti2cclk;

  clk_max = SEC2NSEC / I2C_Charac[I2C_speed].freq_min;
  clk_min = SEC2NSEC / I2C_Charac[I2C_speed].freq_max;

  prev_error = ti2cspeed;

  for (uint32_t count = 0U; count < I2c_valid_timing_nbr; count++)
  {
    /* tPRESC = (PRESC+1) x tI2CCLK*/
    uint32_t tpresc = (I2c_valid_timing[count].presc + 1U) * ti2cclk;

    for (scll = 0; scll < I2C_SCLL_MAX; scll++)
    {
      /* tLOW(min) <= tAF(min) + tDNF + 2 x tI2CCLK + [(SCLL+1) x tPRESC ] */
      uint32_t tscl_l = tafdel_min + dnf_delay + (2U * ti2cclk) + ((scll + 1U) * tpresc);


      /* The I2CCLK period tI2CCLK must respect the following conditions:
      tI2CCLK < (tLOW - tfilters) / 4 and tI2CCLK < tHIGH */
      if ((tscl_l > I2C_Charac[I2C_speed].lscl_min) && (ti2cclk < ((tscl_l - tafdel_min - dnf_delay) / 4U)))
      {
        for (sclh = 0; sclh < I2C_SCLH_MAX; sclh++)
        {
          /* tHIGH(min) <= tAF(min) + tDNF + 2 x tI2CCLK + [(SCLH+1) x tPRESC] */
          uint32_t tscl_h = tafdel_min + dnf_delay + (2U * ti2cclk) + ((sclh + 1U) * tpresc);

          /* tSCL = tf + tLOW + tr + tHIGH */
          uint32_t tscl = tscl_l + tscl_h + I2C_Charac[I2C_speed].trise + I2C_Charac[I2C_speed].tfall;

          if ((tscl >= clk_min) && (tscl <= clk_max)
              && (tscl_h >= I2C_Charac[I2C_speed].hscl_min) && (ti2cclk < tscl_h))
          {
            int32_t error = (int32_t)tscl - (int32_t)ti2cspeed;

            if (error < 0)
            {
              error = -error;
            }

            /* look for the timings with the lowest clock error */
            if ((uint32_t)error < prev_error)
            {
              prev_error = (uint32_t)error;
              I2c_valid_timing[count].scll = scll;
              I2c_valid_timing[count].sclh = sclh;
              ret = count;
            }
          }
        }
      }
    }
  }

  return ret;
}

/**
  * @brief  Convert the SPI baudfreq into tpresc.
  * @param  clock_src_freq : SPI source clock in HZ.
  * @param  baudfreq_mbps : SPI baud freq in mbps.
  * @retval Prescaler divisor
  */
static uint32_t SPI_GetPrescaler(uint32_t clock_src_freq, uint32_t baudfreq_mbps)
{
  uint32_t divisor = 0U;
  uint32_t spi_clk = clock_src_freq;
  uint32_t presc = 0U;

  static const uint32_t baudfreq[] =
  {
    SPI_BAUDRATEPRESCALER_2,
    SPI_BAUDRATEPRESCALER_4,
    SPI_BAUDRATEPRESCALER_8,
    SPI_BAUDRATEPRESCALER_16,
    SPI_BAUDRATEPRESCALER_32,
    SPI_BAUDRATEPRESCALER_64,
    SPI_BAUDRATEPRESCALER_128,
    SPI_BAUDRATEPRESCALER_256,
  };

  while (spi_clk > baudfreq_mbps)
  {
    presc = baudfreq[divisor];
    if (++divisor > 7U)
    {
      break;
    }

    spi_clk = (spi_clk >> 1U);
  }

  return presc;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
