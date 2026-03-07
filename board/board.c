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

#define GPIO_BASE 0x40014000
#define GPIO_CTRL_OFFSET 0x4
#define GPIO_STEP 0x8

#define GPIO_CTRL(n) ((volatile uint32_t *)(GPIO_BASE + ((n) * GPIO_STEP) + GPIO_CTRL_OFFSET))

#define GPIO_OEOVER_BIT 12
#define GPIO_OUTOVER_BIT 8



void blink_easy();
void blink_gpio(); 

int main(int argc, char *argv)
{
    // You can switch these out, they do the same thing
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
    
    // Override the pin to output mode
    *pin_25_ctrl ^= (0x3 << GPIO_OEOVER_BIT);
    
    // Set the pin to high/on 
    *pin_25_ctrl ^= (0x3 << GPIO_OUTOVER_BIT);
    
    while (TRUE)
    {
        sleep_ms(LED_DELAY_MS);

        // Set the pin to low/off
        *pin_25_ctrl ^= (0x1 << GPIO_OUTOVER_BIT);

        sleep_ms(LED_DELAY_MS);

        // Set the pin back to high/on
        *pin_25_ctrl ^= (0x1 << GPIO_OUTOVER_BIT);
    }
    
    return;     
}

