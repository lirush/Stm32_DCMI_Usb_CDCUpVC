#include "periph.h"

UART_HandleTypeDef huart2;
UART_BoxTypeDef buart2;

uint8_t Uart2ReceiveData[UART_RECEIVE_DATA_MAX]={0};
uint8_t Uart2TransmitData[UART_TRANSMIT_DATA_MAX]={0};

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
 if(huart->Instance==USART2)
  {

    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PD6     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

  }

}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
 if(huart->Instance==USART2)
  {

    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PD6     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_6);

    /* USART2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);

  }

}

void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 57600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
buart2.nUart = eUSART2;
buart2.State = RX_FREE;
}

void USART_StartIT(eUART_DesignationTypeDef nuart, eUART_IntTypeDef it)
{
  if(nuart == eUSART2)
    {
      if(it ==IT_IDLE)
	{
	  HAL_UARTEx_ReceiveToIdle_IT(&huart2,Uart2ReceiveData,sizeof(Uart2ReceiveData));
	}
      else if(it==  IT_RXNE)
	{
	  HAL_UART_Receive_IT(&huart2,Uart2ReceiveData,sizeof(Uart2ReceiveData));
	}
      if(it == IT_TXE)
	{
	  HAL_UART_Transmit_IT(&huart2,Uart2TransmitData,sizeof(Uart2TransmitData));
	}
    }
}

void USART2_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart2);

}
