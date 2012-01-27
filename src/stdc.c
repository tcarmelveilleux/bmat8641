/*
 * stdc.c
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

#include "stdc.h"

#define SCRATCH 20        //32Bits go up to 4GB + 1 Byte for \0

//Spare some program space by making a comment of all not used format flag lines
#define USE_LONG        // %lx, %Lu and so on, else only 16 bit integer is allowed
#define USE_STRING                        // %s, %S Strings as parameters
#define USE_CHAR        // %c, %C Chars as parameters
#define USE_INTEGER // %i, %I Remove this format flag. %d, %D does the same
#define USE_HEX                // %x, %X Hexadezimal output
#define USE_UPPERHEX        // %x, %X outputs A,B,C... else a,b,c...
#ifndef USE_HEX
# undef USE_UPPERHEX                // ;)
#endif
#define USE_UPPER // uncommenting this removes %C,%D,%I,%O,%S,%U,%X and %L..
                  // only lowercase format flags are used
#define PADDING   //SPACE and ZERO padding

void *memset(void *dst, int32_t s, uint32_t count) {
    register int8_t *a = dst;
    count++;
    while (--count)
        *a++ = s;
    return dst;
}

void *memcpy(void *dst, const void *src, uint32_t count) {
    register int8_t *d=dst;
    register const int8_t *s=src;
    ++count;
    while (--count) {
        *d = *s;
        ++d; ++s;
    }
    return dst;
}

int32_t memcmp(const void *dst, const void *src, uint32_t count) {
    int32_t r;
    const int8_t *d=dst;
    const int8_t *s=src;
    ++count;
    while (--count) {
        if ((r=(*d - *s)))
            return r;
        ++d;
        ++s;
    }
    return 0;
}

uint32_t strlen(const int8_t *s) {
    uint32_t i;
    if (!s) return 0;
    for (i = 0; *s; ++s) ++i;
    return i;
}

typedef struct Fprint Fprint;
struct Fprint {
    int32_t (*putc)(int32_t c, void *a);
    void *a;
};

void vrprintf(Fprint *fp, const char *fmt, va_list args) {
    uint8_t scratch[SCRATCH];
    uint8_t fmt_flag;
    uint16_t base;
    uint8_t *ptr;
    uint8_t issigned=0;

#ifdef USE_LONG
// #warning "use long"
    uint8_t islong=0;
    uint8_t isvlong=0;
    uint64_t u_val=0;
    int64_t s_val=0;
#else
    uint32_t u_val=0;
    int32_t s_val=0;
#endif

    uint8_t fill;
    uint8_t width;

    for (;;){
        while ((fmt_flag = *(fmt++)) != '%'){                         // Until '%' or '\0'
            if (!fmt_flag){ return; }
            if (fp->putc) fp->putc(fmt_flag, fp->a);
        }

        issigned=0; //default unsigned
        base = 10;

        fmt_flag = *fmt++; //get char after '%'

#ifdef PADDING
        width=0; //no formatting
        fill=0;         //no formatting

        if(fmt_flag=='0' || fmt_flag==' ') //SPACE or ZERO padding        ?
        {
            fill=fmt_flag;
            fmt_flag = *fmt++; //get char after padding char
            while(fmt_flag>='0' && fmt_flag<='9')
            {
                width = 10*width + (fmt_flag-'0');
                fmt_flag = *fmt++; //get char after width char
            }
        }
#endif

#ifdef USE_LONG
        islong=0; //default int value
        isvlong=0;
#ifdef USE_UPPER
        if(fmt_flag=='l' || fmt_flag=='L') //Long value
#else
        if(fmt_flag=='l') //Long value
#endif
        {
            islong=1;
            fmt_flag = *fmt++; //get char after 'l' or 'L'
            if (fmt_flag=='l'){
                isvlong = 1;
                fmt_flag = *fmt++; //get char after 'l' or 'L'
            }
        }
#endif

        switch (fmt_flag)
        {
#ifdef USE_CHAR
        case 'c':
#ifdef USE_UPPER
        case 'C':
#endif
            fmt_flag = va_arg(args, int32_t);
            // no break -> run into default
#endif

        default:
            if (fp->putc)
                fp->putc(fmt_flag, fp->a);
            continue;

#ifdef USE_STRING
#ifdef USE_UPPER
        case 'S':
#endif
        case 's':
            ptr = (uint8_t *)va_arg(args, int8_t *);
            while(*ptr) { if(fp->putc) fp->putc(*ptr, fp->a); ptr++; }
            continue;
#endif

#ifdef USE_OCTAL
        case 'o':
#ifdef USE_UPPER
        case 'O':
#endif
            base = 8;
            if (fp->putc) fp->putc('0', fp->a);
            goto CONVERSION_LOOP;
#endif

#ifdef USE_INTEGER //don't use %i, is same as %d
        case 'i':
#ifdef USE_UPPER
        case 'I':
#endif
#endif
        case 'd':
#ifdef USE_UPPER
        case 'D':
#endif
            issigned=1;
            // no break -> run into next case
        case 'u':
#ifdef USE_UPPER
        case 'U':
#endif

//don't insert some case below this if USE_HEX is undefined !
//or put                         goto CONVERSION_LOOP;        before next case.
#ifdef USE_HEX
            goto CONVERSION_LOOP;
        case 'x':
#ifdef USE_UPPER
        case 'X':
#endif
            base = 16;
#endif

        CONVERSION_LOOP:

            if(issigned) //Signed types
            {
#ifdef USE_LONG
                if(isvlong) { s_val = va_arg(args, int64_t); }
                else if(islong) { s_val = va_arg(args, int32_t); }
                else { s_val = va_arg(args, int32_t); }
#else
                s_val = va_arg(args, int32_t);
#endif

                if(s_val < 0) //Value negativ ?
                {
                    s_val = - s_val; //Make it positiv
                    if (fp->putc) fp->putc('-', fp->a);                 //Output sign
                }

                if(!isvlong)
                    u_val = (uint32_t)s_val;
                else
                    u_val = (uint64_t)s_val;
            } else //Unsigned types
            {
#ifdef USE_LONG
                if(isvlong) {u_val = va_arg(args, uint64_t); }
                else if(islong) { u_val = va_arg(args, uint32_t); }
                else { u_val = va_arg(args, uint32_t); }
#else
                u_val = va_arg(args, uint32_t);
#endif
            }

            ptr = scratch + SCRATCH;
            *--ptr = 0;
            do
            {
                int8_t ch = u_val % base + '0';
#ifdef USE_HEX
                if (ch > '9')
                {
                    ch += 'a' - '9' - 1;
#ifdef USE_UPPERHEX
                    ch-=0x20;
#endif
                }
#endif
                *--ptr = ch;
                u_val /= base;

#ifdef PADDING
                if(width) width--; //calculate number of padding chars
#endif
            } while (u_val);

#ifdef PADDING
            while(width--) *--ptr = fill; //insert padding chars
#endif

            while(*ptr) { if (fp->putc) fp->putc(*ptr, fp->a); ptr++; }
        }
    }
}

void __attribute__ ((weak)) kputchar(int32_t c) {

}

static int32_t printfputc(int32_t c, void *a){
    uint32_t * nc = (uint32_t *) a;
    if(c == '\n'){
        kputchar('\r');
        (*nc)++;
    }

    kputchar(c);
    (*nc)++;
    return 1;
}

int32_t kprintf(const char *fmt, ...){
    int32_t nc=0;
    Fprint fp = {printfputc, (void*)&nc};
    va_list args;
    va_start(args, fmt);
    vrprintf(&fp, fmt, args);
    va_end(args);

    return nc;
}
