#include "usbd_uvc.h"
#include "usbd_req.h"
#include "camera.h"

USBD_UVC_HandleTypeDef uvcInstance;

static uint8_t USBD_UVC_Init(void *pdev, uint8_t cfgidx);
static uint8_t USBD_UVC_DeInit(void *pdev, uint8_t cfgidx);
static uint8_t USBD_UVC_Setup(void *pdev, USB_SETUP_REQ  *req);
static uint8_t USBD_UVC_EP0_RxReady(void *pdev);
static uint8_t USBD_UVC_DataIn(void *pdev, uint8_t epnum);
static uint8_t USBD_UVC_DataOut(void *pdev, uint8_t epnum);
static uint8_t USBD_UVC_SOF(void *pdev);
static uint8_t USBD_UVC_IsoINIncomplete(void *pdev);
static uint8_t USBD_UVC_IsoOutIncomplete(void *pdev);
static uint8_t *USBD_UVC_GetCfgDesc(uint8_t speed, uint16_t *length);
static uint8_t *USBD_UVC_GetDeviceQualifierDesc(uint8_t speed, uint16_t *length);

static void UVC_Req_GetCurrent(USB_OTG_CORE_HANDLE *pdev , USB_SETUP_REQ *req);
static void UVC_Req_SetCurrent(USB_OTG_CORE_HANDLE *pdev , USB_SETUP_REQ *req);


USBD_Class_cb_TypeDef  USBD_UVC =
{
  USBD_UVC_Init,
  USBD_UVC_DeInit,
  USBD_UVC_Setup,
  NULL, /*EP0_TxSent*/
  USBD_UVC_EP0_RxReady, /*EP0_RxReady*/
  USBD_UVC_DataIn,
  USBD_UVC_DataOut,
  USBD_UVC_SOF, /*SOF */
  USBD_UVC_IsoINIncomplete,
  USBD_UVC_IsoOutIncomplete,
  USBD_UVC_GetCfgDesc,
  USBD_UVC_GetCfgDesc,
  USBD_UVC_GetCfgDesc,
  USBD_UVC_GetDeviceQualifierDesc
};

__ALIGN_BEGIN uint8_t USBD_UVC_CfgDesc[USB_UVC_CONFIG_DESC_TOTAL_SIZE] __ALIGN_END =
    {
    		  /* Configuration 1 */
    		  USB_CONFIGUARTION_DESC_SIZE,               // bLength                  9
    		  USB_CONFIGURATION_DESCRIPTOR_TYPE,         // bDescriptorType          2
    		#ifndef VIDEO_USES_ISOC_EP
    		  WBVAL((USB_VIDEO_DESC_SIZE-9)),
    		#else
    		  WBVAL(USB_UVC_CONFIG_DESC_TOTAL_SIZE),
    		#endif
    		  0x02,                                      // bNumInterfaces           2
    		  0x01,                                      // bConfigurationValue      1 ID of this configuration
    		  0x00,                                      // iConfiguration           0 no description available
    		  0x80,                   					// bmAttributes          0x80 Bus Powered
    		  USB_CONFIG_POWER_MA(500),                  // bMaxPower              500 mA

    		  /* Interface Association Descriptor */
    		  UVC_INTERFACE_ASSOCIATION_DESC_SIZE,       // bLength                  8
    		  USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE, // bDescriptorType         11
    		  0x00,                                      // bFirstInterface          0
    		  0x02,                                      // bInterfaceCount          2
    		  CC_VIDEO,                                  // bFunctionClass          14 Video
    		  SC_VIDEO_INTERFACE_COLLECTION,             // bFunctionSubClass        3 Video Interface Collection
    		  PC_PROTOCOL_UNDEFINED,                     // bInterfaceProtocol       0 (protocol undefined)
    		  0x02,                                      // iFunction                2

    		  /* VideoControl Interface Descriptor */


    		  /* Standard VC Interface Descriptor  = interface 0 */
    		  USB_INTERFACE_DESC_SIZE,                   // bLength                  9
    		  USB_INTERFACE_DESCRIPTOR_TYPE,             // bDescriptorType          4
    		  USB_UVC_VCIF_NUM,                          // bInterfaceNumber         0 index of this interface (VC)
    		  0x00,                                      // bAlternateSetting        0 index of this setting
    		  0x00,                                      // bNumEndpoints            0 no endpoints
    		  CC_VIDEO,                                  // bInterfaceClass         14 Video
    		  SC_VIDEOCONTROL,                           // bInterfaceSubClass       1 Video Control
    		  PC_PROTOCOL_UNDEFINED,                     // bInterfaceProtocol       0 (protocol undefined)
    		  0x02,                                      // iFunction                2


    		  /* Class-specific VC Interface Descriptor */
    		  UVC_VC_INTERFACE_HEADER_DESC_SIZE(1),      // bLength                 13 12 + 1 (header + 1*interface
    		  CS_INTERFACE,                              // bDescriptorType         36 (INTERFACE)
    		  VC_HEADER,                                 // bDescriptorSubtype      1 (HEADER)
    		  WBVAL(UVC_VERSION),                        // bcdUVC                  1.10 or 1.00
    		  WBVAL(VC_DESC_TOTAL_SIZE),                 // wTotalLength            header+units+terminals
    		  DBVAL(48000000),                         	 // dwClockFrequency  			48.000000 MHz
    		  0x01,                                      // bInCollection            1 one streaming interface
    		  0x01,                                      // baInterfaceNr( 0)        1 VS interface 1 belongs to this VC interface


    		  /* Input Terminal Descriptor (Camera) */
    		  UVC_CAMERA_TERMINAL_DESC_SIZE(2),          // bLength                 17 15 + 2 controls
    		  CS_INTERFACE,                              // bDescriptorType         36 (INTERFACE)
    		  VC_INPUT_TERMINAL,                         // bDescriptorSubtype       2 (INPUT_TERMINAL)
    		  0x01,                                      // bTerminalID              1 ID of this Terminal
    		  WBVAL(ITT_CAMERA),                         // wTerminalType       0x0201 Camera Sensor
    		  0x00,                                      // bAssocTerminal           0 no Terminal associated
    		  0x00,                                      // iTerminal                0 no description available
    		  WBVAL(0x0000),                             // wObjectiveFocalLengthMin 0
    		  WBVAL(0x0000),                             // wObjectiveFocalLengthMax 0
    		  WBVAL(0x0000),                             // wOcularFocalLength       0
    		  0x02,                                      // bControlSize             2
    		  0x00, 0x00,                                // bmControls          0x0000 no controls supported

    		  /* Output Terminal Descriptor */
    		  UVC_OUTPUT_TERMINAL_DESC_SIZE(0),          // bLength                  9
    		  CS_INTERFACE,                              // bDescriptorType         36 (INTERFACE)
    		  VC_OUTPUT_TERMINAL,                        // bDescriptorSubtype       3 (OUTPUT_TERMINAL)
    		  0x02,                                      // bTerminalID              2 ID of this Terminal
    		  WBVAL(TT_STREAMING),                       // wTerminalType       0x0101 USB streaming terminal
    		  0x00,                                      // bAssocTerminal           0 no Terminal assiciated
    		  0x01,                                      // bSourceID                1 input pin connected to output pin unit 1
    		  0x00,                                      // iTerminal                0 no description available


    		  /* Video Streaming (VS) Interface Descriptor */

    		  /* Standard VS Interface Descriptor  = interface 1 */
    		  // alternate setting 0 = Zero Bandwidth
    		  USB_INTERFACE_DESC_SIZE,                   // bLength                  9
    		  USB_INTERFACE_DESCRIPTOR_TYPE,             // bDescriptorType          4
    		  USB_UVC_VSIF_NUM,                          // bInterfaceNumber         1 index of this interface
    		  0x00,                                      // bAlternateSetting        0 index of this setting
    		#ifndef VIDEO_USES_ISOC_EP
    		  0x01,                                      // bNumEndpoints            0 no EP used
    		#else
    			0x00,                                        /* bNumEndpoints - none, no bandwidth used */
    		#endif
    		  CC_VIDEO,                                  // bInterfaceClass         14 Video
    		  SC_VIDEOSTREAMING,                         // bInterfaceSubClass       2 Video Streaming
    		  PC_PROTOCOL_UNDEFINED,                     // bInterfaceProtocol       0 (protocol undefined)
    		  0x00,                                      // iInterface               0 no description available

    		#ifndef VIDEO_USES_ISOC_EP
    		  /* Standard VS Isochronous Video data Endpoint Descriptor */
    		  USB_ENDPOINT_DESC_SIZE,                   // bLength                  7
    		  USB_ENDPOINT_DESCRIPTOR_TYPE,             // bDescriptorType          5 (ENDPOINT)
    		  USB_ENDPOINT_IN(USB_UVC_ENDPOINT),        // bEndpointAddress      0x83 EP 3 IN
    		  USB_ENDPOINT_TYPE_BULK,            				// bmAttributes             Bulk transfer type
    		  WBVAL(VIDEO_PACKET_SIZE),                 // wMaxPacketSize
    		  0x00,                                      // bInterval
    		#endif

    		  /* Class-specific VS Header Descriptor (Input) */
    		  UVC_VS_INTERFACE_INPUT_HEADER_DESC_SIZE(1,1),// bLength               14 13 + (1*1) (no specific controls used)
    		  CS_INTERFACE,                              // bDescriptorType         36 (INTERFACE)
    		  VS_INPUT_HEADER,                           // bDescriptorSubtype       1 (INPUT_HEADER)
    		  0x01,                                      // bNumFormats              1 one format descriptor follows
    		  WBVAL(VS_DESC_TOTAL_SIZE),
    		  USB_ENDPOINT_IN(USB_UVC_ENDPOINT),         // bEndPointAddress      	 0x83 EP 3 IN
    		  0x00,                                      // bmInfo                   0 no dynamic format change supported
    		  0x02,                                      // bTerminalLink            2 supplies terminal ID 2 (Output terminal)
    		  0x02,                                      // bStillCaptureMethod      0 NO supports still image capture
    		  0x01,                                      // bTriggerSupport          0 HW trigger supported for still image capture
    		  0x00,                                      // bTriggerUsage            0 HW trigger initiate a still image capture
    		  0x01,                                      // bControlSize             1 one byte bmaControls field size
    		  0x00,                                      // bmaControls(0)           0 no VS specific controls

    		  /* Uncompressed Video Format Descriptor */
    		  27, /* bLength */
    		  CS_INTERFACE,                         /* bDescriptorType */
    		  VS_FORMAT_UNCOMPRESSED,               /* bDescriptorSubType */
    		  0x01,                                 /* bFormatIndex */
    		  1,                                    /* bNumFrameDescriptors */
    		  0x59,0x55,0x59,0x32,                  /* Giud Format YUY2 {32595559-0000-0010-8000-00AA00389B71} */
    		//  0x4d,0x34,0x32,0x30,                  /* Giud Format M420 {3032344D-0000-0010-8000-00AA00389B71} */
    		//  0x49,0x34,0x32,0x30,                  /* Giud Format YUY2 {30323449-0000-0010-8000-00AA00389B71} */
    		  0x00,0x00,
    		  0x10,0x00,
    		  0x80,0x00,0x00,0xAA,0x00,0x38,0x9B,0x71,
    		  BITSPERPIXEL,                          /* bBitsPerPixel: 16 for yuy2 */
    		  0x01,                                 /* bDefaultFrameIndex: Default frame index is 1 */
    		  0x00,                                 /* bAspectRatioX */
    		  0x00,                                 /* bAspectRatioY */
    		  0x00,                                 /* bmInterlaceFlags */
    		  0x00,                                 /* bCopyProtect */

    		  /* Uncompressed Video Frame Descriptor */
    		  30, /* bLength */
    		  CS_INTERFACE, /* bDescriptorType */
    		  VS_FRAME_UNCOMPRESSED, /* bDscriptorSubtype */
    		  0x01, /* bFrameIndex */
    		  0x00, /* bmCapabilities: fixed frame-rate */
    		  WBVAL(WIDTH), /* wWidth */
    		  WBVAL(HEIGHT), /* wHeight */
    		  DBVAL(MIN_BIT_RATE), /* dwMinBitRate */
    		  DBVAL(MAX_BIT_RATE), /* dwMaxBitRate */
    		  DBVAL(MAX_FRAME_SIZE), /* dwMaxVideoFrameBufSize */
    		  DBVAL(333333), /* dwDefaultFrameInterval: for 30 FPS */
    		  1, /* bFrameIntervalType */
    		  DBVAL(333333), /* dwFrameInterval(1) */
    //		  DBVAL(400000),
    //		  DBVAL(500000),
    //		  DBVAL(666666),
    //		  DBVAL(1000000),
    //		  DBVAL(2000000),

    		  /* Color Matching Descriptor */
    		  VS_COLOR_MATCHING_DESC_SIZE,          /* bLength */
    		  CS_INTERFACE,                         /* bDescriptorType : CS_INTERFACE */
    		  0x0D,                                 /* bDescriptorSubType : VS_COLORFORMAT */
    		  0x01,                                 /* bColorPrimarie : 1: BT.709, sRGB (default) */
    		  0x01,                                 /* bTransferCharacteristics : 1: BT.709 (default) */
    		  0x04,                                 /* bMatrixCoefficients : 1: BT. 709. */

    		#ifdef VIDEO_USES_ISOC_EP
    		  /* Standard VS Interface Descriptor  = interface 1 */
    		  // alternate setting 1 = operational setting
    		  USB_INTERFACE_DESC_SIZE,                   // bLength                  9
    		  USB_INTERFACE_DESCRIPTOR_TYPE,             // bDescriptorType          4
    		  USB_UVC_VSIF_NUM,                          // bInterfaceNumber         1 index of this interface
    		  0x01,                                      // bAlternateSetting        1 index of this setting
    		  0x01,                                      // bNumEndpoints            1 one EP used
    		  CC_VIDEO,                                  // bInterfaceClass         14 Video
    		  SC_VIDEOSTREAMING,                         // bInterfaceSubClass       2 Video Streaming
    		  PC_PROTOCOL_UNDEFINED,                     // bInterfaceProtocol       0 (protocol undefined)
    		  0x00,                                      // iInterface               0 no description available

    		  /* Standard VS Isochronous Video data Endpoint Descriptor */
    		  USB_ENDPOINT_DESC_SIZE,                   // bLength                  7
    		  USB_ENDPOINT_DESCRIPTOR_TYPE,             // bDescriptorType          5 (ENDPOINT)
    		  USB_ENDPOINT_IN(USB_UVC_ENDPOINT),        // bEndpointAddress      0x83 EP 3 IN
    		  USB_ENDPOINT_TYPE_ISOCHRONOUS,            // bmAttributes             1 isochronous transfer type  | USB_ENDPOINT_SYNC_ASYNCHRONOUS
    		  WBVAL(VIDEO_PACKET_SIZE),                 // wMaxPacketSize
    		  0x01,                                      // bInterval                1 one frame interval
    		#endif
    };


__ALIGN_BEGIN uint8_t USBD_UVC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x0E,
  0x02,
  0x00,
  0x40,
  0x01,
  0x00,
};

//data array for Video Probe and Commit
VideoControl    videoCommitControl =
{
  {0x00,0x00},                      				// bmHint
  {0x01},                           				// bFormatIndex
  {0x01},                           				// bFrameIndex
  {DBVAL(INTERVAL),},                				// dwFrameInterval
  {0x00,0x00,},                     				// wKeyFrameRate
  {0x00,0x00,},                     				// wPFrameRate
  {0x00,0x00,},                     				// wCompQuality
  {0x00,0x00,},                     				// wCompWindowSize
  {0x00,0x00},                      				// wDelay
  {DBVAL(MAX_FRAME_SIZE)},               			// dwMaxVideoFrameSize
  {0x00, 0x00, 0x00, 0x00},         				// dwMaxPayloadTransferSize
  {0x00, 0x00, 0x00, 0x00},         						// dwClockFrequency
  {0x00},                           				// bmFramingInfo
  {0x00},                           				// bPreferedVersion
  {0x00},                           				// bMinVersion
  {0x00},                           				// bMaxVersion
};

VideoControl    videoProbeControl =
{
  {0x00,0x00},                      				// bmHint
  {0x01},                           				// bFormatIndex
  {0x01},                           				// bFrameIndex
  {DBVAL(INTERVAL),},                		// dwFrameInterval
  {0x00,0x00,},                     				// wKeyFrameRate
  {0x00,0x00,},                     				// wPFrameRate
  {0x00,0x00,},                     				// wCompQuality
  {0x00,0x00,},                     				// wCompWindowSize
  {0x00,0x00},                      				// wDelay
  {DBVAL(MAX_FRAME_SIZE)},              // dwMaxVideoFrameSize
  {0x00, 0x00, 0x00, 0x00},         		// dwMaxPayloadTransferSize
  {0x00, 0x00, 0x00, 0x00},         		// dwClockFrequency
  {0x00},                           				// bmFramingInfo
  {0x00},                           				// bPreferedVersion
  {0x00},                           				// bMinVersion
  {0x00},                           				// bMaxVersion
};


static uint8_t USBD_UVC_Init(void *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);

  USBD_UVC_HandleTypeDef *huvc = NULL;

  ( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_uvc = &uvcInstance;
  huvc =( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_uvc;

  if (huvc == NULL)
  {
      ( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_uvc = NULL;
    return (uint8_t)USBD_FAIL;
  }

  DCD_EP_Open(pdev, USB_ENDPOINT_IN(1), VIDEO_PACKET_SIZE, USB_OTG_EP_ISOC);

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_UVC_DeInit(void *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);

  ( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_uvc = NULL;

  DCD_EP_Close (pdev , USB_ENDPOINT_IN(1));

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_UVC_Setup(void *pdev, USB_SETUP_REQ  *req)
{
  uint8_t *pbuf;
  uint16_t len=0;
  USBD_UVC_HandleTypeDef *huvc =  ( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_uvc;

  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  /* Class request */
  case USB_REQ_TYPE_CLASS :
    switch (req->bRequest)
    {
    case UVC_GET_CUR:
	UVC_Req_GetCurrent(pdev, req);
	break;
    case UVC_GET_DEF:
    case UVC_GET_MIN:
    case UVC_GET_MAX:
      UVC_Req_SetCurrent(pdev, req);
      break;

    case UVC_SET_CUR:
      UVC_Req_SetCurrent(pdev, req);
      break;

    default:
       USBD_CtlError(pdev, req);
       return USBD_FAIL;
    }
    break;
  /* Interface & Endpoint request */
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {
    case USB_REQ_GET_DESCRIPTOR:
	if( (req->wValue >> 8) == 0x21)
	{
			pbuf = USBD_UVC_CfgDesc + 18;
			len = MIN(USB_UVC_CONFIG_DESC_TOTAL_SIZE, req->wLength);
	}
	USBD_CtlSendData(pdev,pbuf,len);
	break;
    case USB_REQ_GET_INTERFACE:
      USBD_CtlSendData (pdev,
			(uint8_t *)&huvc->Interface,
			1);
      break;
    case USB_REQ_SET_INTERFACE:
      huvc->Interface = (uint8_t)(req->wValue);
      if (huvc->Interface == 1) {
	huvc->PlayStatus = 1;
      } else {
	DCD_EP_Flush(pdev, USB_ENDPOINT_IN(1));
	huvc->PlayStatus = 0;
      }
      break;
    }
    break;
  default:
    break;
  }

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_UVC_EP0_RxReady(void *pdev)
{

  return (uint8_t)USBD_OK;
}

extern volatile uint8_t ColorImage;
static uint32_t packet_cnt=0;
CameraTypeDef *ptr =&Camera;
static uint8_t USBD_UVC_DataIn(void *pdev, uint8_t epnum)
{
  USBD_UVC_HandleTypeDef *huvc =  ( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_uvc;
  DCD_EP_Flush(pdev, USB_ENDPOINT_IN(1));

  if (huvc->FrameBytesCount >= MAX_FRAME_SIZE)
  {
	  huvc->FrameBytesCount = 0;
	  huvc->FrameToggleByte ^= 1;
	  packet_cnt=0;
	  ptr->FlagFrameTrans=0;
	  GPIOC->ODR &= ~(1<<5);
  }

	uint8_t packet[UVC_IN_EP1_PACKET_SIZE];
	uint8_t *ptr_packet = packet;
	uint8_t header[2] = {2, huvc->FrameToggleByte};
	*ptr_packet++ = header[0];
	*ptr_packet++ = header[1];
	uint32_t packet_size = 2;

    if(ptr->FlagFrameTrans)
      {
	uint16_t *ptr_data = (uint16_t*)(0xC0000000 +packet_cnt*(UVC_IN_EP1_PACKET_SIZE-2));
	while (packet_size < UVC_IN_EP1_PACKET_SIZE && huvc->FrameBytesCount < MAX_FRAME_SIZE)
	{
	      *ptr_packet++ = *ptr_data >> 8;
	      *ptr_packet++ = *ptr_data++;
	      packet_size += 2;
	      huvc->FrameBytesCount += 2;
	}
	packet_cnt++;
      }
    if(huvc->PlayStatus == 2)
      {
	DCD_EP_Tx( pdev, USB_ENDPOINT_IN(1), (uint8_t*)&packet, (uint32_t)packet_size);
      }

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_UVC_DataOut(void *pdev, uint8_t epnum)
{

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_UVC_SOF(void *pdev)
{
  USBD_UVC_HandleTypeDef *huvc =  ( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_uvc;

  if (huvc->PlayStatus == 1)
  {
	  DCD_EP_Flush (pdev, USB_ENDPOINT_IN(USB_UVC_ENDPOINT));
	  uint16_t buf=0x0002;
	  DCD_EP_Tx(pdev, USB_ENDPOINT_IN(USB_UVC_ENDPOINT), (uint8_t*)&buf, (uint32_t)2);
	  huvc->PlayStatus = 2;

  }
  return (uint8_t)USBD_OK;
}

static uint8_t USBD_UVC_IsoINIncomplete(void *pdev)
{
  UNUSED(pdev);

  return (uint8_t)USBD_OK;
}
static uint8_t USBD_UVC_IsoOutIncomplete(void *pdev)
{
  UNUSED(pdev);

  return (uint8_t)USBD_OK;
}

static uint8_t *USBD_UVC_GetCfgDesc(uint8_t speed, uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_UVC_CfgDesc);

  return USBD_UVC_CfgDesc;
}

static uint8_t *USBD_UVC_GetDeviceQualifierDesc(uint8_t speed, uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_UVC_DeviceQualifierDesc);

  return USBD_UVC_DeviceQualifierDesc;
}

static void UVC_Req_GetCurrent(USB_OTG_CORE_HANDLE *pdev , USB_SETUP_REQ *req)
{
  /* Send the current mute state */

//  USBD_LL_FlushEP (pdev, USB_ENDPOINT_OUT(0)); // ???
  DCD_EP_Flush(pdev,USB_ENDPOINT_OUT(0));

  if(req->wValue == 256)
  {
		      //Probe Request
	  USBD_CtlSendData (pdev, (uint8_t*)&videoProbeControl, req->wLength);
  }
  if(req->wValue == 512)
  {
		      //Commit Request
	  USBD_CtlSendData (pdev, (uint8_t*)&videoCommitControl, req->wLength);
  }

}

static void UVC_Req_SetCurrent(USB_OTG_CORE_HANDLE *pdev , USB_SETUP_REQ *req)
{
  if (req->wLength)
  {
    /* Prepare the reception of the buffer over EP0 */

    if(req->wValue == 256)
    {
		      //Probe Request
		      USBD_CtlPrepareRx (pdev, (uint8_t*)&videoProbeControl, req->wLength);
    }
    if(req->wValue == 512)
    {
		      //Commit Request
		      USBD_CtlPrepareRx (pdev, (uint8_t*)&videoCommitControl, req->wLength);
    }

  }
}
