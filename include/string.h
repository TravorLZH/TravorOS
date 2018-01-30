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
/* string.h: String and Memory Functions */
#ifndef	__STRING_H_
#define	__STRING_H_
#ifdef	__cplusplus
extern	"C"{
#endif
// String functions
extern char* strchr(const char*,int c);
extern char* strcpy(char* dest,char* src);
extern unsigned int strlen(const char*);
/* Not standard string function(s) */
extern char* strrev(char *str);
#ifdef	__cplusplus
}
#endif
#endif

