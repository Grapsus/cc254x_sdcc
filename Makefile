CC=sdcc
#CFLAGS=--model-medium --debug --code-loc 0x0000 --code-size 0x7400 --iram-size 0x0100 --xram-loc 0xF000 --xram-size 0xF00
CFLAGS=--model-medium

all:
	sdas8051 -glos -p delay.s
	$(CC) $(CFLAGS) -c util.c -o util.rel
	$(CC) $(CFLAGS) -DUART0 -c uart.c -o uart.rel
	$(CC) $(CFLAGS) blink.c -o blink.hex util.rel delay.rel uart.rel

clean:
	rm *.asm *.hex *.lst *.map *.mem *.rel *.lk *.rst *.sym *.adb *.cdb *.omf -f

flash:
	cc-tool -f -e -w blink.hex
