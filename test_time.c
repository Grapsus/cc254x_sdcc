/* code samples to test timer */

#include "cc254x_types.h"
#include "cc254x_map.h"

#include "time.h"
#include "util.h"
#include "uart0.h"

#include <stdio.h>

int main(void) {
    init_clock();
    timeInit();
    uart0Init();
    //uart0SetBaudRate(9600);
    // TODO fixme uart0SetBaudRate is broken
    // below are hardcoded register values for 115200 baud
    U0BAUD = 216;
    U0GCR &= 0x1F;
    U0GCR |= 11;
    
    printf("start\r\n");

    while(1) {
        delay_ms(500);
        printf("getMs() => %ld\r\n", getMs());
    }
}
