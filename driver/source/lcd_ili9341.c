
#include "driver/lcd_ili9341.h"
#include "driver/lcd_ili9341_lld.h"
#include "TimeDelay.h"

#define ILI_SLEEP_OUT                   0x11u
#define ILI_GAMMA_SET                   0x26u
#define ILI_DISPLAY_ON                  0x29u
#define ILI_MEMORY_ACCESS               0x36u
#define ILI_PIXEL_FORMAT                0x3au
#define ILI_FRAME_RATE                  0xb1u
#define ILI_DISPLAY_FUNCTION            0xb6u
#define ILI_POWER_1                     0xc0u
#define ILI_POWER_2                     0xc1u
#define ILI_VCOM_1                      0xc5u
#define ILI_VCOM_2                      0xc7u
#define ILI_POWER_A                     0xcbu
#define ILI_POWER_B                     0xcfu
#define ILI_POSITIVE_GAMMA              0xe0u
#define ILI_NEGATIVE_GAMMA              0xe1u
#define ILI_DRIVER_TIMING_A             0xe8u
#define ILI_DRIVER_TIMING_B             0xeau
#define ILI_POWER_ON_SEQUENCE           0xedu
#define ILI_ENABLE_3G                   0xf2u
#define ILI_PUMP_RATIO                  0xf7u

void lcd_init(void)
{
    ili9341_lld_init();

    ili9341_lld_write_cmd(ILI_POWER_A);
    ili9341_lld_write_data(0x39);
    ili9341_lld_write_data(0x2c);
    ili9341_lld_write_data(0x00);
    ili9341_lld_write_data(0x34);
    ili9341_lld_write_data(0x02);

    ili9341_lld_write_cmd(ILI_POWER_B);
    ili9341_lld_write_data(0x00);
    ili9341_lld_write_data(0xc1);
    ili9341_lld_write_data(0x30);

    ili9341_lld_write_cmd(ILI_DRIVER_TIMING_A);
    ili9341_lld_write_data(0x85);
    ili9341_lld_write_data(0x00);
    ili9341_lld_write_data(0x78);

    ili9341_lld_write_cmd(ILI_DRIVER_TIMING_B);
    ili9341_lld_write_data(0x00);
    ili9341_lld_write_data(0x00);

    ili9341_lld_write_cmd(ILI_POWER_ON_SEQUENCE);
    ili9341_lld_write_data(0x64);
    ili9341_lld_write_data(0x03);
    ili9341_lld_write_data(0x12);
    ili9341_lld_write_data(0x81);

    ili9341_lld_write_cmd(ILI_PUMP_RATIO);
    ili9341_lld_write_data(0x20);

    ili9341_lld_write_cmd(ILI_POWER_1);
    ili9341_lld_write_data(0x23);

    ili9341_lld_write_cmd(ILI_POWER_2);
    ili9341_lld_write_data(0x10);

    ili9341_lld_write_cmd(ILI_VCOM_1);
    ili9341_lld_write_data(0x3e);
    ili9341_lld_write_data(0x28);

    ili9341_lld_write_cmd(ILI_VCOM_2);
    ili9341_lld_write_data(0x86);

    ili9341_lld_write_cmd(ILI_MEMORY_ACCESS);
    ili9341_lld_write_data(0x48);

    ili9341_lld_write_cmd(ILI_PIXEL_FORMAT);
    ili9341_lld_write_data(0x55);

    ili9341_lld_write_cmd(ILI_FRAME_RATE);
    ili9341_lld_write_data(0x00);
    ili9341_lld_write_data(0x18);

    ili9341_lld_write_cmd(ILI_DISPLAY_FUNCTION);
    ili9341_lld_write_data(0x08);
    ili9341_lld_write_data(0x82);
    ili9341_lld_write_data(0x27);

    ili9341_lld_write_cmd(ILI_ENABLE_3G);
    ili9341_lld_write_data(0x00);

    ili9341_lld_write_cmd(ILI_GAMMA_SET);
    ili9341_lld_write_data(0x01);

    ili9341_lld_write_cmd(ILI_POSITIVE_GAMMA);
    ili9341_lld_write_data(0x0f);
    ili9341_lld_write_data(0x31);
    ili9341_lld_write_data(0x2b);
    ili9341_lld_write_data(0x0c);
    ili9341_lld_write_data(0x0e);
    ili9341_lld_write_data(0x08);
    ili9341_lld_write_data(0x4e);
    ili9341_lld_write_data(0xf1);
    ili9341_lld_write_data(0x37);
    ili9341_lld_write_data(0x07);
    ili9341_lld_write_data(0x10);
    ili9341_lld_write_data(0x03);
    ili9341_lld_write_data(0x0e);
    ili9341_lld_write_data(0x09);
    ili9341_lld_write_data(0x00);

    ili9341_lld_write_cmd(ILI_NEGATIVE_GAMMA);
    ili9341_lld_write_data(0x00);
    ili9341_lld_write_data(0x0e);
    ili9341_lld_write_data(0x14);
    ili9341_lld_write_data(0x03);
    ili9341_lld_write_data(0x11);
    ili9341_lld_write_data(0x07);
    ili9341_lld_write_data(0x31);
    ili9341_lld_write_data(0xc1);
    ili9341_lld_write_data(0x48);
    ili9341_lld_write_data(0x08);
    ili9341_lld_write_data(0x0f);
    ili9341_lld_write_data(0x0c);
    ili9341_lld_write_data(0x31);
    ili9341_lld_write_data(0x36);
    ili9341_lld_write_data(0x0f);

    ili9341_lld_write_cmd(ILI_SLEEP_OUT);
    DelayMs(120);

    ili9341_lld_write_cmd(ILI_DISPLAY_ON);
}
