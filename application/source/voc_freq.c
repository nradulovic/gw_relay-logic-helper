
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <peripheral/timer.h>
#include "arch/intr.h"

#define CONFIG_NUM_OF_SAMPLES           16

#define VOC_FREQ_GPIO                   PORTD
#define VOC_FREQ_TRIS                   TRISD
#define VOC_FREQ_PIN                    7

#define VOC_FREQ_CN_NO                  16

#define CNCON_ON                        (0x1u << 15)

static uint32_t g_current_val;

static void timer_init(void)
{
    T3CON           = 0;
    T2CON           = 0;
    T2CONbits.T32   = 1;
    TMR2            = 0;
    PR2             = UINT32_MAX;
}

static void timer_start(void)
{
    T2CONSET = T2_ON;
}

static void timer_stop(void)
{
    T2CONCLR = T2_ON;
}

static uint32_t timer_read(void)
{
    return (TMR2);
}

static void timer_clear(void)
{
    TMR2 = 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR) change_notice_isr(void)
{
    static bool     is_period_started = true;
    static uint32_t sample_no;
    static uint32_t acc_val;
    uint32_t        port_state;

    port_state  = VOC_FREQ_GPIO;
    port_state &= (0x1u << VOC_FREQ_PIN);

    if (port_state) {

        if (is_period_started) {
            timer_start();
            is_period_started = false;
        } else {
            timer_stop();
            acc_val += timer_read();
            timer_clear();
            sample_no++;

            if (sample_no == CONFIG_NUM_OF_SAMPLES) {
                sample_no = 0;
                g_current_val = acc_val / CONFIG_NUM_OF_SAMPLES;
                acc_val     = 0;
            }
            is_period_started = true;
        }
    }
    IFS1bits.CNIF  = 0;
}

void voc_freq_init(void)
{
    timer_init();
    CNCON |= CNCON_ON;
    CNEN  |= (0x1u << VOC_FREQ_CN_NO);
    VOC_FREQ_TRIS |= (0x1u << VOC_FREQ_PIN);
    TRISF         |= (0x1u << 3);
    IPC6bits.CNIP  = ES_INTR_DEFAULT_ISR_PRIO;
    IPC6bits.CNIS  = 0;
    IFS1bits.CNIF  = 0;
    IEC1bits.CNIE  = 1;
}

uint32_t voc_freq_raw(void)
{
    return (g_current_val);
}
