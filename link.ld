/* linker.ld: Linker script for kernel */
ENTRY(start)
SECTIONS
{
	. = 0x00100000;
	.text	:
	{
		code = .; _code = .; __code = .;
		*(.text)
		. = ALIGN(0x200);
	}
	.data	:
	{
		data = .; _data = .; __data = .;
		*(.data)
		*(.rodata)
		. = ALIGN(0x200);
	}
	.bss	:
	{
		bss = .; _bss = .; __bss = .;
		*(.bss)
		. = ALIGN(0x200);
		end_kernel = . + 0x200;
	}

	end = .; _end = .; __end = .;
}
