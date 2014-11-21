
#include <xc.h>
#include <sys/attribs.h>

#include "driver/clock.h"
#include "driver/adc.h"
#include "GenericTypeDefs.h"

#define CONFIG_ADC_ISR_PRIORITY         4
#define CONFIG_ADC_ISR_SUBPRIORITY      0

#define CONFIG_ADC_FREQUENCY            100

#define CONFIG_NUM_OF_CHANNELS          16

#define CONFIG_NUM_OF_SAMPLES           8

#if (CONFIG_ADC_FREQUENCY < 250)
#define TMR3_PRESCALER                  3
#elif (CONFIG_ADC_FREQUENCY < 500)
#define TMR3_PRESCALER                  2
#elif (CONFIG_ADC_FREQUENCY < 1000)
#define TMR3_PRESCALER                  1
#else
#define TMR3_PRESCALER                  0
#endif

#define AD_CON1_DONE                    (0x1u << 0)
#define AD_CON1_SAMP                    (0x1u << 1)
#define AD_CON1_ASAM                    (0x1u << 2)
#define AD_CON1_CLRASAM                 (0x1u << 4)
#define AD_CON1_SSRC_TIMER3             (0x2u << 5)
#define AD_CON1_FORM_U16_INTEGER        (0x0u << 8)
#define AD_CON1_FORM_S16_FRACTIONAL     (0x3u << 8)
#define AD_CON1_FORM_U32_FRACTIONAL     (0x6u << 8)
#define AD_CON1_FORM_S32_FRACTIONAL     (0x7u << 8)
#define AD_CON1_SIDL                    (0x1u << 13)
#define AD_CON1_ON                      (0x1u << 15)

#define AD_CON2_BUFM                    (0x1u << 1)
#define AD_CON2_SMPI(x)                 (((x) - 1u) << 2)
#define AD_CON2_BUFS                    (0x1u << 7)
#define AD_CON2_CSCNA                   (0x1u << 10)
#define AD_CON2_VCFG_AVDD_AVSS          (0x0u << 13)

#define AD_CON3_ADCS(x)                 ((x) << 0)
#define AD_CON3_SAMC_31TAD              (0x1fu << 8)
#define AD_CON3_ADRC                    (0x1u << 15)

#define AD_CHS_CH0SA(x)                 ((x) << 16)
#define AD_CHS_CH0NA                    (0x1u << 23)
#define AD_CHS_CH0SB(x)                 ((x) << 24)
#define AD_CHS_CH0NB                    (0x1u << 31)

#define IFS0_AD1IF                      (0x1u << 28)
#define IEC0_AD1IE                      (0x1u << 28)
#define IPC5_AD1_PRIORITY_Msk           (0x7u << 26)
#define IPC5_AD1_PRIORITY(x)            ((x) << 26)
#define IPC5_AD1_SUBPRIORITY_Msk        (0x3u << 24)
#define IPC5_AD1_SUBPRIORITY(x)         ((x) << 24)

#define T_CON_ON                        (0x1u << 15)
#define T_CON_TCKPS(x)                  ((x) << 4)

struct adcChannel {
    int32_t             output[CONFIG_NUM_OF_SAMPLES];
    void             (* callback)(int32_t);
};

static bool     g_batch_is_done = false;
static uint32_t adcEnabledChannels;
static uint32_t adcNumOfEnabledChannels;
static uint32_t adcNumOfSamples;
static struct adcChannel Channel[CONFIG_NUM_OF_CHANNELS];

static void enableTmr(void) {
    T3CON    = T_CON_TCKPS(TMR3_PRESCALER);
    TMR3     = 0u;
    PR3      = clockGetPeripheralClock() / (CONFIG_ADC_FREQUENCY * (0x1u << TMR3_PRESCALER));
    T3CONSET = T_CON_ON;
}

static void disableTmr(void) {
    T3CON   = 0u;
}

static void enableAdc(uint32_t numOfEnabledChannels) {
    AD1CON1 = AD_CON1_FORM_U16_INTEGER    | AD_CON1_SSRC_TIMER3 | AD_CON1_ASAM;
    AD1CON2 = AD_CON2_VCFG_AVDD_AVSS      | AD_CON2_CSCNA       | AD_CON2_SMPI(numOfEnabledChannels);
    AD1CON3 = AD_CON3_ADCS(0xffu);
    AD1CHS  = 0u;
    IFS0CLR = IFS0_AD1IF;
    IEC0SET = IEC0_AD1IE;
    AD1CON1SET = AD_CON1_ON;
}

static void disableAdc(void) {
    AD1CSSL = 0u;
    AD1CON1 = 0u;
    IFS0CLR = IFS0_AD1IF;
    IEC0CLR = IEC0_AD1IE;
}

void initAdcDriver(void) {
    g_batch_is_done         = false;
    disableAdc();
    adcEnabledChannels      = 0u;
    adcNumOfEnabledChannels = 0u;
    IPC5CLR = IPC5_AD1_PRIORITY_Msk | IPC5_AD1_SUBPRIORITY_Msk;
    IPC5SET = IPC5_AD1_PRIORITY(CONFIG_ADC_ISR_PRIORITY) | IPC5_AD1_SUBPRIORITY(CONFIG_ADC_ISR_SUBPRIORITY);
}

bool adc_batch_is_done(void)
{
    if (g_batch_is_done) {
        g_batch_is_done = false;

        return (true);
    } else {

        return (false);
    }
}

void adcSetZero(uint32_t zero)
{
    uint32_t            channel;
    uint32_t            itr;

    for (channel = 0; channel < 16; channel++) {
        for (itr = 0; itr < CONFIG_NUM_OF_SAMPLES; itr++) {
            Channel[channel].output[itr] = zero;
        }
    }
}

void adcEnableChannel(uint32_t id, void (* callback)(int32_t)) {
    id &= 0x1fu;

    memset(&Channel[id].output, 0, sizeof(Channel[id].output));
    Channel[id].callback = callback;

    if (adcEnabledChannels != 0u) {
        disableTmr();
        disableAdc();
    }
    adcEnabledChannels |= (0x1u << id);
    AD1CSSL = adcEnabledChannels;
    adcNumOfEnabledChannels++;
    enableAdc(adcNumOfEnabledChannels);
    enableTmr();
}

void adcDisableChannel(uint32_t id) {
    id &= 0x1fu;
    Channel[id].callback = NULL;
    disableTmr();
    disableAdc();
    adcEnabledChannels &= ~(0x1u << id);
    adcNumOfEnabledChannels--;

    if (adcEnabledChannels != 0u) {
        AD1CSSL = adcEnabledChannels;
        enableAdc(adcNumOfEnabledChannels);
        enableTmr();
    }
}

int32_t adcReadChannel(uint32_t id) {
    id &= 0x1fu;

    if ((adcEnabledChannels & (0x1u << id)) != 0u) {
        int32_t         retval;
        uint32_t        itr;

        for (retval = 0, itr = 0; itr < CONFIG_NUM_OF_SAMPLES; itr++) {
            retval += Channel[id].output[itr];
        }
        retval /= CONFIG_NUM_OF_SAMPLES;

        return (retval);
    } else {

        return (0);
    }
}

void __ISR(_ADC_VECTOR) adcHandler(void) {
    int32_t             value;
    uint32_t            cnt;
    uint32_t            id;

    id = 0u;

    for (cnt = 0; cnt < 16; cnt++) {
        value = (int32_t)(&ADC1BUF0)[cnt * 4u];

        while ((adcEnabledChannels & (0x1u << id)) == 0u) {
            id++;
        }

        if (id < CONFIG_NUM_OF_CHANNELS) {
            Channel[id].output[adcNumOfSamples] = value;

            if (Channel[id].callback != NULL) {
                Channel[id].callback(value);
            }
            id++;
        }
    }
    adcNumOfSamples++;

    if (adcNumOfSamples >= CONFIG_NUM_OF_SAMPLES) {
        adcNumOfSamples = 0;
        g_batch_is_done = true;
    }
    IFS0CLR = IFS0_AD1IF;
}
