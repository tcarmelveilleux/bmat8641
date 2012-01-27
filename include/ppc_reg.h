/**
 * @file ppc_reg.h
 *
 * @brief PowerPC special-function register (SPR) definitions
 *
 * @date Created on: 05/10/2010
 *
 * @author Tennessee Carmel-Veilleux (tennessee.carmelveilleux -at- gmail.com)
 *
 * @version 1.0 $Rev$
 *
 * PowerPC special-function register (SPR) definitions
 *
 * Some constants adapted from Linux 2.6.33.2 arch/powerpc/include/asm/reg.h
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

#ifndef _PPC_REG_H_
#define _PPC_REG_H_

/** Convert from standard bit number (LSb = 0) to PowerPC bit number (MSb = 0) */
#define BIT_TO_PPCBIT(n) (31-(n))

/** Create mask from bit number */
#ifdef __ASSEMBLY__
#define __MASK(X)	(1<<(X))
#define __MASK(X)	(1<<(X))
#else
#define __MASK(X)	(1UL<<(X))
#endif

#ifndef __ASSEMBLY__

/* Two levels of macro to permit macro expansion within stringification (GNU C Preprocessor sec 3.4) */
#define stringify(s)    tostring(s)
#define tostring(s) #s

/** SPR and MSR access macros */
#define mfmsr()     ({uint32_t rval; asm volatile("mfmsr %0" : "=r" (rval)); rval;})
#define mtmsr(value)    asm volatile("mtmsr %0" : : "r" (value) : "memory")

#define mfdec()     ({uint32_t rval; asm volatile("mfdec %0" : "=r" (rval)); rval;})
#define mtdec(value)    asm volatile("mtdec %0" : : "r" (value) : "memory")

#define mftbu()     ({uint32_t rval; asm volatile("mftbu %0" : "=r" (rval)); rval;})
#define mttbu(value)    asm volatile("mttbu %0" : : "r" (value) : "memory")

#define mftb()     ({uint32_t rval; asm volatile("mftb %0" : "=r" (rval)); rval;})
#define mttbl(value)    asm volatile("mttbl %0" : : "r" (value) : "memory")

#define mfspr(sprn)   ({uint32_t rval; asm volatile("mfspr %0," stringify(sprn) : "=r" (rval)); rval;})
#define mtspr(sprn, value)    asm volatile("mtspr " stringify(sprn) ",%0" : : "r" (value) : "memory")

#endif /* !define(__ASSEMBLY__) */

/* ---------- MSR: Machine state register ---------- */
#define MSR_VEC_BIT		6	    /* Enable AltiVec */
#define MSR_VSX_BIT		8		/* Enable VSX */
#define MSR_POW_BIT		13		/* Enable Power Management */
#define MSR_WE_BIT		13		/* Wait State Enable */
#define MSR_TGPR_BIT	14		/* TLB Update registers in use */
#define MSR_CE_BIT		14		/* Critical Interrupt Enable */
#define MSR_ILE_BIT		15		/* Interrupt Little Endian */
#define MSR_EE_BIT		16		/* External Interrupt Enable */
#define MSR_PR_BIT		17		/* Problem State / Privilege Level */
#define MSR_FP_BIT		18		/* Floating Point enable */
#define MSR_ME_BIT		19		/* Machine Check Enable */
#define MSR_FE0_BIT		20		/* Floating Exception mode 0 */
#define MSR_SE_BIT		21		/* Single Step */
#define MSR_BE_BIT		22		/* Branch Trace */
#define MSR_DE_BIT		22 		/* Debug Exception Enable */
#define MSR_FE1_BIT		23		/* Floating Exception mode 1 */
#define MSR_IP_BIT		25		/* Exception prefix 0x000/0xFFF */
#define MSR_IR_BIT		26 		/* Instruction Relocate */
#define MSR_DR_BIT		27 		/* Data Relocate */
#define MSR_PE_BIT		28		/* Protection Enable */
#define MSR_PX_BIT		29		/* Protection Exclusive Mode */
#define MSR_PMM_BIT		29		/* Performance monitor */
#define MSR_RI_BIT		30		/* Recoverable Exception */
#define MSR_LE_BIT		31 		/* Little Endian */

#define MSR_VEC		__MASK(31-MSR_VEC_BIT)		/* Enable AltiVec */
#define MSR_VSX		__MASK(31-MSR_VSX_BIT)		/* Enable VSX */
#define MSR_POW		__MASK(31-MSR_POW_BIT)		/* Enable Power Management */
#define MSR_WE		__MASK(31-MSR_WE_BIT)		/* Wait State Enable */
#define MSR_TGPR	__MASK(31-MSR_TGPR_BIT)	/* TLB Update registers in use */
#define MSR_CE		__MASK(31-MSR_CE_BIT)		/* Critical Interrupt Enable */
#define MSR_ILE		__MASK(31-MSR_ILE_BIT)		/* Interrupt Little Endian */
#define MSR_EE		__MASK(31-MSR_EE_BIT)		/* External Interrupt Enable */
#define MSR_PR		__MASK(31-MSR_PR_BIT)		/* Problem State / Privilege Level */
#define MSR_FP		__MASK(31-MSR_FP_BIT)		/* Floating Point enable */
#define MSR_ME		__MASK(31-MSR_ME_BIT)		/* Machine Check Enable */
#define MSR_FE0		__MASK(31-MSR_FE0_BIT)		/* Floating Exception mode 0 */
#define MSR_SE		__MASK(31-MSR_SE_BIT)		/* Single Step */
#define MSR_BE		__MASK(31-MSR_BE_BIT)		/* Branch Trace */
#define MSR_DE		__MASK(31-MSR_DE_BIT)		/* Debug Exception Enable */
#define MSR_FE1		__MASK(31-MSR_FE1_BIT)		/* Floating Exception mode 1 */
#define MSR_IP		__MASK(31-MSR_IP_BIT)		/* Exception prefix 0x000/0xFFF */
#define MSR_IR		__MASK(31-MSR_IR_BIT)		/* Instruction Relocate */
#define MSR_DR		__MASK(31-MSR_DR_BIT)		/* Data Relocate */
#define MSR_PE		__MASK(31-MSR_PE_BIT)		/* Protection Enable */
#define MSR_PX		__MASK(31-MSR_PX_BIT)		/* Protection Exclusive Mode */

#ifndef MSR_PMM
#define MSR_PMM		__MASK(31-MSR_PMM_BIT)		/* Performance monitor */
#endif

#define MSR_RI		__MASK(31-MSR_RI_BIT)		/* Recoverable Exception */
#define MSR_LE		__MASK(31-MSR_LE_BIT)		/* Little Endian */

/* ---------- L2CR: L2 Control Register  ---------- */
#define L2CR	1017

#define L2CR_L2E_BIT	0	/* Bit 0: L2 enable. Used to enable the L2 cache.  */
#define L2CR_L2PE_BIT	1	/* Bit 1: L2 data parity checking enable */
                            /* Bits 2-3: Reserved, will read as 0b11. */
                            /* Bits 4-9: Reserved */
#define L2CR_L2I_BIT	10	/* Bit 10: L2 global invalidate  */
#define L2CR_L2IO_BIT	11	/* Bit 11: L2 instruction-only. Causes the L2 cache to allocate lines for instruction cache transactions only. */
                            /* Bits 12-14: Reserved */
#define L2CR_L2DO_BIT	15	/* Bit 15: L2 data only. L2 cache lines are allocated for data cache transactions only. */
                            /* Bits 16-18: Reserved */
#define L2CR_L2REP_BIT	19	/* Bit 19: L2 replacement algorithm selection on a miss */
#define L2CR_L2HWF_BIT	20	/* Bit 20: L2 hardware flush */
                            /* Bits 21-23: Reserved */
                            /* Bits 24-27: Reserved. Writing these bits will result in undefined L2 cache behavior.  */
                            /* Bits 28-31: Reserved */

#define L2CR_L2E	__MASK(31)  /* Bit 0: L2 enable. Used to enable the L2 cache.  */
#define L2CR_L2PE	__MASK(30)  /* Bit 1: L2 data parity checking enable */
#define L2CR_L2I	__MASK(21)  /* Bit 10: L2 global invalidate  */
#define L2CR_L2IO	__MASK(20)  /* Bit 11: L2 instruction-only. Causes the L2 cache to allocate lines for instruction cache transactions only. */
#define L2CR_L2DO	__MASK(16)  /* Bit 15: L2 data only. L2 cache lines are allocated for data cache transactions only. */
#define L2CR_L2REP	__MASK(12)  /* Bit 19: L2 replacement algorithm selection on a miss */
#define L2CR_L2HWF	__MASK(11)  /* Bit 20: L2 hardware flush */

/* ---------- HID0: Hardware implementation-dependent registers.  ---------- */
#define HID0    1008

                                /* Bits 0-4: Reserved */
#define HID0_TBEN_BIT   5   /* Bit 5: Time base enable */
                                /* Bit 6: Reserved. */
#define HID0_STEN_BIT   7   /* Bit 7: Software table search enable. */
#define HID0_HIGH_BAT_EN_BIT    8   /* Bit 8: Additional BATs enabled for the e600 core */
#define HID0_NAP_BIT    9   /* Bit 9: Nap mode enable. Operates in conjunction with MSR[POW].  */
#define HID0_SLEEP_BIT  10  /* Bit 10: Sleep mode enable. Operates in conjunction with MSR[POW].  */
#define HID0_DPM_BIT    11  /* Bit 11: Dynamic power management enable */
                                /* Bit 12: Reserved. For test use; software should not set this bit. */
#define HID0_BHTCLR_BIT 13  /* Bit 13: Clear branch history table */
#define HID0_XAEN_BIT   14  /* Bit 14: Extended addressing enabled */
#define HID0_NHR_BIT    15  /* Bit 15: Not hard reset (software-use only). Helps software distinguish a hard reset from a soft reset.  */
#define HID0_ICE_BIT    16  /* Bit 16: Instruction cache enable */
#define HID0_DCE_BIT    17  /* Bit 17: Data cache enable */
#define HID0_ILOCK_BIT  18  /* Bit 18: Instruction cache lock */
#define HID0_DLOCK_BIT  19  /* Bit 19: Data cache lock  */
#define HID0_ICFI_BIT   20  /* Bit 20: Instruction cache flash invalidate */
#define HID0_DCFI_BIT   21  /* Bit 21: Data cache flash invalidate */
#define HID0_SPD_BIT    22  /* Bit 22: Speculative data cache and instruction cache access disable */
#define HID0_XBSEN_BIT  23  /* Bit 23: Extended BAT block size enable.  */
#define HID0_SGE_BIT    24  /* Bit 24: Store gathering enable */
                                /* Bit 25: Reserved. Defined as DCFA on some earlier processors. */
#define HID0_BTIC_BIT   26  /* Bit 26: Branch target instruction cache enable. Used to enable use of the 128-entry branch instruction cache. */
#define HID0_LRSTK_BIT  27  /* Bit 27: Link register stack enable */
#define HID0_FOLD_BIT   28  /* Bit 28: Branch folding enable */
#define HID0_BHT_BIT    29  /* Bit 29: Branch history table enable */
#define HID0_NOPDST_BIT 30  /* Bit 30: No-op dst, dstt, dstst, and dststt instructions */
#define HID0_NOPTI_BIT  31  /* Bit 31: No-op the data cache touch instructions */

#define HID0_TBEN   __MASK(26)
#define HID0_STEN   __MASK(24)
#define HID0_HIGH_BAT_EN    __MASK(23)
#define HID0_NAP    __MASK(22)
#define HID0_SLEEP  __MASK(21)
#define HID0_DPM    __MASK(20)
#define HID0_BHTCLR __MASK(18)
#define HID0_XAEN   __MASK(17)
#define HID0_NHR    __MASK(16)
#define HID0_ICE    __MASK(15)
#define HID0_DCE    __MASK(14)
#define HID0_ILOCK  __MASK(13)
#define HID0_DLOCK  __MASK(12)
#define HID0_ICFI   __MASK(11)
#define HID0_DCFI   __MASK(10)
#define HID0_SPD    __MASK(9)
#define HID0_XBSEN  __MASK(8)
#define HID0_SGE    __MASK(7)
#define HID0_BTIC   __MASK(5)
#define HID0_LRSTK  __MASK(4)
#define HID0_FOLD   __MASK(3)
#define HID0_BHT    __MASK(2)
#define HID0_NOPDST __MASK(1)
#define HID0_NOPTI  __MASK(0)

/* ---------- HID1: Hardware implementation-dependent registers  ---------- */
#define HID1    1009

#define HID1_EMCP_BIT   0   /* Bit 0: Machine check signal enable */
                                /* Bit 1: Reserved */
#define HID1_EBA_BIT    2   /* Bit 2: Enable/disable MPX bus address bus parity checking. */
#define HID1_EBD_BIT    3   /* Bit 3: Enable/disable MPX bus data parity checking. */
                                /* Bits 4-7: Reserved */
#define HID1_DFS4_BIT   8   /* Bit 8: Dynamic frequency switching (DFS) divide-by-four mode. */
#define HID1_DFS2_BIT   9   /* Bit 9: Dynamic frequency switching (DFS) divide-by-two mode. */
                                /* Bits 10-13: Reserved */
#define HID1_PC5_BIT    14  /* Bit 14: PLL configuration bit 5 (read-only). Reflects the state of the PLL multiplier. */
#define HID1_PC0_BIT    15  /* Bit 15: PLL configuration bit 0 (read-only). Reflects the state of the PLL multiplier. */
#define HID1_PC1_BIT    16  /* Bit 16: PLL configuration bit 1 (read-only). Reflects the state of the PLL multiplier. */
#define HID1_PC2_BIT    17  /* Bit 17: PLL configuration bit 2 (read-only). Reflects the state of the PLL multiplier. */
#define HID1_PC3_BIT    18  /* Bit 18: PLL configuration bit 3 (read-only). Reflects the state of the PLL multiplier. */
#define HID1_PC4_BIT    19  /* Bit 19: PLL configuration bit 4 (read-only). Reflects the state of the PLL multiplier. */
#define HID1_SYNCBE_BIT 20  /* Bit 20: Address broadcast enable for sync, eieio */
#define HID1_ABE_BIT    21  /* Bit 21: Address broadcast enable for dcbf, dcbst, dcbi, icbi, tlbie, and tlbsync. */
                                /* Bits 22-31: Reserved. Read as 0b00_1000_0000. */

#define HID1_EMCP   __MASK(31)
#define HID1_EBA    __MASK(29)
#define HID1_EBD    __MASK(28)
#define HID1_DFS4   __MASK(23)
#define HID1_DFS2   __MASK(22)
#define HID1_PC5    __MASK(17)
#define HID1_PC0    __MASK(16)
#define HID1_PC1    __MASK(15)
#define HID1_PC2    __MASK(14)
#define HID1_PC3    __MASK(13)
#define HID1_PC4    __MASK(12)
#define HID1_SYNCBE __MASK(11)
#define HID1_ABE    __MASK(10)

/** SRR0: Save/Restore register 0 */
#define SRR0    26

/** SRR1: Save/Restore register 0 */
#define SRR1    27

/** SPRG0: General SPR 0 */
#define SPRG0   272

/** SPRG1: General SPR 1 */
#define SPRG1   273

/** SPRG2: General SPR 2 */
#define SPRG2   274

/** SPRG3: General SPR 3 */
#define SPRG3   275

/** DAR: Data address register */
#define DAR     19

/** DSISR: DSISR */
#define DSISR   18

/** DEC: Decrementer */
#define DEC     22

/** TBL: Time base upper */
#define TBL     284

/** TBU: Time base lower  */
#define TBU     285

/** PIR: Processor ID */
#define PIR     1023

/** PVR: Processor version  */
#define PVR     287

/** XER: Integer exception register */
#define XER     1

/** MSSCR0: Memory Subsystem Control Register */
#define MSSCR0  1014

/* IBAT SPR numbers */
#define IBAT0L 0x211   /* Instruction BAT 0 Lower Register */
#define IBAT0U 0x210   /* Instruction BAT 0 Upper Register */
#define IBAT1L 0x213   /* Instruction BAT 1 Lower Register */
#define IBAT1U 0x212   /* Instruction BAT 1 Upper Register */
#define IBAT2L 0x215   /* Instruction BAT 2 Lower Register */
#define IBAT2U 0x214   /* Instruction BAT 2 Upper Register */
#define IBAT3L 0x217   /* Instruction BAT 3 Lower Register */
#define IBAT3U 0x216   /* Instruction BAT 3 Upper Register */

#define IBAT4L 0x231   /* Instruction BAT 4 Lower Register */
#define IBAT4U 0x230   /* Instruction BAT 4 Upper Register */
#define IBAT5L 0x233   /* Instruction BAT 5 Lower Register */
#define IBAT5U 0x232   /* Instruction BAT 5 Upper Register */
#define IBAT6L 0x235   /* Instruction BAT 6 Lower Register */
#define IBAT6U 0x234   /* Instruction BAT 6 Upper Register */
#define IBAT7L 0x237   /* Instruction BAT 7 Lower Register */
#define IBAT7U 0x236   /* Instruction BAT 7 Upper Register */

/* DBAT SPR Numbers */
#define DBAT0L 0x219   /* Data BAT 0 Lower Register */
#define DBAT0U 0x218   /* Data BAT 0 Upper Register */
#define DBAT1L 0x21B   /* Data BAT 1 Lower Register */
#define DBAT1U 0x21A   /* Data BAT 1 Upper Register */
#define DBAT2L 0x21D   /* Data BAT 2 Lower Register */
#define DBAT2U 0x21C   /* Data BAT 2 Upper Register */
#define DBAT3L 0x21F   /* Data BAT 3 Lower Register */
#define DBAT3U 0x21E   /* Data BAT 3 Upper Register */

#define DBAT4L 0x239   /* Data BAT 4 Lower Register */
#define DBAT4U 0x238   /* Data BAT 4 Upper Register */
#define DBAT5L 0x23B   /* Data BAT 5 Lower Register */
#define DBAT5U 0x23A   /* Data BAT 5 Upper Register */
#define DBAT6L 0x23D   /* Data BAT 6 Lower Register */
#define DBAT6U 0x23C   /* Data BAT 6 Upper Register */
#define DBAT7L 0x23F   /* Data BAT 7 Lower Register */
#define DBAT7U 0x23E   /* Data BAT 7 Lower Register */

#endif /* _PPC_REG_H_ */
