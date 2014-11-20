
#include "driver/i2c.h"
#include <string.h>

void i2c_driver_init(void)
{
    
}

void i2c_bus_open(
    struct i2c_bus *          handle,
    const struct i2c_bus_config *    config)
{
    handle->id    = config->id;
    handle->flags = config->flags;
    handle->id->open(config, handle);
}

void i2c_close(
    struct i2c_bus *  handle) {

    handle->id->close(handle);
}

void i2c_bus_ack(
    struct i2c_bus *          handle) {

    handle->id->ack(handle);
}

void i2c_bus_nack(
    struct i2c_bus *          handle) {

    handle->id->nack(handle);
}

bool i2c_bus_write_array(
    struct i2c_bus *          handle,
    const uint8_t *             data,
    size_t                      size) {

    while (size != 0) {

        if (handle->id->write(handle, *data) != true) {

            return (false);
        }
        data++;
        size--;
    }

    return (true);
}

bool i2c_bus_write(
    struct i2c_bus *          handle,
    uint8_t                     data) {

    return (handle->id->write(handle, data));
}

void i2c_bus_read_array(
    struct i2c_bus *          handle,
    uint8_t *                   data,
    size_t                      size) {

    while (size != 0) {

        *data = handle->id->read(handle);
        handle->id->ack(handle);
        data++;
        size--;
    }
}

uint8_t i2c_bus_read(
    struct i2c_bus *          handle) {

    return (handle->id->read(handle));
}

void i2c_bus_start(
    struct i2c_bus *          handle) {

    handle->id->start(handle);
}

void i2c_bus_restart(
    struct i2c_bus *          handle) {

    handle->id->restart(handle);
}

void i2c_bus_stop(
    struct i2c_bus *          handle) {

    handle->id->stop(handle);
}

void i2c_slave_open(struct i2c_slave * slave, const struct i2c_slave_config * config, struct i2c_bus * bus, uint8_t id)
{
    slave->bus      = bus;
    slave->address  = config->address | id;
    slave->flags    = config->flags;
}

void i2c_slave_close(struct i2c_slave * slave)
{
    memset(slave, 0, sizeof(*slave));
}

bool i2c_slave_read(struct i2c_slave * slave, uint8_t address, void * data, size_t size)
{
    i2c_bus_start(slave->bus);
    
    if (!((slave->flags & I2C_SLAVE_RD_REPEAT) && (address == I2C_REPEAT_LAST_ADDRESS))) {
        if (i2c_bus_write(slave->bus, slave->address) == false) {
            goto FAILURE;
        }

        if (i2c_bus_write(slave->bus, address) == false) {
            goto FAILURE;
        }

        if (slave->flags & I2C_SLAVE_RD_START_STOP) {
            i2c_bus_stop(slave->bus);
            i2c_bus_start(slave->bus);
        } else {
            i2c_bus_restart(slave->bus);
        }
    }

    if (i2c_bus_write(slave->bus, slave->address | 0x01u) == false) {
        goto FAILURE;
    }
    size--;

    if (size != 0) {
        i2c_bus_read_array(slave->bus, data, size);
    }
    ((uint8_t *)data)[size] = i2c_bus_read(slave->bus);

    if (slave->flags & I2C_SLAVE_RD_NACK) {
        i2c_bus_nack(slave->bus);
    }
    i2c_bus_stop(slave->bus);

    return (true);
FAILURE:
    i2c_bus_stop(slave->bus);

    return (false);
}

bool i2c_slave_write(struct i2c_slave * slave, uint8_t address, const void * data, size_t size)
{
    i2c_bus_start(slave->bus);

    if (i2c_bus_write(slave->bus, slave->address) == false) {
        goto FAILURE;
    }

    if (i2c_bus_write(slave->bus, address) == false) {
        goto FAILURE;
    }

    if (i2c_bus_write_array(slave->bus, data, size) == false) {
        goto FAILURE;
    }
    i2c_bus_stop(slave->bus);

    return (true);
FAILURE:
    i2c_bus_stop(slave->bus);

    return (false);
}