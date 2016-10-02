CC=sdcc
#CFLAGS=--model-medium --debug --code-loc 0x0000 --code-size 0x7400 --iram-size 0x0100 --xram-loc 0xF000 --xram-size 0xF00
CFLAGS=--model-medium -L/usr/share/sdcc/include/
SDCC_LIBS=/usr/share/sdcc/lib/medium/libsdcc.lib

all: test_blink.hex test_uart.hex test_time.hex test_usb.hex

libs: delay.s util.c uart.c
	sdas8051 -glos -p delay.s
	$(CC) $(CFLAGS) -c util.c -o util.rel
	$(CC) $(CFLAGS) -c time.c -o time.rel
	$(CC) $(CFLAGS) -DUART0 -c uart.c -o uart.rel
	$(CC) $(CFLAGS) -c usb.c -o usb.rel
	$(CC) $(CFLAGS) -c usb_cdc_acm.c -o usb_cdc_acm.rel

test_blink.hex: test_blink.c libs
	$(CC) $(CFLAGS) test_blink.c -o test_blink.hex util.rel delay.rel

test_uart.hex: test_uart.c libs
	$(CC) $(CFLAGS) test_uart.c -o test_uart.hex util.rel delay.rel uart.rel $(SDCC_LIBS)

test_time.hex: test_time.c libs
	$(CC) $(CFLAGS) test_time.c -o test_time.hex util.rel delay.rel uart.rel time.rel $(SDCC_LIBS)

test_usb.hex: test_usb.c libs
	$(CC) $(CFLAGS) test_usb.c -o test_usb.hex util.rel delay.rel time.rel usb.rel usb_cdc_acm.rel

clean:
	rm *.asm *.hex *.lst *.map *.mem *.rel *.lk *.rst *.sym *.adb *.cdb *.omf -f

flash:
	cc-tool -f -e -w $(HEX)
