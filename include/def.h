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
/* def.h: Basic constants definitions */
#include <sys/types.h>
#include <errno.h>
#ifndef	__DEF_H_
#define	__DEF_H_
// Basic constants
#define	NULL	(void*)0
#define	EOF	-1
#define	BUFSIZ	512
#define	KERNEL_SUCCESS	0
#define	KERNEL_FAILURE	1
#endif
