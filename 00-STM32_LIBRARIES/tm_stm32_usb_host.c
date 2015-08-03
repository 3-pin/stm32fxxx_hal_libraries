/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2015
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#include "tm_stm32_usb_host.h"

/* Variables for HCD and main for USB */
USBH_HandleTypeDef hUSBHost_FS;
USBH_HandleTypeDef hUSBHost_HS;

/* Create variable with pointers */
static USBH_HandleTypeDef* hUSBHosts[3] = {&hUSBHost_FS, &hUSBHost_HS};

/* Private functions */
static void USBH_ProcessCallback(USBH_HandleTypeDef* hUSB, uint8_t id);

TM_USBH_Result_t TM_USBH_Init(TM_USBH_t USB_Mode) {
#ifdef USB_USE_FS
	/* Init FS mode */
	if (USB_Mode == TM_USBH_FS || USB_Mode == TM_USBH_Both) {
		/* Init FS */
		USBH_Init(&hUSBHost_FS, USBH_ProcessCallback, USB_ID_FS);
	}
#endif
	
#ifdef USB_USE_HS
	/* Init HS mode */
	if (USB_Mode == TM_USBH_HS || USB_Mode == TM_USBH_Both) {
		/* Init HS */
		USBH_Init(&hUSBHost_HS, USBH_ProcessCallback, USB_ID_HS);
	}
#endif
	
	/* Return OK */
	return TM_USBH_Result_Ok;
}

TM_USBH_Result_t TM_USBH_Start(TM_USBH_t USB_Mode) {
#ifdef USB_USE_FS
	/* Start FS mode */
	if (USB_Mode == TM_USBH_FS || USB_Mode == TM_USBH_Both) {
		/* Start FS */
		USBH_Start(&hUSBHost_FS);
	}
#endif
	
#ifdef USB_USE_HS
	/* Start HS mode */
	if (USB_Mode == TM_USBH_HS || USB_Mode == TM_USBH_Both) {
		/* Start HS */
		USBH_Start(&hUSBHost_HS);
	}
#endif
	
	/* Return OK */
	return TM_USBH_Result_Ok;
}

TM_USBH_Result_t TM_USBH_Restart(TM_USBH_t USB_Mode) {
#ifdef USB_USE_FS
	/* Restart FS mode */
	if (USB_Mode == TM_USBH_FS || USB_Mode == TM_USBH_Both) {
		/* Restart FS */
		USBH_ReEnumerate(&hUSBHost_FS);
	}
#endif
	
#ifdef USB_USE_HS
	/* Restart HS mode */
	if (USB_Mode == TM_USBH_HS || USB_Mode == TM_USBH_Both) {
		/* Restart HS */
		USBH_ReEnumerate(&hUSBHost_HS);
	}
#endif
	
	/* Return OK */
	return TM_USBH_Result_Ok;
}

TM_USBH_Result_t TM_USBH_Stop(TM_USBH_t USB_Mode) {
#ifdef USB_USE_FS
	/* STOP FS mode */
	if (USB_Mode == TM_USBH_FS || USB_Mode == TM_USBH_Both) {
		/* STOP FS */
		USBH_Stop(&hUSBHost_FS);
	}
#endif
	
#ifdef USB_USE_HS
	/* Process HS mode */
	if (USB_Mode == TM_USBH_HS || USB_Mode == TM_USBH_Both) {
		/* STOP HS */
		USBH_Stop(&hUSBHost_HS);
	}
#endif
	
	/* Return OK */
	return TM_USBH_Result_Ok;
}

TM_USBH_Result_t TM_USBH_Process(TM_USBH_t USB_Mode) {
#ifdef USB_USE_FS
	/* Process FS mode */
	if (USB_Mode == TM_USBH_FS || USB_Mode == TM_USBH_Both) {
		/* Process FS */
		USBH_Process(&hUSBHost_FS);
	}
#endif
	
#ifdef USB_USE_HS
	/* Process HS mode */
	if (USB_Mode == TM_USBH_HS || USB_Mode == TM_USBH_Both) {
		/* Process HS */
		USBH_Process(&hUSBHost_HS);
	}
#endif
	
	/* Return OK */
	return TM_USBH_Result_Ok;
}

TM_USBH_Result_t TM_USBH_IsConnected(TM_USBH_t USB_Mode) {
	/* Check if any device connected to USB */
	if (hUSBHosts[(uint8_t)USB_Mode]->device.is_connected) {
		/* Return OK */
		return TM_USBH_Result_Ok;
	}
	
	/* Return OK */
	return TM_USBH_Result_Error;
}

USBH_HandleTypeDef* TM_USBH_GetUSBPointer(TM_USBH_t USB_Mode) {
	/* Return pointer to USB handle */
	return hUSBHosts[(uint8_t)USB_Mode];
}

uint16_t TM_USBH_GetVID(TM_USBH_t USB_Mode) {
	/* Return vendor ID */
	return hUSBHosts[(uint8_t)USB_Mode]->device.DevDesc.idVendor;
}

uint16_t TM_USBH_GetPID(TM_USBH_t USB_Mode) {
	/* Return product ID */
	return hUSBHosts[(uint8_t)USB_Mode]->device.DevDesc.idProduct;
}

/* Private functions */	
static void USBH_ProcessCallback(USBH_HandleTypeDef* hUSB, uint8_t id) {
	/* TO-DO: Call user function */
	switch (id) { 
		case HOST_USER_SELECT_CONFIGURATION:
			break;
		case HOST_USER_DISCONNECTION:
			break;
		case HOST_USER_CLASS_ACTIVE:
			break;
		case HOST_USER_CONNECTION:
			break;
		default:
			break; 
	}
}
