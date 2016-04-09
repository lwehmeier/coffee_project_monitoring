/*
 * lowLvlHandlers.cpp
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include <string.h>
#include "config.h"
#include "emergencyShutdown.h"
#include "lowLvlHandlers.h"
#include "logger.h"
#include "hal.h"
#include <stdio.h>
signal_t lowLvlSignals;
time_t wdtlastPing;
/*functions are called in order, functions can clear signals by removing the corresponding bit from their return value*/
signalhndlr_fkt lowLvlHndlrs[]=
{
		handleOffBtn,
		handleNewSample,
		handleWDTPing
};

void lowLvlHandlers_callHandlers()
{
	lowLvlSignals&=0x07;//lower 3bit only, lowLvlFunctions may only handle lowLvl signals
	uint8_t arrSz=sizeof(lowLvlHndlrs) / sizeof(lowLvlHndlrs[0]);
	for(uint8_t j=0;j<arrSz;j++)
	{
		signal_t ret_signal=lowLvlHndlrs[j](lowLvlSignals);
		lowLvlSignals=ret_signal&0x7;
		highLvlSignals|=(ret_signal&~(ret_signal&0x07));
	}
}

signal_t handleNewSample(signal_t signal)
{
	if(!(signal&signal_ADCSample))
		return signal;
	signal&=~signal_ADCSample;
	float voltage=get1V8Sample();
	if(voltage<ERR1V8_LOW)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"1V8 low: %f",voltage);
		logMessage(LOGLEVEL_ERR,msg,strlen(msg));
		signal|=signal_Error1V8;
	}
	else if(voltage<WARN1V8_LOW)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"1V8 low: %f",voltage);
		logMessage(LOGLEVEL_WARN,msg,strlen(msg));
		signal|=signal_Warn1V8;
	}
	else if(voltage>ERR1V8_HIGH)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"1V8 high: %f",voltage);
		logMessage(LOGLEVEL_ERR,msg,strlen(msg));
		signal|=signal_Error1V8;
	}
	else if(voltage>WARN1V8_HIGH)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"1V8 high: %f",voltage);
		logMessage(LOGLEVEL_WARN,msg,strlen(msg));
		signal|=signal_Warn1V8;
	}
	voltage=get3V3Sample();
	if(voltage<ERR3V3_LOW)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"3V3 low: %f",voltage);
		logMessage(LOGLEVEL_ERR,msg,strlen(msg));
		signal|=signal_Error3V3;
	}
	else if(voltage<WARN3V3_LOW)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"3V3 low: %f",voltage);
		logMessage(LOGLEVEL_WARN,msg,strlen(msg));
		signal|=signal_Warn3V3;
	}
	else if(voltage>ERR3V3_HIGH)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"3V3 high: %f",voltage);
		logMessage(LOGLEVEL_ERR,msg,strlen(msg));
		signal|=signal_Error3V3;
	}
	else if(voltage>WARN3V3_HIGH)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"3V3 high: %f",voltage);
		logMessage(LOGLEVEL_WARN,msg,strlen(msg));
		signal|=signal_Warn3V3;
	}
	voltage=get5V0Sample();
	if(voltage<ERR5V0_LOW)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"5V0 low: %f",voltage);
		logMessage(LOGLEVEL_ERR,msg,strlen(msg));
		signal|=signal_Error5V0;
	}
	else if(voltage<WARN5V0_LOW)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"5V0 low: %f",voltage);
		logMessage(LOGLEVEL_WARN,msg,strlen(msg));
		signal|=signal_Warn5V0;
	}
	else if(voltage>ERR5V0_HIGH)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"5V0 high: %f",voltage);
		logMessage(LOGLEVEL_ERR,msg,strlen(msg));
		signal|=signal_Error5V0;
	}
	else if(voltage>WARN5V0_HIGH)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"5V0 high: %f",voltage);
		logMessage(LOGLEVEL_WARN,msg,strlen(msg));
		signal|=signal_Warn5V0;
	}
	voltage=get12V0Sample();
	if(voltage<ERR12V0_LOW)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"12V0 low: %f",voltage);
		logMessage(LOGLEVEL_ERR,msg,strlen(msg));
		signal|=signal_Error12V0;
	}
	else if(voltage<WARN12V0_LOW)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"12V0 low: %f",voltage);
		logMessage(LOGLEVEL_WARN,msg,strlen(msg));
		signal|=signal_Warn12V0;
	}
	else if(voltage>ERR12V0_HIGH)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"12V0 high: %f",voltage);
		logMessage(LOGLEVEL_ERR,msg,strlen(msg));
		signal|=signal_Error12V0;
	}
	else if(voltage>WARN12V0_HIGH)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"12V0 high: %f",voltage);
		logMessage(LOGLEVEL_WARN,msg,strlen(msg));
		signal|=signal_Warn12V0;
	}
	voltage=get24V0Sample();
	if(voltage<ERR24V0_LOW)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"24V0 low: %f",voltage);
		logMessage(LOGLEVEL_ERR,msg,strlen(msg));
		signal|=signal_Error24V0;
	}
	else if(voltage<WARN24V0_LOW)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"24V0 low: %f",voltage);
		logMessage(LOGLEVEL_WARN,msg,strlen(msg));
		signal|=signal_Warn24V0;
	}
	else if(voltage>ERR24V0_HIGH)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"24V0 high: %f",voltage);
		logMessage(LOGLEVEL_ERR,msg,strlen(msg));
		signal|=signal_Error24V0;
	}
	else if(voltage>WARN24V0_HIGH)
	{
		char msg[LOGMAXMESSAGEPAYLOAD];
		snprintf(msg,LOGMAXMESSAGEPAYLOAD,"24V0 high: %f",voltage);
		logMessage(LOGLEVEL_WARN,msg,strlen(msg));
		signal|=signal_Warn24V0;
	}
	return signal;
}
signal_t handleWDTPing(signal_t signal)
{
	if(signal&signal_WatchdogPing)
		wdtlastPing=getSystick();
	if(getSystick()-wdtlastPing<ERRWDTTIMEOUT)
	{
		logMessage(LOGLEVEL_ERR,"watchdog timeout",strlen("watchdog timeout"));
		signal|=signal_WDTError;
	}
	else if(getSystick()-wdtlastPing<WARNWDTTIMEOUT)
	{
		logMessage(LOGLEVEL_WARN,"watchdog near timeout",strlen("watchdog near timeout"));
		signal|=signal_WDTError;
	}
	signal&=~signal_WatchdogPing;
	return signal;
}
signal_t handleOffBtn(signal_t signal)
{

	if(!(signal&signal_WatchdogPing))
		return signal;
	signal&=~signal_OffBtn;
	emergency_shutdown();
	logMessage(LOGLEVEL_ERR,"em. off btn pressed",strlen("em. off btn pressed"));
	return signal;
}
void lowLvlHandlers_init()
{
	wdtlastPing=getSystick();
}
