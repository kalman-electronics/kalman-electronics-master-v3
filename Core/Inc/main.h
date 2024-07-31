/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define PC_ON_Pin GPIO_PIN_13
#define PC_ON_GPIO_Port GPIOC
#define PC_RESET_Pin GPIO_PIN_14
#define PC_RESET_GPIO_Port GPIOC
#define ADC_24V_Pin GPIO_PIN_0
#define ADC_24V_GPIO_Port GPIOC
#define ADC_5V_Pin GPIO_PIN_1
#define ADC_5V_GPIO_Port GPIOC
#define ADC_3V3_Pin GPIO_PIN_2
#define ADC_3V3_GPIO_Port GPIOC
#define RS422_TX_Pin GPIO_PIN_2
#define RS422_TX_GPIO_Port GPIOA
#define RS422_RX_Pin GPIO_PIN_3
#define RS422_RX_GPIO_Port GPIOA
#define SATEL_TX_Pin GPIO_PIN_4
#define SATEL_TX_GPIO_Port GPIOC
#define SATEL_RX_Pin GPIO_PIN_5
#define SATEL_RX_GPIO_Port GPIOC
#define RS422_DE_Pin GPIO_PIN_1
#define RS422_DE_GPIO_Port GPIOB
#define RS422_RE_Pin GPIO_PIN_2
#define RS422_RE_GPIO_Port GPIOB
#define PC_RX_Pin GPIO_PIN_10
#define PC_RX_GPIO_Port GPIOB
#define PC_TX_Pin GPIO_PIN_11
#define PC_TX_GPIO_Port GPIOB
#define TCAN2_CS_Pin GPIO_PIN_14
#define TCAN2_CS_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_6
#define SCL_GPIO_Port GPIOC
#define SDA_Pin GPIO_PIN_7
#define SDA_GPIO_Port GPIOC
#define SATEL_REB_Pin GPIO_PIN_11
#define SATEL_REB_GPIO_Port GPIOA
#define SATEL_DE_Pin GPIO_PIN_12
#define SATEL_DE_GPIO_Port GPIOA
#define TCAN_CS_Pin GPIO_PIN_15
#define TCAN_CS_GPIO_Port GPIOA
#define WIFI_TX_Pin GPIO_PIN_3
#define WIFI_TX_GPIO_Port GPIOB
#define WIFI_RX_Pin GPIO_PIN_4
#define WIFI_RX_GPIO_Port GPIOB
#define WIFI_EN_Pin GPIO_PIN_5
#define WIFI_EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
