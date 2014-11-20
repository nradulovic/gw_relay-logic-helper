/* 
 * File:   ad5242.h
 * Author: nenad
 *
 * Created on October 27, 2014, 4:08 AM
 */

#ifndef AD5242_H
#define	AD5242_H

#include "base/error.h"
#include "driver/i2c.h"

#ifdef	__cplusplus
extern "C" {
#endif

struct ad5242_handle
{
    struct i2c_slave            comm;
};

esError ad5242_init_driver(struct ad5242_handle * handle, struct i2c_bus * bus, uint8_t id);
esError ad5242_term_driver(struct ad5242_handle * handle);
esError ad5242_set_pot1(struct ad5242_handle * handle, uint8_t val);

#ifdef	__cplusplus
}
#endif

#endif	/* AD5242_H */

