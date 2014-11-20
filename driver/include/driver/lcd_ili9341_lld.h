/* 
 * File:   lcd_ili9341_lld.h
 * Author: nenad
 *
 * Created on 29 October 2014, 22:09
 */

#ifndef LCD_ILI9341_LLD_H
#define	LCD_ILI9341_LLD_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

void ili9341_lld_init(void);
void ili9341_lld_reset(void);
void ili9341_lld_write_cmd(uint32_t cmd);
void ili9341_lld_write_data(uint32_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_ILI9341_LLD_H */

