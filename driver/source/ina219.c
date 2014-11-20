
#include "driver/ina219.h"
#include "driver/i2c.h"

#define INA219_CONFIGURATION            0x00u
#define INA219_SHUNT                    0x01u
#define INA219_BUS                      0x02u
#define INA219_POWER                    0x03u
#define INA219_CURRENT                  0x04u
#define INA219_CALIBRATION              0x05u

#define INA219_ID                       0x80u

static const struct i2c_slave_config g_ina219_i2c_config =
{
    I2C_SLAVE_RD_START_STOP | I2C_SLAVE_RD_NACK,
    INA219_ID
};

esError ina219_init_driver(struct ina219_handle * handle, struct i2c_bus * bus, uint8_t id)
{
    uint8_t             dummy_array[2];

    i2c_slave_open(&handle->comm, &g_ina219_i2c_config, bus, id);

    if (i2c_slave_read(&handle->comm, INA219_BUS, dummy_array, sizeof(dummy_array)) == false) {
        i2c_slave_close(&handle->comm);

        return (ES_ERROR_DEVICE_FAIL);
    } else {

        return (ES_ERROR_NONE);
    }
}

void ina219_term_driver(struct ina219_handle * handle)
{
    i2c_slave_close(&handle->comm);
}

esError ina219_get_shunt_voltage(struct ina219_handle * handle, int32_t * value)
{
    uint8_t             array[2];

    if (i2c_slave_read(&handle->comm, INA219_SHUNT, array, sizeof(array)) == true) {
        *value = ((uint32_t)array[0] << 8u) | array[1];

        return (ES_ERROR_NONE);
    } else {

        return (ES_ERROR_DEVICE_FAIL);
    }
}

esError ina219_get_bus_voltage(struct ina219_handle * handle, int32_t * value)
{
    uint8_t             array[2];

    if (i2c_slave_read(&handle->comm, INA219_BUS, array, sizeof(array)) == true) {
        *value = ((uint32_t)array[0] << 8u) | array[1];

        return (ES_ERROR_NONE);
    } else {

        return (ES_ERROR_DEVICE_FAIL);
    }
}
