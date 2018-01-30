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
/* kbd.h: Function prototypes of Keyboard Driver */
#ifndef	__KBD_H_
#define	__KBD_H_
// Key code definitions
#define	VK_BACK		0x08
#define VK_TAB		0x09
#define	VK_RETURN	0x0A
#define	VK_SHIFT	0x10
#define	VK_CONTROL	0x11
#define	VK_MENU		0x12	// ALT button
#define	VK_PAUSE	0x13
#define	VK_CAPITAL	0x14	// Caps Lock
#define	VK_ESCAPE	0x1B
#define	VK_SPACE	0x20
#define	VK_END		0x23
#define	VK_HOME		0x24
// Arrow keys
#define	VK_LEFT		0x25
#define	VK_UP		0x26
#define	VK_RIGHT	0x27
#define	VK_DOWN		0x28
#define	VK_F1		0x70
#define	VK_F2		0x71
#define	VK_F3		0x72
#define	VK_F4		0x73
#define	VK_F5		0x74
#define	VK_F6		0x75
#define	VK_F7		0x76
#define	VK_F8		0x77
#define	VK_F9		0x78
#define	VK_F10		0x79
#define	VK_F11		0x7A
#define	VK_F12		0x7B
#ifdef	__cplusplus
extern	"C"{
#endif
extern const char press_char[];			// Scan code table
extern char _getchar(void);			// Get character from keyboard without printing it
extern char code2char(unsigned char code);	// Convert scan code to key code
extern char getScancode();			// Get scan code from keyboard
#ifdef	__cplusplus
}
#endif
#endif
