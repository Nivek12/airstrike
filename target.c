/*
 * target.c
 *
 *  Created on: Mar 19, 2015
 *      Author: Chris
 */
#include "target.h"
#define M_PI 3.14159265358979323846
#define RANGE 1000000
#define PIXY_PIXEL_AZ 75/320
#define PIXY_PIXEL_EL 47/200
#define PIXY_PIXEL_WIDTH  320
#define PIXY_PIXEL_HEIGHT 200
#define S2P_X 0
#define S2P_Y 0
#define S2P_Z 0

Block g_target = {0, 0, 0, 0, 0, 0};
uint16_t c_triesSinceLastDet = 10;

bool foundTarget(void) {
	return (c_triesSinceLastDet < 5);
}

void InitTargetModule(void) {
	InitSPIModule();
	init();

}

char* getTargetString(char * targetString) {
	sprintf(targetString, "%u|%u|%u|%u",
			(unsigned int) g_target.x, (unsigned int) g_target.y,
			(unsigned int) g_target.height, (unsigned int) g_target.width);
	return targetString;
}

uint8_t TargetMainLoopTask(void)
{
	g_numBlocks = getBlocks(MAX_BLOCKS);
	if (g_numBlocks > 0)
	{
		g_target = g_blocks[0];
		c_triesSinceLastDet = 0;
	} else
	{
		c_triesSinceLastDet++;
	}
	return g_numBlocks;
}

float* getTargetSphericalCoords(float* target_coords)
{
	target_coords[0] = RANGE;

	float p_x = g_target.x    - (PIXY_PIXEL_WIDTH/2);
	float p_y = (-g_target.y) + (PIXY_PIXEL_HEIGHT/2);

	//printf("Pixy Pre-00   X: %5u,   Y: %5u\n" , g_target.x, g_target.y);
	//printf("Pixy Pixels   X: %5f,   Y: %5f\n", p_x, p_y);

	target_coords[0] = RANGE;
	target_coords[1] = 90 - (p_y*PIXY_PIXEL_EL);
	target_coords[2] = (-p_x)*PIXY_PIXEL_AZ;


	//printf("Pixy Angles   Yaw: %5f, Pitch: %5f\n", target_coords[2], 90-target_coords[1]);
	return target_coords;
}

float* getServoAngles(float *servo_s_coords)
{
	float target_s_coords[3];
	if (foundTarget())
	{

		getTargetSphericalCoords(target_s_coords);
		float target_c_coords[3];
		float servo_c_coords[3];
		float rad_theta = target_s_coords[1] * (M_PI/180);
		float rad_phi   = target_s_coords[2] * (M_PI/180);
		target_c_coords[0] = target_s_coords[0] * sin(rad_theta) * cos(rad_phi);
		target_c_coords[1] = target_s_coords[0] * sin(rad_theta) * sin(rad_phi);
		target_c_coords[2] = target_s_coords[0] * cos(rad_theta);

		servo_c_coords[0] = S2P_X + target_c_coords[0];
		servo_c_coords[1] = S2P_Y + target_c_coords[1];
		servo_c_coords[2] = S2P_Z + target_c_coords[2];

		printf("Pixy:  %3.5f, %3.5f, %3.5f\n"
			   "S2P:   %3.5f, %3.5f, %3.5f\n"
			   "Servo: %3.5f, %3.5f, %3.5f\n",
			   target_c_coords[0], target_c_coords[1], target_c_coords[2],
			   S2P_X,              S2P_Y,              S2P_Z,
			   servo_c_coords[0],  servo_c_coords[1],  servo_c_coords[2]);

		servo_s_coords[0] = sqrt((servo_c_coords[0] * servo_c_coords[0]) +
								 (servo_c_coords[1] * servo_c_coords[1]) +
							     (servo_c_coords[2] * servo_c_coords[2]));
		servo_s_coords[1] = 90 - (acos(servo_c_coords[2]/servo_s_coords[0]) * (180.0 / M_PI));
		servo_s_coords[2] = atan(servo_c_coords[1]/servo_c_coords[0]) * (180.0 / M_PI);
	}
	else
	{
		servo_s_coords[0] = 0;
		servo_s_coords[1] = 0;
		servo_s_coords[2] = 0;
	}

	return servo_s_coords;
}



