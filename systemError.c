/*
 * systemError.c
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include <string.h>
#include "hal.h"
#include "logger.h"
#include "emergencyShutdown.h"
void systemError(const char* msg)
{
	emergency_shutdown();
	logMessage(LOGLEVEL_ERR,msg, strlen(msg));
}
