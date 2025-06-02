/******************************************************************************
* File Name: dummy_driver_example.h
*
* Description: This file implements the protocol using a dummy driver.
*
* Related Document: See README.md
*
*******************************************************************************/

#ifndef _DUMMY_DRIVER_H_
#define _DUMMY_DRIVER_H_

#include <stdbool.h>
#include "protocol/protocol.h"

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

bool dev_register( protocol_t* protocol );

#endif