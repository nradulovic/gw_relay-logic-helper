
/*=========================================================  INCLUDE FILES  ==*/

#include <xc.h>

#include "base/bitop.h"

#include "driver/i2c.h"
#include "driver/clock.h"
#include "driver/gpio.h"

/*=========================================================  LOCAL MACRO's  ==*/

#define CONFIG_PULSE_GOBBLER_NS         104

#define I2C_CON_SEN                     (0x1u << 0)
#define I2C_CON_RSEN                    (0x1u << 1)
#define I2C_CON_PEN                     (0x1u << 2)
#define I2C_CON_RCEN                    (0x1u << 3)
#define I2C_CON_ACKEN                   (0x1u << 4)
#define I2C_CON_ACKDT                   (0x1u << 5)
#define I2C_CON_DISSLW                  (0x1u << 9)
#define I2C_CON_ON                      (0x1u << 15)

#define I2C_STAT_TBF                    (0x1u << 0)
#define I2C_STAT_RBF                    (0x1u << 1)
#define I2C_STAT_P                      (0x1u << 4)
#define I2C_STAT_BCL                    (0x1u << 10)
#define I2C_STAT_TRSTAT                 (0x1u << 14)
#define I2C_STAT_ACKSTAT                (0x1u << 15)

/*======================================================  LOCAL DATA TYPES  ==*/
/*=============================================  LOCAL FUNCTION PROTOTYPES  ==*/

static void open(const struct i2c_bus_config *, struct i2c_bus *);
static void close(struct i2c_bus *);
static bool write(struct i2c_bus *, uint8_t);
static uint8_t read(struct i2c_bus *);
static void start(struct i2c_bus *);
static void restart(struct i2c_bus *);
static void stop(struct i2c_bus *);
static void ack(struct i2c_bus *);
static void nack(struct i2c_bus *);

/*=======================================================  LOCAL VARIABLES  ==*/
/*======================================================  GLOBAL VARIABLES  ==*/

const struct i2c_id I2C1 = {
    open,
    close,
    write,
    read,
    start,
    restart,
    stop,
    ack,
    nack
};

/*============================================  LOCAL FUNCTION DEFINITIONS  ==*/

static void open(const struct i2c_bus_config * config, struct i2c_bus * handle) {
    uint32_t        pbclk;

    TRISD           &= ~(0x1u << 9);
    TRISD           &= ~(0x1u << 10);
    
    I2C1CON         = 0;
    I2C1STAT        = 0;

    if (config->speed > 100000) {
        I2C1CONSET = I2C_CON_DISSLW;
    }
    pbclk   = clockGetPeripheralClock();
    I2C1BRG =
        (pbclk / (2 * config->speed)) - ES_DIVISION_ROUND((CONFIG_PULSE_GOBBLER_NS * (pbclk / 1000)), 1000000) - 2;

    I2C1CONSET       = I2C_CON_ON;
}

static void close(struct i2c_bus * handle) {
    (void)handle;
    
    while ((I2C1CON & (I2C_CON_SEN | I2C_CON_RSEN | I2C_CON_PEN | I2C_CON_RCEN | I2C_CON_ACKEN)) != 0);

    I2C1CON = 0;
}

static bool write(struct i2c_bus * handle, uint8_t data) {

    while ((I2C1CON & (I2C_CON_SEN | I2C_CON_RSEN | I2C_CON_PEN | I2C_CON_RCEN | I2C_CON_ACKEN)) != 0);

    I2C1TRN = data;

    while (I2C1STAT & I2C_STAT_TRSTAT);

    if (I2C1STAT & (I2C_STAT_ACKSTAT | I2C_STAT_BCL)) {

        return (false);
    } else {

        return (true);
    }
}

static uint8_t read(struct i2c_bus * handle) {

    while ((I2C1CON & (I2C_CON_SEN | I2C_CON_RSEN | I2C_CON_PEN | I2C_CON_RCEN | I2C_CON_ACKEN)) != 0);
    I2C1CON |= I2C_CON_RCEN;

    while ((I2C1STAT & I2C_STAT_RBF) == 0);

    while (I2C1CON & I2C_CON_RCEN);

    return (I2C1RCV);
}

static void start(struct i2c_bus * handle) {
    (void)handle;

    while ((I2C1CON & (I2C_CON_SEN | I2C_CON_RSEN | I2C_CON_PEN | I2C_CON_RCEN | I2C_CON_ACKEN)) != 0);

    I2C1CONSET = I2C_CON_SEN;
}

static void restart(struct i2c_bus * handle) {
    (void)handle;
    
    while ((I2C1CON & (I2C_CON_SEN | I2C_CON_RSEN | I2C_CON_PEN | I2C_CON_RCEN | I2C_CON_ACKEN)) != 0);

    I2C1CONSET = I2C_CON_RSEN;
}

static void stop(struct i2c_bus * handle) {
    (void)handle;

    while ((I2C1CON & (I2C_CON_SEN | I2C_CON_RSEN | I2C_CON_PEN | I2C_CON_RCEN | I2C_CON_ACKEN)) != 0);

    I2C1CONSET = I2C_CON_PEN;
}

static void ack(struct i2c_bus * handle) {
    (void)handle;

    while ((I2C1CON & (I2C_CON_SEN | I2C_CON_RSEN | I2C_CON_PEN | I2C_CON_RCEN | I2C_CON_ACKEN)) != 0);

    I2C1CONCLR = I2C_CON_ACKDT;
    I2C1CONSET = I2C_CON_ACKEN;
}

static void nack(struct i2c_bus * handle) {
    (void)handle;

    while ((I2C1CON & (I2C_CON_SEN | I2C_CON_RSEN | I2C_CON_PEN | I2C_CON_RCEN | I2C_CON_ACKEN)) != 0);

    I2C1CONSET = I2C_CON_ACKDT;
    I2C1CONSET = I2C_CON_ACKEN;
}

/*===================================  GLOBAL PRIVATE FUNCTION DEFINITIONS  ==*/
/*====================================  GLOBAL PUBLIC FUNCTION DEFINITIONS  ==*/
/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//******************************************************
 * END of lld_i2c1.c
 ******************************************************************************/
