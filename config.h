/*
 * config.h
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include <stdint.h>


#define LOWLVLHNDLRINTVL 5
#define HIGHLVLHNDLRINTVL 10


/*UART CFG (hardcoded 8N1)*/
#define UARTBAUD 38400

/*ADC config*/
#define ADC1V8CHNL 0
#define ADC3V3CHNL 1
#define ADC5V0CHNL 2
#define ADC12V0CHNL 3
#define ADC24V0CHNL 4
#define ADC1V8DIV 1
#define ADC3V3DIV 2
#define ADC5V0DIV 3
#define ADC12V0DIV 10
#define ADC24V0DIV 15

/*off button and emergency off cfg see mcu specific hal*/

/*devices to receive pings from*/
#define NUMWDTCLIENTS 1
extern uint8_t WDTCLIENTIDS[NUMWDTCLIENTS];

/*log configuration*/
#define LOGMAXMESSAGESZ 64
#define LOGMAXMESSAGEPAYLOAD 50

/*voltage settings*/
#define WARN1V8_LOW 1.7f
#define WARN1V8_HIGH 1.9f
#define ERR1V8_LOW 1.5f
#define ERR1V8_HIGH 2.1f
#define WARN3V3_LOW 3.0f
#define WARN3V3_HIGH 3.5f
#define ERR3V3_LOW 2.8f
#define ERR3V3_HIGH 3.6f
#define WARN5V0_LOW 4.6f
#define WARN5V0_HIGH 5.3f
#define ERR5V0_LOW 4.4f
#define ERR5V0_HIGH 5.5f
#define WARN12V0_LOW 11.2f
#define WARN12V0_HIGH 12.5f
#define ERR12V0_LOW 10.9f
#define ERR12V0_HIGH 13.0f
#define WARN24V0_LOW 22.0f
#define WARN24V0_HIGH 24.5f
#define ERR24V0_LOW 21.5f
#define ERR24V0_HIGH 25.3f

/*WDT ping settings in ms*/
#define WARNWDTTIMEOUT 50
#define ERRWDTTIMEOUT 150


#endif /* CONFIG_H_ */
