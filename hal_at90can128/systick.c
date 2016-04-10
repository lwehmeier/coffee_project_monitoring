/*
 * systick.c
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../hal.h"
#include "systick.h"
static uint8_t numCB=0;
static systick_cb cbf[10];
void systick_init()
{
	TCCR1A=0;
	TCNT1=0;
	TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS10);//CTCmode, prescaler 1024
	OCR1A=(F_CPU/1024ul)/1000ul;
	TIMSK1|=(1<<OCIE1A);
}
uint8_t systick_registerCallback(void (*cb)(void))
{
	if(numCB>=9)
		return 0;
	cbf[numCB]=cb;
	numCB++;
}
extern volatile time_t systick;
ISR(TIMER1_COMPA_vect)
{
	systick++;
	for(uint8_t i=0; i<numCB;i++)
		cbf[i]();
}
