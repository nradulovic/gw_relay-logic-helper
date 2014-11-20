
#include "driver/rtc.h"
#include "driver/i2c.h"
#include "base/error.h"
#include "base/debug.h"
#include <string.h>
#include <xc.h>

#define CONFIG_DEFAULT_YEAR             2014
#define CONFIG_DEFAULT_MONTH            1
#define CONFIG_DEFAULT_DAY              1
#define CONFIG_DEFAULT_HOUR             0
#define CONFIG_DEFAULT_MINUTE           0
#define CONFIG_DEFAULT_SECOND           0

#define REG_CONTROL_1                   0x00
#define REG_CONTROL_INT                 0x01
#define REG_CONTROL_INT_FLAG            0x02
#define REG_CONTROL_STATUS              0x03
#define REG_CONTROL_RESET               0x04

#define REG_SECONDS                     0x08
#define REG_MINUTES                     0x09
#define REG_HOURS                       0x0a
#define REG_DAYS                        0x0b
#define REG_WEEKDAYS                    0x0c
#define REG_MONTHS                      0x0d
#define REG_YEARS                       0x0e

#define REG_ALARM_SECONDS               0x10
#define REG_ALARM_MINUTE                0x11
#define REG_ALARM_HOUR                  0x12
#define REG_ALARM_DAYS                  0x13
#define REG_ALARM_WEEKDAYS              0x14
#define REG_ALARM_MONTHS                0x15
#define REG_ALARM_YEAR                  0x16

#define REG_TIMER_LOW                   0x18
#define REG_TIMER_HIGH                  0x19

#define REG_TEMPERATURE                 0x20

#define CONTROL_1_WE                    (0x1u << 0)
#define CONTROL_1_TE                    (0x1u << 1)
#define CONTROL_1_TAR                   (0x1u << 2)
#define CONTROL_1_EERE                  (0x1u << 3)
#define CONTROL_1_SRON                  (0x1u << 4)
#define CONTROL_1_TD0                   (0x1u << 5)
#define CONTROL_1_TD1                   (0x1u << 6)
#define CONTROL_1_CLK_INT               (0x1u << 7)

#define CONTROL_INT_AIE                 (0x1u << 0)
#define CONTROL_INT_TIE                 (0x1u << 1)
#define CONTROL_INT_V1IE                (0x1u << 2)
#define CONTROL_INT_V2IE                (0x1u << 3)
#define CONTROL_INT_SRIE                (0x1u << 4)

#define CONTROL_INT_FLAG_AF             (0x1u << 0)
#define CONTROL_INT_FLAG_TF             (0x1u << 1)
#define CONTROL_INT_FLAG_V1IF           (0x1u << 2)
#define CONTROL_INT_FLAG_V2IF           (0x1u << 3)
#define CONTROL_INT_FLAG_SRF            (0x1u << 4)

#define CONTROL_STATUS_V1F              (0x1u << 2)
#define CONTROL_STATUS_V2F              (0x1u << 3)
#define CONTROL_STATUS_SR               (0x1u << 4)
#define CONTROL_STATUS_PON              (0x1u << 5)
#define CONTROL_STATUS_EEBUSY           (0x1u << 7)

#define CONTROL_RESET_SYSR              (0x1u << 4)

#define HOURS_12_24_MODE                (0x1u << 6)
#define HOURS_AM_PM                     (0x1u << 5)

#define RTC_SLAVE_ADDRESS               0xac
#define RTC_READ_CMD                    (RTC_SLAVE_ADDRESS |  0x1u)
#define RTC_WRITE_CMD                   (RTC_SLAVE_ADDRESS & ~0x1u)


struct rtc_time_registers
{
    uint8_t             seconds;
    uint8_t             minutes;
    uint8_t             hours;
    uint8_t             days;
    uint8_t             weekdays;
    uint8_t             months;
    uint8_t             years;
};

static struct i2c_bus * g_i2c_rtc_bus;

static struct rtc_time   g_current_time;

const struct i2c_slave_config rtc_i2c_config =
{
    I2C_SLAVE_RD_START_STOP | I2C_SLAVE_RD_NACK,
    RTC_SLAVE_ADDRESS
};

static esError rtc_read_array(uint8_t address, uint8_t * data, size_t size) {
    i2c_bus_start(g_i2c_rtc_bus);

    if (i2c_bus_write(g_i2c_rtc_bus, RTC_WRITE_CMD) == false) {
        goto FAILURE;
    }

    if (i2c_bus_write(g_i2c_rtc_bus, address) == false) {
        goto FAILURE;
    }
    i2c_bus_stop(g_i2c_rtc_bus);
    i2c_bus_start(g_i2c_rtc_bus);

    if (i2c_bus_write(g_i2c_rtc_bus, RTC_READ_CMD) == false) {
        goto FAILURE;
    }
    size--;

    if (size != 0) {
        i2c_bus_read_array(g_i2c_rtc_bus, data, size);
    }
    data[size] = i2c_bus_read(g_i2c_rtc_bus);
    i2c_bus_nack(g_i2c_rtc_bus);
    i2c_bus_stop(g_i2c_rtc_bus);

    return (ES_ERROR_NONE);
FAILURE:
    i2c_bus_stop(g_i2c_rtc_bus);

    return (ES_ERROR_DEVICE_FAIL);
}

static esError rtc_write_array(uint8_t address, const uint8_t * data, size_t size) {

    i2c_bus_start(g_i2c_rtc_bus);

    if (i2c_bus_write(g_i2c_rtc_bus, RTC_WRITE_CMD) == false) {
        goto FAILURE;
    }

    if (i2c_bus_write(g_i2c_rtc_bus, address) == false) {
        goto FAILURE;
    }

    if (i2c_bus_write_array(g_i2c_rtc_bus, data, size) == false) {
        goto FAILURE;
    }
    i2c_bus_stop(g_i2c_rtc_bus);

    return (ES_ERROR_NONE);
FAILURE:
    i2c_bus_stop(g_i2c_rtc_bus);

    return (ES_ERROR_DEVICE_FAIL);
}

static esError rtc_read(uint8_t address, uint8_t * data) {

    return (rtc_read_array(address, data, 1));
}

static esError rtc_write(uint8_t address, uint8_t data) {

    return (rtc_write_array(address, &data, 1));
}

static uint8_t bcdToBin(uint8_t data) {
    uint8_t             retval;

    retval  = ((data >> 0) & 0xfu) * 1u;
    retval += ((data >> 4) & 0xfu) * 10u;

    return (retval);
}

static uint8_t binToBcd(uint8_t data) {
    uint8_t             retval;

    retval  = ((data / 10) & 0xfu) << 4;
    retval |= ((data % 10) & 0xfu) << 0;

    return (retval);
}

static esError rtc_fetch_time(struct rtc_time * time) {

    struct rtc_time_registers regs;

    if (rtc_read_array(REG_SECONDS, (uint8_t *)&regs, sizeof(regs)) != ES_ERROR_NONE) {
        goto FAILURE;
    }
    time->year   = (uint16_t)bcdToBin(regs.years) + 2000u;
    time->month  = bcdToBin(regs.months);
    time->day    = bcdToBin(regs.days);
    time->hour   = bcdToBin(regs.hours);
    time->minute = bcdToBin(regs.minutes);
    time->second = bcdToBin(regs.seconds);

    return (ES_ERROR_NONE);
FAILURE:
    time->year   = CONFIG_DEFAULT_YEAR;
    time->month  = CONFIG_DEFAULT_MONTH;
    time->day    = CONFIG_DEFAULT_DAY;
    time->hour   = CONFIG_DEFAULT_HOUR;
    time->minute = CONFIG_DEFAULT_MINUTE;
    time->second = CONFIG_DEFAULT_SECOND;

    return (ES_ERROR_DEVICE_FAIL);
}

static esError rtc_put_time(const struct rtc_time * time) {
    struct rtc_time_registers regs;
    esError             error;

    regs.years   = binToBcd(time->year - 2000u);
    regs.months  = binToBcd(time->month);
    regs.days    = binToBcd(time->day);
    regs.hours   = binToBcd(time->hour);
    regs.minutes = binToBcd(time->minute);
    regs.seconds = binToBcd(time->second);

    error = rtc_write_array(REG_SECONDS, (const uint8_t *)&regs, sizeof(regs));

    if (error != ES_ERROR_NONE) {
        goto FAILURE;
    }

    return (ES_ERROR_NONE);
FAILURE:

    return (ES_ERROR_DEVICE_FAIL);
}

void rtc_init_driver(struct i2c_bus * i2c_bus) {
    uint8_t             reg;
    struct rtc_time_registers regs;

    g_i2c_rtc_bus = i2c_bus;

    if (rtc_read(REG_CONTROL_STATUS, &reg) != ES_ERROR_NONE) {
        goto FAILURE;
    }

    if (reg & CONTROL_STATUS_PON) {
        reg &= ~CONTROL_STATUS_PON;

        if (rtc_write(REG_CONTROL_STATUS, reg) != ES_ERROR_NONE) {
            goto FAILURE;
        }
        g_current_time.year   = CONFIG_DEFAULT_YEAR;
        g_current_time.month  = CONFIG_DEFAULT_MONTH;
        g_current_time.day    = CONFIG_DEFAULT_DAY;
        g_current_time.hour   = CONFIG_DEFAULT_HOUR;
        g_current_time.minute = CONFIG_DEFAULT_MINUTE;
        g_current_time.second = CONFIG_DEFAULT_SECOND;

        if (rtc_set_time_i(&g_current_time) != ES_ERROR_NONE) {
            goto FAILURE;
        }
    }
    memset(&regs, 0, sizeof(regs));

    if (rtc_write_array(REG_ALARM_SECONDS, (const uint8_t *)&regs, sizeof(regs)) != ES_ERROR_NONE) {
        goto FAILURE;
    }
    
    if (rtc_write(REG_CONTROL_INT, 0) != ES_ERROR_NONE) {
        goto FAILURE;
    }
    reg = CONTROL_1_WE;

    if (rtc_write(REG_CONTROL_1, reg) != ES_ERROR_NONE) {
        goto FAILURE;
    }

    if (rtc_write(REG_TIMER_LOW, 32) != ES_ERROR_NONE) {
        goto FAILURE;
    }

    if (rtc_write(REG_TIMER_HIGH, 0) != ES_ERROR_NONE) {
        goto FAILURE;
    }
    reg |= CONTROL_1_TAR;

    if (rtc_write(REG_CONTROL_1, reg) != ES_ERROR_NONE) {
        goto FAILURE;
    }
    reg |= CONTROL_1_TE;

    if (rtc_write(REG_CONTROL_1, reg) != ES_ERROR_NONE) {
        goto FAILURE;
    }


    if (rtc_write(REG_CONTROL_INT_FLAG, 0) != ES_ERROR_NONE) {
        goto FAILURE;
    }

    if (rtc_write(REG_CONTROL_INT, CONTROL_INT_TIE) != ES_ERROR_NONE) {
        goto FAILURE;
    }

    return;
FAILURE:
    g_current_time.year   = CONFIG_DEFAULT_YEAR;
    g_current_time.month  = CONFIG_DEFAULT_MONTH;
    g_current_time.day    = CONFIG_DEFAULT_DAY;
    g_current_time.hour   = CONFIG_DEFAULT_HOUR;
    g_current_time.minute = CONFIG_DEFAULT_MINUTE;
    g_current_time.second = CONFIG_DEFAULT_SECOND;

    return;
}

void rtc_term_driver(void)
{
    g_i2c_rtc_bus = NULL;
}

bool isRtcActive(void) {
    return (true);
}

esError rtc_set_time_i(const struct rtc_time * time) {
    esError             error;

    error = rtc_put_time(time);

    if (error == ES_ERROR_NONE) {
        g_current_time = *time;
    }

    return (error);
}

esError rtc_get_time_i(struct rtc_time * time)
{
    *time = g_current_time;

    return (ES_ERROR_NONE);
}

void rtc_tick_i(void)
{
    rtc_write(REG_CONTROL_INT_FLAG, 0);
    rtc_fetch_time(&g_current_time);
}

