/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/ibeacon_service.c
  * @author  MCD Application Team
  * @brief
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

/* Includes ------------------------------------------------------------------*/
#include "app_common.h"
#include "ble.h"
#include "ibeacon.h"
#include "ibeacon_service.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LSM6DSM.h"
#include "stm32_seq.h"
#include "main.h"
/* USER CODE END Includes */

/* Private typedef ------------------------------------------------------------*/

typedef struct
{
    uint16_t AdvertisingInterval;/*!< Specifies the desired advertising interval. */
    uint8_t * UuID;              /*!< Specifies the 16-byte UUID to which the beacon belongs. */
    uint8_t * MajorID;           /*!< Specifies the 2-byte beacon identifying information. */
    uint8_t * MinorID;           /*!< Specifies the 2-byte beacon identifying information. */
    uint8_t CalibratedTxPower;   /*!< Specifies the power at 1m. */
} IBeacon_InitTypeDef;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
#define ADVERTISING_INTERVAL_INCREMENT (16)
/* USER CODE BEGIN PV */
extern I2C_HandleTypeDef hi2c1;
extern RTC_HandleTypeDef hrtc;
extern float data[3];

uint8_t handPos_state = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
extern uint8_t runAlgo(void);
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/

static tBleStatus IBeacon_Init(IBeacon_InitTypeDef *IBeacon_Init)
{
/* USER CODE BEGIN IBeacon_Init_1 */

/* USER CODE END IBeacon_Init_1 */
  tBleStatus ret = BLE_STATUS_SUCCESS;
  uint16_t AdvertisingInterval = (IBeacon_Init->AdvertisingInterval * ADVERTISING_INTERVAL_INCREMENT / 10);

  /* Disable scan response. */
  hci_le_set_scan_response_data(0, NULL);

  /* Put the device in a non-connectable mode. */
  ret = aci_gap_set_discoverable(ADV_NONCONN_IND,                          /*< Advertise as non-connectable, undirected. */
                                 AdvertisingInterval, AdvertisingInterval, /*< Set the advertising interval as 700 ms (0.625 us increment). */
                                 PUBLIC_ADDR, NO_WHITE_LIST_USE,           /*< Use the public address, with no white list. */
                                 0, NULL,                                  /*< Do not use a local name. */
                                 0, NULL,                                  /*< Do not include the service UUID list. */
                                 0, 0);                                    /*< Do not set a slave connection interval. */

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  /* Remove the TX power level advertisement (this is done to decrease the packet size). */
  ret = aci_gap_delete_ad_type(AD_TYPE_TX_POWER_LEVEL);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

	 uint8_t service_data[] =
	 {
	   26,                                                        /*< Length. */
	   AD_TYPE_MANUFACTURER_SPECIFIC_DATA,                        /*< 1-byte Manufacturer Specific Data data type value. */
	   0x4C, 0x00, 												 /*< 2-byte Manufacturer Data (I-Beacon). */
	   0x02, 0x15,                            					 /*< 2-byte Beacon ID */
	   0x00, 0x00, 0x00, 0x09, 0x8e, 0x22, 0x45, 0x41,
	   0x9d, 0x4c, 0x21, 0xed, 0xae, 0x82, 0xed, 0x19,			 /*< 16-byte Proximity UUID. */
	   0x00, 0x02,					 	 	 					 /*< 2-byte Major */
	   0x00, 0x01,					 		 			 		 /*< 2-byte Hand Position */
	   0x01,						     		 				 /*< 1-byte Power*/
	 };

  uint8_t flags[] =
  {
    2,                                                                      /*< Length. */
    AD_TYPE_FLAGS,                                                          /*< Flags data type value. */
    (FLAG_BIT_LE_GENERAL_DISCOVERABLE_MODE | FLAG_BIT_BR_EDR_NOT_SUPPORTED) /*< BLE general discoverable, without BR/EDR support. */
  };

  /* Update the service data. */
  ret = aci_gap_update_adv_data(sizeof(service_data), service_data);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  /* Update the adverstising flags. */
  ret = aci_gap_update_adv_data(sizeof(flags), flags);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }
/* USER CODE BEGIN IBeacon_Init_2 */

/* USER CODE END IBeacon_Init_2 */
  return ret;
}

void IBeacon_Process(void)
{
/* USER CODE BEGIN IBeacon_Process_1 */

/* USER CODE END IBeacon_Process_1 */
  /* Default ibeacon */
  uint8_t UuID[]    = { UUID };
  uint8_t MajorID[] = { MAJOR_ID };
  uint8_t MinorID[] = { MINOR_ID };

  IBeacon_InitTypeDef IBeacon_InitStruct =
  {
    .AdvertisingInterval = ADVERTISING_INTERVAL_IN_MS,
    .UuID                = UuID,
    .MajorID             = MajorID,
    .MinorID             = MinorID,
    .CalibratedTxPower   = CALIBRATED_TX_POWER_AT_1_M
  };

#ifdef USE_OTA
  if(((*(uint8_t *)(OTA_BEACON_DATA_ADDRESS + OFFSET_PAYLOAD_LENGTH)) ==  27) &&
     ((*(uint8_t *)(OTA_BEACON_DATA_ADDRESS + OFFSET_PAYLOAD_DATA)) ==  26))
  {
    uint8_t i;
    uint32_t data_address = OTA_BEACON_DATA_ADDRESS + OFFSET_PAYLOAD_DATA + 6;

    for(i = 0; i < 16; i++)
      IBeacon_InitStruct.UuID[i] = *(uint8_t *)(data_address + i);
    data_address += 16;
    for(i = 0; i < 2; i++)
      IBeacon_InitStruct.MinorID[i] = *(uint8_t *)(data_address + i);
    data_address += 2;
    for(i = 0; i < 2; i++)
      IBeacon_InitStruct.MajorID[i] = *(uint8_t *)(data_address + i);
    data_address += 2;
    IBeacon_InitStruct.CalibratedTxPower = *(uint8_t *)(data_address);
  }
#endif

  IBeacon_Init(&IBeacon_InitStruct);
/* USER CODE BEGIN IBeacon_Process_2 */

/* USER CODE END IBeacon_Process_2 */
}
/* USER CODE BEGIN FD */
void initHandPosition(void) {
	  LSM6DSM_stop_acc(hi2c1,AODR_POWER_DOWN);
	  LSM6DSM_start_gyro(hi2c1, GFS_500DPS, GODR_26Hz);
	  UTIL_SEQ_SetTask(1<<CFG_TASK_GET_HAND_POS, CFG_SCH_PRIO_0);
}

void getHandPosition(void) {
	 HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
	 LSM6DSM_wait_for_Data(hi2c1);
     LSM6DSM_readGyro(hi2c1, data);
	 handPos_state = runAlgo();
	 if(handPos_state) {
		 uint8_t service_data[] =
		 {
		   26,                                                        /*< Length. */
		   AD_TYPE_MANUFACTURER_SPECIFIC_DATA,                        /*< 1-byte Manufacturer Specific Data data type value. */
		   0x4C, 0x00, 												 /*< 2-byte Manufacturer Data (I-Beacon). */
		   0x02, 0x15,                            					 /*< 2-byte Beacon ID */
		   0x00, 0x00, 0x00, 0x09, 0x8e, 0x22, 0x45, 0x41,
		   0x9d, 0x4c, 0x21, 0xed, 0xae, 0x82, 0xed, 0x19,			 /*< 16-byte Proximity UUID. */
		   0x00, 0x02,					 	 	 					 /*< 2-byte Major */
		   0x00, handPos_state,					 		 			 /*< 2-byte Hand Position */
		   0x01,						     		 				 /*< 1-byte Power*/
		 };
	    aci_gap_update_adv_data(sizeof(service_data), service_data);
	 }
	 HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0x01F4, RTC_WAKEUPCLOCK_RTCCLK_DIV16);		//325ms wake up = 0x028A		250ms = 1F4
	 HAL_SuspendTick();
	 HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}

/* USER CODE END FD */
