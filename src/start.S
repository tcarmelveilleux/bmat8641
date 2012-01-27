/**
 * @file start.S
 *
 * @brief Exception table and startup code for MPC8641 bare-metal application
 *
 * @date Created on: 05/10/2010
 *
 * @author Tennessee Carmel-Veilleux (tennessee.carmelveilleux -at- gmail.com)
 *
 * @version 1.0 $Rev$
 *
 * Exception table and startup code for MPC8641 bare-metal application
 *
 * Startup Steps:
 *   Step 1- Disable interrupts and reset decrementer
 *   Step 2- Zero-out BSS section
 *   Step 3- Copy U-Boot argc and argv data
 *   Step 4- Set up a consistent stack frame with SP in GPR1
 *   Step 5- Set-up EABI registers GPR2 and GPR13 to point to small data areas
 *   Step 6- Set-up the interrupts subsystem by calling SetupIrqs in irqs.c
 *   Step 7- Setup call to main()
 *   Step 8- Branch to main()
 *
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

#include "ppc_reg.h"
#include "ppc_asm.h"
#include "ppc_asm_handlers.h"

.section .irqtab, "ax"
/* PowerPC Exception table */
.globl _ExceptionTable
.balign 4
_ExceptionTable:

/* Signature */
.ascii "Bare Metal MPC8641 Exception Table (first letter of 'Bare' at address " ## #CONFIG_START_ADDRESS ## ")"

/* Move over header */
. = _ExceptionTable + 0x100
    /* All processors arrive here. For cpus other than 0,
       we must make sure that if we arrived from a high-boot
       vector (0xfffXXXXX), we jump to low memory to prevent
       running-off the boot translation page. The trampoline
       also prevents being in a memory space without translation
       when BATs are setup and translation is enabled in early
       setup. */
.globl _reset_vector
_reset_vector:
    lis     r6,_start@h
    ori     r6,r6,_start@l
    /* Trampoline branch */
    mtctr   r6
    bctr
    sync

/* Machine check */
    STD_EXCEPTION(0x200, MachineCheck, DoException)

/* Data Storage exception. */
    STD_EXCEPTION(0x300, DataStorage, DoException)

/* Instruction Storage exception. */
    STD_EXCEPTION(0x400, InstStorage, DoException)

/* External Interrupt exception. */
    STD_PIC_IRQ(0x500, ExtInterrupt, DoIrq)

/* Alignment exception. */
    . = _ExceptionTable + 0x600
Alignment:
    EXCEPTION_PROLOG(SRR0, SRR1)
    /* On top of saving the minimum context, also save
       DAR, and DSISR in the frame. r4 and r5 are also
       the 2nd and 3rd parameters of functions, so the
       alignment handler will already have DAR and DSISR
       as its 2nd and 3rd arguments, respectively. */
    mfspr   r4,DAR
    stw     r4,_DAR(r21)
    mfspr   r5,DSISR
    stw     r5,_DSISR(r21)
    li      r6,6
    addi    r3,r1,STACK_FRAME_OVERHEAD
    EXC_XFER_TEMPLATE(Alignment, DoAlignment, int_return, KERNEL_MSR, COPY_EE)

/* Program check exception */
    . = _ExceptionTable + 0x700
ProgramCheck:
    EXCEPTION_PROLOG(SRR0, SRR1)
    addi    r3,r1,STACK_FRAME_OVERHEAD
    li      r6,7
    EXC_XFER_TEMPLATE(ProgramCheck, DoProgramCheck, int_return,
        KERNEL_MSR, COPY_EE)

    STD_EXCEPTION(0x800, FPUnavailable, DoException)
    STD_EXCEPTION(0x900, Decrementer, DoDecrementer)
    STD_EXCEPTION(0xa00, Trap_0a, DoException)
    STD_EXCEPTION(0xb00, Trap_0b, DoException)
    STD_EXCEPTION(0xc00, SystemCall, DoException)
    STD_EXCEPTION(0xd00, SingleStep, DoException)
    STD_EXCEPTION(0xe00, Trap_0e, DoException)
    STD_EXCEPTION(0xf00, Trap_0f, DoException)
    STD_EXCEPTION(0x1000, SoftEmu, DoException)
    STD_EXCEPTION(0x1100, InstructionTLBMiss, DoException)
    STD_EXCEPTION(0x1200, DataTLBMiss, DoException)
    STD_EXCEPTION(0x1300, InstructionTLBError, DoException)
    STD_EXCEPTION(0x1400, DataTLBError, DoException)
    STD_EXCEPTION(0x1500, Reserved5, DoException)
    STD_EXCEPTION(0x1600, Reserved6, DoException)
    STD_EXCEPTION(0x1700, Reserved7, DoException)
    STD_EXCEPTION(0x1800, Reserved8, DoException)
    STD_EXCEPTION(0x1900, Reserved9, DoException)
    STD_EXCEPTION(0x1a00, ReservedA, DoException)
    STD_EXCEPTION(0x1b00, ReservedB, DoException)
    STD_EXCEPTION(0x1c00, DataBreakpoint, DoException)
    STD_EXCEPTION(0x1d00, InstructionBreakpoint, DoException)
    STD_EXCEPTION(0x1e00, PeripheralBreakpoint, DoException)
    STD_EXCEPTION(0x1f00, DevPortBreakpoint, DoException)

.text

/***************************************************/
/*********** EXCEPTION HELPER CODE *****************/
/***************************************************/

/*
 * This code finishes saving the registers to the exception frame
 * and jumps to the appropriate handler for the exception.
 * Register r21 is pointer into trap frame, r1 has new stack pointer,
 * r6 must contain an adapted "irq number" specific to the handler type
 * (from the transfer template).
 */
transfer_to_handler:
    mflr    r9
    /* Save xSRR0 to frame */
    stw     r22,_NIP(r21)
    /* Disable power management in xSRR1 and save xSRR1 to frame */
    lis     r22,MSR_POW@h
    andc    r23,r23,r22
    stw     r23,_MSR(r21)
    /* Save r7 through r31 in the frame */
    SAVE_GPR(7, r21)
    SAVE_4GPRS(8, r21)
    SAVE_8GPRS(12, r21)
    SAVE_8GPRS(24, r21)
    /* Store exception-specific irq number */
    stw     r6,_IRQNR(r21)
    /* Clear-out the system-call result and error status*/
    li      r22,0
    stw     r22,RESULT(r21)
    stw     r22,_ERROR(r21)
    /* Use SPRG2 to hold system call return value */
    mtspr   SPRG2,r22
    /* Get virtual address of handler from EXC_XFER_TEMPLATE constants pool */
    lwz     r24,0(r9) /* r9 is LR (from earlier) */
    /* Get exception prologue address from EXC_XFER_TEMPLATE constants pool */
    lwz     r23,4(r9)
    /* Clear MSR[RI], indicating that context could not
     * be retrieved by a reset or machine check because we are about
     * to overwrite SRR0 and SRR1. See MPCFPE32B sec 6.4.
     */
    mfmsr   r22
    andi.   r0,r22,MSR_RI
    mtmsr   r0
    /* Prepare SRR0 and SRR1 with handler address and kernel MSR for RFI context synchronization */
    mtspr   SRR0,r24
    mtspr   SRR1,r20
    /* Set return address to exception prologue */
    mtlr    r23
    SYNC
    /* jump to handler, enable MMU, synchronize context */
    rfi

/*
 * Returns from a PIC IRQ, acknowledging the end of the
 * IRQ handling in the epilogue.
 */
irq_return:
    /* r1 is assumed to be back at exception frame (unstacked) */
    /* Disable interrupts because context restore might affect nesting */
    mfmsr   r28
    li      r4,0
    ori     r4,r4,MSR_EE
    andc    r28,r28,r4
    SYNC            /* FIXME: "Some chip revs need this..." (really ? Which, why ?) */
    mtmsr   r28
    SYNC
    EXCEPTION_EPILOGUE(EOI_CODE)

/*
 * Returns from an exception. Simply restores the context.
 */
int_return:
    /* r1 is assumed to be back at exception frame (unstacked) */
    /* Disable interrupts because context restore might affect nesting */
    mfmsr   r28
    li      r4,0
    ori     r4,r4,MSR_EE
    andc    r28,r28,r4
    SYNC            /* FIXME: "Some chip revs need this..." (really ? Which, why ?) */
    mtmsr   r28
    SYNC

    EXCEPTION_EPILOGUE(NO_EOI_CODE)

/***************************************************/
/***************** STARTUP CODE ********************/
/***************************************************/

.global _start
_start:
    /*----- Step 1- Disable interrupts and reset decrementer */
    /* Disable interrupts by clearing MSR[EE] */
    mfmsr   r6
    rlwinm  r6,r6,0,16,16
    mtmsr   r6

    /* Reset decrementer to 0xFFFFFFFF */
    orc     r6,r6,r6
    mtdec   r6

    /*----- Step 2- Zero-out BSS section */
clear_bss:
    addis   r5,0,_sbss@h
    ori     r5,r5,_sbss@l
    addis   r6,0,_ebss@h
    ori     r6,r6,_ebss@l

    /* Skip clearing if no bss present */
    cmplw   cr0, r5, r6
    beq     2f

    /* Clear loop */
    li      r0, 0
1:
    stw     r0, 0(r5)
    addi    r5, r5, 4
    cmplw   cr0, r5, r6
    bne     1b
2:
    sync

    /*----- Step 3- Copy U-Boot argc and argv data */
save_uboot_state:
    addis   r5,0,UBOOT_ARGC@h
    ori     r5,r5,UBOOT_ARGC@l
    stw     r3,0(r5)

    addis   r5,0,UBOOT_ARGV@h
    ori     r5,r5,UBOOT_ARGV@l
    stw     r4,0(r5)

    /*----- Step 4- Set up a consistent stack frame with SP in GPR1 */
setup_stack_frame:
    /* Set up stack pointer for the user application */
    addis   r1,0,(_stack_top)@h
    ori     r1,r1,(_stack_top)@l

    lis     r0,0
    /* Make sure the backchain word is null */
    stwu    r0,-8(r1)
    /* Clear-out LR save word */
    stw     r0,4(r1)

    /*----- Step 5- Set-up EABI registers GPR2 and GPR13 to point to small data areas */
setup_eabi:
    addis   r13,0,_SDA_BASE_@h
    ori     r13,r13,_SDA_BASE_@l
    addis   r2,0,_SDA2_BASE_@h
    ori     r2,r2,_SDA2_BASE_@l

    /*----- Step 6- Set-up the interrupts subsystem by calling SetupIrqs in irqs.c */
init_before_main:
    bl      SetupIrqs

    /*----- Step 7- Setup call to main() ----- */
setup_call_to_main:
    /* Place the entrypoint address in SRR0. */
    addis   r5,0,main@h
    ori     r5,r5,main@l
    mtspr   SRR0,r5

    /* Put the MSR value for the application into SRR1. */
    addis   r5,0,KERNEL_MSR@h
    ori     r5,r5,KERNEL_MSR@l
    mtspr   SRR1, r5

    /* Save the return address for returning after main() in the link register. */
save_return_address:
    addis   r5,0,_halt_system@h
    ori     r5,r5,_halt_system@l
    mtlr    r5

/*----- Step 8- Branch to main() */
branch_to_main:
    /* Restore parameters from U-Boot (argc and argv) */
    addis   r5,0,UBOOT_ARGC@h
    ori     r5,r5,UBOOT_ARGC@l
    lwz     r3,0(r5)

    addis   r5,0,UBOOT_ARGV@h
    ori     r5,r5,UBOOT_ARGV@l
    lwz     r4,0(r5)

    /* Use a context-synchronizing RFI to set MSR and PC to branch into main() */
    sync
    rfi

/*************************************vvvvv THIS IS WHERE main() RETURNS vvvvv*/
.global _halt_system
_halt_system:
    /* Save exit code in a global variable for easy symbolic display */
    addis   r4,0,_MainExitCode@h
    ori     r4,r4,_MainExitCode@l
    stw     r3,0(r4)

    /* Add a magic breakpoint when system is halted */
    simics_magic_breakpoint 2
1:
    b 1b    /* Endless loop */

/*---------------------------------------------------------------------
 * Define space for data items needed by this code
 *---------------------------------------------------------------------
 */
.section ".bss"

/* Storage for argc and argv provided by U-Boot */
.balign 4
UBOOT_ARGC:
.long 0
UBOOT_ARGV:
.long 0

.global _MainExitCode
/* G is global variable, 1 is int, so G1 is a global int type descriptor.
 * 32 is N_GSYM, meaning this stabs is a global symbol.
 */
.stabs "int:t1=r1;-2147483648;2147483647;",128,0,0,0
.stabs "_MainExitCode:G1",32,0,0,0
_MainExitCode:
.long 0


/* Stack space for bare-metal application */
.balign 8
_stack:
.space (CONFIG_STACK_SIZE * 1024)
_stack_top:
