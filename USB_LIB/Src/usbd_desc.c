//--------------------------------------------------------------
// File     : usbd_desc.c
//--------------------------------------------------------------

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_req.h"
#include "usbd_conf.h"
#include "usb_regs.h"


#define USBD_VID                        0x0483  // VID
#define USBD_PID                        0xAB12  // PID
#define USBD_VER                        0x0100  // Version


#define USBD_LANGID_STRING              0x409
#define USBD_MANUFACTURER_STRING        "Radioavionica"

#define USBD_PRODUCT_FS_STRING          "Composite UVC CDC Device"
#define USBD_SERIALNUMBER_FS_STRING     "000000000100"

#define USBD_CONFIGURATION_FS_STRING    "Composite Config"
#define USBD_INTERFACE_FS_STRING        "Composite Interface"


USBD_DEVICE USR_desc =
{
  USBD_USR_DeviceDescriptor,
  USBD_USR_LangIDStrDescriptor, 
  USBD_USR_ManufacturerStrDescriptor,
  USBD_USR_ProductStrDescriptor,
  USBD_USR_SerialStrDescriptor,
  USBD_USR_ConfigStrDescriptor,
  USBD_USR_InterfaceStrDescriptor,
  
};


// USBD_DeviceDesc
__ALIGN_BEGIN uint8_t USBD_DeviceDesc[USB_SIZ_DEVICE_DESC] __ALIGN_END =
{
    0x12,
    USB_DEVICE_DESCRIPTOR_TYPE,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    USB_OTG_MAX_EP0_SIZE,
    LOBYTE(USBD_VID),
    HIBYTE(USBD_VID),
    LOBYTE(USBD_PID),
    HIBYTE(USBD_PID),
    LOBYTE(USBD_VER),
    HIBYTE(USBD_VER),
    USBD_IDX_MFC_STR,
    USBD_IDX_PRODUCT_STR,
    USBD_IDX_SERIAL_STR,
    USBD_CFG_MAX_NUM
};


// USBD_DeviceQualifierDesc
__ALIGN_BEGIN uint8_t USBD_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
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


// USBD_LangIDDesc
__ALIGN_BEGIN uint8_t USBD_LangIDDesc[USB_SIZ_STRING_LANGID] __ALIGN_END =
{
     USB_SIZ_STRING_LANGID,         
     USB_DESC_TYPE_STRING,       
     LOBYTE(USBD_LANGID_STRING),
     HIBYTE(USBD_LANGID_STRING), 
};

//--------------------------------------------------------------
uint8_t *  USBD_USR_DeviceDescriptor( uint8_t speed , uint16_t *length)
{
  *length = sizeof(USBD_DeviceDesc);
  return USBD_DeviceDesc;
}

//--------------------------------------------------------------
uint8_t *  USBD_USR_LangIDStrDescriptor( uint8_t speed , uint16_t *length)
{
  *length =  sizeof(USBD_LangIDDesc);  
  return USBD_LangIDDesc;
}


//--------------------------------------------------------------
uint8_t *  USBD_USR_ProductStrDescriptor( uint8_t speed , uint16_t *length)
{

    USBD_GetString ((uint8_t*)USBD_PRODUCT_FS_STRING, USBD_StrDesc, length);
  return USBD_StrDesc;
}

//--------------------------------------------------------------
uint8_t *  USBD_USR_ManufacturerStrDescriptor( uint8_t speed , uint16_t *length)
{
  USBD_GetString ((uint8_t*)USBD_MANUFACTURER_STRING, USBD_StrDesc, length);
  return USBD_StrDesc;
}

//--------------------------------------------------------------
uint8_t *  USBD_USR_SerialStrDescriptor( uint8_t speed , uint16_t *length)
{

    USBD_GetString ((uint8_t*)USBD_SERIALNUMBER_FS_STRING, USBD_StrDesc, length);
  return USBD_StrDesc;
}

//--------------------------------------------------------------
uint8_t *  USBD_USR_ConfigStrDescriptor( uint8_t speed , uint16_t *length)
{

    USBD_GetString ((uint8_t*)USBD_CONFIGURATION_FS_STRING, USBD_StrDesc, length);

  return USBD_StrDesc;  
}


//--------------------------------------------------------------
uint8_t *  USBD_USR_InterfaceStrDescriptor( uint8_t speed , uint16_t *length)
{

    USBD_GetString ((uint8_t*)USBD_INTERFACE_FS_STRING, USBD_StrDesc, length);

  return USBD_StrDesc;  
}



