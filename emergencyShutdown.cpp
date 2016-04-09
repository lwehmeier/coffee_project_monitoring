/*
 * emergencyShutdown.cpp
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include <string.h>
#include "hal.h"
#include "logger.h"
extern "C" void emergency_shutdown()
{
	hal_emergency_shutdown();
	logMessage(LOGLEVEL_ERR,"EM. SHTDWN. triggered",strlen("EM. SHTDWN. triggered"));

}
