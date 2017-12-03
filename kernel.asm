ORG	0
start:
mov	si,msg
call	os_print_string
jmp	$

msg	db	"Hello world!",0Dh,0Ah,0
