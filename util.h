#include "cc254x_types.h"

void init_clock();
void delay_us(unsigned char microseconds);
void delay_ms(uint16 milliseconds);
void disableUsbPullup();
void enableUsbPullup();
uint8 vinPowerPresent();
/* even if we don't use this interrupt, make sure we have a vector for it
   so that the interrupt table has at least 17 entries, otherwise SDCC makes
   a sorter table and places code just after it :s */
void isr_wdt() __interrupt(17);
