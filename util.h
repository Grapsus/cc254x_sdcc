#include "cc254x_types.h"

void init_clock();
void delay_us(unsigned char microseconds);
void delay_ms(uint16 milliseconds);
void disableUsbPullup();
void enableUsbPullup();
uint8 vinPowerPresent();
