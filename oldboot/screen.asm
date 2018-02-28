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
os_set_cursor:
	mov	ah,02h
	int	10h
	ret
clear_screen:
	pusha
	mov bh,0
	mov	dl,0
	call	os_set_cursor
	mov	ah,6
	mov	al,0
	mov	bh,7
	mov	cx,0
	mov	dh,24
	mov	dl,79
	int	10h
	popa
	ret