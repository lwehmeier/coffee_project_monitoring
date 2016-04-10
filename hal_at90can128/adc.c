/*
 * adc.c
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../config.h"
#include "hal_at90can128.h"
volatile uint8_t adcc=0;
volatile uint8_t adcmap[]={ ADC1V8CHNL,ADC3V3CHNL,ADC5V0CHNL,ADC12V0CHNL, ADC24V0CHNL};
extern volatile uint16_t last1V8Sample,last3V3Sample,last5V0Sample,last12V0Sample,last24V0Sample;
void adc_init()
{
	ADMUX=(1<<REFS1)|(1<<REFS0);
	adc_setChannel(adcmap[0]);
	ADCSRA|=(1<<ADIE)|(1<<ADEN)|(1<<ADATE)|7;//max prescaler
	ADCSRB|=(1<<ADTS0)|(1<<ADTS2);//on timer1 compb match
	OCR1B=(F_CPU/1024ul)/1000/2ul;//set tim1compb (10hz update rate
	ADCSRA|=(1<<ADSC);
}
void adc_setChannel(uint8_t ch)
{
	ADMUX=(ADMUX&0xA0)|(ch&0x1F);
}
ISR(ADC_vect)
{
	switch(adcc)
	{
	case 0:
		last1V8Sample=ADC;
		break;
	case 1:
		last3V3Sample=ADC;
		break;
	case 2:
		last5V0Sample=ADC;
		break;
	case 3:
		last12V0Sample=ADC;
		break;
	case 4:
		last24V0Sample=ADC;
		break;
	}
	adcc++;
	if(adcc>=5)
		adcc=0;
	adc_setChannel(adcmap[adcc]);
	ADCSRA|=(1<<ADSC);
}
