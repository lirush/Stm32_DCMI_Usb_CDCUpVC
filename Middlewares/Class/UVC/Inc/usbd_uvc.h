#ifndef __USBD_UVC_H
#define __USBD_UVC_H

#include  "usbd_ioreq.h"

extern USBD_Class_cb_TypeDef USBD_UVC;

typedef struct
{
  uint32_t Interface;
  __IO uint8_t  PlayStatus; //0 - stream stopped, 1 - ready to stream, 2 - stream running
  uint32_t FrameBytesCount;
  uint8_t  FrameToggleByte;
  uint32_t FrameCount;
  uint32_t MicroframeCount;
}USBD_UVC_HandleTypeDef;

//UVC 1.0 uses only 26 first bytes
typedef struct _VideoControl{
  uint8_t    bmHint[2];                      // 2
  uint8_t    bFormatIndex[1];                // 3
  uint8_t    bFrameIndex[1];                 // 4
  uint8_t    dwFrameInterval[4];             // 8
  uint8_t    wKeyFrameRate[2];               // 10
  uint8_t    wPFrameRate[2];                 // 12
  uint8_t    wCompQuality[2];                // 14
  uint8_t    wCompWindowSize[2];             // 16
  uint8_t    wDelay[2];                      // 18
  uint8_t    dwMaxVideoFrameSize[4];         // 22
  uint8_t    dwMaxPayloadTransferSize[4];    // 26
  uint8_t    dwClockFrequency[4];
  uint8_t    bmFramingInfo[1];
  uint8_t    bPreferedVersion[1];
  uint8_t    bMinVersion[1];
  uint8_t    bMaxVersion[1];
} VideoControl;

#define	UVC_1_1
#define VIDEO_USES_ISOC_EP								(0x01)
#define _UVC_IN_EP 											(0x81U)
#define USB_UVC_ENDPOINT									(0x01)
#define UVC_UNCOMPRESSED								(1)

// USB Video device class specification version 1.10
#ifdef UVC_1_1
#define UVC_VERSION                             							(0x0110)      // UVC 1.1
#else
#define UVC_VERSION                             							(0x0100)      // UVC 1.0
#endif

#define WBVAL(x) (x & 0xFF),((x >> 8) & 0xFF)
#define DBVAL(x) (x & 0xFF),((x >> 8) & 0xFF),((x >> 16) & 0xFF),((x >> 24) & 0xFF)

#define USB_CONFIG_POWER_MA(mA)                				((mA)/2)
#define USB_ENDPOINT_DIRECTION_MASK            				(0x80)
#define USB_ENDPOINT_OUT(addr)                 					((addr) | 0x00)
#define USB_ENDPOINT_IN(addr)                  					((addr) | 0x80)

#define USB_DEVICE_DESC_SIZE        							(sizeof(USB_DEVICE_DESCRIPTOR))
#define USB_CONFIGUARTION_DESC_SIZE 					(0x09)
#define USB_INTERFACE_DESC_SIZE     						(0x09)
#define USB_ENDPOINT_DESC_SIZE     						(0x07)
#define UVC_INTERFACE_ASSOCIATION_DESC_SIZE 			(0x08)
#define UVC_VC_ENDPOINT_DESC_SIZE   						(0x05)
#define USB_VIDEO_DESC_SIZE 								(0x9F)

#define UVC_VC_INTERFACE_HEADER_DESC_SIZE(n)  			(char)(12+n)
#define UVC_CAMERA_TERMINAL_DESC_SIZE(n)      			(char)(15+n)
#define UVC_OUTPUT_TERMINAL_DESC_SIZE(n)      			(char)(9+n)
#define UVC_VS_INTERFACE_INPUT_HEADER_DESC_SIZE(a,b) 	(char) (13+a*b)

#define VS_FORMAT_UNCOMPRESSED_DESC_SIZE  			(char)(0x0b)
#define VS_FRAME_UNCOMPRESSED_DESC_SIZE   				(char)(0x26)
#define VS_FRAME_COMPRESSED_DESC_SIZE   				(char)(0x26)
#define VS_COLOR_MATCHING_DESC_SIZE   					(char)(0x06)

#define USB_CONFIGURATION_DESCRIPTOR_TYPE       			(0x02)
#define USB_INTERFACE_DESCRIPTOR_TYPE           			(0x04)
#define USB_ENDPOINT_DESCRIPTOR_TYPE           		 		(0x05)
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE 	(0x0b)

#define CC_VIDEO                                   							(0x0E)

// Video Interface Subclass Codes
#define SC_UNDEFINED                               						(0x00)
#define SC_VIDEOCONTROL                            					(0x01)
#define SC_VIDEOSTREAMING                          					(0x02)
#define SC_VIDEO_INTERFACE_COLLECTION              			(0x03)

// Video Interface Protocol Codes
#define PC_PROTOCOL_UNDEFINED                      				(0x00)

#define USB_UVC_VCIF_NUM 								(0x00)
#define USB_UVC_VSIF_NUM            							(0x01)

// Video Class-Specific Descriptor Types
#define CS_UNDEFINED                               						(0x20)
#define CS_DEVICE                                  							(0x21)
#define CS_CONFIGURATION                           					(0x22)
#define CS_STRING                                  							(0x23)
#define CS_INTERFACE                               						(0x24)
#define CS_ENDPOINT                                						(0x25)

// Video Class-Specific VideoControl Interface Descriptor Subtypes
#define VC_DESCRIPTOR_UNDEFINED                    				(0x00)
#define VC_HEADER                                  							(0x01)
#define VC_INPUT_TERMINAL                          					(0x02)
#define VC_OUTPUT_TERMINAL                         					(0x03)
#define VC_SELECTOR_UNIT                           					(0x04)
#define VC_PROCESSING_UNIT                         					(0x05)
#define VC_EXTENSION_UNIT                          					(0x06)

// Input Terminal Types
#define ITT_VENDOR_SPECIFIC                      					(0x0200)
#define ITT_CAMERA                               							(0x0201)
#define ITT_MEDIA_TRANSPORT_INPUT                				(0x0202)
// USB Terminal Types
#define TT_VENDOR_SPECIFIC         	             					(0x0100)
#define TT_STREAMING               	             						(0x0101)

// Video Class-Specific VideoStreaming Interface Descriptor Subtypes
#define VS_UNDEFINED                               						(0x00)
#define VS_INPUT_HEADER                           						(0x01)
#define VS_OUTPUT_HEADER                           					(0x02)
#define VS_STILL_IMAGE_FRAME                       					(0x03)
#define VS_FORMAT_UNCOMPRESSED                     				(0x04)
#define VS_FRAME_UNCOMPRESSED                      				(0x05)
#define VS_FORMAT_MJPEG                            					(0x06)
#define VS_FRAME_MJPEG                             						(0x07)
#define VS_FORMAT_MPEG2TS                          					(0x0A)
#define VS_FORMAT_DV                               						(0x0C)
#define VS_COLORFORMAT                             					(0x0D)
#define VS_FORMAT_FRAME_BASED                      				(0x10)
#define VS_FRAME_FRAME_BASED                       				(0x11)
#define VS_FORMAT_STREAM_BASED                     				(0x12)

/* bmAttributes in Endpoint Descriptor */
#define USB_ENDPOINT_TYPE_MASK                					(0x03)
#define USB_ENDPOINT_TYPE_CONTROL              				(0x00)
#define USB_ENDPOINT_TYPE_ISOCHRONOUS          			(0x01)
#define USB_ENDPOINT_TYPE_BULK                 					(0x02)
#define USB_ENDPOINT_TYPE_INTERRUPT            				(0x03)
#define USB_ENDPOINT_SYNC_MASK                 				(0x0C)
#define USB_ENDPOINT_SYNC_NO_SYNCHRONIZATION   		(0x00)
#define USB_ENDPOINT_SYNC_ASYNCHRONOUS         			(0x04)
#define USB_ENDPOINT_SYNC_ADAPTIVE             				(0x08)
#define USB_ENDPOINT_SYNC_SYNCHRONOUS          			(0x0C)
#define USB_ENDPOINT_USAGE_MASK                				(0x30)
#define USB_ENDPOINT_USAGE_DATA                				(0x00)
#define USB_ENDPOINT_USAGE_FEEDBACK            				(0x10)
#define USB_ENDPOINT_USAGE_IMPLICIT_FEEDBACK   		(0x20)
#define USB_ENDPOINT_USAGE_RESERVED            				(0x30)

#define UVC_IN_EP1_PACKET_SIZE         						(960+2)//(960+2)
#define WIDTH                                         							(unsigned int)640
#define HEIGHT                                        							(unsigned int)480
#define CAM_FPS                                       							(25)
#define VIDEO_PACKET_SIZE                             					(unsigned int)(0x1bff)//0x1bff - set 11, 12 bits. size buffer is 1023
#define BITSPERPIXEL										(16)
#define BYTESPERPIXEL										(2)
#define MIN_BIT_RATE                                  						(unsigned long)(WIDTH*HEIGHT*BITSPERPIXEL*CAM_FPS)//16 bit
#define MAX_BIT_RATE                                  						(unsigned long)(WIDTH*HEIGHT*BITSPERPIXEL*CAM_FPS)
//#define MIN_BIT_RATE                                  					(unsigned long)(0x7CE000)
//#define MAX_BIT_RATE                                  					(unsigned long)(0x3E80000)
// #define MIN_BIT_RATE                                  					(unsigned long)(24576000)
// #define MAX_BIT_RATE                                  					(unsigned long)(147456000)
#define MAX_FRAME_SIZE                                					(unsigned long)(WIDTH*HEIGHT*2)//yuy2
//#define MAX_FRAME_SIZE                                					(unsigned long)(61080)//jpeg

#define INTERVAL                                      							(unsigned long)(10000000ul/CAM_FPS)
#define PACKETS_IN_FRAME                             					(unsigned int)(MAX_FRAME_SIZE/(VIDEO_PACKET_SIZE-2))

#define VC_TERMINAL_SIZE 	(unsigned int)(UVC_VC_INTERFACE_HEADER_DESC_SIZE(1) + UVC_CAMERA_TERMINAL_DESC_SIZE(2) + UVC_OUTPUT_TERMINAL_DESC_SIZE(0))
#define VC_HEADER_SIZE 	(unsigned int)(UVC_VS_INTERFACE_INPUT_HEADER_DESC_SIZE(1,1) + VS_FORMAT_UNCOMPRESSED_DESC_SIZE + VS_FRAME_UNCOMPRESSED_DESC_SIZE + VS_COLOR_MATCHING_DESC_SIZE)
#define VC_DESC_TOTAL_SIZE ((12+1)+(15+2)+9)
#define VS_DESC_TOTAL_SIZE ((13+1*1)+27+30)
#ifdef UVC_UNCOMPRESSED
#define USB_UVC_CONFIG_DESC_TOTAL_SIZE 	(9+8+9+VC_DESC_TOTAL_SIZE+9+VS_DESC_TOTAL_SIZE+6+9+7)
#else
#define USB_UVC_CONFIG_DESC_TOTAL_SIZE 	(USB_CONFIGUARTION_DESC_SIZE \
												   + UVC_INTERFACE_ASSOCIATION_DESC_SIZE \
												   + USB_INTERFACE_DESC_SIZE \
												   + VC_TERMINAL_SIZE \
												   + USB_INTERFACE_DESC_SIZE \
												   + VC_HEADER_SIZE \
												   + USB_INTERFACE_DESC_SIZE \
												   + USB_ENDPOINT_DESC_SIZE)	//(9+8+9+VC_DESC_TOTAL_SIZE+9+VS_DESC_TOTAL_SIZE+6+9+7)
#endif


// Video Class-Specific Request Codes
// (USB_Video_Class_1.1.pdf, A.8 Video Class-Specific Request Codes)
#define RC_UNDEFINED                               						(0x00)
#define UVC_SET_CUR                                						(0x01)
#define UVC_GET_CUR                                						(0x81)
#define UVC_GET_MIN                                						(0x82)
#define UVC_GET_MAX                                						(0x83)
#define UVC_GET_RES                                						(0x84)
#define UVC_GET_LEN                                						(0x85)
#define UVC_GET_INFO                               						(0x86)
#define UVC_GET_DEF                                						(0x87)

extern __ALIGN_BEGIN uint8_t USBD_UVC_CfgDesc[USB_UVC_CONFIG_DESC_TOTAL_SIZE] __ALIGN_END;
extern __ALIGN_BEGIN uint8_t USBD_UVC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END;

#endif
