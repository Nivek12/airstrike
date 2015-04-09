/*
 * target.h
 *
 *  Created on: Mar 14, 2015
 *      Author: Chris
 */

#ifndef TARGET_H_
#define TARGET_H_

#include <stdbool.h>
#include <math.h>
#include "pixy.h"

extern Block g_target;

bool foundTarget(void);
void InitTargetModule(void);
char* getTargetString(char * targetString);
uint8_t TargetMainLoopTask(void);
float* getTargetSphericalCoords(float*);
float* getServoAngles(float*);

#endif /* TARGET_H_ */
