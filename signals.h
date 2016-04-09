/*
 * signals.h
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */

#ifndef SIGNALS_H_
#define SIGNALS_H_
#include <stdint.h>
typedef uint16_t signal_t;
typedef signal_t (*signalhndlr_fkt)(signal_t);
enum
{
	/*low level signals*/
	signal_ADCSample=(1<<0),
	signal_WatchdogPing=(1<<1),
	signal_OffBtn=(1<<2),
	/*high level signals*/
		/*voltage supervision signals*/
	signal_Warn1V8=(1<<3), signal_Error1V8=(1<<4),
	signal_Warn3V3=(1<<5), signal_Error3V3=(1<<6),
	signal_Warn5V0=(1<<7), signal_Error5V0=(1<<8),
	signal_Warn12V0=(1<<9), signal_Error12V0=(1<<10),
	signal_Warn24V0=(1<<11), signal_Error24V0=(1<<12),
		/*Watchdog signals*/
	signal_WDTWarn=(1<<13), signal_WDTError=(1<<14),
};



#endif /* SIGNALS_H_ */
