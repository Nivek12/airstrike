/*
 * spi_interface.h
 *
 *  Created on: Mar 14, 2015
 *      Author: Chris
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include <stdio.h>
#include <stdint.h>
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "gpio.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "spi.h"

#define SPI_IF_BIT_RATE  1000000
#define ONE_CAM
#define MAX_BLOCKS       100
#define CAM_A            0
#define CAM_B            1
#define PIN_8_to_GPIO    0x2
#define PIN_4_to_GPIO    0x20

uint8_t g_currentCamera = CAM_A;

void enableCS(uint8_t cam) {
	switch (cam) {
		case CAM_A:
			MAP_GPIOPinWrite(GPIOA1_BASE, PIN_4_to_GPIO, 0x0);
			break;
		case CAM_B:
			MAP_GPIOPinWrite(GPIOA2_BASE, PIN_8_to_GPIO, 0x0);
			break;
	}
}

void disableCS(uint8_t cam) {
	switch (cam) {
		case CAM_A:
			MAP_GPIOPinWrite(GPIOA1_BASE, PIN_4_to_GPIO, PIN_4_to_GPIO);
			break;
		case CAM_B:
			MAP_GPIOPinWrite(GPIOA2_BASE, PIN_8_to_GPIO, PIN_8_to_GPIO);
			break;
		}
}

uint8_t getByte(uint8_t out) {
	uint8_t w = 0;

	//enableCS(g_currentCamera);

	MAP_SPITransfer(GSPI_BASE, &out, &w, 1, 0);

	//disableCS(g_currentCamera);

	return w;
}

void InitSPIModule(void) {
	//
	// Reset SPI
	//
	MAP_SPIReset(GSPI_BASE);

	//
	// Configure SPI interface
	//
	MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
					 SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_0,
					 (
					 SPI_3PIN_MODE    |
					 SPI_TURBO_OFF    |
					 SPI_WL_8));

	//disableCS(CAM_A);
	//disableCS(CAM_B);

	//
	// Enable SPI for communication
	//
	MAP_SPIEnable(GSPI_BASE);
}

#endif /* SPI_INTERFACE_H_ */
