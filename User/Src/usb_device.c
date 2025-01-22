#include "usb_device.h"
#include "usbd_composite.h"
#include "usbd_usr.h"
#include "usbd_def.h"
#include "usbd_desc.h"

USB_OTG_CORE_HANDLE  USB_OTG_dev;

void USB_DeviceInit(void)
{
  USBD_Init(&USB_OTG_dev, USB_OTG_HS_CORE_ID, &USR_desc, &USBD_UVC_CDC_ClassDriver, &USR_cb);
}
