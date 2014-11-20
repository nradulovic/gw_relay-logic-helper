
#include "driver/ad5242.h"
#include "base/error.h"

#define AD5242_ID                       0x58

static struct i2c_slave_config g_ad5242_i2c_config =
{
    I2C_SLAVE_RD_START_STOP | I2C_SLAVE_RD_NACK | I2C_SLAVE_RD_REPEAT,
    AD5242_ID
};

esError ad5242_init_driver(struct ad5242_handle * handle, struct i2c_bus * bus, uint8_t id)
{
    i2c_slave_open(&handle->comm, &g_ad5242_i2c_config, bus, id);

    return (ES_ERROR_NONE);
}

esError ad5242_term_driver(struct ad5242_handle * handle)
{
    i2c_slave_close(&handle->comm);

    return (ES_ERROR_NONE);
}

esError ad5242_set_pot1(struct ad5242_handle * handle, uint8_t val)
{
    if (i2c_slave_write(&handle->comm, 0, &val, 1) == false) {
        return (ES_ERROR_DEVICE_FAIL);
    } 
    return (ES_ERROR_NONE);
}
