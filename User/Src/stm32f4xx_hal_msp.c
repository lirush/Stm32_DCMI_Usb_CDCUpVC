/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32f4xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
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
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
//extern DMA_HandleTypeDef hdma_dcmi;

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
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
//void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
//{
//  if(huart->Instance==UART8)
//  {
//  /* USER CODE BEGIN UART8_MspDeInit 0 */
//
//  /* USER CODE END UART8_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_UART8_CLK_DISABLE();
//
//    /**UART8 GPIO Configuration
//    PE0     ------> UART8_RX
//    PE1     ------> UART8_TX
//    */
//    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0|GPIO_PIN_1);
//
//    /* UART8 interrupt DeInit */
//    HAL_NVIC_DisableIRQ(UART8_IRQn);
//  /* USER CODE BEGIN UART8_MspDeInit 1 */
//
//  /* USER CODE END UART8_MspDeInit 1 */
//  }
//  else if(huart->Instance==USART1)
//  {
//  /* USER CODE BEGIN USART1_MspDeInit 0 */
//
//  /* USER CODE END USART1_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_USART1_CLK_DISABLE();
//
//    /**USART1 GPIO Configuration
//    PA9     ------> USART1_TX
//    PA10     ------> USART1_RX
//    */
//    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);
//
//    /* USART1 interrupt DeInit */
//    HAL_NVIC_DisableIRQ(USART1_IRQn);
//  /* USER CODE BEGIN USART1_MspDeInit 1 */
//
//  /* USER CODE END USART1_MspDeInit 1 */
//  }
//
//}


/* USER CODE END 1 */
