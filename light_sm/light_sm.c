#include <baremetalc.h>
// CMake uses pico SDK to compile pioasm and create the header file for us
// I believe, at time of compilation, this file is in build/CMakeFiles/light.dir
#include <../../light_sm.pio.h>

void wait(int, int, int*, volatile uint32_t*);

int main(int argc, char *argv)
{
    volatile uint32_t *pin_1_ctrl, *pin_2_ctrl, *pin_3_ctrl, *pin_4_ctrl, *pin_25_ctrl;
    volatile uint32_t *pio_sm0_ctrl, *pio_sm1_ctrl, *pio_sm2_ctrl, *pio_sm3_ctrl;
    volatile uint32_t *pio_sm0_pinctrl, *pio_sm1_pinctrl, *pio_sm2_pinctrl, *pio_sm3_pinctrl;
    volatile uint32_t* pio_ctrl;

    // Turn on the pico led every 500ms
    int led_time = 500;
    int counter = 0;
    
    // Light gpio pins
    pin_1_ctrl = GPIO_CTRL(1);
    pin_2_ctrl = GPIO_CTRL(2);
    pin_3_ctrl = GPIO_CTRL(3);
    pin_4_ctrl = GPIO_CTRL(4);
    
    // Select PIO0 as the function for GPIO1-4
    *pin_1_ctrl = 0x6;
    *pin_2_ctrl = 0x6;
    *pin_3_ctrl = 0x6;
    *pin_4_ctrl = 0x6;
    
    // Board LED
    pin_25_ctrl = GPIO_CTRL(25);
    *pin_25_ctrl = (3 << GPIO_OEOVER_BIT);

    // State machine pinctrl
    pio_sm0_pinctrl = PIO_SM_PINCTRL(PIO_0, 0);
    pio_sm1_pinctrl = PIO_SM_PINCTRL(PIO_0, 1);
    pio_sm2_pinctrl = PIO_SM_PINCTRL(PIO_0, 2);
    pio_sm3_pinctrl = PIO_SM_PINCTRL(PIO_0, 3);

    // Setup state machines pins to right gpio 
    // 5 bit offset is for set_base
    // 26 bit offset is for set_count
    *pio_sm0_pinctrl = ( (1 << 5) | (1 << 26) );
    *pio_sm1_pinctrl = ( (2 << 5) | (1 << 26) );
    *pio_sm2_pinctrl = ( (3 << 5) | (1 << 26) );
    *pio_sm3_pinctrl = ( (4 << 5) | (1 << 26) );

    // State machines control
    pio_sm0_ctrl = PIO_SM_TX_FIFO(PIO_0, 0);
    pio_sm1_ctrl = PIO_SM_TX_FIFO(PIO_0, 1);
    pio_sm2_ctrl = PIO_SM_TX_FIFO(PIO_0, 2);
    pio_sm3_ctrl = PIO_SM_TX_FIFO(PIO_0, 3);

    // Set state machines to run at apprx 8mhz
    // NOTE: assume pico is running at 125mhz
    (void) set_pio_sm_clock_speed(0, 0, 15, 8);
    (void) set_pio_sm_clock_speed(0, 1, 15, 8);
    (void) set_pio_sm_clock_speed(0, 2, 15, 8);
    (void) set_pio_sm_clock_speed(0, 3, 15, 8);

    // Load the instructions to PIO0
    (void) load_pio_instructions(0, light_sm_program_instructions, light_sm_program.length);
    
    // Enable SM1-SM4 on PIO0
    pio_ctrl = (volatile uint32_t *)PIO_0;
    *pio_ctrl |= (1 << 4) - 1;

    while (TRUE)
    {
        wait(led_time, 200, &counter, pin_25_ctrl);
        // SM0, turn on first led
        *pio_sm0_ctrl = 0x1;
        
        wait(led_time, 200, &counter, pin_25_ctrl);
        // SM1, turn on second led
        *pio_sm1_ctrl = 0x1;
        
        wait(led_time, 3000, &counter, pin_25_ctrl);
        // SM3, turn on third led
        *pio_sm2_ctrl = 0x1;
        
        wait(led_time, 200, &counter, pin_25_ctrl);
        // SM4, turn on fourth led
        *pio_sm3_ctrl = 0x1;
        
        wait(led_time, 200, &counter, pin_25_ctrl);
        // Turn off all led's
        *pio_sm0_ctrl = 0x0;
        *pio_sm1_ctrl = 0x0;
        *pio_sm2_ctrl = 0x0;
        *pio_sm3_ctrl = 0x0;
    }

    return 0;
}

/* Function: wait
 * Description:
 *  Pauses execution of thread for 'step' milliseconds
 *  Also switches the board led on/off using the flag 
 *  and counter variables
 *
 * Input:
 *  flag: when to switch led on/off
 *  step: time (in ms) to pause execution
 *  counter: tracks steps
 *  pin: GPIO 25 pin control
 */
void wait(int flag, int step, int* counter, volatile uint32_t* pin)
{   
    int tmp_step = 0;

    // When step exceedes flag, go ahead an keep led timing consistent
    while ( (*counter + step) > flag )
    {
        tmp_step = (flag - *counter);
        step -= tmp_step;
        milli_wait(tmp_step);
        *pin ^= (1 << GPIO_OUTOVER_BIT);
        *counter = 0;
    }
    
    milli_wait(step);
    *counter += step;
    if (*counter >= flag)
    {
        *pin ^= (1 << GPIO_OUTOVER_BIT);
        *counter = 0;
    }
}
