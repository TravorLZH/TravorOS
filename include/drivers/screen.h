/* 
* TravorOS: A simple OS running on Intel x86 Architecture
* Copyright (C) 2017  Travor Liu
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* screen.h: Function declarations of screen driver */
#ifndef	__SCREEN_H_
#define	__SCREEN_H_
#define	VIDEO_ADDRESS	0xb8000
#define	MAX_ROWS	25
#define	MAX_COLS	80
// Attribute byte for our default color scheme.
#define	WHITE_ON_BLACK	0x0f
// Screen device I/O ports
#define	REG_SCREEN_CTRL	0x3D4
#define	REG_SCREEN_DATA	0x3D5
// Screen algorithms
#define OFFSET(col,row)	get_screen_offset((col),(row))
#define	ROWS(offset)	((offset)/2*MAX_COLS)
#define	COLS(offset)	((offset)/2%MAX_COLS)
// Macro functions
#define	set_cursor_pos(x,y)	set_cursor(OFFSET((x),(y)))
#ifdef	__cplusplus
extern "C"{
#endif
extern void print_at(const char* str,int col,int row,char attr);
extern void print_char(char character,int col,int row,char attribute_byte);
extern void set_cursor(int offset);
extern int get_cursor();
#ifdef	__cplusplus
}
#endif
#endif
