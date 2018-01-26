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
/* misc.h: It contains some fundamental standard and not standard C functions which are implemented by myself. */
#include <types.h>
#ifndef	__MISC_H_
#define	__MISC_H_
// Basic constants
#define	NULL	0
#define	EOF		-1
#define	TRUE	1
#define	FALSE	0
#ifdef	__cplusplus
extern "C"{
#endif
// These should be in ctypes.h
extern int isalpha(int c);
extern int isdigit(int c);
extern int isgraph(int c);
extern int isprint(int c);
extern int ispunct(int c);
extern int isspace(int c);

extern int islower(int c);
extern int isupper(int c);

extern int tolower(int c);
extern int toupper(int c);

// String functions
extern char* strchr(const char*,int c);
extern char* strcpy(char* dest,char* src);
extern unsigned int strlen(const char*);
/* Not standard string function(s) */
extern char* strrev(char *str);

// Conversion functions
/* String -> Integer */
extern int atoi(const char *nptr);
extern long atol(const char *nptr);
extern long long atoll(const char *nptr);
/* Integer -> String */
extern void itoa(int n,char *s);
extern void itoh(size_t n,char *s); // Byte to hex string

// Memory function
extern void* memcpy(void* dest,const void* src,size_t n);
extern void* memset(void* dest,int ch,size_t n);

#ifdef	__cplusplus
}
#endif
#endif
