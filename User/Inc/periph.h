#ifndef __PERIPH_H
#define  __PERIPH_H

#include "stm32f4xx_hal.h"

/*----------------------GPIO Setting-------------------*/
#define LED_BLUE1_PORT				(GPIOC)
#define LED_BLUE1_Pin					(GPIO_PIN_4)
#define LED_GREEN_PORT				(GPIOC)
#define LED_GREEN_Pin					(GPIO_PIN_5)
#define CAM_ISPW_GPIO_Port 			(GPIOB)
#define CAM_ISPW_Pin 					(GPIO_PIN_2)
#define LED_BLUE2_PORT				(GPIOA)
#define LED_BLUE2_PIN					(GPIO_PIN_4)
#define LED_WHITE_GPIO_Port 			(GPIOA)
#define LED_WHITE_Pin 					(GPIO_PIN_7)
#define CAM_EN_GPIO_Port 				(GPIOH)
#define CAM_EN_Pin 						(GPIO_PIN_13)
#define MOT_SW2_GPIO_Port 			(GPIOI)
#define MOT_SW2_Pin 					(GPIO_PIN_4)
#define MOT_SW1_GPIO_Port 			(GPIOI)
#define MOT_SW1_Pin 					(GPIO_PIN_5)
#define MOT_CONTROL_1_GPIO_Port 	(GPIOI)
#define MOT_CONTROL_1_Pin 			(GPIO_PIN_6)
#define MOT_CONTROL_2_GPIO_Port 	(GPIOI)
#define MOT_CONTROL_2_Pin 			(GPIO_PIN_7)
/*----------------------GPIO Setting-------------------*/

/*----------------------SDRAM Setting-------------------*/
#define SDRAM_BANK_ADDR                 ((uint32_t)0xC0000000)
#define WRITE_READ_ADDR     			((uint32_t)0x0000)

/* #define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_8 */
#define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_16

/* #define SDCLOCK_PERIOD                   FMC_SDRAM_CLOCK_PERIOD_2 */
#define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3

#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)
/*----------------------SDRAM Setting-------------------*/

/*---------------------UARTSetting begin------------------------------*/
  #define	UART_RECEIVE_DATA_MAX					(55)
#define	UART_TRANSMIT_DATA_MAX				(55)
/*---------------------UARTSetting end------------------------------*/

/*---------------------UARTbegin------------------------------*/
typedef enum{
  eUSART1=1,
  eUSART2,
  eUSART3,
  eUART4,
  eUART5,
  eUSART6,
  eUART7,
  eUART8
}eUART_DesignationTypeDef;

typedef enum{
  IT_PE,
  IT_TXE,
  IT_TC,
  IT_RXNE,
  IT_IDLE,
  IT_LBD,
  IT_CTS,
  IT_ERR
}eUART_IntTypeDef;

typedef enum{
  RX_FREE,
  RX_BUSY
}eUART_StateTypeDef;

typedef struct{
  eUART_DesignationTypeDef	nUart;
  eUART_IntTypeDef			It;
  uint8_t 					State;
  uint8_t						FlagReceived;
}UART_BoxTypeDef;

/*---------------------UARTend------------------------------*/

void MX_GPIO_Init(void);
void MX_DCMI_Init(void);
void MX_USART2_UART_Init(void);
void MX_DMA_Init(void);
void MX_FMC_Init(void);
void SDRAM_Init(void);
void USART_StartIT(eUART_DesignationTypeDef nuart, uint8_t it);

void CameraInit(void);
void SendCommandToCameraAndParseResponse(void);
uint8_t GrabCamFrame(void);
void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset);

void Error_Handler(void);

/*---------------------UARTData begin------------------------------*/
extern UART_HandleTypeDef huart2;
extern UART_BoxTypeDef buart2;
/*---------------------UARTData end------------------------------*/

#endif
