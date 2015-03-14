/*
 * network.h
 *
 *  Created on: Feb 24, 2015
 *      Author: Kevin
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <stdio.h>

// Simplelink includes
#include "common.h"
#include "simplelink.h"

static long ConfigureSimplelinkToAP();
void HTTPServerInit();
static unsigned short itoa(char cNum, char *cString);

#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif

// Application specific status/error codes
typedef enum{
    // Choosing -0x7D0 to avoid overlap w/ host-driver's error codes
    LAN_CONNECTION_FAILED = -0x7D0,
    INTERNET_CONNECTION_FAILED = LAN_CONNECTION_FAILED - 1,
    DEVICE_NOT_IN_AP_MODE = INTERNET_CONNECTION_FAILED - 1,

    STATUS_CODE_MAX = -0xBB8
}e_AppStatusCodes;

#endif /* NETWORK_H_ */
