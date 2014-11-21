/* 
 * File:   main.c
 * Author: nenad
 *
 * Created on 22 October 2014, 21:35
 */

#include <stdio.h>
#include <stdlib.h>

#include "mcu_config.h"

#include "driver/adc.h"
#include "driver/clock.h"
#include "driver/gpio.h"
#include "driver/intr.h"
#include "driver/systick.h"
#include "arch/intr_config.h"
#include "main.h"

#define CONFIG_RELAY_COUPLED_GPIO           &GpioB
#define CONFIG_RELAY_COUPLED_PIN            5

#define CONFIG_RELAY_DECOUPLED_GPIO         &GpioA
#define CONFIG_RELAY_DECOUPLED_PIN          4

#define CONFIG_RELAY_GROUND_BLOCKED_GPIO    &GpioB
#define CONFIG_RELAY_GROUND_BLOCKED_PIN     3

#define CONFIG_RELAY_CLOSE_BLOCKED_GPIO     &GpioB
#define CONFIG_RELAY_CLOSE_BLOCKED_PIN      15

#define CONFIG_SENS_COUPLER_GPIO            &GpioB
#define CONFIG_SENS_COUPLER_PIN             2
#define CONFIG_SENS_COUPLER_CHANNEL         4

#define CONFIG_SENS_GROUND_GPIO             &GpioA
#define CONFIG_SENS_GROUND_PIN              0
#define CONFIG_SENS_GROUND_CHANNEL          0

#define CONFIG_SENS_CLOSE_GPIO              &GpioA
#define CONFIG_SENS_CLOSE_PIN               1
#define CONFIG_SENS_CLOSE_CHANNEL           1

#define CONFIG_COUPLER_COUPLED              30
#define CONFIG_COUPLER_DECOUPLED            70
#define CONFIG_COUPLER_HYST                 4

#define CONFIG_GROUND_DETECTED              70
#define CONFIG_GROUND_HYST                  10

#define CONFIG_CLOSE_DETECTED               70
#define CONFIG_CLOSE_HYST                   10

#define CONFIG_SENS_HI_RES                  1000ul
#define CONFIG_SENS_LO_RES                  1000ul

#define CONFIG_SENS_VOLTAGE_MV              5000ul

#define ADC_RELATIVE_FULL_SCALE_VAL                                             \
    (((uint64_t)1024ul * (uint64_t)CONFIG_SENS_VOLTAGE_MV * (uint64_t)CONFIG_SENS_LO_RES) / (((uint64_t)CONFIG_SENS_HI_RES + (uint64_t)CONFIG_SENS_LO_RES) * (uint64_t)3300ul))

#define ADC_RELATIVE_HALF_SCALE_VAL                                             \
    (ADC_RELATIVE_FULL_SCALE_VAL / (uint64_t)2ul)

static void board_init_intr(void)
{
    initIntrDriver();
}

static void board_init_clock(void)
{
    initClockDriver();
}

static void board_init_gpio(void)
{
    initGpioDriver();

    gpioSetAsOutput(CONFIG_RELAY_COUPLED_GPIO,        CONFIG_RELAY_COUPLED_PIN);
    gpioSetAsOutput(CONFIG_RELAY_DECOUPLED_GPIO,      CONFIG_RELAY_DECOUPLED_PIN);
    gpioSetAsOutput(CONFIG_RELAY_GROUND_BLOCKED_GPIO, CONFIG_RELAY_GROUND_BLOCKED_PIN);
    gpioSetAsOutput(CONFIG_RELAY_CLOSE_BLOCKED_GPIO,  CONFIG_RELAY_CLOSE_BLOCKED_PIN);
}

static void board_init_adc(void)
{
    initAdcDriver();
    adcSetZero(ADC_RELATIVE_HALF_SCALE_VAL);

    gpioSetAsInput(CONFIG_SENS_COUPLER_GPIO, CONFIG_SENS_COUPLER_PIN);
    *(CONFIG_SENS_COUPLER_GPIO)->ansel |= (0x1u << CONFIG_SENS_COUPLER_PIN);
    adcEnableChannel(CONFIG_SENS_COUPLER_CHANNEL, NULL);

    gpioSetAsInput(CONFIG_SENS_CLOSE_GPIO, CONFIG_SENS_CLOSE_PIN);
    *(CONFIG_SENS_CLOSE_GPIO)->ansel |= (0x1u << CONFIG_SENS_CLOSE_PIN);
    adcEnableChannel(CONFIG_SENS_CLOSE_CHANNEL,   NULL);

    gpioSetAsInput(CONFIG_SENS_GROUND_GPIO, CONFIG_SENS_GROUND_PIN);
    *(CONFIG_SENS_GROUND_GPIO)->ansel |= (0x1u << CONFIG_SENS_GROUND_PIN);
    adcEnableChannel(CONFIG_SENS_GROUND_CHANNEL, NULL);
}

static uint32_t convert_to_relative(int32_t adc_value)
{
    uint32_t         retval;

    retval = (uint32_t)abs(adc_value - (int32_t)ADC_RELATIVE_HALF_SCALE_VAL);
    retval *= (uint32_t)100ul;
    retval /= (uint32_t)ADC_RELATIVE_HALF_SCALE_VAL;

    return (retval);
}

static void process_coupler(void)
{
    int32_t coupler;

    enum coupler_state
    {
        STATE_INIT,
        STATE_COUPLED,
        STATE_DECOUPLED,
        STATE_UNDEFINED
    };

    static enum coupler_state coupler_state = STATE_INIT;
    coupler = convert_to_relative(adcReadChannel(CONFIG_SENS_COUPLER_CHANNEL));

    switch (coupler_state) {
        case STATE_INIT: {
            coupler_state = STATE_UNDEFINED;
            break;
        }
        case STATE_COUPLED : {
            gpio_set(CONFIG_RELAY_COUPLED_GPIO,   CONFIG_RELAY_COUPLED_PIN);
            gpio_clr(CONFIG_RELAY_DECOUPLED_GPIO, CONFIG_RELAY_DECOUPLED_PIN);
            
            if (coupler < CONFIG_COUPLER_COUPLED - CONFIG_COUPLER_HYST) {
                coupler_state = STATE_UNDEFINED;
            }
            break;
        }
        case STATE_DECOUPLED : {
            gpio_clr(CONFIG_RELAY_COUPLED_GPIO,   CONFIG_RELAY_COUPLED_PIN);
            gpio_set(CONFIG_RELAY_DECOUPLED_GPIO, CONFIG_RELAY_DECOUPLED_PIN);

            if (coupler > CONFIG_COUPLER_DECOUPLED + CONFIG_COUPLER_HYST) {
                coupler_state = STATE_UNDEFINED;
            }
            break;
        }
        case STATE_UNDEFINED : {
            gpio_clr(CONFIG_RELAY_COUPLED_GPIO,   CONFIG_RELAY_COUPLED_PIN);
            gpio_clr(CONFIG_RELAY_DECOUPLED_GPIO, CONFIG_RELAY_DECOUPLED_PIN);

            if (coupler <= CONFIG_COUPLER_DECOUPLED) {
                coupler_state = STATE_DECOUPLED;
            } else if (coupler >= CONFIG_COUPLER_COUPLED) {
                coupler_state = STATE_COUPLED;
            } else {
                coupler_state = STATE_UNDEFINED;
            }
            break;
        }
    }
}

static void process_ground_blocker(void)
{
    uint32_t            ground;

    enum ground_state
    {
        STATE_INIT,
        STATE_DETECTED,
        STATE_NOT_DETECTED
    };
    static enum ground_state ground_state = STATE_INIT;
    ground = convert_to_relative(adcReadChannel(CONFIG_SENS_GROUND_CHANNEL));

    switch (ground_state) {
        case STATE_INIT : {
            ground_state = STATE_NOT_DETECTED;
            break;
        }
        case STATE_DETECTED : {
            gpio_set(CONFIG_RELAY_GROUND_BLOCKED_GPIO, CONFIG_RELAY_GROUND_BLOCKED_PIN);
            
            if (ground < CONFIG_GROUND_DETECTED - CONFIG_GROUND_HYST) {
                ground_state = STATE_NOT_DETECTED;
            }
            break;
        }
        case STATE_NOT_DETECTED : {
            gpio_clr(CONFIG_RELAY_GROUND_BLOCKED_GPIO, CONFIG_RELAY_GROUND_BLOCKED_PIN);

            if (ground > CONFIG_GROUND_DETECTED) {
                ground_state = STATE_DETECTED;
            }
            break;
        }
    }
}

static void process_close_blocker(void)
{
    uint32_t            close;

    enum close_state
    {
        STATE_INIT,
        STATE_DETECTED,
        STATE_NOT_DETECTED
    };
    static enum close_state close_state = STATE_INIT;
    close = convert_to_relative(adcReadChannel(CONFIG_SENS_CLOSE_CHANNEL));

    switch (close_state) {
        case STATE_INIT : {
            close_state = STATE_NOT_DETECTED;
            break;
        }
        case STATE_DETECTED : {
            gpio_set(CONFIG_RELAY_CLOSE_BLOCKED_GPIO, CONFIG_RELAY_CLOSE_BLOCKED_PIN);

            if (close < CONFIG_CLOSE_DETECTED - CONFIG_CLOSE_HYST) {
                close_state = STATE_NOT_DETECTED;
            }
            break;
        }
        case STATE_NOT_DETECTED : {
            gpio_clr(CONFIG_RELAY_CLOSE_BLOCKED_GPIO, CONFIG_RELAY_CLOSE_BLOCKED_PIN);

            if (close > CONFIG_CLOSE_DETECTED) {
                close_state = STATE_DETECTED;
            }
            break;
        }
    }
}

static void initial_delay(void)
{
    uint32_t            batch_no;

    for (batch_no = 0; batch_no < 16; batch_no++) {
        while (!adc_batch_is_done());
    }
}

/*
 * 
 */
int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    board_init_intr();
    board_init_clock();
    board_init_gpio();
    board_init_adc();

    initial_delay();

    for (;;) {
        process_coupler();
        process_ground_blocker();
        process_close_blocker();
    }
    
    return (EXIT_SUCCESS);
}

