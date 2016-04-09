/*
 * highLvlHandlers.cpp
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include "highLvlHandlers.h"
signal_t highLvlSignals;
/*functions are called in order, functions can clear signals by removing the corresponding bit from their return value*/
signalhndlr_fkt highLvlHndlrs[]=
{
//		handleERR1V8,
//		handleWARN1V8
};
void highLvlHandlers_callHandlers()
{
	highLvlSignals&=0x07;//lower 3bit only, lowLvlFunctions may only handle lowLvl signals
	uint8_t arrSz=sizeof(highLvlHndlrs) / sizeof(highLvlHndlrs[0]);
	for(uint8_t j=0;j<arrSz;j++)
	{
		highLvlSignals=highLvlHndlrs[j](highLvlSignals);
	}
}
signal_t handleERR1V8(signal_t signal)
{
	return signal;
}
signal_t handleWARN1V8(signal_t signal)
{
	return signal;
}
