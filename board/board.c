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

int main(int argc, char *argv)
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

    return 0;
}

