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
#define MAX_BLOCKS       100
#define CAM_A            0
#define CAM_B            1
#define CAM_A_CS         GPIO_PIN_5
#define CAM_B_CS         GPIO_PIN_4

uint8_t g_CameraSelect = CAM_A;

uint8_t getByte(uint8_t out) {
	unsigned long w = 0;

	MAP_SPIDataPut(GSPI_BASE, out);
	MAP_SPIDataGet(GSPI_BASE, &w);

	uint8_t r = 0;

	r |= ((w) & 0xFF);

	return r;
}

void enablePixyCS(uint8_t cam) {

	switch (cam)
	{
		case CAM_A:
			MAP_GPIOPinWrite(GPIOA1_BASE, CAM_A_CS, 0);
			break;
		case CAM_B:
			MAP_GPIOPinWrite(GPIOA1_BASE, CAM_B_CS, 0);
			break;
	}

}

void disablePixyCS(uint8_t cam) {

	switch (cam)
		{
			case CAM_A:
				MAP_GPIOPinWrite(GPIOA1_BASE, CAM_A_CS, CAM_A_CS);
				break;
			case CAM_B:
				MAP_GPIOPinWrite(GPIOA1_BASE, CAM_B_CS, CAM_B_CS);
				break;
		}

}

void InitSPIModule(void) {

	disablePixyCS(CAM_A);
	disablePixyCS(CAM_B);

	//
	// Reset SPI
	//
	MAP_SPIReset(GSPI_BASE);

	//
	// Configure SPI interface
	//
	MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
					 SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_0,
					 (SPI_HW_CTRL_CS  |
					 SPI_4PIN_MODE    |
					 SPI_TURBO_OFF    |
					 SPI_CS_ACTIVELOW |
					 SPI_WL_8));

	//
	// Enable SPI for communication
	//
	MAP_SPIEnable(GSPI_BASE);
}

#endif /* SPI_INTERFACE_H_ */
