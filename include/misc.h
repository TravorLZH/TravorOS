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
/* misc.h: Some functions that I cannot put them into proper headers */
#include <types.h>
#ifndef	__MISC_H_
#define	__MISC_H_
#ifdef	__cplusplus
extern	"C"{
#endif
// Conversion functions
/* String -> Integer */
extern int atoi(const char *nptr);
/* Integer -> String */
extern void itoa(int n,char *s);
extern void itoh(size_t n,char *s); // Integer to hex string
#ifdef	__cplusplus
}
#endif
#endif
