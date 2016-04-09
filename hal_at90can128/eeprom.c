/*
 * eeprom.c
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */
#include <avr/eeprom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eeprom.h"
/**
 * layout
 * nvramptr
 * fat
 * buffer
 */
static uint8_t nvram_storage[4096] EEMEM;
static uint16_t nvramFAT[NVRAMMAXENTRIES];
uint8_t nvramPtr;
static uint16_t rbStart=NVRAMMAXENTRIES*2+1;//FAT+RBpointer
/*returns id*/
uint8_t nvram_addEntry(const char* data, uint8_t size)
{
	nvramPtr++;
	nvramPtr%=NVRAMMAXENTRIES;
	eeprom_write_word(&nvram_storage[nvramPtr*2], rbStart+nvramPtr*LOGMAXMESSAGESZ);
	eeprom_write_block(data, &nvram_storage[rbStart+nvramPtr*LOGMAXMESSAGESZ], size);
	return nvramPtr;
}
void nvram_readEntry(const char* data, uint8_t *size, uint8_t id)
{
	eeprom_read_block(data, &nvram_storage[rbStart+id*LOGMAXMESSAGESZ], size);
}
