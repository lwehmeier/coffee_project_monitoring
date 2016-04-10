/*
 * hal_at90can128.c
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "../hal.h"
#include "hal_at90can128.h"
#include "../config.h"
#include "twislave.h"
#include "uart.h"
#include "eeprom.h"
#include "systick.h"
#include "adc.h"

uint8_t WDTCLIENTIDS[NUMWDTCLIENTS]=
{
		0x01
};
static float voltages[5];

volatile uint16_t last1V8Sample=0,last3V3Sample=0,last5V0Sample=0,last12V0Sample=0,last24V0Sample=0;
static uint8_t wdtPing=0;
volatile time_t systick;
/***
 * additional AT90CAN128 stuff
 */
float getVoltageFromADCVal(uint16_t val)
{
	return ((float)val)/((float)ADCMAXVAL)*ADCREFVAL;
}

/***
 * HAL implementation
 */
void hal_init()
{
	init_twi_slave(I2CADDR);
	i2cdata[0]=0;
	uart_init(UART_BAUD_SELECT(UARTBAUD,F_CPU));
	systick_init();
	adc_init();
	sei();
}

float get1V8Sample()
{
	return getVoltageFromADCVal(last1V8Sample)*ADC1V8DIV;
}
float get3V3Sample()
{
	return getVoltageFromADCVal(last3V3Sample)*ADC3V3DIV;
}
float get5V0Sample()
{
	return getVoltageFromADCVal(last5V0Sample)*ADC5V0DIV;
}
float get12V0Sample()
{
	return getVoltageFromADCVal(last12V0Sample)*ADC12V0DIV;
}
float get24V0Sample()
{
	return getVoltageFromADCVal(last24V0Sample)*ADC24V0DIV;
}

/*return i2c id of latest ping sender since the last call, 0 if none*/
uint8_t getWDTPing()
{
	uint8_t id=i2cdata[0];
	i2cdata[0]=0;
	return id;
}

/*returns status of emergency shutdown button (0,1)*/
uint8_t getOffBtn()
{
	return OFFBTNPIN&OFFBTNPINNR?1:0;
}

/*shutdown 230v section*/
void hal_emergency_shutdown()
{
	OFFPORT&=~OFFBTNPINNR;
}
void hal_emergency_shutdown_revoke()
{
	OFFPORT|=OFFBTNPINNR;
}
/*returns systick in ms*/
time_t getSystick()
{
	return systick;
}

/*nvram functions for logging*/
	/*appends message to log, returns message id*/
uint32_t nvram_putMessage(const char* c)
{
	return nvram_addEntry(c,strnlen(c,LOGMAXMESSAGESZ));
}
	/*get message from log*/
void nvram_getMessage(uint32_t id, char* data)
{
	nvram_readEntry(data,LOGMAXMESSAGESZ,id);
}
extern uint8_t nvramPtr;
uint32_t nvram_getCurrentMsgID()
{
	return nvramPtr;
}
uint32_t nvram_getNumMessages()
{
	return NVRAMMAXENTRIES;
}

/*register periodic callback (time in ms)*/
/*TODO: currently every ms*/
void registerPeriodicCallback(periodicCallback_fkt f,uint16_t time)
{
	systick_registerCallback(f);
}

/*uart functions*/
void uart_puti(const int32_t i)
{
	char t[10];
	snprintf(t,10,"%d",i);
	uart_puts(t);
}
void uart_putf(const float i)
{
	char t[10];
	snprintf(t,10,"%f",(double)i);
	uart_puts(t);
}
	/*returns true if all bytes were read or newline was reached, writes numBytesRead to sz, only returns 1 line (\n)*/
uint8_t uart_gets(char* msg,uint16_t* sz)
{
	uint16_t s=*sz-1;
	int16_t i=0;
	for(;i<s;i++)
	{
		msg[i]=uart_getc();
		if(msg[i]==UART_NO_DATA)
		{
			msg[i]=0;
			*sz=i-1>0?i-1:0;
			return 0;
		}
		if(msg[i]=='\n')
		{
			msg[i+1]=0;
			break;
		}
	}
	*sz=i;
	return 1;
}
int32_t uart_geti();
float uart_getf();
