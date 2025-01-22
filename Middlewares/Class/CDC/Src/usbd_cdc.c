#include "usbd_cdc.h"
#include "usbd_req.h"

USBD_CDC_HandleTypeDef cdcInstance;

extern USBD_CDC_ItfTypeDef USBD_CDC_Interface_fops_HS;

static uint8_t USBD_CDC_Init(void *pdev, uint8_t cfgidx);
static uint8_t USBD_CDC_DeInit(void *pdev, uint8_t cfgidx);
static uint8_t USBD_CDC_Setup(void *pdev, USB_SETUP_REQ *req);
static uint8_t USBD_CDC_EP0_RxReady(void *pdev);
static uint8_t USBD_CDC_DataIn(void *pdev, uint8_t epnum);
static uint8_t USBD_CDC_DataOut(void *pdev, uint8_t epnum);
static uint8_t *USBD_CDC_GetHSCfgDesc(uint8_t speed, uint16_t *length);
static uint8_t *USBD_CDC_GetFSCfgDesc(uint8_t speed, uint16_t *length);
static uint8_t *USBD_CDC_GetOtherSpeedCfgDesc(uint8_t speed, uint16_t *length);
uint8_t *USBD_CDC_GetDeviceQualifierDescriptor(uint8_t speed, uint16_t *length);

USBD_Class_cb_TypeDef  USBD_CDC =
{
  USBD_CDC_Init,
  USBD_CDC_DeInit,
  USBD_CDC_Setup,
  NULL,                 /* EP0_TxSent */
  USBD_CDC_EP0_RxReady,
  USBD_CDC_DataIn,
  USBD_CDC_DataOut,
  NULL,
  NULL,
  NULL,
  USBD_CDC_GetHSCfgDesc,
  USBD_CDC_GetFSCfgDesc,
  USBD_CDC_GetOtherSpeedCfgDesc,
  USBD_CDC_GetDeviceQualifierDescriptor,
};

__ALIGN_BEGIN static uint8_t USBD_CDC_CfgDesc[USB_CDC_CONFIG_DESC_SIZ] __ALIGN_END =
{
  /* Configuration Descriptor */
  0x09,                                       /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,                /* bDescriptorType: Configuration */
  USB_CDC_CONFIG_DESC_SIZ,                    /* wTotalLength */
  0x00,
  0x02,                                       /* bNumInterfaces: 2 interfaces */
  0x01,                                       /* bConfigurationValue: Configuration value */
  0x00,                                       /* iConfiguration: Index of string descriptor
                                                 describing the configuration */
#if (USBD_SELF_POWERED == 1U)
  0xC0,                                       /* bmAttributes: Bus Powered according to user configuration */
#else
  0x80,                                       /* bmAttributes: Bus Powered according to user configuration */
#endif /* USBD_SELF_POWERED */
  0x80,                             	  /* MaxPower (mA) */

  /*---------------------------------------------------------------------------*/

  /* Interface Descriptor */
  0x09,                                       /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,                    /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,                                       /* bInterfaceNumber: Number of Interface */
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
  0x01,                                       /* bDataInterface */

  /* ACM Functional Descriptor */
  0x04,                                       /* bFunctionLength */
  0x24,                                       /* bDescriptorType: CS_INTERFACE */
  0x02,                                       /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,                                       /* bmCapabilities */

  /* Union Functional Descriptor */
  0x05,                                       /* bFunctionLength */
  0x24,                                       /* bDescriptorType: CS_INTERFACE */
  0x06,                                       /* bDescriptorSubtype: Union func desc */
  0x00,                                       /* bMasterInterface: Communication class interface */
  0x01,                                       /* bSlaveInterface0: Data Class Interface */

  /* Endpoint 2 Descriptor */
  0x07,                                       /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                                 /* bEndpointAddress */
  0x03,                                       /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE),                /* wMaxPacketSize */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  CDC_FS_BINTERVAL,                           /* bInterval */
  /*---------------------------------------------------------------------------*/

  /* Data class interface descriptor */
  0x09,                                       /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,                    /* bDescriptorType: */
  0x01,                                       /* bInterfaceNumber: Number of Interface */
  0x00,                                       /* bAlternateSetting: Alternate setting */
  0x02,                                       /* bNumEndpoints: Two endpoints used */
  0x0A,                                       /* bInterfaceClass: CDC */
  0x00,                                       /* bInterfaceSubClass */
  0x00,                                       /* bInterfaceProtocol */
  0x00,                                       /* iInterface */

  /* Endpoint OUT Descriptor */
  0x07,                                       /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                                 /* bEndpointAddress */
  0x02,                                       /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),        /* wMaxPacketSize */
  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
  0x00,                                       /* bInterval */

  /* Endpoint IN Descriptor */
  0x07,                                       /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
  CDC_IN_EP,                                  /* bEndpointAddress */
  0x02,                                       /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),        /* wMaxPacketSize */
  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
  0x00                                        /* bInterval */
};

__ALIGN_BEGIN static uint8_t USBD_CDC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

static uint8_t CDCInEpAdd = CDC_IN_EP;
static uint8_t CDCOutEpAdd = CDC_OUT_EP;
static uint8_t CDCCmdEpAdd = CDC_CMD_EP;

static uint8_t USBD_CDC_Init(void *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);
  USBD_CDC_HandleTypeDef *hcdc = NULL;

  ( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_cdc_acm = &cdcInstance;
  hcdc =( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_cdc_acm;

  if (hcdc == NULL)
  {
      ( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_cdc_acm = NULL;
    return (uint8_t)USBD_FAIL;
  }

  if(((USB_OTG_CORE_HANDLE *)pdev)->cfg.speed == USB_OTG_SPEED_HIGH)
    {
      /* Open EP IN */
      DCD_EP_Open(pdev, CDCInEpAdd, CDC_DATA_HS_IN_PACKET_SIZE, USB_OTG_EP_BULK);

      /* Open EP OUT */
      DCD_EP_Open(pdev, CDCOutEpAdd,  CDC_DATA_HS_OUT_PACKET_SIZE, USB_OTG_EP_BULK);
    }

  /* Open Command IN EP */
  DCD_EP_Open(pdev, CDCCmdEpAdd, CDC_CMD_PACKET_SIZE, USB_OTG_EP_INT);

  /* Init  physical Interface components */
  USBD_CDC_Interface_fops_HS.Init();

  /* Init Xfer states */
  hcdc->TxState = 0U;
  hcdc->RxState = 0U;

  if (hcdc->RxBuffer == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  if (((USB_OTG_CORE_HANDLE *)pdev)->cfg.speed == USB_OTG_SPEED_HIGH)
  {
    /* Prepare Out endpoint to receive next packet */
      DCD_EP_PrepareRx(pdev, CDCOutEpAdd, hcdc->RxBuffer, CDC_DATA_HS_OUT_PACKET_SIZE);
  }

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_CDC_DeInit(void *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);

  ( (USB_OTG_CORE_HANDLE *)pdev)->dev.usr_cdc_acm = NULL;

  /* Open EP IN */
  DCD_EP_Close(pdev, CDCInEpAdd);

  /* Open EP OUT */
  DCD_EP_Close(pdev, CDCOutEpAdd);

  /* Open Command IN EP */
  DCD_EP_Close(pdev, CDCCmdEpAdd);

  /* Restore default state of the Interface physical components */
  USBD_CDC_Interface_fops_HS.DeInit();

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_CDC_Setup(void *pdev, USB_SETUP_REQ *req)
{
  USBD_CDC_HandleTypeDef *hcdc = &cdcInstance;
  uint16_t len;
  uint8_t ifalt = 0U;
  uint16_t status_info = 0U;
  USBD_Status ret = USBD_OK;

  if (hcdc == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
    case USB_REQ_TYPE_CLASS:
      if (req->wLength != 0U)
      {
        if ((req->bmRequest & 0x80U) != 0U)
        {
            USBD_CDC_Interface_fops_HS.Control(req->bRequest, (uint8_t *)hcdc->data, req->wLength);

          len = MIN(CDC_REQ_MAX_DATA_SIZE, req->wLength);
          (void)USBD_CtlSendData(pdev, (uint8_t *)hcdc->data, len);
        }
        else
        {
          hcdc->CmdOpCode = req->bRequest;
          hcdc->CmdLength = (uint8_t)MIN(req->wLength, USB_MAX_EP0_SIZE);

          (void)USBD_CtlPrepareRx(pdev, (uint8_t *)hcdc->data, hcdc->CmdLength);
        }
      }
      else
      {
	  USBD_CDC_Interface_fops_HS.Control(req->bRequest, (uint8_t *)req, 0U);
      }
      break;

    case USB_REQ_TYPE_STANDARD:
      switch (req->bRequest)
      {
        case USB_REQ_GET_STATUS:
          if (((USB_OTG_CORE_HANDLE *)pdev)->dev.device_state == USBD_STATE_CONFIGURED)
          {
            (void)USBD_CtlSendData(pdev, (uint8_t *)&status_info, 2U);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_GET_INTERFACE:
          if (((USB_OTG_CORE_HANDLE *)pdev)->dev.device_state == USBD_STATE_CONFIGURED)
          {
            (void)USBD_CtlSendData(pdev, &ifalt, 1U);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_SET_INTERFACE:
          if (((USB_OTG_CORE_HANDLE *)pdev)->dev.device_state != USBD_STATE_CONFIGURED)
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_CLEAR_FEATURE:
          break;

        default:
          USBD_CtlError(pdev, req);
          ret = USBD_FAIL;
          break;
      }
      break;

    default:
      USBD_CtlError(pdev, req);
      ret = USBD_FAIL;
      break;
  }

  return (uint8_t)ret;
}

static uint8_t USBD_CDC_EP0_RxReady(void *pdev)
{
  USBD_CDC_HandleTypeDef *hcdc = &cdcInstance;

  if (hcdc == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  if (hcdc->CmdOpCode != 0xFFU)
  {
    USBD_CDC_Interface_fops_HS.Control(hcdc->CmdOpCode, (uint8_t *)hcdc->data, (uint16_t)hcdc->CmdLength);
    hcdc->CmdOpCode = 0xFFU;
  }
  return (uint8_t)USBD_OK;
}

static uint8_t USBD_CDC_DataIn(void *pdev, uint8_t epnum)
{
  USBD_CDC_HandleTypeDef *hcdc = &cdcInstance;

  if((((USB_OTG_CORE_HANDLE *)pdev)->dev.in_ep[epnum & 0xFU].total_data_len >0U)
      && ((((USB_OTG_CORE_HANDLE *)pdev)->dev.in_ep[epnum & 0xFU].total_data_len % CDC_DATA_HS_IN_PACKET_SIZE)==0U))
  {
    /* Update the packet total length */
      ((USB_OTG_CORE_HANDLE *)pdev)->dev.in_ep[epnum & 0xFU].total_data_len = 0U;

    /* Send ZLP */
    DCD_EP_Tx (pdev, epnum, NULL, 0);

  }
  else
  {
    hcdc->TxState = 0U;

    if (USBD_CDC_Interface_fops_HS.TransmitCplt != NULL)
    {
      USBD_CDC_Interface_fops_HS.TransmitCplt(hcdc->TxBuffer, &hcdc->TxLength, epnum);
    }

  }

  return (uint8_t)USBD_OK;
}

static uint8_t USBD_CDC_DataOut(void *pdev, uint8_t epnum)
{
  USBD_CDC_HandleTypeDef *hcdc = &cdcInstance;

  /* Get the received data length */
  hcdc->RxLength = ((USB_OTG_CORE_HANDLE*)pdev)->dev.out_ep[epnum].xfer_count;

  /* USB data will be immediately processed, this allow next USB traffic being
  NAKed till the end of the application Xfer */

  USBD_CDC_Interface_fops_HS.Receive(hcdc->RxBuffer, &hcdc->RxLength);

  return (uint8_t)USBD_OK;
}

static uint8_t *USBD_CDC_GetHSCfgDesc(uint8_t speed, uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_CDC_CfgDesc);
  return USBD_CDC_CfgDesc;
}

static uint8_t *USBD_CDC_GetFSCfgDesc(uint8_t speed, uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_CDC_CfgDesc);
  return USBD_CDC_CfgDesc;
}

static uint8_t *USBD_CDC_GetOtherSpeedCfgDesc(uint8_t speed, uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_CDC_CfgDesc);
  return USBD_CDC_CfgDesc;
}

uint8_t *USBD_CDC_GetDeviceQualifierDescriptor(uint8_t speed, uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_CDC_DeviceQualifierDesc);

  return USBD_CDC_DeviceQualifierDesc;
}

//uint8_t USBD_CDC_RegisterInterface(void *pdev, USBD_CDC_ItfTypeDef *fops)
//{
//  if (fops == NULL)
//  {
//    return (uint8_t)USBD_FAIL;
//  }
//
//  pdev->pUserData_CDC_ACM = fops;
//
//  return (uint8_t)USBD_OK;
//}

uint8_t USBD_CDC_SetTxBuffer(uint8_t *pbuff, uint32_t length)
{
  USBD_CDC_HandleTypeDef *hcdc = &cdcInstance;;

  hcdc->TxBuffer = pbuff;
  hcdc->TxLength = length;

  return (uint8_t)USBD_OK;
}

uint8_t USBD_CDC_SetRxBuffer(uint8_t *pbuff)
{
  USBD_CDC_HandleTypeDef *hcdc = &cdcInstance;

  hcdc->RxBuffer = pbuff;

  return (uint8_t)USBD_OK;
}

uint8_t USBD_CDC_TransmitPacket(void *pdev)
{
  USBD_CDC_HandleTypeDef *hcdc = &cdcInstance;
  USBD_Status ret = USBD_BUSY;

  if (hcdc->TxState == 0U)
  {
    /* Tx Transfer in progress */
    hcdc->TxState = 1U;

    /* Update the packet total length */
    ((USB_OTG_CORE_HANDLE *)pdev)->dev.in_ep[CDCInEpAdd & 0xFU].total_data_len = hcdc->TxLength;

    /* Transmit next packet */
    DCD_EP_Tx (pdev, CDCInEpAdd, hcdc->TxBuffer, hcdc->TxLength);

    ret = USBD_OK;
  }
  else
  {
    return USBD_BUSY;
  }

  return (uint8_t)ret;
}

uint8_t USBD_CDC_ReceivePacket(void *pdev)
{
  USBD_CDC_HandleTypeDef *hcdc = &cdcInstance;

  if (((USB_OTG_CORE_HANDLE *)pdev)->cfg.speed == USB_OTG_SPEED_HIGH)
  {
    /* Prepare Out endpoint to receive next packet */
    DCD_EP_PrepareRx(pdev, CDCOutEpAdd, hcdc->RxBuffer, CDC_DATA_HS_OUT_PACKET_SIZE);
  }
  else
  {
    /* Prepare Out endpoint to receive next packet */
      DCD_EP_PrepareRx(pdev, CDCOutEpAdd, hcdc->RxBuffer, CDC_DATA_FS_OUT_PACKET_SIZE);
  }

  return (uint8_t)USBD_OK;
}
