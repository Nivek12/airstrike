/*
 * servos.c
 *
 *  Created on: Mar 19, 2015
 *      Author: Kevin
 */

#include "servos.h"

#define SERVO_GAIN		1
#define SERVO_OFFSET	1

//2ms = 25.5
//1ms = 12.75
void SetPitchAngle(float degrees)
{

	UpdateDutyCycle(TIMERA2_BASE, TIMER_B, 100);
}

void SetYawAngle(float degrees)
{

	UpdateDutyCycle(TIMERA3_BASE, TIMER_A, 100);
}

int DegreesToWidth(float degrees)
{

	return -1;
}

