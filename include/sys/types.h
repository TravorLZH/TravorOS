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
/* types.h: Definitions of signed and unsigned integer types */
#ifndef	__TYPES_H_
#define	__TYPES_H_
typedef unsigned int size_t;
#ifndef	HAVE_INT
// Definitions of signed int(s)
typedef char			int8_t;
typedef short			int16_t;
typedef int			int32_t;
typedef long long		int64_t;
// Definitions of unsigned int(s)
typedef unsigned char 		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
typedef unsigned long long	uint64_t;
#endif
#endif
