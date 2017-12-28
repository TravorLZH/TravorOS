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
; Reading disk: Load DH sectors to ES:BX from drive DL
disk_load:
	push	dx
	
	mov	ah,0x02
	mov	al,dh
	mov	ch,0x00
	mov	dh,0x00
	mov	cl,0x02
	
	int	0x13
	jc	disk_error
	pop	dx
	cmp	dh,al
	jne	disk_error2
	ret
disk_error:
	mov	bx,DISK_ERROR_MSG
	call	print_string
	call	CRLF
	jmp	$

disk_error2:
	mov	bx,DISK_ERROR_MSG2
	call	print_string
	call	CRLF
	jmp	$
; Variables
DISK_SUCCESS	db	"SUCCESS",0
LOADING_DISK	db	"Loading disk...",0
DISK_ERROR_MSG	db	"ERROR: Failed to read disk",0
DISK_ERROR_MSG2	db	"ERROR: Failed to load disk data",0