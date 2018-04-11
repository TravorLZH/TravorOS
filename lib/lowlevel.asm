[bits	32]
[global set_interrupt]
[global _set_interrupt]
[global clear_interrupt]
[global _clear_interrupt]

_set_interrupt:
set_interrupt:
	sti
	ret

_clear_interrupt:
clear_interrupt:
	cli
	ret
