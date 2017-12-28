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
#include <screen.h>
#include <basic_io.h>

// Implementations for screen operations

void clear_screen(){
	int row=0;
	int col=0;
	for(;row<MAX_ROWS;row++){
		for(;col<MAX_COLS;col++){
			print_char(' ',row,col,WHITE_ON_BLACK);
		}
	}
}

int get_cursor(){
	// The device uses its control register as an index
	// to select its internal registers, of which we are
	// interested in:
	// 	reg 14: which is the high byte of the cursor's offset
	// 	reg 15: which is the low byte of the cursor's offset
	// Once the internal register had been selected, we may read or
	// write a byte on the data register.
	port_byte_out(REG_SCREEN_CTRL,14);
	int offset=port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out(REG_SCREEN_CTRL,15);
	offset+=port_byte_in(REG_SCREEN_DATA);
	return offset*2;
}

void set_cursor(int offset){
	offset /=2;
	port_byte_out(REG_SCREEN_CTRL,14);
	port_byte_out(REG_SCREEN_DATA,(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL,15);
	port_byte_out(REG_SCREEN_DATA,(offset & 0xFF));
}
int handle_scrolling(int offset){
	// If the cursor is within the screen return it unmodified
	if(offset<MAX_ROWS*MAX_COLS*2){
		return offset;
	}
	/* Shuffle the rows back one. */
	int i;
	for(i=1;i<MAX_ROWS;i++){
		memcpy(get_screen_offset(0,i-1)+VIDEO_ADDRESS,get_screen_offset(0,i)+VIDEO_ADDRESS,MAX_COLS*2);
	}
	/* Blank the last line by setting all bytes to 0 */
	char* last_line=(char*)(get_screen_offset(0,MAX_ROWS-1)+VIDEO_ADDRESS);
	for(i=0;i<MAX_COLS*2;i++){
		last_line[i]=0;
	}
	
	// Move the offset back one row, such that it is now on
	// row, rather than off the edge of the screen.
	offset-=2*MAX_COLS;
	
	// Return the updated cursor position.
	return offset;
}
int get_screen_offset(int col,int row){
	return (row*MAX_COLS+col)*2;
}
void print_at(const char* str,int col,int row,char attr){
	int i=0;
	if(col>=0 && row>=0){
		set_cursor(get_screen_offset(col,row));
	}
	for(;*(str+i)!=0;i++){
		print_char(*(str+i),col++,row,attr);
	}
}
/* Print a char on the screen at col, row, or at cursor position */
void print_char(char character,int col,int row,char attribute_byte){
	/* Create a byte (char) pointer to the start of video memory */
	unsigned char *vidmem=(unsigned char*)VIDEO_ADDRESS;
	
	/* If attribute byte is zero, assume the default style. */
	if(!attribute_byte){
		attribute_byte=WHITE_ON_BLACK;
	}
	
	/* Get the video memory offset for the screen location */
	int offset;
	/* If col and row are non-negative, use them for offset. */
	if(col >= 0 && row >= 0){
		offset=get_screen_offset(col,row);
	/* Otherwise, use the current cursor position */
	}else{
		offset=get_cursor();
	}
	// Detecting special characters
	int rows;
	switch(character){
		// If we see a Backspace, remove the current character and attribute
		// then decrement the offset.
		case '\b':
		vidmem[offset-2]=0;
		offset-=2;
		set_cursor(offset);
		return;
		break;
		// If we see a CR (Carriage Return), set the offset to the start of line.
		case '\r':
		rows=offset/(2*MAX_COLS);
		set_cursor_pos(0,rows);
		return;
		break;
		// If we see a newline character, set offset to the end of
		// current row, so it will be advanced to the first col
		// of the next row.
		case '\n':
		rows=offset/(2*MAX_COLS);
		offset=get_screen_offset(79,rows);
		break;
		// Otherwise, write the character and its attribute byte to
		// video memory at our calculated offset.
		default:
		vidmem[offset]=character;
		vidmem[offset+1]=attribute_byte;
	}
	
	// Update the offset to the next character cell, which is
	// two bytes ahead of the current cell.
	offset+=2;
	// Make scrolling adjustment, for when we reach the top of the screen.
	offset=handle_scrolling(offset);
	// Update the cursor position on the screen device.
	set_cursor(offset);
}