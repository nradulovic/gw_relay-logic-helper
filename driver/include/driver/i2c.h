/* 
 * File:   i2c.h
 * Author: nenad
 *
 * Created on May 3, 2014, 6:35 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "driver/lld_i2c1.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define I2C_REPEAT_LAST_ADDRESS         (0xffu)

enum i2c_config_flags {
    I2C_BUS_ADDRESS_10BIT           = (0x1 << 10),
    I2C_BUS_ADDRESS_7BIT            = (0x0 << 10),
};

enum i2c_slave_flags
{
    I2C_SLAVE_RD_START_STOP         = (0x1u << 0),
    I2C_SLAVE_RD_NACK               = (0x1u << 1),
    I2C_SLAVE_RD_REPEAT             = (0x1u << 2)
};

struct i2c_id;

struct i2c_bus_config
{
    const struct i2c_id *   id;
    uint32_t                flags;
    uint32_t                speed;
    uint32_t                isr_prio;
};

struct i2c_bus
{
    const struct i2c_id *   id;
    uint32_t                flags;
};

struct i2c_slave_config
{
    uint32_t                flags;
    uint8_t                 address;
};

struct i2c_slave
{
    struct i2c_bus *        bus;
    uint32_t                flags;
    uint8_t                 address;
};

struct i2c_id {
    void             (* open)(const struct i2c_bus_config *, struct i2c_bus *);
    void             (* close)(struct i2c_bus *);
    bool             (* write)(struct i2c_bus *, uint8_t);
    uint8_t          (* read)(struct i2c_bus *);
    void             (* start)(struct i2c_bus *);
    void             (* restart)(struct i2c_bus *);
    void             (* stop)(struct i2c_bus *);
    void             (* ack)(struct i2c_bus *);
    void             (* nack)(struct i2c_bus *);
};

void i2c_driver_init(void);

void i2c_bus_open(
    struct i2c_bus *            bus,
    const struct i2c_bus_config *   config);

void i2c_close(
    struct i2c_bus *            bus);

void i2c_bus_ack(
    struct i2c_bus *            bus);

void i2c_bus_nack(
    struct i2c_bus *            bus);

bool i2c_bus_write_array(
    struct i2c_bus *            bus,
    const uint8_t *             data,
    size_t                      size);

bool i2c_bus_write(
    struct i2c_bus *            bus,
    uint8_t                     data);

void i2c_bus_read_array(
    struct i2c_bus *            bus,
    uint8_t *                   data,
    size_t                      size);

uint8_t i2c_bus_read(
    struct i2c_bus *            bus);

void i2c_bus_start(
    struct i2c_bus *            bus);

void i2c_bus_restart(
    struct i2c_bus *            bus);

void i2c_bus_stop(
    struct i2c_bus *            bus);

void i2c_slave_open(struct i2c_slave * slave, const struct i2c_slave_config * config, struct i2c_bus * bus, uint8_t id);
void i2c_slave_close(struct i2c_slave * slave);
bool i2c_slave_read(struct i2c_slave * slave, uint8_t address, void * data, size_t size);
bool i2c_slave_write(struct i2c_slave * slave, uint8_t address, const void * data, size_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

