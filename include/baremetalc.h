#ifndef BAREMETALC_H
#define BAREMETALC_H

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#define GPIO 0x40014000
#define GPIO_CTRL_OFFSET 0x4
#define GPIO_STEP 0x8

#define GPIO_CTRL(n) ((volatile uint32_t *)(GPIO + ((n) * GPIO_STEP) + GPIO_CTRL_OFFSET))

#define GPIO_OEOVER_BIT 12
#define GPIO_OUTOVER_BIT 8

#define SIO 0xd0000000
#define SIO_GPIO_OUT_SET (* (volatile uint32_t *)(SIO + 0x14))
#define SIO_GPIO_OUT_CLR (* (volatile uint32_t *)(SIO + 0x18))
#define SIO_GPIO_OE_SET (* (volatile uint32_t *)(SIO + 0x24))

#define TIME 0x40054000
// Bits 32-63 of the 64 bit nanosecond timer
#define TIMEAWH (* (volatile uint32_t *)(TIME + 0x24))
// Bits 0-31 of the 64 bit nanosecond timer
#define TIMEAWL (* (volatile uint32_t *)(TIME + 0x28))

void micro_wait(uint64_t);
void milli_wait(int);

#endif
