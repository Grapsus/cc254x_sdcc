/* this is an attempt to port Wixel SDK serial USB (CDC ACM protocol) code to cc2540
   WORK IN PROGRESS, compiles but doesn't work yet

   beware this is cc2540 only, cc2541 doesn't have USB hardware
   you're left with UART for communication

============================================
  usb_serial app:*/

/*
 * TODO: Support for USB CDC ACM control signals.
 * TODO: use LEDs to give feedback about USB activity.
 * TODO: UART flow control
 * TODO: give feedback about framing, parity, overrun errors to user and also to USB host
 * TODO: allow any control signal (or inverted control signal) to be mapped
 *       to any Wixel pin
 * TODO: add parameter for placing TX and RX in any of the 4 available locations
 * TODO: add a parameter for doing inverted TTL serial on RX and TX.
 * TODO: support the SendBreak request?
 * TODO: look at other usb-to-serial converters to see what their default values
 *       are for DTR and RTS (the current defaults set by usb_cdc_acm.lib are RTS=1,DTR=0)
 */

#include "cc254x_types.h"
#include "cc254x_map.h"
#include "time.h"
#include "util.h"
#include "usb.h"
#include "usb_com.h"

char CODE *msg = "Hello from USB!\r\n";

void usb_puts(uint8 CODE *str)
{
    while(*str)
    {
        if(usbComTxAvailable()) {
            usbComTxSendByte(*str++);
        }
    }
}

#include <stdio.h>

void main()
{
    uint32 t = 0;

    init_clock();
    timeInit();
    usbInit();

    while(1)
    {  
        usbComService();
        if(getMs() - t > 3000)
        {
            t = getMs();
            usb_puts(msg);
        }
    }
}
