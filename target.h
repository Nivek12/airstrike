/*
 * target.h
 *
 *  Created on: Mar 14, 2015
 *      Author: Chris
 */

#ifndef TARGET_H_
#define TARGET_H_

#include <stdbool.h>
#include "pixy.h"

bool foundTarget(void);
void InitTargetModule(void);
char* getFaggotBlocksForKevinTheFag(char * faggotString);
uint8_t TargetMainLoopTask(void);

#endif /* TARGET_H_ */
