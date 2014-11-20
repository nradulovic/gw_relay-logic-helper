/* 
 * File:   rtc.h
 * Author: nenad
 *
 * Created on April 15, 2014, 12:13 AM
 */

#ifndef RTC_H
#define	RTC_H

#include <stdint.h>
#include <stdbool.h>

#include "base/error.h"
#include "driver/i2c.h"

#ifdef	__cplusplus
extern "C" {
#endif

extern const struct i2c_slave_config rtc_i2c_config;

struct rtc_time {
    uint16_t            year;
    uint8_t             month;
    uint8_t             day;
    uint8_t             hour;
    uint8_t             minute;
    uint8_t             second;
};

void rtc_init_driver(struct i2c_bus * i2c_bus);
void rtc_term_driver(void);
esError rtc_set_time_i(const struct rtc_time * time);
esError rtc_get_time_i(struct rtc_time * time);
void rtc_tick_i(void);
bool rtc_is_active(void);

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

