/*
 * AIRSTIKE
 *
 */

#include <stdio.h>

// Subsystem includes
#include "network.h"
#include "pwm.h"
#include "target.h"

//Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"

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

/*
 * main.c
 */
int main(void) {
	
	BoardInit();
	PinMuxConfig();
	InitPWMModules();
	InitTargetModule();
	HTTPServerInit();

	//PWM testing
	UpdateDutyCycle(TIMERA2_BASE, TIMER_B, 100);
	while(1)
	{
		_SlNonOsMainLoopTask();
		TargetMainLoopTask();
	}
}
