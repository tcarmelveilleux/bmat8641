/**
 * @file core/include/ppc/ppc_asm.h
 *
 * @brief Assembly helper definitions
 *
 * @date Created on: 2010-04-29
 *
 * @author Tennessee Carmel-Veilleux (tennessee.carmelveilleux -at- gmail.com)
 *
 * @version XM-PPC-2.2.2 rev $Rev$
 *
 * Assembly helper definitions
 *
 * Register names and replacement opcodes
 */
/*
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

#ifndef _ARCH_PPC_PPC_ASM_H_
#define _ARCH_PPC_PPC_ASM_H_

#ifdef __ASSEMBLY__

/* Condition Register Bit Fields */
#define	cr0	0
#define	cr1	1
#define	cr2	2
#define	cr3	3
#define	cr4	4
#define	cr5	5
#define	cr6	6
#define	cr7	7

/* General Purpose Registers (GPRs) */

#define	r0	0
#define	r1	1
#define	r2	2
#define	r3	3
#define	r4	4
#define	r5	5
#define	r6	6
#define	r7	7
#define	r8	8
#define	r9	9
#define	r10	10
#define	r11	11
#define	r12	12
#define	r13	13
#define	r14	14
#define	r15	15
#define	r16	16
#define	r17	17
#define	r18	18
#define	r19	19
#define	r20	20
#define	r21	21
#define	r22	22
#define	r23	23
#define	r24	24
#define	r25	25
#define	r26	26
#define	r27	27
#define	r28	28
#define	r29	29
#define	r30	30
#define	r31	31

/* simics_magic_breakpoint assembler macro
 *
 * Creates a magic breakpoint with value "num" using the instruction specified
 * in figure 3.1 of the "Using Simics for Software Development" manual from
 * Simics 4.
 *
 */
.macro simics_magic_breakpoint num
/* Ensure argument is valid ( 0 <= num < (1 << 15) ) */
.if !( (\num >= 0) && (\num < (1 << 15)) )
.error "simics_magic_breakpoint with invalid value"
.endif
    rlwimi ((\num >> 10) & 0x1f),((\num >> 10) & 0x1f),0,((\num >> 5) & 0x1f),((\num >> 0) & 0x1f)
.endm

#endif /* __ASSEMBLER__ */
#endif /* _ARCH_PPC_PPC_ASM_H_ */
