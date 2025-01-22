/*
  ******************************************************************************
  * @file    main.c
  * @author  Радиоавионика НИЦ
  * @version V1.0.0
  * @date    07-11-2023
  * @brief   Composite USB UVC CDC
  ******************************************************************************
  */

#include "main.h"
#include "usb_device.h"
#include "string.h"

#define BUFFER_SIZE         ((uint32_t)0x0100)

uint32_t aTxBuffer[256];
uint32_t aRxBuffer[256];

void SystemClock_Config(void);
void Error_Handler(void);

extern uint8_t CDC_Transmit_HS(uint8_t* Buf, uint16_t Len);

volatile uint8_t ColorImage = 0x90;
//uint8_t tmp[3] = {1,2,3};
uint32_t uwIndex = 0;
uint32_t tmp=0;

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DCMI_Init();
  MX_FMC_Init();
  MX_USART2_UART_Init();
  USB_DeviceInit();

  SDRAM_Init();

  USART_StartIT(eUSART2, IT_IDLE);

  CameraInit();

  while(1)
    {

      if(GrabCamFrame()==0)
	SendCommandToCameraAndParseResponse();

    }

  return 0;
}

/*HCLK=180MHz*/
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

//void Error_Handler(void)
//{
//  __disable_irq();
//  while (1)
//  {
//
//  }
//}
