/*
 * logger.cpp
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include <stdio.h>
#include <string.h>
#include "hal.h"
#include "systemError.h"
#include "logger.h"
#include "config.h"
const char* loglevels[MAXLOGLEVEL]=
{
		"INVLD:%d:",
		"ERR:%d:"
		"WARN:%d:"
};


char logger_currentMsg_read[LOGMAXMESSAGESZ];
char logger_currentMsgSz_read=0;
char logger_currentMsg_write[LOGMAXMESSAGESZ];
char logger_currentMsgSZ_write=0;
extern "C" void logMessage(loglevel_t level, const char* message, uint8_t messageLength)
{
	if(level>=MAXLOGLEVEL)
		level=0;
	snprintf(logger_currentMsg_write,LOGMAXMESSAGESZ-LOGMAXMESSAGEPAYLOAD,loglevels[level],getSystick());
	logger_currentMsgSZ_write=strlen(logger_currentMsg_write);
	strncpy(logger_currentMsg_write+logger_currentMsgSZ_write,message,LOGMAXMESSAGEPAYLOAD);
	logger_currentMsgSZ_write=strnlen(message,LOGMAXMESSAGEPAYLOAD);
	logger_currentMsg_write[LOGMAXMESSAGESZ-1]=0;
	logger_currentMsgSZ_write=strnlen(logger_currentMsg_write,LOGMAXMESSAGESZ);
	nvram_putMessage(logger_currentMsg_write);
}
