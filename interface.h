/*
 * interface.h
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

void interface_init();
uint8_t interface_requestPending();
void interface_handleRequest();

#endif /* INTERFACE_H_ */
