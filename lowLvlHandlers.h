/*
 * lowLvlHandlers.h
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */

#ifndef LOWLVLHANDLERS_H_
#define LOWLVLHANDLERS_H_
#include <stdint.h>
#include "signals.h"
#include "highLvlHandlers.h"
extern signal_t lowLvlSignals;
extern signalhndlr_fkt lowLvlHndlrs[];
void lowLvlHandlers_callHandlers();
signal_t handleNewSample(signal_t);
signal_t handleWDTPing(signal_t);
signal_t handleOffBtn(signal_t);

#endif /* LOWLVLHANDLERS_H_ */
