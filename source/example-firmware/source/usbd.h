/******************************************************************************
* File Name:   usbd.h
*
* Description: This file contains the function prototypes and constants used
*   in usbd.c.
*
*******************************************************************************
* $ Copyright 2024-YEAR Cypress Semiconductor $
*******************************************************************************/

#ifndef __USBD_H__
#define __USBD_H__

#include "protocol/protocol.h"
#include "protocol/pb_encode.h"
#include "protocol/pb_decode.h"

#include "USB.h"
#include "USB_CDC.h"

/*******************************************************************************
* Types
********************************************************************************/

typedef struct {
    protocol_t* protocol;
    pb_istream_t istream;    /* input stream */
    pb_ostream_t ostream;    /* output stream */

    USB_CDC_HANDLE usb_cdcHandle;
    USB_DEVICE_INFO usb_deviceInfo;
} usbd_t;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

usbd_t* usbd_create(protocol_t *protocol);
void usbd_free(usbd_t* usb);

#endif /*__USBD_H__ */

/* [] END OF FILE */
