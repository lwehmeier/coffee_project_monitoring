/*
 * highLvlHandlers.h
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */

#ifndef HIGHLVLHANDLERS_H_
#define HIGHLVLHANDLERS_H_
#include "signals.h"

extern signal_t highLvlSignals;
extern signalhndlr_fkt highLvlHndlrs[];
void highLvlHandlers_callHandlers();
void handleERR1V8();
signal_t ERR1V8hndlr(signal_t);
signal_t handleWARN1V8(signal_t);
#endif /* HIGHLVLHANDLERS_H_ */
