/*
 * fw_RTC.c
 *
 *  Created on: 29 de jun. de 2020
 *      Author: Nicoo
 */

#include "fw_RTC.h"

RTC_TIME_T FullTime;

void RTC_Init(void) {
	Chip_RTC_Init(LPC_RTC);
	Chip_RTC_CntIncrIntConfig(LPC_RTC, RTC_AMR_CIIR_IMSEC, DISABLE);
	Chip_RTC_ClearIntPending(LPC_RTC, RTC_INT_COUNTER_INCREASE | RTC_INT_ALARM);
	NVIC_DisableIRQ((IRQn_Type) RTC_IRQn);
	Chip_RTC_Enable(LPC_RTC, ENABLE);
	Chip_RTC_GetFullTime(LPC_RTC, &FullTime);

}

void RTC_SetFull(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
	FullTime.time[RTC_TIMETYPE_SECOND]  = second;
	FullTime.time[RTC_TIMETYPE_MINUTE]  = minute;
	FullTime.time[RTC_TIMETYPE_HOUR]    = hour;
	FullTime.time[RTC_TIMETYPE_DAYOFMONTH]  = day;
	FullTime.time[RTC_TIMETYPE_MONTH]   = month;
	FullTime.time[RTC_TIMETYPE_YEAR]    = year;

	Chip_RTC_SetFullTime(LPC_RTC, &FullTime);
}

void RTC_SetDate(uint16_t year, uint8_t month, uint8_t day) {
	Chip_RTC_GetFullTime(LPC_RTC, &FullTime);
	RTC_SetFull(year, month, day, FullTime.time[RTC_TIMETYPE_HOUR], FullTime.time[RTC_TIMETYPE_MINUTE], FullTime.time[RTC_TIMETYPE_SECOND]);
}

void RTC_SetTime(uint8_t hour, uint8_t minute, uint8_t second) {
	Chip_RTC_GetFullTime(LPC_RTC, &FullTime);
	RTC_SetFull(FullTime.time[RTC_TIMETYPE_YEAR], FullTime.time[RTC_TIMETYPE_MONTH], FullTime.time[RTC_TIMETYPE_DAYOFMONTH], hour, minute, second);
}

void RTC_GetFull(uint16_t * year, uint8_t * month, uint8_t * day, uint8_t * hour, uint8_t * minute, uint8_t * second) {
	Chip_RTC_GetFullTime(LPC_RTC, &FullTime);
	*year = FullTime.time[RTC_TIMETYPE_YEAR];
	*month = FullTime.time[RTC_TIMETYPE_MONTH];
	*day = FullTime.time[RTC_TIMETYPE_DAYOFMONTH];
	*hour = FullTime.time[RTC_TIMETYPE_HOUR];
	*minute = FullTime.time[RTC_TIMETYPE_MINUTE];
	*second = FullTime.time[RTC_TIMETYPE_SECOND];
}

void RTC_GetTime(uint8_t * hour, uint8_t * minute, uint8_t * second) {
	Chip_RTC_GetFullTime(LPC_RTC, &FullTime);
	*hour = FullTime.time[RTC_TIMETYPE_HOUR];
	*minute = FullTime.time[RTC_TIMETYPE_MINUTE];
	*second = FullTime.time[RTC_TIMETYPE_SECOND];
}
