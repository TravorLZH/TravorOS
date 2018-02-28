; TravorOS: A simple OS running on Intel x86 Architecture
; Copyright (C) 2017  Travor Liu
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <https://www.gnu.org/licenses/>.
;
; Print hexadecimal from DX
print_hex:
	pusha
	mov	si,HEX_OUT + 2
next_char:
	mov	bx,dx
	and	bx,0xf000
	shr	bx,4
	add	bh,0x30
	cmp	bh,0x39
	jg	add_7
add_char_hex:
	mov	al,bh
	mov	[si],bh
	inc	si
	shl	dx,4
	or	dx,dx
	jnz	next_char
	mov	bx,HEX_OUT
	call	print_string
	popa
	ret
add_7:
	add	bh,0x7
	jmp	add_char_hex
HEX_OUT:
	db	'0x0000',0
print_string:
	mov	ah,0Eh
.rep:
	mov	al,[bx]
	add	bx,1
	cmp	al,0
	je	.done
	int	10h
	jmp	.rep
.done:
	ret
CRLF:
	mov	ah,0Eh
	mov	al,0xD
	int	10h
	mov	al,0xA
	int	10h
	ret

; Read Character from keyboard
; Returns: AL the character read from keyboard
read_char:
	mov	ah,0
	int	16h
	ret
