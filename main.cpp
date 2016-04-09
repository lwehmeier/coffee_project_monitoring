/*
 * main.cpp
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include "config.h"
#include "interface.h"
#include "lowLvlHandlers.h"
#include "highLvlHandlers.h"
#include "hal.h"
#include "systemError.h"
time_t lastCallllvl;
time_t lastCallhlvl;
int main()
{
	systemError("controller reset");
	hal_init();
	interface_init();
	lastCallllvl=getSystick();
	lastCallhlvl=getSystick();
	while(1)
	{
		if(getSystick()-lastCallllvl>LOWLVLHNDLRINTVL)
		{
			lowLvlHandlers_callHandlers();
			lastCallllvl=getSystick();
		}
		if(getSystick()-lastCallhlvl>HIGHLVLHNDLRINTVL)
		{
			highLvlHandlers_callHandlers();
			lastCallhlvl=getSystick();
		}
		if(interface_requestPending())
			interface_handleRequest();
	}
	return 0;
}


