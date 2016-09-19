CC=sdcc
CCFLAGS=--model-medium --debug --code-loc 0x0400 --code-size 0x7400 --iram-size 0x0100 --xram-loc 0xF000 --xram-size 0xF00

all:
	sdas8051 $(CFLAGS) -glos -p delay.s
	$(CC) $(CFLAGS) delay.rel -c util.c -o util.rel
	$(CC) $(CFLAGS) delay.rel util.rel blink.c -o blink.hex
