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
#ifdef ONE_CAM
	//enableCS(g_currentCamera);
	uint16_t numBlocks = getBlocks(MAX_BLOCKS);
	//disableCS(g_currentCamera);
#endif

	return numBlocks;
}

#endif /* TARGET_H_ */
