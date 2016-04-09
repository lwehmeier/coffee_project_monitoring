/*
 * hal.h
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#ifndef HAL_H_
#define HAL_H_
#include "config.h"
/*i2c slave address for watchdog ping*/
#define I2CADDR 254
#ifdef __cplusplus
extern "C"{
#endif
typedef uint64_t time_t;
typedef void(*periodicCallback_fkt)(void);
void hal_init();

float get1V8Sample();
float get3V3Sample();
float get5V0Sample();
float get12V0Sample();
float get24V0Sample();

/*return i2c id of latest ping sender since the last call, 0 if none*/
uint8_t getWDTPing();

/*returns status of emergency shutdown button (0,1)*/
uint8_t getOffBtn();

/*shutdown 230v section*/
void hal_emergency_shutdown();
void hal_emergency_shutdown_revoke();

/*returns systick in ms*/
time_t getSystick();

/*nvram functions for logging*/
	/*appends message to log, returns message id*/
uint32_t nvram_putMessage(const char* c);
	/*get message from log*/
void nvram_getMessage(uint32_t id, char* data);
uint32_t nvram_getCurrentMsgID();
uint32_t nvram_getNumMessages();

/*register periodic callback (time in ms)*/
void registerPeriodicCallback(periodicCallback_fkt,uint16_t);

/*uart functions*/
void uart_putc(const char);
void uart_puts(const char*);
void uart_puti(const int32_t);
void uart_putf(const float);
unsigned int uart_getc();
/*returns true if all bytes were read or newline was reached, writes numBytesRead to sz, only returns 1 line (\n)*/
uint8_t uart_gets(char*,uint16_t* sz);
int32_t uart_geti();
float uart_getf();

#ifdef __cplusplus
};
#endif

#endif /* HAL_H_ */
