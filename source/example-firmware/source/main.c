/******************************************************************************
* File Name:   main.c
*
* Description: Implementation of Tensor Streaming Protocol v2 for PSOC 6.
*******************************************************************************
* $ Copyright 2024-YEAR Cypress Semiconductor $
*******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <cyhal.h>
#include <stdio.h>

#include "protocol/protocol.h"
#include "usbd.h"
#include "build.h"
#include "clock.h"
#include "board.h"

#include "devices/protocol_example.h"

/*******************************************************************************
** The purpose of this project is to explain how the protocol is used for
** streaming a single sensor of data. Hardware drivers are not implemented but
** instead data is generated with a simple data generator.
**
** There is no real meaning of talking about physical quantities here since the
** representation could be anything. However there is a timing component involved.
** This timing could for example be the number of samples per second,
** radar_frames per second or any other quantity. The timing component is used
** for letting DEEPCRAFT Studio know about how much data it should expect for each timing
** period and to let it update its graphical UI.
**
** The protocol is running in pseudo full-duplex. Almost everything is run in a
** single thread from the view of application. Thus it also checks the status of
** any driver using polling.
**
** In the end of the main function it enters a loop that will constantly check
** for incoming configuration-data, incoming start and stop commands. During
** each check of incoming data it check if any of the drivers are ready to send
** something. This polling are very fast.
** More details of the protocol can be found in the devices/protocol_example.c file
** that is created as an example for this tutorial. 
** 
** Note: The source files under protocol/ are generated and should not be modified.
** There is no need to modify those files to use the protocol.
*******************************************************************************/

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  This is the main function. It never returns.
*
*******************************************************************************/
int main(void)
{

    /* Base system initialization  */
    board_init_system();

/*******************************************************************************
*   This clock init sets up the timer that is used by the device driver to 
*   synchronize the data fetching. The polling will use check if data is ready to
*   be sent over the protocol. 
*******************************************************************************/
    /* Start timer */
    if(!clock_init())
    {
    }

    /* Initialize retarget-io to use the debug UART port */
    if(!board_enable_debug_console())
    {
    }

    /* Firmware version */
    protocol_Version firmware_version = {
        .major = 1,
        .minor = 2,
        .build = BUILD_DATE,
        .revision = BUILD_TIME
    };

    /* Serial UUID */
    uint8_t* serial = board_get_serial_uuid();

    /* Create a protocol instance containing the name of the board, serial/UUID (to identify the individual board), 
     and a firmware version to identify the version. All this information can be displayed in Studio. */
    protocol_t* protocol = protocol_create("PSOC 6 AI (CY8KIT-06S2-AI)", serial, firmware_version);

    /* Add reset function that can be triggered from Studio to reset the board through the UI. */
    protocol->board_reset = board_reset;

    /* Debug console print */
    printf("\x1b[2J\x1b[;H");
    printf("*********** Firmware Debug Console ***********\n\n");
    printf("Board Name             : %s\r\n", protocol->board.name);
    printf("Board Serial           : %02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\n",
        serial[0], serial[1], serial[2], serial[3],
        serial[4], serial[5],
        serial[6], serial[7],
        serial[8], serial[9],
        serial[10], serial[11], serial[12], serial[13], serial[14], serial[15]);
    printf("Firmware Version       : %" PRIu32 ".%" PRIu32 ".%" PRIu32 ".%" PRIu32 "\n\n",
        protocol->board.firmware_version.major,
        protocol->board.firmware_version.minor,
        protocol->board.firmware_version.build,
        protocol->board.firmware_version.revision);
    printf("Protocol Version       : %" PRIu32 ".%" PRIu32 ".%" PRIu32 ".%" PRIu32 "\n\n",
        protocol->board.protocol_version.major,
        protocol->board.protocol_version.minor,
        protocol->board.protocol_version.build,
        protocol->board.protocol_version.revision);



/*******************************************************************************
*   This registering of the device describes how the device will appear in
*   Studio. A board can have multiple devices.
*******************************************************************************/
    if(!dev_register( protocol ))
    {
        printf("Sample registration failed.\n");
        while( true );
    }

/*******************************************************************************
*   I have no details here at the moment but the streaming should be possible
*   to reroute or design for other communication channels than the USB. However
*   studio expects the board to be found on one of the COM ports, usually a
*   Virtual Com Port (VCP).
*******************************************************************************/
    /* Initialize the streaming interface */
    usbd_t* usb = usbd_create(protocol);

    printf("Ready accepting commands.\r\n");

/*******************************************************************************
*   Start the communication using the protocol. Processing begins with the
*   Studio fetching information of the registered devices. It then lets the
*   user configure the device. Setting parameters in the struct. Once the
*   device is configured using the Studio interface the user can then start
*   displaying and recording the data in Studio.
*
*   protocol_process_request() reads and processes a complete package. 
*   While waiting for packages this function calls protocol_call_device_poll() that 
*   in turn reads/writes to/from devices and writes packages.
*   This call happens in _usbd_read().
*
*   In short, this for-loop iterates one step for each incoming package, and while
*   waiting for new packages, packages are continuously sent.
*******************************************************************************/
    for (;;)
    {
        protocol_process_request(protocol, &usb->istream, &usb->ostream);
    }
}

/* [] END OF FILE */
