/*
 * eeprom.h
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */

#ifndef HAL_AT90CAN128_EEPROM_H_
#define HAL_AT90CAN128_EEPROM_H_
#include "hal_at90can128.h"
#include "../hal.h"


uint8_t nvram_addEntry(const char* data, uint8_t size);
void nvram_readEntry(const char* data, uint8_t *size, uint8_t id);
#endif /* HAL_AT90CAN128_EEPROM_H_ */
