gcc=arm-none-eabi-gcc
objcopy=arm-none-eabi-objcopy

FLAGS= -ggdb3 -nostdlib -std=c99 -mcpu=cortex-m4 \
       -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Wall \
       -Werror -nostartfiles -mthumb

binary_code: object_code
	$(objcopy) -O binary blink.elf blink.bin

object_code: ../miscellaneous/startup.s
	$(gcc) $(FLAGS) -T ../miscellaneous/Tiva.lds -o blink.elf \
    ../miscellaneous/startup.s *.c

openocd:
	openocd -f ../miscellaneous/ek-tm4c123gxl.cfg

gdb:
	ddd --debugger "arm-none-eabi-gdb blink.elf --command ../miscellaneous/gdb_startup"

flash: blink.bin
	lm4flash blink.bin

clean:
	rm blink.bin blink.elf
