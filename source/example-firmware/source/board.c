/******************************************************************************
* File Name:   board.c
*
* Description: This file provides basic board functionalities like
*         - reset
*         - debug console
*         - serial
*
*******************************************************************************
* $ Copyright 2024-YEAR Cypress Semiconductor $
*******************************************************************************/

#include <cy_retarget_io.h>
#include <string.h>
#include <stdlib.h>
#include <cyhal.h>
#include <cybsp.h>

#include "protocol/protocol.h"
#include "board.h"

/*******************************************************************************
* Function Name: init_system
********************************************************************************
* Summary:
*   Initializes the system including device and board peripherals.
*******************************************************************************/
void board_init_system(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    if (result != CY_RSLT_SUCCESS)
    {
        CY_HALT();
    }

    /* Initialize the User LED */
    cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT,
        CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

    /* Enable global interrupts */
    __enable_irq();
}

/*******************************************************************************
* Function Name: enable_debug_console
********************************************************************************
* Summary:
*   Initializes the debug UART port for retarget-io.
*
* Return:
*   True if initialization is successful, otherwise false.
*******************************************************************************/
bool board_enable_debug_console(void)
{
    cy_rslt_t result;

    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);
    if(result != CY_RSLT_SUCCESS)
    {
        return false;
    }

    return true;
}

/*******************************************************************************
* Function Name: board_get_serial_uuid
********************************************************************************
* Summary:
*   Retrieves the unique serial UUID of the board.
*
* Return:
*   Pointer to the serial UUID array.
*******************************************************************************/
uint8_t* board_get_serial_uuid(void)
{
    /* Create serial UUID {290DE5CB-460B-41BF-XXXX-XXXXXXXXXXXX}. */
    /* Last part is silicon unique ID. */
    uint64_t serial64 = Cy_SysLib_GetUniqueId();
    static uint8_t serial[16] = {
            0x29, 0x0d, 0xe5, 0xcb, 0x46, 0x0b, 0x41, 0xbf,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    memcpy(serial + 8, &serial64, 8);

    return serial;
}

/*******************************************************************************
* Function Name: board_reset
********************************************************************************
* Summary:
*   Resets the board.
*
* Parameters:
*   protocol: Pointer to the protocol object.
*******************************************************************************/
void board_reset(protocol_t* protocol)
{
    UNUSED(protocol);

    NVIC_SystemReset();
}


/* [] END OF FILE */
