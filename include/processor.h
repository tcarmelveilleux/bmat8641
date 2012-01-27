/**
 * @file processor.h
 *
 * @brief Several processor macros and defines for the PowerPC archicture
 *
 * @date Created on: 05/10/2010
 *
 * @author Tennessee Carmel-Veilleux (tennessee.carmelveilleux -at- gmail.com)
 *
 * @version 1.0 $Rev$
 *
 * Several processor macros and defines for the PowerPC archicture
 *
 * Some IO routines come from U-Boot 2010-03 (include/asm-ppc/io.h),
 * originally from Linux source code, modified By Rob Taylor,
 * Flying Pig Systems, 2000.
 */
/*
 * COPYRIGHT 2000 Rob Taylor, Flying Pig Systems
 * COPYRIGHT 2010 Tennessee Carmel-Veilleux and Ecole de technologie superieure
 *
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

#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

/** Simics magic instruction parameter validation macro */
#define __MAGIC_CASSERT(p) do {                                 \
        typedef int __check_magic_argument[(p) ? 1 : -1];       \
} while (0)

/** Simics magic instruction insertion macro */
#define MAGIC(n) do {                                           \
       __MAGIC_CASSERT((n) >= 0 && (n) < (1 << 15));            \
       __asm__ __volatile__ ("rlwimi %0,%0,0,%1,%2"             \
                             :: "i" (((n) >> 10) & 0x1f),       \
                                "i" (((n) >>  5) & 0x1f),       \
                                "i" (((n) >>  0) & 0x1f));      \
} while (0)

/*
 * 8, 16 and 32 bit, big-endian I/O operations, with barrier.
 * Functions:
 *
 * Read operations have additional twi & isync to make sure the read
 * is actually performed (i.e. the data has come back) before we start
 * executing any following instructions.
 *
 * Read operations have additional twi & isync to make sure the read
 * is actually performed (i.e. the data has come back) before we start
 * executing any following instructions.
 *
 * A data-dependent branch followed by an isync ensures that no
 * instructions after the isync in program order will be
 * (speculatively) executed before the isync has completed, and
 * the isync won't complete until the branch is resolved. The
 * the load that the twi depends on has to complete before
 * anything else is executed; in particular, it's a barrier to
 * keep MMIO reads ordered before main-storage accesses.
  */

#define __iomem

static inline uint32_t io_in8(const volatile uint8_t __iomem *addr)
{
    uint32_t ret;

    __asm__ __volatile__(
        "sync; lbz%U1%X1 %0,%1;\n"
        "twi 0,%0,0;\n"
        "isync" : "=r" (ret) : "m" (*addr) : "memory");
    return ret;
}

static inline void io_out8(volatile uint8_t __iomem *addr, uint32_t val)
{
    __asm__ __volatile__("stb%U0%X0 %1,%0; eieio" : "=m" (*addr) : "r" (val) : "memory");
}

static inline uint32_t io_in16be(const volatile uint16_t __iomem *addr)
{
    uint32_t ret;

    __asm__ __volatile__("sync; lhz%U1%X1 %0,%1;\n"
                 "twi 0,%0,0;\n"
                 "isync" : "=r" (ret) : "m" (*addr) : "memory");
    return ret;
}

static inline void io_out16be(volatile uint16_t __iomem *addr, uint32_t val)
{
    __asm__ __volatile__("sync; sth%U0%X0 %1,%0" : "=m" (*addr) : "r" (val) : "memory");
}

static inline uint32_t io_in32be(const volatile uint32_t __iomem *addr)
{
    uint32_t ret;

    __asm__ __volatile__("sync; lwz%U1%X1 %0,%1;\n"
                 "twi 0,%0,0;\n"
                 "isync" : "=r" (ret) : "m" (*addr) : "memory");
    return ret;
}

static inline void io_out32be(volatile uint32_t __iomem *addr, uint32_t val)
{
    __asm__ __volatile__("sync; stw%U0%X0 %1,%0" : "=m" (*addr) : "r" (val) : "memory");
}

/**
 * Enforce In-order Execution of I/O:
 * Acts as a barrier to ensure all previous I/O accesses have
 * completed before any further ones are issued.
 */
static inline void eieio(void)
{
    __asm__ __volatile__ ("eieio" : : : "memory");
}

/**
 * Full data barrier (sync emitted)
 */
static inline void sync(void)
{
    __asm__ __volatile__ ("sync" : : : "memory");
}

/**
 * Instruction barrier (isync emitted)
 */
static inline void isync(void)
{
    __asm__ __volatile__ ("isync" : : : "memory");
}

#endif /* !defined(_PROCESSOR_H_) */
