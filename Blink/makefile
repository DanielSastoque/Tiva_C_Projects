gcc=arm-none-eabi-gcc
objcopy=arm-none-eabi-objcopy

FLAGS= -ggdb3 -nostdlib -std=c99 -mcpu=cortex-m4 \
       -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Wall \
       -Werror -nostartfiles -mthumb

blink.bin: blink.elf
	$(objcopy) -O binary blink.elf blink.bin

blink.elf: ../startup.s
	$(gcc) $(FLAGS) -T ../Tiva.lds -o blink.elf \
    ../startup.s main.c led.c

openocd:
	openocd -f ../ek-tm4c123gxl.cfg

gdb:
	ddd --debugger "arm-none-eabi-gdb blink.elf --command gdb_startup"

flash:
	lm4flash blink.bin

clean:
	rm blink.bin blink.elf
