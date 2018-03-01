%ifdef	MINGW
%define	print_at _print_at
%endif
[global	shutdown]
[global	_shutdown]
[global	reboot]
[global	_reboot]
[extern	print_at]

_shutdown:
shutdown:
	push	0x0F
	push	-1
	push	-1
	push	NO_SHUTDOWN
	call	print_at
	add	esp,16
	hlt
	ret

NO_SHUTDOWN	db	"shutdown: function not implemented! Attempting to halt",0xA,0

_reboot:
reboot:
	cli			; Disable interrupts
	mov	al,0xFE	; Tell the keyboard controller to
	out	0x64,al	; activate the CPU reset line
	hlt
	ret
