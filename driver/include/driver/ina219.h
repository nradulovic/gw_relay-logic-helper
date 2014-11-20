/* 
 * File:   ina219.h
 * Author: nenad
 *
 * Created on October 26, 2014, 9:48 PM
 */

#ifndef INA219_H
#define	INA219_H

#include <stdint.h>
#include "base/error.h"
#include "driver/i2c.h"

#ifdef	__cplusplus
extern "C" {
#endif

struct ina219_handle
{
    struct i2c_slave    comm;
};

esError ina219_init_driver(struct ina219_handle * handle, struct i2c_bus * bus, uint8_t id);
void ina219_term_driver(struct ina219_handle * handle);
esError ina219_get_shunt_voltage(struct ina219_handle * handle, int32_t * value);
esError ina219_get_bus_voltage(struct ina219_handle * handle, int32_t * value);

#ifdef	__cplusplus
}
#endif

#endif	/* INA219_H */

