/*
 * interface.cpp
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include <stdint.h>
#include <stdio.h>
#include "hal.h"
static time_t lastpub=0;
void interface_init()
{
	lastpub=getSystick();
}
uint8_t interface_requestPending()
{
	if(getSystick()-lastpub>500)
	{
		lastpub=getSystick();
		return true;
	}
	return false;
	//TODO: check for new messages
}
void interface_handleRequest()
{
	char t[75];
	snprintf(t,75,"1V8: %f, 3v3: %f, 5V0: %f, 12V0: %f, 24V0: %f\r\n", get1V8Sample(),get3V3Sample(), get5V0Sample(), get12V0Sample(), get24V0Sample());
	uart_puts(t);
	//TODO: handle/implement protocol
}
