/* linker.ld: Linker script for kernel */
ENTRY(start)
SECTIONS
{
	. = 0x00100000;
	.text	:
	{
		code = .; _code = .; __code = .;
		*(.text)
		. = ALIGN(0x1000);
	}
	.data	:
	{
		data = .; _data = .; __data = .;
		*(.data)
		*(.rodata)
		. = ALIGN(0x1000);
	}
	.bss	:
	{
		bss = .; _bss = .; __bss = .;
		*(.bss)
		. = ALIGN(0x1000);
		endkernel = .;
	}

	end = .; _end = .; __end = .;
}
