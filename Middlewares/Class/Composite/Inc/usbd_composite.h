#ifndef __USBD_COMPOSITE_H
#define __USBD_COMPOSITE_H

#include "usbd_uvc.h"
#include "usbd_cdc.h"

#define USB_UVC_CDC_CONFIG_DESC_TOTAL_SIZE	(233)//(USB_UVC_CONFIG_DESC_TOTAL_SIZE + USB_CDC_CONFIG_DESC_SIZ + 8) //(USB_UVC_CONFIG_DESC_TOTAL_SIZE)

extern USBD_Class_cb_TypeDef  USBD_UVC_CDC_ClassDriver;

#endif
