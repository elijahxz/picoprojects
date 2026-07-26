#ifndef BAREMETALC_H
#define BAREMETALC_H
#include <stdint.h>

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

// GPIO Defines
#define GPIO 0x40014000
#define GPIO_CTRL_OFFSET 0x4
#define GPIO_STEP 0x8

#define GPIO_CTRL(n) ((volatile uint32_t *)(GPIO + ((n) * GPIO_STEP) + GPIO_CTRL_OFFSET))

#define GPIO_OEOVER_BIT 12
#define GPIO_OUTOVER_BIT 8

// SIO Defines
#define SIO 0xd0000000
#define SIO_GPIO_OUT_SET (* (volatile uint32_t *)(SIO + 0x14))
#define SIO_GPIO_OUT_CLR (* (volatile uint32_t *)(SIO + 0x18))
#define SIO_GPIO_OE_SET (* (volatile uint32_t *)(SIO + 0x24))

// TIME defines
#define TIME 0x40054000
// Bits 32-63 of the 64 bit nanosecond timer
#define TIMEAWH (* (volatile uint32_t *)(TIME + 0x24))
// Bits 0-31 of the 64 bit nanosecond timer
#define TIMEAWL (* (volatile uint32_t *)(TIME + 0x28))

#define CLOCK 0x40008000
#define DEFAULT_CLOCK_SPEED 125000000

// PIO defines
#define PIO_0 0x50200000
#define PIO_1 0x50300000

#define PIO_CLKDIV_STEP 0x018
#define PIO_CLKDIV_OFFSET 0x0C8
#define PIO_SM_CLKDIV_CTRL(pio, n) ((volatile uint32_t *)(pio + ((n) * PIO_CLKDIV_STEP) + PIO_CLKDIV_OFFSET))

#define PIO_SMCTRL_STEP 0x018
#define PIO_SMCTRL_OFFSET 0x0DC
#define PIO_SM_PINCTRL(pio, n) ((volatile uint32_t *)(pio + ((n) * PIO_SMCTRL_STEP) + PIO_SMCTRL_OFFSET))

#define PIO_SMEXEC_STEP 0x018
#define PIO_SMEXEC_OFFSET 0x0CC
#define PIO_SM_EXECCTRL(pio, n) ((volatile uint32_t *)(pio + ((n) * PIO_SMEXEC_STEP) + PIO_SMEXEC_OFFSET))

#define PIO_MEM_LENGTH 32

#define PIO_MEM_STEP 0x04
#define PIO_MEM_OFFSET 0x048
#define PIO_MEM_ADDR(pio, n) ((volatile uint32_t *)(pio + ((n) * PIO_MEM_STEP) + PIO_MEM_OFFSET))

#define PIO_TX_STEP 0x04
#define PIO_TX_OFFSET 0x010
#define PIO_SM_TX_FIFO(pio, sm) ((volatile uint32_t *)(pio + ((sm) * PIO_TX_STEP) + PIO_TX_OFFSET))

void micro_wait(uint64_t microseconds);
void milli_wait(int);
int set_pio_sm_clock_speed(int, int, int, int);
int load_pio_instructions(int, const uint16_t*, int);

#endif
