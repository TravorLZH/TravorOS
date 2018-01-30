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
/* ctypes.h: Basic functions that determine the category of character(s) */
#ifndef	__CTYPES_H_
#define	__CTYPES_H_
#ifdef	__cplusplus
extern	"C"{
// Basic categories of characters
extern int isalpha(int c);
extern int isdigit(int c);
extern int isgraph(int c);
extern int isprint(int c);
extern int ispunct(int c);
extern int isspace(int c);
// Character cases
extern int islower(int c);
extern int isupper(int c);
// Conversion of character cases
extern int tolower(int c);
extern int toupper(int c);
#ifdef	__cplusplus
}
#endif
#endif

