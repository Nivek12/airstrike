/*
 * target.c
 *
 *  Created on: Mar 19, 2015
 *      Author: Chris
 */

#include "target.h"

bool foundTarget(void) {
	return (g_numBlocks > 0);
}

void InitTargetModule(void) {
	InitSPIModule();
	init();

}

char* getFaggotBlocksForKevinTheFag(char * faggotString) {
	Block bitch = g_blocks[0];
	sprintf(faggotString, "%u|%u|%u|%u",
			(unsigned int) bitch.x, (unsigned int) bitch.y,
			(unsigned int) bitch.height, (unsigned int) bitch.width);
	return faggotString;
}

uint8_t TargetMainLoopTask(void)
{
	//uint16_t numBlocks = 0;
	//g_skipStart = 0;
	//g_CameraSelect = CAM_A;
	//enablePixyCS(g_CameraSelect);
	//g_numBlocks = getBlocks(MAX_BLOCKS);
	//disablePixyCS(g_CameraSelect);
	g_skipStart = 0;
	g_CameraSelect = CAM_B;
	//enablePixyCS(g_CameraSelect);
	g_numBlocks = getBlocks(MAX_BLOCKS);
	//disablePixyCS(g_CameraSelect);

	return g_numBlocks;
}





