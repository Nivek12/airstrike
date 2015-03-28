/*
 * spi_interface.c
 *
 *  Created on: Mar 19, 2015
 *      Author: Chris
 */

#include "spi_interface.h"

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
					 SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_1,
					 (SPI_HW_CTRL_CS   |
					  SPI_4PIN_MODE    |
					  SPI_TURBO_ON    |
					  SPI_CS_ACTIVELOW |
					  SPI_WL_8));
	// Enable SPI for communication
	//
	MAP_SPIEnable(GSPI_BASE);
}


