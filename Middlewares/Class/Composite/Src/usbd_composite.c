#include "usbd_composite.h"
//#include "usbd_ctlreq.h"

static uint8_t  USBD_UVC_CDC_Init (void *pdev, uint8_t cfgidx);
static uint8_t  USBD_UVC_CDC_DeInit (void *pdev, uint8_t cfgidx);
static uint8_t USBD_UVC_CDC_Setup (void *pdev, USB_SETUP_REQ *req);
static uint8_t USBD_UVC_CDC_EP0_RxReady(void *pdev);
static uint8_t USBD_UVC_CDC_DataIn(void *pdev, uint8_t epnum);
static uint8_t USBD_UVC_CDC_DataOut(void *pdev, uint8_t epnum);
static uint8_t USBD_UVC_CDC_SOF(void *pdev);
static uint8_t USBD_UVC_CDC_IsoINIncomplete(void *pdev);
static uint8_t USBD_UVC_CDC_IsoOutIncomplete(void *pdev);
static uint8_t *USBD_UVC_CDC_GetCfgDesc(uint8_t speed, uint16_t *length);
static uint8_t *USBD_UVC_CDC_GetDeviceQualifierDesc(uint8_t speed, uint16_t *length);

uint8_t StateInit=0;

USBD_Class_cb_TypeDef  USBD_UVC_CDC_ClassDriver =
{
    	USBD_UVC_CDC_Init,
    	USBD_UVC_CDC_DeInit,
    	USBD_UVC_CDC_Setup,
    	NULL, //USBD_UVC_CDC_EP0_TxReady,
    	USBD_UVC_CDC_EP0_RxReady,
    	USBD_UVC_CDC_DataIn,
    	USBD_UVC_CDC_DataOut,
    	USBD_UVC_CDC_SOF,
    	USBD_UVC_CDC_IsoINIncomplete,
    	USBD_UVC_CDC_IsoOutIncomplete,
    	USBD_UVC_CDC_GetCfgDesc,
    	USBD_UVC_CDC_GetCfgDesc,
    	USBD_UVC_CDC_GetCfgDesc,
    	USBD_UVC_CDC_GetDeviceQualifierDesc,
};

__ALIGN_BEGIN uint8_t USBD_UVC_CDC_CfgDesc[USB_UVC_CDC_CONFIG_DESC_TOTAL_SIZE] __ALIGN_END =
    {
    		  /* Configuration 1 */
    		  USB_CONFIGUARTION_DESC_SIZE,               // bLength                  9
    		  USB_CONFIGURATION_DESCRIPTOR_TYPE,         // bDescriptorType          2
    		#ifndef VIDEO_USES_ISOC_EP
    		  WBVAL((USB_UVC_CDC_DESC_SIZE-9)),
    		#else
    		  WBVAL(USB_UVC_CDC_CONFIG_DESC_TOTAL_SIZE),
    		#endif
    		  0x04,                                      // bNumInterfaces           4
    		  0x01,                                      // bConfigurationValue      1 ID of this configuration
    		  0x00,                                      // iConfiguration           0 no description available
    		  0xC0,                   					// bmAttributes          0x80 Bus Powered
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

		/******** IAD should be positioned just before the CDC interfaces ******
				 IAD to associate the two CDC interfaces */
		0x08, 										/* bLength */
		0x0B, 										/* bDescriptorType */
		_CDC_CMD_ITF_NBR,				 		/* bFirstInterface */
		0x02, 										/* bInterfaceCount */
		0x02, 										/* bFunctionClass */
		0x02, 										/* bFunctionSubClass */
		0x01, 										/* bFunctionProtocol */
		0x00, 										/* iFunction (Index of string descriptor describing this function) */

		  /* Interface Descriptor */
		  0x09,                                       /* bLength: Interface Descriptor size */
		  USB_DESC_TYPE_INTERFACE,                    /* bDescriptorType: Interface */
		  /* Interface descriptor type */
		  _CDC_CMD_ITF_NBR,        /* bInterfaceNumber: Number of Interface */
		  0x00,                                       /* bAlternateSetting: Alternate setting */
		  0x01,                                       /* bNumEndpoints: One endpoint used */
		  0x02,                                       /* bInterfaceClass: Communication Interface Class */
		  0x02,                                       /* bInterfaceSubClass: Abstract Control Model */
		  0x01,                                       /* bInterfaceProtocol: Common AT commands */
		  0x00,                                       /* iInterface */

		  /* Header Functional Descriptor */
		  0x05,                                       /* bLength: Endpoint Descriptor size */
		  0x24,                                       /* bDescriptorType: CS_INTERFACE */
		  0x00,                                       /* bDescriptorSubtype: Header Func Desc */
		  0x10,                                       /* bcdCDC: spec release number */
		  0x01,

		  /* Call Management Functional Descriptor */
		  0x05,                                       /* bFunctionLength */
		  0x24,                                       /* bDescriptorType: CS_INTERFACE */
		  0x01,                                       /* bDescriptorSubtype: Call Management Func Desc */
		  0x00,                                       /* bmCapabilities: D0+D1 */
		  _CDC_COM_ITF_NBR,       /* bDataInterface */

		  /* ACM Functional Descriptor */
		  0x04,                                       /* bFunctionLength */
		  0x24,                                       /* bDescriptorType: CS_INTERFACE */
		  0x02,                                       /* bDescriptorSubtype: Abstract Control Management desc */
		  0x02,                                       /* bmCapabilities */

		  /* Union Functional Descriptor */
		  0x05,                                       	/* bFunctionLength */
		  0x24,                                       	/* bDescriptorType: CS_INTERFACE */
		  0x06,                                       	/* bDescriptorSubtype: Union func desc */
		  _CDC_CMD_ITF_NBR, 		/* bMasterInterface: Communication class interface */
		  _CDC_COM_ITF_NBR, 		/* bSlaveInterface0: Data Class Interface */

		  /* Endpoint 3 Descriptor */
		  0x07,                                       /* bLength: Endpoint Descriptor size */
		  USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
		  _CDC_CMD_EP,                                 /* bEndpointAddress */
		  0x03,                                       /* bmAttributes: Interrupt */
		  LOBYTE(CDC_CMD_PACKET_SIZE),                /* wMaxPacketSize */
		  HIBYTE(CDC_CMD_PACKET_SIZE),
		  CDC_FS_BINTERVAL,                           /* bInterval */
		  /*---------------------------------------------------------------------------*/

		  /* Data class interface descriptor */
		  0x09,                                       /* bLength: Endpoint Descriptor size */
		  USB_DESC_TYPE_INTERFACE,                    /* bDescriptorType: */
		  _CDC_COM_ITF_NBR,                                       /* bInterfaceNumber: Number of Interface */
		  0x00,                                       /* bAlternateSetting: Alternate setting */
		  0x02,                                       /* bNumEndpoints: Two endpoints used */
		  0x0A,                                       /* bInterfaceClass: CDC */
		  0x00,                                       /* bInterfaceSubClass */
		  0x00,                                       /* bInterfaceProtocol */
		  0x00,                                       /* iInterface */

		  /* Endpoint OUT Descriptor */
		  0x07,                                       /* bLength: Endpoint Descriptor size */
		  USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
		  _CDC_OUT_EP,                                 /* bEndpointAddress */
		  0x02,                                       /* bmAttributes: Bulk */
		  LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),        /* wMaxPacketSize */
		  HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),
		  0x00,                                       /* bInterval */

		  /* Endpoint IN Descriptor */
		  0x07,                                       /* bLength: Endpoint Descriptor size */
		  USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
		  _CDC_IN_EP,                                  /* bEndpointAddress */
		  0x02,                                       /* bmAttributes: Bulk */
		  LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),        /* wMaxPacketSize */
		  HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),
		  0x00                                        /* bInterval */
    };


__ALIGN_BEGIN uint8_t USBD_UVC_CDC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
{
    USB_LEN_DEV_QUALIFIER_DESC,
    USB_DESC_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0xEF,
    0x02,
    0x01,
    0x40,
    0x01,
    0x00,
};


static uint8_t  USBD_UVC_CDC_Init (void *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);
    /* UVC initialization */
    uint8_t ret = USBD_UVC.Init(pdev,cfgidx);
    if(ret != USBD_OK)
      return ret;

    /* CDC initialization */
    ret = USBD_CDC.Init(pdev,cfgidx);
    if(ret != USBD_OK)
	  return ret;

  return (uint8_t)USBD_OK;
}

static uint8_t  USBD_UVC_CDC_DeInit (void *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);
  /* UVC De-initialization */
  uint8_t ret = USBD_UVC.DeInit(pdev,cfgidx);
  if(ret != USBD_OK)
	  return ret;

  /* CDC De-initialization */
  ret = USBD_CDC.DeInit(pdev,cfgidx);
  if(ret != USBD_OK)
	  return ret;

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_UVC_CDC_Setup (void *pdev, USB_SETUP_REQ *req)
{
    if (LOBYTE(req->wIndex) == USB_UVC_VCIF_NUM || LOBYTE(req->wIndex) == USB_UVC_VSIF_NUM)
    {
      return USBD_UVC.Setup(pdev, req);
    }

    if (LOBYTE(req->wIndex) == _CDC_CMD_ITF_NBR || LOBYTE(req->wIndex) == _CDC_COM_ITF_NBR)
    {
      return USBD_CDC.Setup(pdev, req);
    }

  return (uint8_t)USBD_FAIL;
}

static uint8_t USBD_UVC_CDC_EP0_RxReady(void *pdev)
{
  UNUSED(pdev);

  USBD_CDC.EP0_RxReady(pdev);

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_UVC_CDC_DataIn(void *pdev, uint8_t epnum)
{
  if (epnum == (_UVC_IN_EP & 0x7F))
  {
    return USBD_UVC.DataIn(pdev, epnum);
  }

  if (epnum == (_CDC_IN_EP & 0x7F) || epnum == (_CDC_CMD_EP & 0x7F))
  {
    return USBD_CDC.DataIn(pdev, epnum);
  }

  return (uint8_t)USBD_FAIL;
}

static uint8_t USBD_UVC_CDC_DataOut(void *pdev, uint8_t epnum)
{

  if (epnum == _CDC_OUT_EP)
  {
    return USBD_CDC.DataOut(pdev, epnum);
  }

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_UVC_CDC_SOF(void *pdev)
{
  uint8_t ret = USBD_UVC.SOF(pdev);

  if(ret != USBD_OK)
	  return ret;

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_UVC_CDC_IsoINIncomplete(void *pdev)
{
  UNUSED(pdev);

  return (uint8_t)USBD_OK;
}
static uint8_t USBD_UVC_CDC_IsoOutIncomplete(void *pdev)
{
  UNUSED(pdev);

  return (uint8_t)USBD_OK;
}

static uint8_t *USBD_UVC_CDC_GetCfgDesc(uint8_t speed, uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_UVC_CDC_CfgDesc);

  return USBD_UVC_CDC_CfgDesc;
}

static uint8_t *USBD_UVC_CDC_GetDeviceQualifierDesc(uint8_t speed, uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_UVC_CDC_DeviceQualifierDesc);

  return USBD_UVC_CDC_DeviceQualifierDesc;
}
