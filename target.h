/*
 * target.h
 *
 *  Created on: Mar 14, 2015
 *      Author: Chris
 */

#ifndef TARGET_H_
#define TARGET_H_

#include "spi_interface.h"
#include "pixy.h"

void InitTargetModule(void) {
	InitSPIModule();
	init();

}

uint8_t TargetMainLoopTask(void)
{
	uint16_t numBlocks = 0;
	g_CameraSelect = CAM_A;

	puts("\nGetting CAM A Data\n");

	numBlocks = getBlocks(MAX_BLOCKS);
	//g_CameraSelect = CAM_B;

	//puts("\nGetting CAM B Data\n");

	//numBlocks = getBlocks(MAX_BLOCKS);

	return numBlocks;
}

#endif /* TARGET_H_ */
