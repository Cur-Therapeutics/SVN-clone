/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32u0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

extern SPI_HandleTypeDef hspi3;

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/**
 * System clock
 */
#define SYS_CLOCK	56000
/**
 * Standard times
 */
#define TICKS_PER_SECOND	1000

/**
 * Firmware version
 */
#define VER_MAJOR	0
#define VER_MINOR	0
#define VER_BUILD	0

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_GREEN_Pin GPIO_PIN_13
#define LED_GREEN_GPIO_Port GPIOC
#define LED_BLUE_Pin GPIO_PIN_5
#define LED_BLUE_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_2
#define LED_RED_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_12
#define OLED_DC_GPIO_Port GPIOD
#define SPI_SELECT_1_Pin GPIO_PIN_4
#define SPI_SELECT_1_GPIO_Port GPIOD
#define OLED_RST_Pin GPIO_PIN_5
#define OLED_RST_GPIO_Port GPIOD
#define OLED_CS_Pin GPIO_PIN_9
#define OLED_CS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
