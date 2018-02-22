[bits	16]
	jmp	bootloader_main

	UNIT	db	9,8,7,6,4,2,0
	RTC	db	"00","/","00","/","00","-","00","-","00",":","00",":","00"

bootloader_main:
	mov	ax,0x7C0
	mov	ds,ax
	mov	es,ax
	mov	bp,RTC
loop_start:
	mov	si,UNIT
	mov	di,RTC

	call	getRTC	; Get time
	call	printTime

	jmp	loop_start

getRTC:
	call	checkStatus	; Check if RTC is updated
	lodsb	; Get the time
	call	BCD2ASCII	; Change to ASCII
	call	saveTime

	add	di,2	; Increase the di to the next unit

	cmp	si,RTC
	jb	getRTC
	ret

printTime:
	mov	cx,20
	mov	ax,0x1301
	mov	bx,0x00c
	mov	dl,0x00
	int	0x10
	ret

checkStatus:
	mov	al,0xA
	out	0x70,al
	in	al,0x71
	test	al,0x80	; Check the first bit  of al
	jnz	checkStatus
	ret

getTime:
	out	0x70,al
	in	al,0x71
	ret

BCD2ASCII:
	mov	ah,al	; BCD to ASCII (e.g. 00010010=>0001 0010=>1 2=>"1" "2"
	mov	cl,4
	shr	ah,cl
	and	al,0x0F
	add	ah,0x30
	add	al,0x30
	ret
saveTime:
	mov	[di],ah
	inc	di
	mov	[di],al
	ret

	times	510-($-$$)	db	0
	dw	0xAA55
