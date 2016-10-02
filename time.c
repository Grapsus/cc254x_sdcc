/* \file time.c
 *
 * This is the source file for the time component of <code>wixel.lib</code>.
 * For information on how to use these functions, see time.h.
 */

#include "cc254x_map.h"
#include "cc254x_types.h"
#include "time.h"

PDATA volatile uint32 timeMs;

ISR(T4, 0)
{
    T4CTL = 0b11111001;
    timeMs++;
}

uint32 getMs()
{
    uint8 oldT4IE = T4IE;   // store state of timer 4 interrupt (active/inactive?)
    uint32 time;
    T4IE = 0;               // disable timer 4 interrupt
    time = timeMs;          // copy millisecond timer count into a safe variable
    T4IE = oldT4IE;         // restore timer 4 interrupt to its original state
    return time;            // return timer count copy
}

void timeInit()
{
    /* modulo counting doesn't seem to trigger any interrupt on cc2450
     * so we count down and restart the counter each time
     * the value below was calibrated with a stopwatch */
    T4CC0 = 249;
    T4IE = 1;     // Enable Timer 4 interrupt.  (IEN1.T4IE=1)
    
    // DIV=111: 1:128 prescaler
    // START=1: Start the timer
    // OVFIM=1: Enable the overflow interrupt.
    // MODE=01: Count down
    T4CTL = 0b11111001;

    EA = 1; // Globally enable interrupts (IEN0.EA=1).
}

void delayMs(uint16 milliseconds)
{
    // TODO: make this more accurate.
    // A great way would be to use the compare feature of Timer 4 and then
    // wait for the right number of compare events to happen, but then we
    // can't use that channel for PWM in the future.
    while(milliseconds--)
    {
        delay_us(250);
        delay_us(250);
        delay_us(250);
        delay_us(249); // there's some overhead, so only delay by 249 here
    }
}
