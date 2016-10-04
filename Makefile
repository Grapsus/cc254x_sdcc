CC=sdcc
CFLAGS=--model-medium --xram-loc 0x0000 --xram-size 0x2000 --iram-size 0x0100 -I/usr/share/sdcc/include -DUART0
AS=sdas8051
ASFLAGS=-glos -p

LIBS=delay.rel util.rel time.rel uart.rel usb.rel usb_cdc_acm.rel
all: test_blink.hex test_uart.hex test_time.hex test_usb.hex

%.rel: %.c
	$(CC) $(CFLAGS) -c $? -o $@

%.rel: %.s
	$(AS) $(ASFLAGS) $?

%.hex: %.c $(LIBS)
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm *.asm *.hex *.lst *.map *.mem *.rel *.lk *.rst *.sym *.adb *.cdb *.omf -f

flash:
	cc-tool -f -e -w $(HEX)
