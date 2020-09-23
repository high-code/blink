  
SDK_PATH=/home/esp8266/esp-open-sdk/sdk
CC= xtensa-lx106-elf-gcc
CFLAGS = -I . -I $(SDK_PATH)/driver_lib/include -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lc -ldriver -Wl,--end-group -lgcc
LDFLAGS = -Teagle.app.v6.ld -L $(SDK_PATH)/lib

.PHONY: flash clean

%.o:   %.c
		$(CC) $(CFLAGS) -c -o $@ $<
blinky-0x00000.bin: blinky
	esptool.py elf2image $^
blinky: blinky.o
flash: blinky-0x00000.bin
	esptool.py write_flash 0 blinky-0x00000.bin 0x10000 blinky-0x10000.bin
clean:
	rm -f blinky blinky.o blinky-0x00000.bin blinky-0x10000.bin
