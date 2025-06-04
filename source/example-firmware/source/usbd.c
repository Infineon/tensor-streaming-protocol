/******************************************************************************
* File Name:   usbd.c
*
* Description: This file contains functions for streaming data over a serial
*              USB CDC interface.
*
*******************************************************************************
* $ Copyright 2024-YEAR Cypress Semiconductor $
*******************************************************************************/

#include <stddef.h>
#include <stdio.h>
#include <cyhal_system.h>
#include <USB.h>
#include <USB_CDC.h>

#include "protocol/protocol.h"
#include "protocol/pb_encode.h"
#include "protocol/pb_decode.h"
#include "usbd.h"

/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/
static USB_CDC_HANDLE _usbd_add_cdc(void);
static bool _usbd_read(pb_istream_t* stream, pb_byte_t* buf, size_t count);
static bool _usbd_write(pb_ostream_t* stream, const pb_byte_t* buf, size_t count);

/*******************************************************************************
* Functions
*******************************************************************************/

/*******************************************************************************
* Function Name: _usbd_add_cdc
********************************************************************************
* Summary:
*  Initializes USB CDC.
*
*******************************************************************************/
static USB_CDC_HANDLE _usbd_add_cdc(void)
{
    static U8             OutBuffer[USB_FS_BULK_MAX_PACKET_SIZE];
    USB_CDC_INIT_DATA     InitData;
    USB_ADD_EP_INFO       EPBulkIn;
    USB_ADD_EP_INFO       EPBulkOut;
    USB_ADD_EP_INFO       EPIntIn;

    memset(&InitData, 0, sizeof(InitData));
    EPBulkIn.Flags          = 0;                             /* Flags not used */
    EPBulkIn.InDir          = USB_DIR_IN;                    /* IN direction (Device to Host) */
    EPBulkIn.Interval       = 0;                             /* Interval not used for Bulk endpoints */
    EPBulkIn.MaxPacketSize  = USB_FS_BULK_MAX_PACKET_SIZE;   /* Maximum packet size (64B for Bulk in full-speed) */
    EPBulkIn.TransferType   = USB_TRANSFER_TYPE_BULK;        /* Endpoint type - Bulk */
    InitData.EPIn  = USBD_AddEPEx(&EPBulkIn, NULL, 0);

    EPBulkOut.Flags         = 0;                             /* Flags not used */
    EPBulkOut.InDir         = USB_DIR_OUT;                   /* OUT direction (Host to Device) */
    EPBulkOut.Interval      = 0;                             /* Interval not used for Bulk endpoints */
    EPBulkOut.MaxPacketSize = USB_FS_BULK_MAX_PACKET_SIZE;   /* Maximum packet size (64B for Bulk in full-speed) */
    EPBulkOut.TransferType  = USB_TRANSFER_TYPE_BULK;        /* Endpoint type - Bulk */
    InitData.EPOut = USBD_AddEPEx(&EPBulkOut, OutBuffer, sizeof(OutBuffer));

    EPIntIn.Flags           = 0;                             /* Flags not used */
    EPIntIn.InDir           = USB_DIR_IN;                    /* IN direction (Device to Host) */
    EPIntIn.Interval        = 64;                            /* Interval of 8 ms (64 * 125us) */
    EPIntIn.MaxPacketSize   = USB_FS_INT_MAX_PACKET_SIZE ;   /* Maximum packet size (64 for Interrupt) */
    EPIntIn.TransferType    = USB_TRANSFER_TYPE_INT;         /* Endpoint type - Interrupt */
    InitData.EPInt = USBD_AddEPEx(&EPIntIn, NULL, 0);

    return USBD_CDC_Add(&InitData);
}

/*******************************************************************************
* Function Name: usbd_create
********************************************************************************
* Summary:
*   Creates and initializes a new streaming instance.
*
* Parameters:
*   protocol: Pointer to the protocol handle.
*
* Return:
*   Pointer to the newly created streaming instance.
*
*******************************************************************************/
usbd_t* usbd_create(protocol_t *protocol)
{
    usbd_t* usb = malloc(sizeof(usbd_t));

    if(usb == NULL)
    {
        return NULL;
    }

    usb->protocol = protocol;

    static char serial_str[37];
    pb_byte_t *serial = protocol->board.serial.uuid;
    sprintf(serial_str, "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
            serial[0], serial[1], serial[2], serial[3],
            serial[4], serial[5],
            serial[6], serial[7],
            serial[8], serial[9],
            serial[10], serial[11], serial[12], serial[13], serial[14], serial[15]);
    usb->usb_deviceInfo.sSerialNumber = (const char *)serial;
    usb->usb_deviceInfo.VendorId = 0x058B;
    usb->usb_deviceInfo.ProductId = 0x027D;
    usb->usb_deviceInfo.sVendorName = "Infineon Technologies";
    usb->usb_deviceInfo.sProductName = "DEEPCRAFT Streaming Device";

    /* Initializes the USB stack */
    USBD_Init();

    /* Endpoint Initialization for CDC class */
    usb->usb_cdcHandle = _usbd_add_cdc();

    /* Set device info used in enumeration */
    USBD_SetDeviceInfo(&usb->usb_deviceInfo);

    /* Start the USB stack */
    USBD_Start();

    while ((USBD_GetState() & USB_STAT_CONFIGURED) != USB_STAT_CONFIGURED)
    {
        cyhal_system_delay_ms(50U);
    }

// Important: This exports the stream for later use by the protocol!
// A stream is just a read or write function.
    usb->istream = (pb_istream_t){ &_usbd_read, (void*)usb, SIZE_MAX, 0 };
    usb->ostream = (pb_ostream_t){ &_usbd_write, (void*)usb, SIZE_MAX, 0, NULL };

    return usb;
}


/*******************************************************************************
* Function Name: _usbd_read
********************************************************************************
* Summary:
*   Reads data from the serial interface into the provided buffer.
*   This is called by the protocol engine to receive commands.
*   It returns once 'count' number of bytes are read. 
*   While it is waiting for data it calls protocol_call_device_poll().
*
* Parameters:
*   stream: Pointer to the input stream.
*   buf: Pointer to the buffer where the read data will be stored.
*   count: Number of bytes to read.
*
* Return:
*   True if reading is successful, otherwise false.
*
*******************************************************************************/
static bool _usbd_read(pb_istream_t* stream, pb_byte_t* buf, size_t count)
{
    if (count == 0)
    {
        return true;
    }

    usbd_t *usb = (usbd_t*)stream->state;

    /* Ask USB driver to write 'count' number of bytes in the background (this is non-blocking). */
    USBD_CDC_ReadOverlapped(usb->usb_cdcHandle, buf, count);

    /* While retrieving all the requested data, call protocol_call_device_poll(). */
    /* This is needed as we might be waiting here for a long time waiting for new packages from the client. */
    /* If we don't poll the devices here, we don't allow them to perform tasks and stream data.. */
    do {
        protocol_call_device_poll(usb->protocol, &usb->ostream);
    } while(USBD_CDC_GetNumBytesRemToRead(usb->usb_cdcHandle) > 0);

    return true;

}

/*******************************************************************************
* Function Name: _usbd_write
********************************************************************************
* Summary:
*   Writes data from the provided buffer to the serial interface.
*   This is called by the protocol engine as devices are generating data.
*   We don't have to do anything else than writing the buf over our 
*   communication channel (USB in this case).
*
* Parameters:
*   stream: Pointer to the output stream.
*   buf: Pointer to the buffer containing the data to be written.
*   count: Number of bytes to write.
*
* Return:
*   True if writing is successful, otherwise false.
*
*******************************************************************************/
static bool _usbd_write(pb_ostream_t* stream, const pb_byte_t* buf, size_t count)
{
    usbd_t *usb = (usbd_t*)stream->state;

    USBD_CDC_Write(usb->usb_cdcHandle, buf, count, 0);

    /* Block until write is complete */
    USBD_CDC_WaitForTX(usb->usb_cdcHandle, 0);

    return true;
}

/*******************************************************************************
* Function Name: usbd_free
********************************************************************************
* Summary:
*   Frees the allocated resources for the streaming instance.
*
* Parameters:
*   streaming: Pointer to the streaming instance.
*
*******************************************************************************/
void usbd_free(usbd_t* usb)
{
    free(usb);
}


/* [] END OF FILE */
