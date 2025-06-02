/******************************************************************************
* File Name:   board.h
*
* Description: This file provides basic board functionalities like
*         - serial
*         - reset
*         - debug console
*
*******************************************************************************
* $ Copyright 2024-YEAR Cypress Semiconductor $
*******************************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

void board_init_system(void);

bool board_enable_debug_console(void);

uint8_t* board_get_serial_uuid(void);

void board_reset(protocol_t* protocol);

bool board_set_clocks(void);

#endif /* _BOARD_H_ */

/* [] END OF FILE */
