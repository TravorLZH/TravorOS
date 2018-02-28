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
[bits	32]
; Define some constants
VIDEO_MEMORY	equ	0xb8000
WHITE_ON_BLACK	equ	0x0f

; prints a null-terminated string pointed by EDX
print_string_pm:
	pusha
	mov	edx,VIDEO_MEMORY	; Set edx to the start of vid mem.

print_string_pm_loop:
	mov	al,[ebx]	; Store the char at EBX in AL
	mov	ah,WHITE_ON_BLACK	; Store the attributes in AH

	cmp	al,0	; if (al==0), at the end of string, so
	je	done	; jump to done

	mov	[edx],ax	; Store char and attributes at current character cell.
	add	ebx,1		; Increment EBX to the next char in string.
	add	edx,2		; Move to next character cell in vid mem

	jmp	print_string_pm_loop	; loop around to print the next char

done:
	popa
	ret				; Return from the function