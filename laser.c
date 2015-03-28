/*
 * laser.c
 *
 *  Created on: Mar 28, 2015
 *      Author: Kevin
 */

#include "laser.h"

#define PULSE_WIDTH_US	20000

void setLaserPower(float percent)
{
	int width = (int)(PULSE_WIDTH_US*percent);
	UpdateDutyCycle(TIMERA3_BASE, TIMER_B, width);
}



