/******************************************************************************
* File Name:   clock.h
*
* Description: This file provides a clock.
*
*******************************************************************************
* $ Copyright 2024-YEAR Cypress Semiconductor $
*******************************************************************************/

#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <stdint.h>

/*******************************************************************************
* Types
*******************************************************************************/

/* uint32_t will wrap around every 12 hour if CLOCK_TICK_PER_SECOND equals 100000.
 * To avoid this change clock_tick_t to uint64_t.
 */
typedef uint64_t clock_tick_t;

/*******************************************************************************
* Defines
*******************************************************************************/

/* Number of counts per second */
#define CLOCK_TICK_PER_SECOND 100000

/* Interrupt Priority Level  */
#define CLOCK_INTERRUPT_PRIORITY  3

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

bool clock_init(void);
clock_tick_t clock_get_tick();

#endif /* _CLOCK_H_ */

/* [] END OF FILE */
