//--------------------------------------------------------------
// File     : usb_conf.h
//--------------------------------------------------------------


#ifndef __USB_CONF__H__
#define __USB_CONF__H__

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"




#define USE_USB_OTG_HS

#ifdef USE_USB_OTG_HS
  #define USB_OTG_HS_CORE
  #define USE_ULPI_PHY
#endif

/****************** USB OTG HS CONFIGURATION **********************************/
#ifdef USB_OTG_HS_CORE
 #define RX_FIFO_HS_SIZE                          (0x200)
 #define TX0_FIFO_HS_SIZE                        (0x80)
 #define TX1_FIFO_HS_SIZE                        (0xfff)
 #define TX2_FIFO_HS_SIZE                        (0x80)
 #define TX3_FIFO_HS_SIZE                        (0x40)
 #define TX4_FIFO_HS_SIZE                           0
 #define TX5_FIFO_HS_SIZE                           0

// #define USB_OTG_HS_SOF_OUTPUT_ENABLED

 #ifdef USE_ULPI_PHY
  #define USB_OTG_ULPI_PHY_ENABLED
 #endif
 #ifdef USE_EMBEDDED_PHY
   #define USB_OTG_EMBEDDED_PHY_ENABLED
   /* wakeup is working only when HS core is configured in FS mode */
   #define USB_OTG_HS_LOW_PWR_MGMT_SUPPORT
 #endif
 /* #define USB_OTG_HS_INTERNAL_DMA_ENABLED */ /* Be aware that enabling DMA mode will result in data being sent only by
                                                  multiple of 4 packet sizes. This is due to the fact that USB DMA does
                                                  not allow sending data from non word-aligned addresses.
                                                  For this specific application, it is advised to not enable this option
                                                  unless required. */
 #define USB_OTG_HS_DEDICATED_EP1_ENABLED
#endif

/****************** USB OTG FS CONFIGURATION **********************************/
#ifdef USB_OTG_FS_CORE
 #define RX_FIFO_FS_SIZE                          (0x80)
 #define TX0_FIFO_FS_SIZE                        (0x20)
 #define TX1_FIFO_FS_SIZE                        (0x40)
 #define TX2_FIFO_FS_SIZE                        (0x20)
 #define TX3_FIFO_FS_SIZE                        (0x40)

// #define USB_OTG_FS_LOW_PWR_MGMT_SUPPORT
// #define USB_OTG_FS_SOF_OUTPUT_ENABLED
#endif

/****************** USB OTG MODE CONFIGURATION ********************************/


#endif




