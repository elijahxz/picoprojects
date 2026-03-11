#include <stdint.h>
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

