/*
 * hal_at90can128.h
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */

#ifndef HAL_AT90CAN128_H_
#define HAL_AT90CAN128_H_
#include <avr/io.h>
#include "../config.h"
#define ADCMAXVAL 1023
#define ADCREFVAL 2.56f
#define OFFBTNPORT PORTB
#define OFFBTNDDR DDRB
#define OFFBTNPIN PINB
#define OFFBTNPINNR PINB2
#define OFFDDR DDRB
#define OFFPORT PORTB
#define OFFPINNR PINB2
#define NVRAMSZ 4096
#define NVRAMMAXENTRIES (NVRAMSZ/LOGMAXMESSAGESZ)

#ifdef __cplusplus
extern "C"{
#endif


#ifdef __cplusplus
};
#endif
#endif /* HAL_AT90CAN128_H_ */
