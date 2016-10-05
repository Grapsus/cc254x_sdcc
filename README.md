# Intro

This project is an attempt to write an open-source BlueTooth Low Energy stack for TI cc2540 and cc2541 RF MCUs.

At the moment, the only way to write BTLE applications for those chips is to use a binary stack from TI which can only be used in conjuction with the expensive IAR 8051 compiler.

The open-source stack would be built with SDCC. The firmware can then be uploaded to the chip by using the CC Debugger which is supported by cc-tool.

The starting point for this project was the Pololu Wixel SDK which uses a very similar chip, the cc2511 and SDCC. This is where I took and adapted the files for basic register support, UART and USB. The radio code however will need heavy modifications and maybe reverse engineering in order to work on the cc254x for sending BTLE frames.

It seems that cc254x is being replaced by cc2650 which is the same kind of RF MCU but with an ARM core. Even though the cc254x is still marked ACTIVE, this project could be not quite relevant for new harware applications. But I have a lot of cc254x hardware lying around plus I have the feeling that cc254x is closer to already documented chips that work with open-source software.

# Running the code

The Makefile is a mess at the moment, look at it and adapt any hardcoded paths if necessary.

Run `make` to build the libraries and examples.

Run `HEX=test_XXXX.hex make flash` to flash any of the examples onto the chip.

# Status

- `test_blink.c` works and prooves that SDCC can be used to produce code for cc254x
- `test_uart.c` works and is essential for starting to poke the radio hardware
- `test_time.c` uses TIMER4 interrupts to generate a millisecond clock
- `test_usb.c` ugly and incomplete but works for sending data through CDC ACM (cc2540 only)

Now that we have serial communications with the chip, I'm trying to start the radio interface and receive BTLE advertising frames which is the starting point for writing a BTLE stack. I'll post the code as soon as I have something working.

# Resources

- [CC2540/41 System-on-Chip Solution for 2.4-
GHz Bluetooth ® low energy Applications User's Guide](www.ti.com/lit/pdf/swru191)
- [SDCC Manual](http://sdcc.sourceforge.net/doc/sdccman.pdf)
- [TI BLE stack](http://www.ti.com/tool/ble-stack)
- [Pololu Wixel SDK](https://github.com/pololu/wixel-sdk)
- various cheap cc2540 and cc2541 boards from eBay
- TI cc2541 SensorTag devkit
- [TI CC Debugger programmer](http://www.ti.com/tool/cc-debugger)
- [cc-tool](https://github.com/dashesy/cc-tool) for using the CC debugger on Linux
