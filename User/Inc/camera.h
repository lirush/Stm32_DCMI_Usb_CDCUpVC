#ifndef __CAMERA_H
#define __CAMERA_H

#include <stdint.h>
//#include "jpegenc.h"

#define FRAMENUMBUFFS	(2)
#define FRAMELINES			(480)
#define FRAMECOLS			(640)
#define FRAMESIZEWORDS	(FRAMELINES * FRAMECOLS)		//размер фрейма в uint16

enum ADDRBUF
{
	BUFF0=0,
	BUFF1=1
};

enum CMD
{
	CAM_EN,
	CAM_DIS,
	CAM_INIT,
	CAM_DIG_VIDEO_OUT,
	CAM_SYCH_MODE_EN,
	CAM_DATA_CHG_EDGE,
	CAM_CONTRAST_ADV,
	CAM_DRVF,
	CAM_DRVN,
	CAM_DRVS,
	CAM_TWEAK
};

typedef struct{
	uint8_t State;						//enable or disable
	uint8_t CmdFrameComplit;			//exec cmd
	uint32_t AddrBufFrame;
	volatile uint8_t FlagFrameBufFull;
	volatile uint8_t FlagFrameComplit;
	uint8_t FlagFrameTrans;
	uint32_t cntBufFrame;
	uint8_t NumBuffs;					//number of buffers
	char *pBufCmdResponse;
	char *pBufCmdReceived;
	uint16_t ResponseSize;
	uint16_t CmdSize;
	volatile uint8_t FlagCmdResponse;
	volatile uint8_t FlagCmdReceived;
	void (* Start) (void);
	void (* Init) (void);
}CameraTypeDef;

extern CameraTypeDef CameraTV;

typedef struct{
	uint32_t Addr;
	uint8_t FlagFull;
}BufferTypeDef;
extern BufferTypeDef CamBuff[2];

extern CameraTypeDef Camera;

#endif
