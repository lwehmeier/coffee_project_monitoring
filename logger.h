/*
 * logger.h
 *
 *  Created on: 09.04.2016
 *      Author: wehmeier
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#ifdef __cplusplus
extern "C"{
#endif
typedef uint8_t loglevel_t;
void logMessage(loglevel_t level, const char* message, uint8_t messageLength);
enum{LOGLEVEL_ERR=1,LOGLEVEL_WARN,
	MAXLOGLEVEL};
extern const char* loglevels[];
#ifdef __cplusplus
};
#endif
#endif /* LOGGER_H_ */
