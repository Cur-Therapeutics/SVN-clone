/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32u5xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                    /**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{

  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
  * @brief DMA2D MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hdma2d: DMA2D handle pointer
  * @retval None
  */
void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef* hdma2d)
{
  if(hdma2d->Instance==DMA2D)
  {
    /* USER CODE BEGIN DMA2D_MspInit 0 */

    /* USER CODE END DMA2D_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_DMA2D_CLK_ENABLE();
    /* USER CODE BEGIN DMA2D_MspInit 1 */

    /* USER CODE END DMA2D_MspInit 1 */

  }

}

/**
  * @brief DMA2D MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hdma2d: DMA2D handle pointer
  * @retval None
  */
void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef* hdma2d)
{
  if(hdma2d->Instance==DMA2D)
  {
    /* USER CODE BEGIN DMA2D_MspDeInit 0 */

    /* USER CODE END DMA2D_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DMA2D_CLK_DISABLE();
    /* USER CODE BEGIN DMA2D_MspDeInit 1 */

    /* USER CODE END DMA2D_MspDeInit 1 */
  }

}

/**
  * @brief I2C MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hi2c->Instance==I2C1)
  {
    /* USER CODE BEGIN I2C1_MspInit 0 */

    /* USER CODE END I2C1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
    PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB7     ------> I2C1_SDA
    PB6     ------> I2C1_SCL
    */
    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
    /* USER CODE BEGIN I2C1_MspInit 1 */

    /* USER CODE END I2C1_MspInit 1 */

  }

}

/**
  * @brief I2C MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C1)
  {
    /* USER CODE BEGIN I2C1_MspDeInit 0 */

    /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB7     ------> I2C1_SDA
    PB6     ------> I2C1_SCL
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    /* USER CODE BEGIN I2C1_MspDeInit 1 */

    /* USER CODE END I2C1_MspDeInit 1 */
  }

}

/**
  * @brief LTDC MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hltdc: LTDC handle pointer
  * @retval None
  */
void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hltdc->Instance==LTDC)
  {
    /* USER CODE BEGIN LTDC_MspInit 0 */

    /* USER CODE END LTDC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInit.LtdcClockSelection = RCC_LTDCCLKSOURCE_PLL2;
    PeriphClkInit.PLL2.PLL2Source = RCC_PLLSOURCE_MSI;
    PeriphClkInit.PLL2.PLL2M = 12;
    PeriphClkInit.PLL2.PLL2N = 50;
    PeriphClkInit.PLL2.PLL2P = 2;
    PeriphClkInit.PLL2.PLL2Q = 4;
    PeriphClkInit.PLL2.PLL2R = 20;
    PeriphClkInit.PLL2.PLL2RGE = RCC_PLLVCIRANGE_0;
    PeriphClkInit.PLL2.PLL2FRACN = 0;
    PeriphClkInit.PLL2.PLL2ClockOut = RCC_PLL2_DIVR;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PE0     ------> LTDC_HSYNC
    PD3     ------> LTDC_CLK
    PE4     ------> LTDC_B0
    PE1     ------> LTDC_VSYNC
    PC7     ------> LTDC_R1
    PD6     ------> LTDC_DE
    PD1     ------> LTDC_B5
    PC6     ------> LTDC_R0
    PE5     ------> LTDC_G0
    PD0     ------> LTDC_B4
    PE6     ------> LTDC_G1
    PD15     ------> LTDC_B3
    PD11     ------> LTDC_R6
    PF13     ------> LTDC_B1
    PE8     ------> LTDC_B7
    PE13     ------> LTDC_G6
    PD12     ------> LTDC_R7
    PE7     ------> LTDC_B6
    PE15     ------> LTDC_R2
    PE12     ------> LTDC_G5
    PD8     ------> LTDC_R3
    PD14     ------> LTDC_B2
    PE9     ------> LTDC_G2
    PE10     ------> LTDC_G3
    PE11     ------> LTDC_G4
    PD10     ------> LTDC_R5
    PD9     ------> LTDC_R4
    PE14     ------> LTDC_G7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_1|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_13|GPIO_PIN_7
                          |GPIO_PIN_15|GPIO_PIN_12|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_LTDC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_15
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_8|GPIO_PIN_14
                          |GPIO_PIN_10|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_LTDC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_LTDC;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_LTDC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_LTDC;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
    /* USER CODE BEGIN LTDC_MspInit 1 */

    /* USER CODE END LTDC_MspInit 1 */

  }

}

/**
  * @brief LTDC MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hltdc: LTDC handle pointer
  * @retval None
  */
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc)
{
  if(hltdc->Instance==LTDC)
  {
    /* USER CODE BEGIN LTDC_MspDeInit 0 */

    /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PE0     ------> LTDC_HSYNC
    PD3     ------> LTDC_CLK
    PE4     ------> LTDC_B0
    PE1     ------> LTDC_VSYNC
    PC7     ------> LTDC_R1
    PD6     ------> LTDC_DE
    PD1     ------> LTDC_B5
    PC6     ------> LTDC_R0
    PE5     ------> LTDC_G0
    PD0     ------> LTDC_B4
    PE6     ------> LTDC_G1
    PD15     ------> LTDC_B3
    PD11     ------> LTDC_R6
    PF13     ------> LTDC_B1
    PE8     ------> LTDC_B7
    PE13     ------> LTDC_G6
    PD12     ------> LTDC_R7
    PE7     ------> LTDC_B6
    PE15     ------> LTDC_R2
    PE12     ------> LTDC_G5
    PD8     ------> LTDC_R3
    PD14     ------> LTDC_B2
    PE9     ------> LTDC_G2
    PE10     ------> LTDC_G3
    PE11     ------> LTDC_G4
    PD10     ------> LTDC_R5
    PD9     ------> LTDC_R4
    PE14     ------> LTDC_G7
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_1|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_13|GPIO_PIN_7
                          |GPIO_PIN_15|GPIO_PIN_12|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_14);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_1|GPIO_PIN_0
                          |GPIO_PIN_15|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_8
                          |GPIO_PIN_14|GPIO_PIN_10|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_7|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_13);

    /* LTDC interrupt DeInit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
    /* USER CODE BEGIN LTDC_MspDeInit 1 */

    /* USER CODE END LTDC_MspDeInit 1 */
  }

}

static uint32_t HAL_RCC_OSPIM_CLK_ENABLED=0;

/**
  * @brief OSPI MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hospi: OSPI handle pointer
  * @retval None
  */
void HAL_OSPI_MspInit(OSPI_HandleTypeDef* hospi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hospi->Instance==OCTOSPI1)
  {
    /* USER CODE BEGIN OCTOSPI1_MspInit 0 */

    /* USER CODE END OCTOSPI1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
    PeriphClkInit.OspiClockSelection = RCC_OSPICLKSOURCE_SYSCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    HAL_RCC_OSPIM_CLK_ENABLED++;
    if(HAL_RCC_OSPIM_CLK_ENABLED==1){
      __HAL_RCC_OSPIM_CLK_ENABLE();
    }
    __HAL_RCC_OSPI1_CLK_ENABLE();

    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**OCTOSPI1 GPIO Configuration
    PG15     ------> OCTOSPIM_P2_DQS
    PG12     ------> OCTOSPIM_P2_NCS
    PG9     ------> OCTOSPIM_P2_IO6
    PG10     ------> OCTOSPIM_P2_IO7
    PH6     ------> OCTOSPIM_P2_CLK
    PH8     ------> OCTOSPIM_P2_IO3
    PF0     ------> OCTOSPIM_P2_IO0
    PF2     ------> OCTOSPIM_P2_IO2
    PF1     ------> OCTOSPIM_P2_IO1
    PH10     ------> OCTOSPIM_P2_IO5
    PH9     ------> OCTOSPIM_P2_IO4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_12|GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_OCTOSPI2;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_OCTOSPI2;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_OCTOSPI2;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /* OCTOSPI1 interrupt Init */
    HAL_NVIC_SetPriority(OCTOSPI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OCTOSPI1_IRQn);
    /* USER CODE BEGIN OCTOSPI1_MspInit 1 */

    /* USER CODE END OCTOSPI1_MspInit 1 */
  }
  else if(hospi->Instance==OCTOSPI2)
  {
    /* USER CODE BEGIN OCTOSPI2_MspInit 0 */

    /* USER CODE END OCTOSPI2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
    PeriphClkInit.OspiClockSelection = RCC_OSPICLKSOURCE_SYSCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    HAL_RCC_OSPIM_CLK_ENABLED++;
    if(HAL_RCC_OSPIM_CLK_ENABLED==1){
      __HAL_RCC_OSPIM_CLK_ENABLE();
    }
    __HAL_RCC_OSPI2_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**OCTOSPI2 GPIO Configuration
    PD4     ------> OCTOSPIM_P1_IO4
    PD5     ------> OCTOSPIM_P1_IO5
    PD7     ------> OCTOSPIM_P1_IO7
    PF10     ------> OCTOSPIM_P1_CLK
    PF7     ------> OCTOSPIM_P1_IO2
    PF9     ------> OCTOSPIM_P1_IO1
    PF6     ------> OCTOSPIM_P1_IO3
    PF8     ------> OCTOSPIM_P1_IO0
    PA2     ------> OCTOSPIM_P1_NCS
    PC3     ------> OCTOSPIM_P1_IO6
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_OCTOSPI1;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_6|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* OCTOSPI2 interrupt Init */
    HAL_NVIC_SetPriority(OCTOSPI2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OCTOSPI2_IRQn);
    /* USER CODE BEGIN OCTOSPI2_MspInit 1 */

    /* USER CODE END OCTOSPI2_MspInit 1 */
  }

}

/**
  * @brief OSPI MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hospi: OSPI handle pointer
  * @retval None
  */
void HAL_OSPI_MspDeInit(OSPI_HandleTypeDef* hospi)
{
  if(hospi->Instance==OCTOSPI1)
  {
    /* USER CODE BEGIN OCTOSPI1_MspDeInit 0 */

    /* USER CODE END OCTOSPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_OSPIM_CLK_ENABLED--;
    if(HAL_RCC_OSPIM_CLK_ENABLED==0){
      __HAL_RCC_OSPIM_CLK_DISABLE();
    }
    __HAL_RCC_OSPI1_CLK_DISABLE();

    /**OCTOSPI1 GPIO Configuration
    PG15     ------> OCTOSPIM_P2_DQS
    PG12     ------> OCTOSPIM_P2_NCS
    PG9     ------> OCTOSPIM_P2_IO6
    PG10     ------> OCTOSPIM_P2_IO7
    PH6     ------> OCTOSPIM_P2_CLK
    PH8     ------> OCTOSPIM_P2_IO3
    PF0     ------> OCTOSPIM_P2_IO0
    PF2     ------> OCTOSPIM_P2_IO2
    PF1     ------> OCTOSPIM_P2_IO1
    PH10     ------> OCTOSPIM_P2_IO5
    PH9     ------> OCTOSPIM_P2_IO4
    */
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_15|GPIO_PIN_12|GPIO_PIN_9|GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_1);

    /* OCTOSPI1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(OCTOSPI1_IRQn);
    /* USER CODE BEGIN OCTOSPI1_MspDeInit 1 */

    /* USER CODE END OCTOSPI1_MspDeInit 1 */
  }
  else if(hospi->Instance==OCTOSPI2)
  {
    /* USER CODE BEGIN OCTOSPI2_MspDeInit 0 */

    /* USER CODE END OCTOSPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_OSPIM_CLK_ENABLED--;
    if(HAL_RCC_OSPIM_CLK_ENABLED==0){
      __HAL_RCC_OSPIM_CLK_DISABLE();
    }
    __HAL_RCC_OSPI2_CLK_DISABLE();

    /**OCTOSPI2 GPIO Configuration
    PD4     ------> OCTOSPIM_P1_IO4
    PD5     ------> OCTOSPIM_P1_IO5
    PD7     ------> OCTOSPIM_P1_IO7
    PF10     ------> OCTOSPIM_P1_CLK
    PF7     ------> OCTOSPIM_P1_IO2
    PF9     ------> OCTOSPIM_P1_IO1
    PF6     ------> OCTOSPIM_P1_IO3
    PF8     ------> OCTOSPIM_P1_IO0
    PA2     ------> OCTOSPIM_P1_NCS
    PC3     ------> OCTOSPIM_P1_IO6
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10|GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_6
                          |GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_3);

    /* OCTOSPI2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(OCTOSPI2_IRQn);
    /* USER CODE BEGIN OCTOSPI2_MspDeInit 1 */

    /* USER CODE END OCTOSPI2_MspDeInit 1 */
  }

}

/**
  * @brief RTC MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hrtc: RTC handle pointer
  * @retval None
  */
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hrtc->Instance==RTC)
  {
    /* USER CODE BEGIN RTC_MspInit 0 */

    /* USER CODE END RTC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_RTC_ENABLE();
    __HAL_RCC_RTCAPB_CLK_ENABLE();
    __HAL_RCC_RTCAPB_CLKAM_ENABLE();
    /* USER CODE BEGIN RTC_MspInit 1 */

    /* USER CODE END RTC_MspInit 1 */

  }

}

/**
  * @brief RTC MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hrtc: RTC handle pointer
  * @retval None
  */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
  if(hrtc->Instance==RTC)
  {
    /* USER CODE BEGIN RTC_MspDeInit 0 */

    /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
    __HAL_RCC_RTCAPB_CLK_DISABLE();
    __HAL_RCC_RTCAPB_CLKAM_DISABLE();
    /* USER CODE BEGIN RTC_MspDeInit 1 */

    /* USER CODE END RTC_MspDeInit 1 */
  }

}

/**
  * @brief SPI MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hspi->Instance==SPI2)
  {
    /* USER CODE BEGIN SPI2_MspInit 0 */

    /* USER CODE END SPI2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SPI2;
    PeriphClkInit.Spi2ClockSelection = RCC_SPI2CLKSOURCE_SYSCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    /**SPI2 GPIO Configuration
    PA9     ------> SPI2_SCK
    PI2     ------> SPI2_MISO
    PI3     ------> SPI2_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_SPI2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /* USER CODE BEGIN SPI2_MspInit 1 */

    /* USER CODE END SPI2_MspInit 1 */

  }

}

/**
  * @brief SPI MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
  if(hspi->Instance==SPI2)
  {
    /* USER CODE BEGIN SPI2_MspDeInit 0 */

    /* USER CODE END SPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();

    /**SPI2 GPIO Configuration
    PA9     ------> SPI2_SCK
    PI2     ------> SPI2_MISO
    PI3     ------> SPI2_MOSI
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_2|GPIO_PIN_3);

    /* USER CODE BEGIN SPI2_MspDeInit 1 */

    /* USER CODE END SPI2_MspDeInit 1 */
  }

}

/**
  * @brief TIM_Base MSP Initialization
  * This function configures the hardware resources used in this example
  * @param htim_base: TIM_Base handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM8)
  {
    /* USER CODE BEGIN TIM8_MspInit 0 */

    /* USER CODE END TIM8_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM8_CLK_ENABLE();
    /* USER CODE BEGIN TIM8_MspInit 1 */

    /* USER CODE END TIM8_MspInit 1 */

  }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim->Instance==TIM8)
  {
    /* USER CODE BEGIN TIM8_MspPostInit 0 */

    /* USER CODE END TIM8_MspPostInit 0 */

    __HAL_RCC_GPIOI_CLK_ENABLE();
    /**TIM8 GPIO Configuration
    PI5     ------> TIM8_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /* USER CODE BEGIN TIM8_MspPostInit 1 */

    /* USER CODE END TIM8_MspPostInit 1 */
  }

}
/**
  * @brief TIM_Base MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param htim_base: TIM_Base handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM8)
  {
    /* USER CODE BEGIN TIM8_MspDeInit 0 */

    /* USER CODE END TIM8_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM8_CLK_DISABLE();
    /* USER CODE BEGIN TIM8_MspDeInit 1 */

    /* USER CODE END TIM8_MspDeInit 1 */
  }

}

/**
  * @brief UART MSP Initialization
  * This function configures the hardware resources used in this example
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(huart->Instance==UART4)
  {
    /* USER CODE BEGIN UART4_MspInit 0 */

    /* USER CODE END UART4_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_UART4;
    PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_UART4_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**UART4 GPIO Configuration
    PA0     ------> UART4_TX
    PA1     ------> UART4_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* UART4 interrupt Init */
    HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);
    /* USER CODE BEGIN UART4_MspInit 1 */

    /* USER CODE END UART4_MspInit 1 */

  }

}

/**
  * @brief UART MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==UART4)
  {
    /* USER CODE BEGIN UART4_MspDeInit 0 */

    /* USER CODE END UART4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART4_CLK_DISABLE();

    /**UART4 GPIO Configuration
    PA0     ------> UART4_TX
    PA1     ------> UART4_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1);

    /* UART4 interrupt DeInit */
    HAL_NVIC_DisableIRQ(UART4_IRQn);
    /* USER CODE BEGIN UART4_MspDeInit 1 */

    /* USER CODE END UART4_MspDeInit 1 */
  }

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
