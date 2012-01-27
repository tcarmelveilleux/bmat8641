/**
 * @file ppc_asm_handlers.h
 *
 * @brief PowerPC assembly exception templates
 *
 * @date Created on: 05/10/2010
 *
 * @author Tennessee Carmel-Veilleux (tennessee.carmelveilleux -at- gmail.com)
 * @author Wolfgang Denk, DENX Software Engineering (wd@denx.de)
 *
 * @version 1.0 $Rev$
 *
 * PowerPC assembly exception templates
 *
 * These exception templates and macros are adapted from
 * file include/ppc_asm.tmpl from U-Boot 2010.03.
 *
 */
/*
 * COPYRIGHT 2000-2002 Wolfgang Denk, DENX Software Engineering (wd@denx.de)
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

#ifndef _PPC_ASM_HANDLERS_H_
#define _PPC_ASM_HANDLERS_H_

/* ASM offsets into some structures */
#define _HANDLER_OFFSET 0x0     /* 0x0     offsetof(struct irqTabEntry, handler) */
#define _DATA_OFFSET 0x4        /* 0x4     offsetof(struct irqTabEntry, data) */
#define _IRQCTXT_SIZE_OFFSET 0xac       /* 0xac    sizeof(struct irqCtxt) */
#define _GPR0_OFFSET 0x8        /* 0x8     8+offsetof(struct irqCtxt, gpr[0]) */
#define _GPR1_OFFSET 0xc        /* 0xc     8+offsetof(struct irqCtxt, gpr[1]) */
#define _GPR2_OFFSET 0x10       /* 0x10    8+offsetof(struct irqCtxt, gpr[2]) */
#define _GPR3_OFFSET 0x14       /* 0x14    8+offsetof(struct irqCtxt, gpr[3]) */
#define _GPR4_OFFSET 0x18       /* 0x18    8+offsetof(struct irqCtxt, gpr[4]) */
#define _GPR5_OFFSET 0x1c       /* 0x1c    8+offsetof(struct irqCtxt, gpr[5]) */
#define _GPR6_OFFSET 0x20       /* 0x20    8+offsetof(struct irqCtxt, gpr[6]) */
#define _GPR7_OFFSET 0x24       /* 0x24    8+offsetof(struct irqCtxt, gpr[7]) */
#define _GPR8_OFFSET 0x28       /* 0x28    8+offsetof(struct irqCtxt, gpr[8]) */
#define _GPR9_OFFSET 0x2c       /* 0x2c    8+offsetof(struct irqCtxt, gpr[9]) */
#define _GPR10_OFFSET 0x30      /* 0x30    8+offsetof(struct irqCtxt, gpr[10]) */
#define _GPR11_OFFSET 0x34      /* 0x34    8+offsetof(struct irqCtxt, gpr[11]) */
#define _GPR12_OFFSET 0x38      /* 0x38    8+offsetof(struct irqCtxt, gpr[12]) */
#define _GPR13_OFFSET 0x3c      /* 0x3c    8+offsetof(struct irqCtxt, gpr[13]) */
#define _GPR14_OFFSET 0x40      /* 0x40    8+offsetof(struct irqCtxt, gpr[14]) */
#define _GPR15_OFFSET 0x44      /* 0x44    8+offsetof(struct irqCtxt, gpr[15]) */
#define _GPR16_OFFSET 0x48      /* 0x48    8+offsetof(struct irqCtxt, gpr[16]) */
#define _GPR17_OFFSET 0x4c      /* 0x4c    8+offsetof(struct irqCtxt, gpr[17]) */
#define _GPR18_OFFSET 0x50      /* 0x50    8+offsetof(struct irqCtxt, gpr[18]) */
#define _GPR19_OFFSET 0x54      /* 0x54    8+offsetof(struct irqCtxt, gpr[19]) */
#define _GPR20_OFFSET 0x58      /* 0x58    8+offsetof(struct irqCtxt, gpr[20]) */
#define _GPR21_OFFSET 0x5c      /* 0x5c    8+offsetof(struct irqCtxt, gpr[21]) */
#define _GPR22_OFFSET 0x60      /* 0x60    8+offsetof(struct irqCtxt, gpr[22]) */
#define _GPR23_OFFSET 0x64      /* 0x64    8+offsetof(struct irqCtxt, gpr[23]) */
#define _GPR24_OFFSET 0x68      /* 0x68    8+offsetof(struct irqCtxt, gpr[24]) */
#define _GPR25_OFFSET 0x6c      /* 0x6c    8+offsetof(struct irqCtxt, gpr[25]) */
#define _GPR26_OFFSET 0x70      /* 0x70    8+offsetof(struct irqCtxt, gpr[26]) */
#define _GPR27_OFFSET 0x74      /* 0x74    8+offsetof(struct irqCtxt, gpr[27]) */
#define _GPR28_OFFSET 0x78      /* 0x78    8+offsetof(struct irqCtxt, gpr[28]) */
#define _GPR29_OFFSET 0x7c      /* 0x7c    8+offsetof(struct irqCtxt, gpr[29]) */
#define _GPR30_OFFSET 0x80      /* 0x80    8+offsetof(struct irqCtxt, gpr[30]) */
#define _GPR31_OFFSET 0x84      /* 0x84    8+offsetof(struct irqCtxt, gpr[31]) */
#define _NIP_OFFSET 0x88        /* 0x88    8+offsetof(struct irqCtxt, nip) */
#define _MSR_OFFSET 0x8c        /* 0x8c    8+offsetof(struct irqCtxt, msr) */
#define _IRQNR_OFFSET 0x90      /* 0x90    8+offsetof(struct irqCtxt, irqNr) */
#define _CTR_OFFSET 0x94        /* 0x94    8+offsetof(struct irqCtxt, ctr) */
#define _LR_OFFSET 0x98 /* 0x98    8+offsetof(struct irqCtxt, lr) */
#define _XER_OFFSET 0x9c        /* 0x9c    8+offsetof(struct irqCtxt, xer) */
#define _CCR_OFFSET 0xa0        /* 0xa0    8+offsetof(struct irqCtxt, ccr) */
#define _DAR_OFFSET 0xa4        /* 0xa4    8+offsetof(struct irqCtxt, dar) */
#define _DSISR_OFFSET 0xa8      /* 0xa8    8+offsetof(struct irqCtxt, dsisr) */
#define _RESULT_OFFSET 0xac     /* 0xac    8+offsetof(struct irqCtxt, result) */
#define _ERROR_OFFSET 0xb0      /* 0xb0    8+offsetof(struct irqCtxt, error) */
#define _UBOOT_GLOBAL_DATA_SIZE_OFFSET 0x3c     /* 0x3c    sizeof(UBOOT_global_data_t) */
#define _UBOOT_BOARD_DATA_SIZE_OFFSET 0x50      /* 0x50    sizeof(UBOOT_board_data_t) */
#define _UBOOT_BOARD_DATA_OFFSET 0x0    /* 0x0     offsetof(UBOOT_global_data_t, bd) */

/* Equivalence between asm offsets and exception frame indices name */
#define GPR0    _GPR0_OFFSET
#define GPR1    _GPR1_OFFSET
#define GPR2    _GPR2_OFFSET
#define GPR20   _GPR20_OFFSET
#define GPR21   _GPR21_OFFSET
#define GPR22   _GPR22_OFFSET
#define GPR23   _GPR23_OFFSET
#define RESULT  _RESULT_OFFSET
#define _IRQNR  _IRQNR_OFFSET
#define _ERROR  _ERROR_OFFSET
#define _CCR    _CCR_OFFSET
#define _CTR    _CTR_OFFSET
#define _DAR    _DAR_OFFSET
#define _DSISR  _DSISR_OFFSET
#define _LINK   _LR_OFFSET
#define _MSR    _MSR_OFFSET
#define _NIP    _NIP_OFFSET
#define _XER    _XER_OFFSET

/** Offset of PIC within CCSR */
#define BOARD_PIC_BASE (0x40000)

/** Offset of IACK register within PIC space (table 9-4 of MPC8641DRM) */
#define BOARD_PIC_IACK_OFFSET (0x00A0)

/** Offset of EOI register within PIC space (table 9-4 of MPC8641DRM) */
#define BOARD_PIC_EOI_OFFSET (0x00B0)

/** Full barrier */
#define SYNC    \
    sync;       \
    isync

/*
 * Macros for storing registers into and loading registers from
 * exception frames.
 */
#define SAVE_GPR(n, base)       stw n,GPR0+4*(n)(base)
#define SAVE_2GPRS(n, base)     SAVE_GPR(n, base); SAVE_GPR(n+1, base)
#define SAVE_4GPRS(n, base)     SAVE_2GPRS(n, base); SAVE_2GPRS(n+2, base)
#define SAVE_8GPRS(n, base)     SAVE_4GPRS(n, base); SAVE_4GPRS(n+4, base)
#define SAVE_10GPRS(n, base)    SAVE_8GPRS(n, base); SAVE_2GPRS(n+8, base)
#define REST_GPR(n, base)       lwz n,GPR0+4*(n)(base)
#define REST_2GPRS(n, base)     REST_GPR(n, base); REST_GPR(n+1, base)
#define REST_4GPRS(n, base)     REST_2GPRS(n, base); REST_2GPRS(n+2, base)
#define REST_8GPRS(n, base)     REST_4GPRS(n, base); REST_4GPRS(n+4, base)
#define REST_10GPRS(n, base)    REST_8GPRS(n, base); REST_2GPRS(n+8, base)

/*
 * GCC sometimes accesses words at negative offsets from the stack
 * pointer, although the SysV ABI says it shouldn't.  To cope with
 * this, we leave this much untouched space on the stack on exception
 * entry.
 */
#define STACK_UNDERHEAD 64

/*
 * EABI defines a minimum frame as having a backchain word (4 bytes)
 * and LR save area (4 bytes), with 8 bytes alignment.
 */
#define STACK_FRAME_OVERHEAD 8

/*
 * Exception frame size is struct irqCtxt size + the overhead.
 * Also make sure EXC_FRAME_SIZE is a multiple of 8.
 */
#define EXC_FRAME_SIZE    (((_IRQCTXT_SIZE_OFFSET + STACK_FRAME_OVERHEAD) + 7) &~ 0x7)

/**
 * Common exception prologue code.  This code runs with
 * address translation turned off on non-BOOKE PowerPC
 * (i.e. using physical addresses).
 *
 * @param xSRR0 - SRR0 register for this type of exception (ie: SRR0, CSRR0, MCSRR0)
 * @param xSRR1 - SRR1 register for this type of exception (ie: SRR1, CSRR1, MCSRR1)
 *
 * Post-conditions:
 *   - GPRs r0, r1, r2, r3, r4, r5, r6, r20, r21, r22, r23 are saved
 *   - SPRs LR, CTR, XER, DAR_DEAR are saved
 *   - r21 is exception frame pointer
 *   - r1 is exception stack pointer
 *   - r22 is xSRR0
 *   - r23 is xSRR1
 *   - r0, r2, r3, r4, r5, r6 r20 are scratch registers
 *   - Exception frame is valid with correct backchain word
 *   - Exception frame is setup to contain a struct irqCtxt as
 *     defined in core/include/arch/irqs.h. All registers are
 *     saved based on offsets in this struct, so that the exception
 *     handler later on can use the context information.
 *
 * FIXME: We assume sprg3 has the physical address of the current
 * task's thread_struct.
 */
#define EXCEPTION_PROLOG(xSRR0, xSRR1)                                  \
    /* Use r20, r21 as scratch, saving initial values in SPRG0,SPRG1 */ \
    mtspr   SPRG0,r20;                                                  \
    mtspr   SPRG1,r21;                                                  \
    mfcr    r20; /* r20 <- CR */                                        \
    /* Allocate exception stack frame in current context's              \
     * stack, with r21 as frame pointer */                              \
    subi    r21,r1,EXC_FRAME_SIZE + STACK_UNDERHEAD;                      \
    stw     r20,_CCR(r21);  /* Save CR */                               \
    /* Save r22, r23 */                                                 \
    stw     r22,GPR22(r21);                                             \
    stw     r23,GPR23(r21);                                             \
    /* Save original r20 from SPRG0 copy */                             \
    mfspr   r20,SPRG0;                                                  \
    stw     r20,GPR20(r21);                                             \
    /* Save original r21 from SPRG1 copy */                             \
    mfspr   r22,SPRG1;                                                  \
    stw     r22,GPR21(r21);                                             \
    /* --- Here: r20, r22, r23: scratch, r21: FP */                     \
    /* Save SPRs: LR, CTR, XER, DAR */                             \
    mflr    r20;                                                        \
    stw     r20,_LINK(r21);                                             \
    mfctr   r22;                                                        \
    stw     r22,_CTR(r21);                                              \
    mfspr   r20,XER;                                                    \
    stw     r20,_XER(r21);                                              \
    mfspr   r20, DAR;                                              \
    stw     r20,_DAR(r21);                                              \
    /* Get xSRR0, xSRR1 copies in r22, r23 */                           \
    mfspr   r22,xSRR0;                                                  \
    mfspr   r23,xSRR1;                                                  \
    /* Save r0, r1, r2 */                                               \
    stw     r0,GPR0(r21);                                               \
    stw     r1,GPR1(r21);                                               \
    stw     r2,GPR2(r21);                                               \
    /* Save pre-exception SP (r1) at 0(FP) -> backchain word */         \
    stw     r1,0(r21);                                                  \
    /* Set SP(r1) to FP -> Set kernel's new SP */                       \
    mr      r1,r21;                                                     \
    /* Save r3, r4, r5, r6 */                                           \
    SAVE_4GPRS(3, r21);

#define EOI_CODE(z,r)                                                  \
    li      z,0;                                                        \
    lis     r,(CONFIG_CCSR_BASE+BOARD_PIC_BASE+BOARD_PIC_EOI_OFFSET)@h;       \
    ori     r,r,(CONFIG_CCSR_BASE+BOARD_PIC_BASE+BOARD_PIC_EOI_OFFSET)@l;     \
    stw     z,0(r)
#define NO_EOI_CODE(z,r)

#define EXCEPTION_EPILOGUE(eoi)                                         \
    /* Restore CTR, LR, XER and CR */                                   \
    lwz     r2,_CTR(r1);                                                \
    lwz     r0,_LINK(r1);                                               \
    mtctr   r2;                                                         \
    mtlr    r0;                                                         \
    lwz     r2,_XER(r1);                                                \
    lwz     r0,_CCR(r1);                                                \
    mtspr   XER,r2;                                                     \
    mtcrf   0xFF,r0;                                                    \
    /* Restore r3-r31, r0 and r2 are scratch, r1 is still exception FP */ \
    REST_10GPRS(3, r1);                                                 \
    REST_10GPRS(13, r1);                                                \
    REST_8GPRS(23, r1);                                                 \
    REST_GPR(31, r1);                                                   \
    /* Restore environment prior to interrupt for RFI */                \
    lwz     r2,_NIP(r1);                                                \
    lwz     r0,_MSR(r1);                                                \
    mtspr   SRR0,r2;                                                    \
    mtspr   SRR1,r0;                                                    \
    /* Acknowledge end of interrupt if necessary */                     \
    eoi(r0,r2);                                                         \
    /* Restore pre-interrupt r0, r1 and r2 */                           \
    lwz     r0,GPR0(r1);                                                \
    lwz     r2,GPR2(r1);                                                \
    lwz     r1,GPR1(r1);                                                \
    /* Return from interrupt */                                         \
    SYNC;                                                               \
    rfi

/*
 * Note: code which follows this uses cr0.eq (set if from kernel),
 * r21, r22 (SRR0), and r23 (SRR1).
 */

/*
 * Exception vectors.
 *
 * The data words for `hdlr' and `int_return' are initialized with
 * OFFSET values only; they must be relocated first before they can
 * be used!
 */
#define COPY_EE(d, s)       rlwimi d,s,0,16,16
#define NOCOPY(d, s)
#define SET_RI(t)           mfmsr   t; \
                            ori     t,t,MSR_RI; \
                            mtmsr   t;
#define NO_SET_RI(t)
/** Exception handler transfer template
 *
 * @param label - label to use for exception constants table in the code
 * @param hdlr - address (label) of actual handler to call
 * @param intrtrn - address (label) where to jump to return from the exception
 * @param msr - MSR value to use after jumping to handler in kernel
 * @param copyee - macro (from the two above (COPY_EE(d,s) or NOCOPY(d,s)) to use to determine whether we copy xSRR1[EE] into kernel MSR
 *
 * Post-conditions: same as EXCEPTION_PROLOGUE, but r20 is now kernel MSR to be put in SRR1 prior to rfi.
 */
#define EXC_XFER_TEMPLATE(label, hdlr, intrtrn, msr, copyee)     \
    /* Set LR to address of transfer_to_handler, for blrl branch further down */ \
    bl  1f;                                             \
1:  mflr    r20;                                        \
    lwz r20,(.L_ ## label)-1b+8(r20);                   \
    mtlr    r20;                                        \
    /* Set r20 to desired kernel MSR value, copying EE  \
     * and IP from xSRR1 (stored in r23) if necessary    \
     */                                                 \
    li  r20,msr;                                        \
    copyee(r20,r23);                                    \
    rlwimi  r20,r23,0,25,25;                            \
    /* Branch to transfer_to_handler (already in LR)    \
     * and link so that LR now contains the address of  \
     * _L ## label (ie: points to handler address to    \
     * use). The transfer_to_handler routine will get   \
     * the data from the table using the LR as base.    \
     */                                                 \
    blrl;                                               \
.L_ ## label :                                          \
    .long   hdlr;                                       \
    .long   intrtrn;                                    \
    .long   transfer_to_handler;

/** Standard exception template
 *
 * @param offset - offset of this exception into the exception table
 * @param label - label to use for exception table entry
 * @param hdlr - address (label) of handler to call
 */
#define STD_EXCEPTION(offset, label, hdlr)              \
    . = _ExceptionTable + offset;                        \
label:                                                  \
    EXCEPTION_PROLOG(SRR0, SRR1);                       \
    /* Adjust r1 with stack frame overhead (back-chain  \
     * word + LR save) so that we have the address of   \
     * the beginning of the saved context area in the   \
     * frame in r3. r3 is the register used for the     \
     * first parameter of function calls, so when we    \
     * call the handler function, its first parameter   \
     * will be a pointer to a struct irqCtxt.           \
     */                                                 \
    addi    r3,r1,STACK_FRAME_OVERHEAD;                 \
    /* Preload r6 with exception number (0-31 for       \
     * regular exception or 0-127 for irqs)             \
     */                                                 \
    li      r6,(offset >> 8);                          \
    /* Transfer to the exception handler to finish      \
     * context saving and setup.                        \
     */                                                 \
    EXC_XFER_TEMPLATE(label, hdlr, int_return, KERNEL_MSR, NOCOPY)  \

/** Standard PIC Vectored IRQ template
 *
 * This template acknowledges the IRQ source from the PIC,
 * and turns on IRQs after the prologue.
 *
 * @param offset - offset of this exception into the exception table
 * @param label - label to use for exception table entry
 * @param hdlr - address (label) of handler to call
 */
#define STD_PIC_IRQ(offset, label, hdlr)                \
    . = _ExceptionTable + offset;                        \
label:                                                  \
    EXCEPTION_PROLOG(SRR0, SRR1);                       \
    addi    r3,r1,STACK_FRAME_OVERHEAD;                 \
    /* For IRQs we read PIC[IACK} to obtain the vector  \
     * number and acknowledge the IRQ. Only the 7 LSbs  \
     * of the vector number are used.                   \
     */                                                 \
    lis     r4,(CONFIG_CCSR_BASE+BOARD_PIC_BASE+BOARD_PIC_IACK_OFFSET)@h;      \
    ori     r6,r4,(CONFIG_CCSR_BASE+BOARD_PIC_BASE+BOARD_PIC_IACK_OFFSET)@l;   \
    lwz     r5,0(r6);                                   \
    andi.   r6,r5,0x7f;                                 \
    /* Set MSR[EE] to allow nesting of interrupts starting here \
     * and MSR[RI] to tell reset and machine check exceptions \
     * that SRR0 and SRR1 have been saved.              \
     */                                                 \
    mfmsr   r5;                                         \
    ori     r0,r5,(MSR_RI | MSR_EE);                    \
    mtmsr   r0;                                         \
    /* Transfer to the exception handler to finish      \
     * context saving and setup.                        \
     */                                                 \
    EXC_XFER_TEMPLATE(label, hdlr, irq_return, KERNEL_MSR, COPY_EE)  \

#endif /* _PPC_ASM_HANDLERS_H_ */
