/** usb_serial app:

This app allows you to turn a Wixel into a USB-to-TTL serial adapter.

For complete documentation and a precompiled version of this app, see the
"USB-to-Serial App" section of the Pololu Wixel User's Guide:
http://www.pololu.com/docs/0J46


== Pinout ==

P1_0 = nDTR: general purpose output pin controlled by computer
P1_1 = nRTS: general purpose output pin controlled by computer
P1_2 = nDSR: general purpose input pin reported to computer
P1_3 = nCD: general purpose input pin reported to computer
(P1_4: Reserved for CT flow control line in future version.)
(P1_5: Reserved for RT flow control line in future version.)
P1_6 = TX:  transmits data from computer
P1_7 = RX:  receives data and sends it to the computer
*/

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

/** Dependencies **************************************************************/
#include "cc254x_map.h"
//#include <random.h>
#include <time.h>

#include "util.h"

#include "usb.h"
#include "usb_com.h"

#include "uart0.h"

/** Functions *****************************************************************/
void usbToUartService()
{
    uint8 signals;

    // Data
    while(usbComRxAvailable() && uart0TxAvailable())
    {
        uart0TxSendByte(usbComRxReceiveByte());
    }

    while(uart0RxAvailable() && usbComTxAvailable())
    {
        usbComTxSendByte(uart0RxReceiveByte());
    }

    // Control lines controlled by computer.
    P1_0 = !(usbComRxControlSignals() & ACM_CONTROL_LINE_DTR);
    P1_1 = !(usbComRxControlSignals() & ACM_CONTROL_LINE_RTS);
    P1DIR |= (1<<0) | (1<<1);

    // Control lines controlled by device.

    signals = 0;
    if (!P1_2){ signals |= ACM_SERIAL_STATE_TX_CARRIER; } // TX Carrier = DSR
    if (!P1_3){ signals |= ACM_SERIAL_STATE_RX_CARRIER; } // RX Carrier = CD
    usbComTxControlSignals(signals);
}

void lineCodingChanged()
{
    uart0SetBaudRate(usbComLineCoding.dwDTERate);
    uart0SetParity(usbComLineCoding.bParityType);
    uart0SetStopBits(usbComLineCoding.bCharFormat);
}

void main()
{
    //systemInit();
    init_clock();
    usbInit();
    usbComLineCodingChangeHandler = &lineCodingChanged;

    uart0Init();
    lineCodingChanged();

    while(1)
    {
        usbComService();
        usbToUartService();
    }
}
