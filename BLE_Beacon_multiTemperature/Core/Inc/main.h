/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal.h"
#include "app_conf.h"
#include "app_entry.h"
#include "app_common.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Data_Ready_1_Pin GPIO_PIN_4
#define Data_Ready_1_GPIO_Port GPIOB
#define Data_Ready_1_EXTI_IRQn EXTI4_IRQn
#define Data_Ready_2_Pin GPIO_PIN_5
#define Data_Ready_2_GPIO_Port GPIOB
#define Data_Ready_2_EXTI_IRQn EXTI9_5_IRQn
#define Data_Ready_3_Pin GPIO_PIN_6
#define Data_Ready_3_GPIO_Port GPIOB
#define Data_Ready_3_EXTI_IRQn EXTI9_5_IRQn
#define Data_Ready_4_Pin GPIO_PIN_7
#define Data_Ready_4_GPIO_Port GPIOB
#define Data_Ready_4_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */
#define Device_ID_1	TMP117_DeviceID1
#define Device_ID_2	TMP117_DeviceID2
#define Device_ID_3	TMP117_DeviceID3
#define Device_ID_4	TMP117_DeviceID4
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
