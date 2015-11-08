#ifndef __USBH_RTLSDR_H
#define __USBH_RTLSDR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
	 
#define VENDOR_SPECIFIC_CLASS	0xFF
#define VENDOR_SPECIFIC_SUBCLASS 0xFF
#define VENDOR_SPECIFIC_PROTOCOL 0xFF

#define CTRL_IN		0xC0
#define CTRL_OUT	0x40
#define CTRL_TIMEOUT	300
#define BULK_TIMEOUT	0
	 
typedef struct _RTLSDR_Process
{
 uint8_t InPipe;
 uint8_t InEp;
 uint16_t InEpSize;     
}
RTLSDR_HandleTypeDef;	 
	 
extern USBH_ClassTypeDef  RTLSDR_Class;
#define USBH_RTLSDR_CLASS    &RTLSDR_Class

#ifdef __cplusplus
}
#endif

#endif /* USBH_RTLSDR_H */
