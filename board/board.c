#include <pico/stdlib.h>
#ifndef LED_DELAY_MS
    #define LED_DELAY_MS 500
#endif

#ifndef PICO_DEFAULT_LED_PIN
    #warning board requires a pico board with a regular LED
#endif

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


void blink_easy();
void blink_gpio(); 
void blink_sio(); 

int main(int argc, char *argv)
{
    // You can switch these out, they do the same thing
    //blink_sio();
    blink_gpio();
    //blink_easy();

    return 0;
}

/* Function: blink_easy
 * Description:
 *  Turns the LED on the board on and off through the pico sdk
 *
 * Input: none
 * Output: none
 */
void blink_easy()
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (TRUE)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, TRUE);
        sleep_ms(LED_DELAY_MS);
        gpio_put(PICO_DEFAULT_LED_PIN, FALSE);
        sleep_ms(LED_DELAY_MS);
    }
    return;
}

/* Function: blink_gpio
 * Description:
 *  Turns the LED on the board on and off through the GPIO registers.
 *
 *  OEOVER & OUTOVER bits:
 *      00 -> normal
 *      01 -> invert
 *      10 -> low
 *      11 -> high
 *
 * Input: none
 * Output: none
 */
void blink_gpio()
{
    int pin = 25;
    volatile uint32_t* pin_25_ctrl;
    
    // Get the pin we would like to control
    pin_25_ctrl = GPIO_CTRL(pin);
    
    // Set the pin to output mode
    *pin_25_ctrl = (3 << GPIO_OEOVER_BIT | 3 << GPIO_OUTOVER_BIT);
    
    while (TRUE)
    {
        sleep_ms(LED_DELAY_MS);

        // Set the pin to low/off
        *pin_25_ctrl ^= (1 << GPIO_OUTOVER_BIT);

        sleep_ms(LED_DELAY_MS);

        // Set the pin back to high/on
        *pin_25_ctrl ^= (1 << GPIO_OUTOVER_BIT);
    }
    
    return;     
}


/* Function: blink_sio
 * Description:
 *  Turns the LED on the board on and off through the SIO registers
 *  SIO: single-cycle input/output
 *
 * Input: none
 * Output: none
 */
void blink_sio()
{
    int pin_25 = 25;
    volatile uint32_t* pin_25_ctrl;
    
    // Get the pin we would like to control
    pin_25_ctrl = GPIO_CTRL(pin_25);

    // Connect the pin to the SIO
    *pin_25_ctrl = 5;

    // Set the pin to output mode
    SIO_GPIO_OE_SET = (1 << pin_25); 

    while (TRUE)
    {
        // Set the pin to high (on)
        SIO_GPIO_OUT_SET = (1 << pin_25);
        sleep_ms(LED_DELAY_MS);

        // Set the pin to low (off)
        SIO_GPIO_OUT_CLR = (1 << pin_25);
        sleep_ms(LED_DELAY_MS);
    }
    
    return;
}

