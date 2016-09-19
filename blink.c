#include "cc254x_types.h"
#include "cc254x_map.h"
#include "util.h"
#include "uart0.h"

int main(void) {
    init_clock();
    uart0Init();
    //uart0SetBaudRate(9600);
    U0BAUD = 216;
    U0GCR &= 0x1F;
    U0GCR |= 11;

    P1DIR |= 0x04;

    while(1) {
        delay_ms(500);
        P1 ^= 0x04;
        if(uart0TxAvailable() >= 3) {
            uart0TxSendByte('H');
            uart0TxSendByte('i');
            uart0TxSendByte('!');
        }
    }
}
