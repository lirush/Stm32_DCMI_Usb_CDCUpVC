#include "camera.h"
#include "string.h"
#include "main.h"

#define LINEFEED	(0x0A)
#define ENDL		(0x0d)

CameraTypeDef Camera;		//TV - thermal imager
CameraTypeDef *pcamera = &Camera;
char ResponseCmdFromCam[50];
char ReceiveCmdToCam[50];
char ok[3] = "ok\r";
static uint8_t CamTweak=1;

volatile uint16_t vLineCntFrame=0;
//BufferTypeDef CamBuff[2];
//uint8_t* line_buffer;
//uint32_t AddrBuf[FRAMENUMBUFFS] = {0xc0000000,0xc00ca800};

extern uint8_t Uart2ReceiveData[UART_RECEIVE_DATA_MAX];

extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart2;
extern DCMI_HandleTypeDef hdcmi;
extern DMA_HandleTypeDef hdma_dcmi;
//extern TIM_HandleTypeDef htim7;

//see Astir2 User Guide.
char *Cmd[11]={
		"cam power\r",
		"cam dispower\r",
		"cam init\r",
		"video output 18\r",	//page 33. Register 0x7D
		"rw 99 129\r",
		"rw 68 0\r",
		"bc mode 3\r",
		"cam drvf\r",
		"cam drvn\r",
		"cam drvs\r",
		"cam tweak\r"
};
extern char ReceiveCmd[50];

void CameraStart(void)
{
	HAL_UART_Transmit(&huart2,(uint8_t *)Cmd[CAM_SYCH_MODE_EN],strlen(Cmd[CAM_SYCH_MODE_EN]),100);
	HAL_Delay(40);
	HAL_UART_Transmit(&huart2,(uint8_t *)Cmd[CAM_DIG_VIDEO_OUT],strlen(Cmd[CAM_DIG_VIDEO_OUT]),100);
}

void CameraInit(void)
{
	pcamera->pBufCmdResponse = ResponseCmdFromCam;
	pcamera->pBufCmdReceived = ReceiveCmdToCam;
	pcamera->Start = CameraStart;
}

static void ResponseToCmd(char *str1, char *str2, uint8_t size)
{
	memcpy(str1+strlen(str1),str2,size);
	CDC_Transmit_HS((uint8_t *)str1,strlen(str1));
}

uint8_t ParseResponseToCmd(void)
{
	char temp[50] = "Done ";
	if(strcmp(Cmd[CAM_EN],pcamera->pBufCmdReceived)==0)
	{
		if(!(CAM_EN_GPIO_Port->ODR & CAM_EN_Pin))
		{
			CAM_EN_GPIO_Port->ODR |=CAM_EN_Pin;
			if(CAM_EN_GPIO_Port->ODR & CAM_EN_Pin)
			{
				CAM_ISPW_GPIO_Port->ODR |= CAM_ISPW_Pin;
			}
		}
		ResponseToCmd(temp,Cmd[CAM_EN],strlen(Cmd[CAM_EN]));
		pcamera->CmdFrameComplit = CAM_EN;
		return 1;
	}
	if(strcmp(Cmd[CAM_DIS],pcamera->pBufCmdReceived)==0)
	{
		if((CAM_EN_GPIO_Port->ODR & CAM_EN_Pin))
		{
			CAM_EN_GPIO_Port->ODR &= ~CAM_EN_Pin;
			if(!(CAM_EN_GPIO_Port->ODR & CAM_EN_Pin))
			{
				CAM_ISPW_GPIO_Port->ODR &= ~CAM_ISPW_Pin;
			}
		}
		ResponseToCmd(temp,Cmd[CAM_DIS],strlen(Cmd[CAM_DIS]));
		pcamera->CmdFrameComplit = CAM_DIS;
		pcamera->FlagFrameComplit=0;
		return 1;
	}
	if(strcmp(Cmd[CAM_INIT],pcamera->pBufCmdReceived)==0)
	{
		pcamera->Start();
		ResponseToCmd(temp,Cmd[CAM_INIT],strlen(Cmd[CAM_INIT]));
		pcamera->CmdFrameComplit = CAM_INIT;
		HAL_Delay(4);
		return 1;
	}
	if(strcmp(Cmd[CAM_TWEAK],pcamera->pBufCmdReceived)==0)
	  {
		pcamera->Start();
		ResponseToCmd(temp,Cmd[CAM_TWEAK],strlen(Cmd[CAM_TWEAK]));
		pcamera->CmdFrameComplit = CAM_INIT;
		HAL_Delay(CamTweak++);
		return 1;
	  }
	if(strcmp(Cmd[CAM_DRVF],pcamera->pBufCmdReceived)==0)
	{
		if(MOT_CONTROL_2_GPIO_Port->IDR & MOT_CONTROL_2_Pin)
		{
			MOT_CONTROL_2_GPIO_Port->ODR &= ~MOT_CONTROL_2_Pin;
		}
		MOT_CONTROL_1_GPIO_Port->ODR |= MOT_CONTROL_1_Pin;
		return 1;
	}
	if(strcmp(Cmd[CAM_DRVN],pcamera->pBufCmdReceived)==0)
	{
		if(MOT_CONTROL_1_GPIO_Port->IDR & MOT_CONTROL_1_Pin)
		{
			MOT_CONTROL_1_GPIO_Port->ODR &= ~MOT_CONTROL_1_Pin;
		}
		MOT_CONTROL_2_GPIO_Port->ODR |= MOT_CONTROL_2_Pin;
		return 1;
	}
	if(strcmp(Cmd[CAM_DRVS],pcamera->pBufCmdReceived)==0)
	{
		if(MOT_CONTROL_1_GPIO_Port->IDR & MOT_CONTROL_1_Pin)
		{
			MOT_CONTROL_1_GPIO_Port->ODR &= ~MOT_CONTROL_1_Pin;
		}
		if(MOT_CONTROL_2_GPIO_Port->IDR & MOT_CONTROL_2_Pin)
		{
			MOT_CONTROL_2_GPIO_Port->ODR &= ~MOT_CONTROL_2_Pin;
		}
		return 1;
	}
	return 0;
}

uint8_t GrabCamFrame(void)
{
	CameraTypeDef *ptr = &Camera;
	if(ptr->FlagFrameTrans)return 0;												//this means the frame is sent via uvc. you can parse cmd.
	if(ptr->CmdFrameComplit == CAM_INIT)
	{
			HAL_DCMI_Start_DMA(&hdcmi,DCMI_MODE_CONTINUOUS,SDRAM_BANK_ADDR,FRAMESIZEWORDS);
			while(pcamera->FlagFrameComplit==0)
			{
			    ;
			}
			GPIOC->ODR |= (1<<5);
			ptr->FlagFrameTrans=1;
			pcamera->FlagFrameComplit=0;
	}
	return ptr->FlagFrameTrans;
}

void HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi)
{
//	if(vLineCntFrame++ ==FRAMELINES)
//	{
//		HAL_DCMI_Stop(hdcmi);
//
//		vLineCntFrame=0;
//
//		for(uint8_t num=0; num<FRAMENUMBUFFS; num++)
//		{
//			if(pCameraTV->AddrBufFrame == AddrBuf[num])
//			{
//				pCameraTV->FlagFrameBufFull |= (1<<num);
//				if(!(pCameraTV->FlagBusy & (1<<(num^0x01))))
//					pCameraTV->AddrBufFrame = AddrBuf[num^0x01];
//				break;
//			}
//		}
//		GPIOC->ODR ^= (1<<5);
//		HAL_DCMI_Start_DMA(hdcmi,DCMI_MODE_CONTINUOUS,(uint32_t)pCameraTV->AddrBufFrame,307200);
//	}
	if(vLineCntFrame++ ==FRAMELINES)
	{
//		HAL_DCMI_Suspend(hdcmi);
//		HAL_DCMI_Stop(hdcmi);
		__HAL_DCMI_DISABLE(hdcmi);						//this is not safe stop DCMI over DMA, but allows the frame to be stable
		HAL_DMA_Abort(hdcmi->DMA_Handle);
		vLineCntFrame=0;
//		HAL_TIM_Base_Stop_IT(&htim7);
		pcamera->FlagFrameComplit =1;
	}
}

//static volatile uint8_t CntTimTick=0;
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//  if(htim->Instance == TIM7)
//  {
//	if(!(DCMI->CR & (1<<14)))							//if dcmi is not enable -> enable
//	{
//
////		if(CntTimTick++>=5)
//		{
//			LED_WHITE_GPIO_Port->ODR |= (1<<7);
////			CntTimTick=0;
//			HAL_DCMI_Start_DMA(&hdcmi,DCMI_MODE_CONTINUOUS,SDRAM_BANK_ADDR,307200);
//		}
//	}
//  }
//}

void SendCommandToCameraAndParseResponse(void)
{
	if(pcamera->FlagCmdReceived)
	{
		if(ParseResponseToCmd()==0)
		{
			HAL_UART_Transmit(&huart2,(uint8_t *)pcamera->pBufCmdReceived, strlen(pcamera->pBufCmdReceived),100);
		}
		memset(pcamera->pBufCmdReceived,0x00,strlen(pcamera->pBufCmdReceived));
		pcamera->FlagCmdReceived=0;
	}
	if(pcamera->FlagCmdResponse)
	{
		//hardcoding: the command "read config\r" answers not correct. the bytes 0x21 0x20 must be 0x10 0x13 to the manual. now there is zero
		uint8_t len = 0;
		if(*(uint32_t *)(pcamera->pBufCmdResponse+16)==0x12345678)	// 0x12345678 is bytes number 4-7 Astir2 User Guide
			len = 34 + sizeof("read config\r");
		else len = strlen(pcamera->pBufCmdResponse);
//		if(pcamera->CmdFrameComplit == CAM_INIT)
//		  CDC_Transmit_HS((uint8_t *)ok,strlen(ok));
//		else
		  CDC_Transmit_HS((uint8_t *)pcamera->pBufCmdResponse,len);
		memset(pcamera->pBufCmdResponse,0x00,strlen(pcamera->pBufCmdResponse));
		pcamera->FlagCmdResponse=0;
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if(huart->Instance == USART2)
    {
      memcpy((void *)pcamera->pBufCmdResponse+pcamera->ResponseSize, Uart2ReceiveData, Size);
      pcamera->ResponseSize += Size;

      USART_StartIT(eUSART2, IT_IDLE);

      //hardcoding: the command "read config\r" answers not correct. the bytes 0x21 0x20 must be 0x10 0x13 to the manual. now there is zero
      if(((pcamera->pBufCmdResponse[pcamera->ResponseSize-1]==LINEFEED) \
	  && (pcamera->pBufCmdResponse[pcamera->ResponseSize-2]==ENDL)) || (*(uint32_t *)(pcamera->pBufCmdResponse+16)==0x12345678)) // 0x12345678 is bytes number 4-7 Astir2 User Guide
      {
	  pcamera->FlagCmdResponse=1;
	  pcamera->ResponseSize = 0;
      }
    }
}

void CDC_ReceiveCallback_HS(uint8_t* Buf, uint32_t *Len)
{
  	static uint8_t cnt=0;
  	uint32_t len = *Len;
  	if(pcamera->FlagCmdReceived==0)
  	{
	    memcpy((void *)pcamera->pBufCmdReceived+cnt,Buf,len);
	    if(pcamera->pBufCmdReceived[cnt]==ENDL)
	    {
		    cnt=0;
		    pcamera->FlagCmdReceived=1;
	    }
	    else cnt +=len;
  	}
}

