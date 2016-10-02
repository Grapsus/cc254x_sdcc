/* code samples to test serial communications with UART
 * hook a 3.3 V usb to serial adapter like this:
 *  - cc254x P0.3 TX => adapter's RX
 *  - cc254x P0.3 RX => adapter's TX
 *  see "Table 7-1. Peripheral I/O Pin Mapping" for an
 *  alternate configuration */

#include "cc254x_types.h"
#include "cc254x_map.h"
#include "util.h"
#include "uart0.h"

#include <stdio.h>

int main(void) {
    char buf[30];

    init_clock();
    uart0Init();
    //uart0SetBaudRate(9600);
    // TODO fixme uart0SetBaudRate is broken
    // below are hardcoded register values for 115200 baud
    U0BAUD = 216;
    U0GCR &= 0x1F;
    U0GCR |= 11;

    while(1) {
        delay_ms(500);
        // direct IO periodic output
        /*if(uart0TxAvailable() >= 3) {
            uart0TxSendByte('H');
            uart0TxSendByte('i');
            uart0TxSendByte('!');
        }*/
        // stdio periodic output
        /*printf("Hello world!\r\n");*/
        // stdio 2 input and output
        printf("Name?\r\n");
        gets( buf);
        printf("Hi %s !\r\n", buf);
    }
}
