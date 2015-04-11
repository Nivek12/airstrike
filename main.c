/*
 * AIRSTIKE
 *
 */

#define TRACK_TIMER_INT_MSEC	10

#include <stdio.h>

// Subsystem includes
#include "network.h"
#include "pwm.h"
#include "target.h"
#include "servos.h"
#include "laser.h"

//Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"

//Interface includes
#include "timer_if.h"

#include "HttpCore.h"

//PinMux include
#include "pin_mux_config.h"

//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************

//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void BoardInit(void)
{
	/* In case of TI-RTOS vector table is initialize by OS itself */
	#ifndef USE_TIRTOS
	  //
	  // Set vector table base
	  //
	#if defined(ccs)
		MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
	#endif
	#if defined(ewarm)
		MAP_IntVTableBaseSet((unsigned long)&__vector_table);
	#endif
	#endif
	  //
	  // Enable Processor
	  //
	  MAP_IntMasterEnable();
	  MAP_IntEnable(FAULT_SYSTICK);

	  PRCMCC3200MCUInit();
}

void TimerBaseA0IntHandler(void)
{
	TargetMainLoopTask();

	//SetPitchAngle(0);
	//SetYawAngle(0);

	if (foundTarget())
	{
		float servo_angles[3];
		getServoAngles(servo_angles);
		//printf("Servo-Angles  Yaw: %5f, Pitch: %5f\n\n", servo_angles[2], servo_angles[1]);
		SetPitchAngle(servo_angles[1]);
		SetYawAngle(servo_angles[2]);
	}
	else
	{
		SetPitchAngle(0);
		SetYawAngle(0);
	}

	if (onTarget())
	{
		SetLaserPower(0.9);
	}
	else
	{
		SetLaserPower(0);
	}

	printf("WE TRIED!\n");
	Timer_IF_InterruptClear(TIMERA0_BASE);
}

void StartTrackTimer()
{
	Timer_IF_Init(PRCM_TIMERA0, TIMERA0_BASE, TIMER_CFG_PERIODIC, TIMER_BOTH, 0);
	Timer_IF_IntSetup(TIMERA0_BASE, TIMER_BOTH, TimerBaseA0IntHandler);
	Timer_IF_Start(TIMERA0_BASE, TIMER_BOTH, TRACK_TIMER_INT_MSEC);
}

/*
 * main.c
 */
int main(void) {
	
	BoardInit();
	PinMuxConfig();
	InitPWMModules();
	InitTargetModule();
	HTTPServerInit();
	StartTrackTimer();


	while (1)
	{
		_SlNonOsMainLoopTask();

		SetLaserPower(0);
		MAP_UtilsDelay(8000000);
		SetLaserPower(0.99);
		MAP_UtilsDelay(8000000);

		//TargetMainLoopTask();

//		SetLaserPower(0);
//		SetPitchAngle(0);
//		SetYawAngle(0);
	}


}
