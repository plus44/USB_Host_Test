#include "usbh_rtlsdr.h"

#define USBH_RTLSDR_BUFFER_SIZE 512

static USBH_StatusTypeDef USBH_RTLSDR_InterfaceInit(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_RTLSDR_InterfaceDeInit(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_RTLSDR_ClassRequest(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_RTLSDR_Process(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_RTLSDR_SOFProcess(USBH_HandleTypeDef *phost);


USBH_ClassTypeDef RTLSDR_Class = 
{
	"VENDOR",
	VENDOR_SPECIFIC_CLASS,
	USBH_RTLSDR_InterfaceInit,
  USBH_RTLSDR_InterfaceDeInit,
  USBH_RTLSDR_ClassRequest,
  USBH_RTLSDR_Process,
  USBH_RTLSDR_SOFProcess,
	NULL
};

static USBH_StatusTypeDef USBH_RTLSDR_InterfaceInit(USBH_HandleTypeDef *phost) {
	uint8_t interface;
	USBH_StatusTypeDef status = USBH_FAIL;
	RTLSDR_HandleTypeDef *RTLSDR_Handle;

	
	interface = USBH_FindInterface(phost, VENDOR_SPECIFIC_CLASS, VENDOR_SPECIFIC_SUBCLASS, VENDOR_SPECIFIC_PROTOCOL);
	
	if(interface == 0xFF) /* Not Valid Interface */
  {
    USBH_DbgLog ("Cannot Find the interface for %s class.", phost->pActiveClass->Name);
    status = USBH_FAIL;      
  }
	else 
	{
		phost->pActiveClass->pData = (RTLSDR_HandleTypeDef *)USBH_malloc (sizeof(RTLSDR_HandleTypeDef));
		RTLSDR_Handle =  (RTLSDR_HandleTypeDef *) phost->pActiveClass->pData; 
		USBH_memset(RTLSDR_Handle, 0, sizeof(RTLSDR_HandleTypeDef));
		
		USBH_SelectInterface (phost, interface);
		
		if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bEndpointAddress & 0x80)
    {
      RTLSDR_Handle->InEp = (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bEndpointAddress);
      RTLSDR_Handle->InEpSize  = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].wMaxPacketSize;
    }
		
		if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[1].bEndpointAddress & 0x80)
    {
      RTLSDR_Handle->InEp = (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[1].bEndpointAddress);
      RTLSDR_Handle->InEpSize  = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[1].wMaxPacketSize;
    }
		
		RTLSDR_Handle->InPipe = USBH_AllocPipe(phost, RTLSDR_Handle->InEp);
		
		/* Open the new channels */
    USBH_OpenPipe  (phost,
                    RTLSDR_Handle->InPipe,
                    RTLSDR_Handle->InEp,
                    phost->device.address,
                    phost->device.speed,
                    USB_EP_TYPE_BULK,
                    RTLSDR_Handle->InEpSize); 
		USBH_LL_SetToggle  (phost, RTLSDR_Handle->InPipe,0);
		
		status = USBH_OK;
	}
	
	return status;
}

static USBH_StatusTypeDef USBH_RTLSDR_InterfaceDeInit(USBH_HandleTypeDef *phost) {
	RTLSDR_HandleTypeDef *RTLSDR_Handle =  (RTLSDR_HandleTypeDef *) phost->pActiveClass->pData;
	
	if ( RTLSDR_Handle->InPipe)
  {
    USBH_ClosePipe(phost, RTLSDR_Handle->InPipe);
    USBH_FreePipe  (phost, RTLSDR_Handle->InPipe);
    RTLSDR_Handle->InPipe = 0;     /* Reset the Channel as Free */
  } 

	if(phost->pActiveClass->pData)
  {
    USBH_free (phost->pActiveClass->pData);
    phost->pActiveClass->pData = 0;
  }
	
	return USBH_OK;
}

static USBH_StatusTypeDef USBH_RTLSDR_ClassRequest(USBH_HandleTypeDef *phost) {
	USBH_StatusTypeDef status = USBH_FAIL;
	return status;
}

static USBH_StatusTypeDef USBH_RTLSDR_Process(USBH_HandleTypeDef *phost) {
	USBH_StatusTypeDef status = USBH_FAIL;
	return status;
}

static USBH_StatusTypeDef USBH_RTLSDR_SOFProcess(USBH_HandleTypeDef *phost) {
	USBH_StatusTypeDef status = USBH_FAIL;
	return status;
}
