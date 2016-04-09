/*
 * systick.h
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */

#ifndef HAL_AT90CAN128_SYSTICK_H_
#define HAL_AT90CAN128_SYSTICK_H_

typedef void(*systick_cb)(void);
void systick_init();
uint8_t systick_registerCallback(void (*cb)(void));
#endif /* HAL_AT90CAN128_SYSTICK_H_ */
