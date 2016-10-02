/* sample code to wiggle P1.2 at 1 Hz */

#include "cc254x_types.h"
#include "cc254x_map.h"
#include "util.h"

int main(void) {
    init_clock();

    P1DIR |= 0x04;

    while(1) {
        delay_ms(500);
        P1 ^= 0x04;
    }
}
