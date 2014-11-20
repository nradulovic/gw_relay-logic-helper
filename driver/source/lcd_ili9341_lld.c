
#include "driver/lcd_ili9341_lld.h"
#include "TimeDelay.h"
#include <xc.h>

#define CONFIG_CS_TRIS                  TRISD
#define CONFIG_CS_GPIO                  LATD
#define CONFIG_CS_PIN                   10

#define CONFIG_DC_TRIS                  TRISG
#define CONFIG_DC_GPIO                  LATG
#define CONFIG_DC_GPIO_SET              LATGSET
#define CONFIG_DC_GPIO_CLR              LATGCLR
#define CONFIG_DC_PIN                   8

#define CONFIG_FMARK_TRIS               TRISG
#define CONFIG_FMARK_GPIO               LATG
#define CONFIG_FMARK_PIN                6

#define ACTIVATE_COMMAND()              CONFIG_DC_GPIO_CLR = (0x1u << CONFIG_DC_PIN)
#define DEACTIVATE_COMMAND()            CONFIG_DC_GPIO_SET = (0x1u << CONFIG_DC_PIN)

/*--  PMCON  -----------------------------------------------------------------*/
#define PMCON_ON                        (0x1u << 15)
#define PMCON_SIDL                      (0x1u << 13)
#define PMCON_ADRMUX_Pos                (11)
#define PMCON_ADRMUX_Msk                (0x3u << PMCON_ADRMUX_Pos)
#define PMCON_ADRMUX(x)                 (((x) << PMCON_ADRMUX_Pos) & PMCON_ADRMUX_Msk)
#define PMCON_PMPTTL                    (0x1u << 10)
#define PMCON_PTWREN                    (0x1u <<  9)
#define PMCON_PTRDEN                    (0x1u <<  8)
#define PMCON_CSF_Pos                   (6)
#define PMCON_CSF_Msk                   (0x3u << PMCON_CSF_Pos)
#define PMCON_CSF(x)                    (((x) << PMCON_CSF_Pos) & PMCON_CSF_Msk)
#define PMCON_ALP                       (0x1u <<  5)
#define PMCON_CS2P                      (0x1u <<  4)
#define PMCON_CS1P                      (0x1u <<  3)
#define PMCON_WRSP                      (0x1u <<  1)
#define PMCON_RDSP                      (0x1u <<  0)

#define PMCON_ADRMUX_SEPARATE           (0)

#define PMCON_CSF_CS1_AND_CS2           (2)
#define PMCON_CSF_CS2_ONLY              (1)
#define PMCON_CSF_NOT_USED              (0)

/*--  PMMODE  ----------------------------------------------------------------*/
#define PMMODE_BUSY                     (0x1u << 15)
#define PMMODE_IRQM_Pos                 (13)
#define PMMODE_IRQM_Msk                 (0x3u << PMMODE_IRQM_Pos)
#define PMMODE_IRQM(x)                  (((x) << PMMODE_IRQM_Pos) & PMMODE_IRQM_Msk)
#define PMMODE_INCM_Pos                 (11)
#define PMMODE_INCM_Msk                 (0x3u << PMMODE_INCM_Pos)
#define PMMODE_INCM(x)                  (((x) << PMMODE_INCM_Pos) & PMMODE_INCM_Msk)
#define PMMODE_MODE16                   (0x1u << 10)
#define PMMODE_MODE_Pos                 (8)
#define PMMODE_MODE_Msk                 (0x3u << PMMODE_MODE_Pos)
#define PMMODE_MODE(x)                  (((x) << PMMODE_MODE_Pos) & PMMODE_MODE_Msk)
#define PMMODE_WAITB_Pos                (6)
#define PMMODE_WAITB_Msk                (0x3u << PMMODE_WAITB_Pos)
#define PMMODE_WAITB(x)                 (((x) << PMMODE_WAITB_Pos) & PMMODE_WAITB_Msk)
#define PMMODE_WAITM_Pos                (2)
#define PMMODE_WAITM_Msk                (0xfu << PMMODE_WAITM_Pos)
#define PMMODE_WAITM(x)                 (((x) << PMMODE_WAITM_Pos) & PMMODE_WAITM_Msk)
#define PMMODE_WAITE_Pos                (0)
#define PMMODE_WAITE_Msk                (0x3u << PMMODE_WAITE_Pos)
#define PMMODE_WAITE(x)                 (((x) << PMMODE_WAITE_Pos) & PMMODE_WAITE_Msk)

#define PMMODE_MODE_MASTER1             (3)
#define PMMODE_MODE_MASTER2             (2)
#define PMMODE_MODE_ENHANCED_SLAVE      (1)
#define PMMODE_MODE_LEGACY_SLAVE        (0)

/*--  PMADDR  ----------------------------------------------------------------*/
#define PMADDR_CS2                      (0x1u << 15)
#define PMADDR_CS1                      (0x1u << 14)

/*--  PMAEN  -----------------------------------------------------------------*/
#define PMAEN_CS2                       (0x1u << 15)
#define PMAEN_CS1                       (0x1u << 14)

/*--  PMSTAT  ----------------------------------------------------------------*/
#define PMSTAT_IBF                      (0x1u << 15)
#define PMSTAT_IBOV                     (0x1u << 14)
#define PMSTAT_IB3F                     (0x1u << 11)
#define PMSTAT_IB2F                     (0x1u << 10)
#define PMSTAT_IB1F                     (0x1u <<  9)
#define PMSTAT_IB0F                     (0x1u <<  8)
#define PMSTAT_OBE                      (0x1u <<  7)
#define PMSTAT_OBUF                     (0x1u <<  6)
#define PMSTAT_OB3E                     (0x1u <<  3)
#define PMSTAT_OB2E                     (0x1u <<  2)
#define PMSTAT_OB1E                     (0x1u <<  1)
#define PMSTAT_OB0E                     (0x1u <<  0)

static void pmp_wait_idle(void)
{
    while (PMMODE & PMMODE_BUSY);
}

static void pmp_write(uint32_t data)
{
    PMDIN = data;
}
 
void ili9341_lld_init(void)
{
#if defined(CONFIG_RST_TRIS)
    CONFIG_RST_TRIS   &= ~(0x1u << CONFIG_RST_PIN);
    CONFIG_RST_GPIO   &= ~(0x1u << CONFIG_RST_PIN);
#endif
    CONFIG_DC_TRIS    &= ~(0x1u << CONFIG_DC_PIN);
    CONFIG_DC_GPIO    &= ~(0x1u << CONFIG_DC_PIN);
    CONFIG_CS_TRIS    &= ~(0x1u << CONFIG_CS_PIN);
    CONFIG_CS_GPIO    &= ~(0x1u << CONFIG_CS_PIN);
    CONFIG_FMARK_TRIS |=  (0x1u << CONFIG_FMARK_PIN);
    
    /* Setup PMP */
    PMCON  = 0;
    Delay10us(1);
    PMCON  = PMCON_ADRMUX(PMCON_ADRMUX_SEPARATE) | PMCON_PMPTTL | PMCON_PTWREN |
             PMCON_CSF(PMCON_CSF_NOT_USED);
    PMMODE = PMMODE_MODE(PMMODE_MODE_MASTER2) | PMMODE_WAITB(3) |
             PMMODE_WAITM(15) | PMMODE_WAITE(3);
    PMAEN  = 0;
    PMCON |= PMCON_ON;

    ili9341_lld_reset();
}

void ili9341_lld_reset(void)
{
#if defined(CONFIG_RST_TRIS)
    CONFIG_RST_GPIO   &= ~(0x1u << CONFIG_RST_PIN);
    /*
     * TODO: Wait 10ms
     */
    CONFIG_RST_GPIO   |=  (0x1u << CONFIG_RST_PIN);
#endif
}

void ili9341_lld_write_cmd(uint32_t cmd)
{
    pmp_wait_idle();
    ACTIVATE_COMMAND();
    pmp_write(cmd);
    pmp_wait_idle();
    DEACTIVATE_COMMAND();
}

void ili9341_lld_write_data(uint32_t data)
{
    pmp_wait_idle();
    pmp_write(data);
    pmp_wait_idle();
}
