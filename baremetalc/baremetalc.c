#include <baremetalc.h>

static uint64_t time_read();

/* Function: micro_wait
 * Description:
 *  Does a wait/sleep for the amount of time passed in as an argument
 *
 * Input: Time in microseconds
 * Output: none
 * Globals:
 *  This threads execution of other user defined software is put on hold.
 */
void micro_wait(uint64_t microseconds)
{
    uint64_t start_time, current_time; 
    
    start_time = time_read();
 
    while(TRUE)
    {
        current_time = time_read();

        /* I really don't think any program I write 
         * will run for 400+ years consecutively, but
         * you never really know...
         */ 
        if (current_time < start_time)
        {
            uint64_t diff = 0xFFFFFFFFFFFFFFFF - start_time; 
            
            if (diff + current_time >= microseconds)
            {
                return;
            } 
        }
        else if ( (current_time - start_time) >= microseconds)
        {
            return;
        }
    }

    return; 
}

/* Function: milli_wait
 * Description:
 *  Does a wait/sleep for the amount of time passed in as an argument
 *
 * Input: Time in milliseconds
 * Output: none
 * Globals: 
 *  This threads execution of other user defined software is put on hold.
 */
void milli_wait(int milliseconds)
{
    micro_wait((uint64_t)milliseconds * 1000ULL);
    return;
}

/* Function: time_read
 * Description:
 *  Gets the boards current time in microseconds
 *
 * Input: none
 * Output: Time since startup in microseconds.
 */
static uint64_t time_read()
{
    uint64_t high, high1, low;

    // Edge case, make sure we capture the second set of bits for the time. 
    do 
    {
        high = TIMEAWH;
        low = TIMEAWL;
        high1 = TIMEAWH;
    } while (high != high1); 
    
    return ((uint64_t)high1 << 32) | low; 
}

/* Function: set_pio_clock_speed
 * Description:
 *  Sets the a pio's clock speed
 *
 * Input:
 *  pio: 0, 1
 *  state_machine: 0, 1, 2, 3
 *  divisor: non-negative
 *  fraction: 0-255
 *      ie: 128 = 0.5
 *
 * Output:
 *  TRUE: sm clock speed set
 *  FALSE: failure
 */
int set_pio_sm_clock_speed(int pio, int state_machine, int divisor, int fraction)
{
    volatile uint32_t* pio_sm_ctrl;
    
    if ( (pio != 0 && pio != 1) || 
         state_machine < 0 || state_machine > 3 ||
         divisor <= 0 || fraction < 0 || fraction >= 256 )
    {
        return FALSE;
    }

    if (divisor == 0)
    {
        fraction = 0;
    }   
 
    if (pio == 0)
    {
        pio_sm_ctrl = PIO_SM_CLKDIV_CTRL(PIO_0, state_machine);
    }
    else
    {
        pio_sm_ctrl = PIO_SM_CLKDIV_CTRL(PIO_1, state_machine);
    }

    *pio_sm_ctrl = (divisor << 16) | (fraction << 8);
  
    return TRUE; 
}

/* Function: set_pio_clock_speed
 * Description:
 *  Sets the a pio's clock speed
 *
 * Input:
 *  pio: 0, 1
 *  program_instructions: array of pio instructions
 *  instruction length: 0-32
 *
 * Output:
 *  TRUE: pio instructions loaded
 *  FALSE: failure
 */
int load_pio_instructions(int pio, const uint16_t * program_instructions, int instruction_length)
{
    volatile uint32_t* pio_mem_ctrl;
    uint32_t pio_addr;
    if (instruction_length > PIO_MEM_LENGTH)
    {
        return FALSE;
    }
    
    if (pio == 0)
    {
        pio_addr = PIO_0;
    }
    else
    {
        pio_addr = PIO_1;
    }

    // Clear out old instructions
    for(int i = 0; i < PIO_MEM_LENGTH; i++)
    {
        pio_mem_ctrl = PIO_MEM_ADDR(pio_addr, i);
        *pio_mem_ctrl = 0x0;
    }

    for(int i = 0; i < instruction_length; i++)
    {
        pio_mem_ctrl = PIO_MEM_ADDR(pio_addr, i);
        *pio_mem_ctrl = program_instructions[i];
    }

    return TRUE;
}
