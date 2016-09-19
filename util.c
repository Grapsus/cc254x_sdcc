#include "cc254x_types.h"
#include "cc254x_map.h"
#include "util.h"

void init_clock()
{
    // OSC_PD=0: Power up both high-speed oscillators: XOSC and HS RCOSC.
    SLEEP &= ~0x04;

    // Wait until the high speed crystal oscillator is stable (SLEEP.XOSC_STB=1)
    // This condition is required to use the radio or USB.
    // According to Table 6.4.2, the waiting should take about 650 microseconds.
    while(!(SLEEP & 0x40));

    // OSC32K = 1: Use low power 32kHz oscillator for the 32 kHz signal.
    // OSC=0: Select high speed crystal oscillator for system clock (24 MHz).
    // TICKSPD=000: Set the timer tick speed to its fastest possible value.
    // CLKSPD=000: Set system clock speed to its fastest possible value (24 MHz).
    //    This is required for using the Forward Error Correction radio feature (which we don't use anymore).
    CLKCON = 0x80;

    // Power down the HS RCOSC (the one that is not currently selected by
    // CLKCON.OSC).
    SLEEP |= 0x04;

    // Enable pre-fetching of instructions from flash,
    // which makes the code execute much faster.
    MEMCTR = 0;
}

void delay_ms(uint16 milliseconds)
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
