/*
 * fw_RTC.h
 *
 *  Created on: 29 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef FW_RTC_H_
#define FW_RTC_H_

#include "chip.h"

void RTC_Init(void);
void RTC_SetFull(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
void RTC_SetDate(uint16_t year, uint8_t month, uint8_t day);
void RTC_SetTime(uint8_t hour, uint8_t minute, uint8_t second);
void RTC_GetFull(uint16_t * year, uint8_t * month, uint8_t * day, uint8_t * hour, uint8_t * minute, uint8_t * second);
void RTC_GetTime(uint8_t * hour, uint8_t * minute, uint8_t * second);

#endif /* FW_RTC_H_ */
