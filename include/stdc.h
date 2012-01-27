/*
 * stdc.h
 * - *printf() based on sprintf() from gcctest9.c by Volker Oth <volkeroth@gmx.de>
 * - Changes made by Holger Klabunde
 * - Changes made by Martin Thomas for the efsl debug output
 * - Changes made by speiro for lpc2000 devices for PaRTiKle
 *
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _STDC_H_
#define _STDC_H_

typedef __builtin_va_list va_list;

#define va_start(v, l) __builtin_va_start(v,l)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v, l) __builtin_va_arg(v,l)

extern void *memset(void *dst, int32_t s, uint32_t count);
extern void *memcpy(void *dst, const void *src, uint32_t count);
extern int32_t memcmp(const void *dst, const void *src, uint32_t count);
extern uint32_t strlen(const int8_t *s);

extern void kputchar(int32_t c);
extern int32_t kprintf(const char *fmt, ...);
#endif
