/**
 * @file src/main.c
 *
 * @brief MPC8641 BMAT (Bare-Metal Application Template) sample program
 *
 * @date Created on: 07/10/2010
 *
 * @author Tennessee Carmel-Veilleux (tennessee.carmelveilleux -at- gmail.com)
 *
 * @version 1.0 $Rev$
 *
 * BMAT sample. This program demonstrates the use of the BMAT to handle
 * interrupts and exceptions on the MPC8641.
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

#include "irqs.h"
#include "immap_86xx.h"
#include "uboot.h"
#include "stdc.h"

/** Simple separator */
#define _________ kprintf("----------\n")

/*****************************************************************************
 * Our implementation of kputchar() for U-Boot console printing with kprintf()
 *****************************************************************************/

/**
 * Register r29 is reserved in U-Boot and BMAT. It always
 * contains a pointer to U-Boot's global board data structure.
 */
register UBOOT_global_data_t *UBOOT_global_data asm("r29");
static void (*LOCAL_UBOOT_putc)(const char) = 0;

void init_output(void) {
    /* U-Boot already configured our console. We only need to assign the
     * function pointer from the call table
     */
    LOCAL_UBOOT_putc = ((*UBOOT_global_data->jt)[UBOOT_EXPORT_putc]);
}

void kputchar(int c) {
    /* Use U-Boot's putc() */
    (*LOCAL_UBOOT_putc)((const char)(c & 0xff));
}


/*****************************************************************************
 * IRQ handling test with Messaging Interrupt 0 and 1
 *****************************************************************************/

/**
 * IRQ handler registered for Messaging Interrupt 0.
 *
 * Displays a message and triggers messaging interrupt 1.
 *
 * @param p_ctxt - pointer to saved interrupt context
 * @param p_irqData - pointer to IRQ-specific data (value is always 0xAA55A55A in this test)
 */
static void messaging0_irq_handler(irqCtxt_t *p_ctxt, void *p_irqData)
{
    /* Read message value, which also clears the IRQ event */
    uint32_t value = immr->im_pic.msgr0;

    /* Print informative message */
    kprintf("[Forced MSG0] Value=0x%08x, Data=0x%08x\n", value, (uint32_t)p_irqData);

    /* Force unhandled interrupt by triggering Messaging Interrupt 1,
     * which is enabled, but does not have a handler set.
     */
    immr->im_pic.msgr1 = 0xBEEFDEAD;
    asm __volatile__ ("" : : : "memory");
}

/**
 * Setup the IRQ processing test
 */
static void setup_irq_test(void)
{
    /* Enable messaging registers 0 and 1 */
    immr->im_pic.mer = 0x00000003;

    /* Set IRQ handler and data value for messaging interrupt 0 */
    SetIrqHandler(HWIRQ_MESSAGING0, messaging0_irq_handler, (void *)0xAA55A55A);

    /* Enable and set priority 10 for messaging interrupt 0 */
    EnableIrq(HWIRQ_MESSAGING0);
    SetPriorityIrq(HWIRQ_MESSAGING0, 10);

    /* Set the destination to be CPU0 for messaging interrupt 0 */
    *g_p_PIC_irq2idr[HWIRQ_MESSAGING0] = (1 << 0);

    /* Enable and set priority 11 (higher than messaging 0) for messaging interrupt 1 */
    /* --------- NOTE: We did not set a handler ! The default handler will be called ! */
    EnableIrq(HWIRQ_MESSAGING1);
    SetPriorityIrq(HWIRQ_MESSAGING1, 11);

    /* Set the destination to be CPU0 for messaging interrupt 1 */
    *g_p_PIC_irq2idr[HWIRQ_MESSAGING1] = (1 << 0);

    /* Enable global interrupts */
    GlobalIrqEnable();
}

/**
 * System call exception handler.
 *
 * @param p_ctxt - pointer to saved interrupt context
 */
static void DoSyscall(irqCtxt_t *p_ctxt)
{
    kprintf("Received a system call !\n");
}

/**
 * Default IRQ handler called when no handler is set. In this
 * implementation, we mask the source after the first time we get
 * an unhandled interrupt, to prevent an infinite loop because
 * the interrupt source flag is never cleared.
 *
 * @param p_ctxt - pointer to saved interrupt context
 * @param p_data - pointer to IRQ-specific data (always NULL in this case)
 */
void DefaultIrqHandler(irqCtxt_t *p_ctxt, void *p_data)
{
    kprintf("Unhandled IRQ source %d (%s) ! Disabling...\n", p_ctxt->irqNr, g_p_PIC_irq_names[p_ctxt->irqNr]);
    DisableIrq(p_ctxt->irqNr);
}

/**
 * Alignment exception handler.
 *
 * @param p_ctxt - pointer to saved interrupt context
 * @param dar - value of DAR on exception entry
 * @param dsisr - value of DSISR on exception entry
 */
void DoAlignment(irqCtxt_t *p_ctxt, uint32_t dar, uint32_t dsisr)
{
    /* Could do something here */
}

/**
 * Decrementer exception handler.
 *
 * @param p_ctxt - pointer to saved interrupt context
 */
void DoDecrementer(irqCtxt_t *p_ctxt)
{
    /* Could do something here */
}

/**
 * Handle the program check exception.
 *
 * In this example, an illegal instruction prints a
 * context dump while a trap exception displays a message.
 *
 * @param p_ctxt - pointer to saved interrupt context
 */
void DoProgramCheck(irqCtxt_t *p_ctxt)
{
    /* ========== IMPORTANT ========
     * Adjust return address since SRR0 value is the EA of the
     * exception-causing instruction. Without this, the exception
     * would always be retriggered on return !
     */
    p_ctxt->nip += 4;

    /* Figure-out which kind of event this was from SRR1 bits [11:14]
     * (see MPCFPE32B sec 6.5.7) */
    uint32_t event_mask = (p_ctxt->msr & 0x001e0000) >> 17;
    if ((1 << 3) == event_mask)
    {
        /* IEEE Floating point enabled exception */
        /* Could do something here */
    }
    else if ((1 << 2) == event_mask)
    {
        /* Illegal instruction exception */
        /* Print a message and dump register states */
        kprintf("Illegal instruction (0x%08x) at PC=0x%08x!\n", *((uint32_t *)(p_ctxt->nip - 4)), (p_ctxt->nip - 4));
        kprintf("CPU state:\n");

        kprintf(" r0: 0x%08x  r1: 0x%08x  r2: 0x%08x  r3: 0x%08x\n", p_ctxt->gpr[0], p_ctxt->gpr[1], p_ctxt->gpr[2], p_ctxt->gpr[3]);
        kprintf(" r4: 0x%08x  r5: 0x%08x  r6: 0x%08x  r7: 0x%08x\n", p_ctxt->gpr[4], p_ctxt->gpr[5], p_ctxt->gpr[6], p_ctxt->gpr[7]);
        kprintf(" r8: 0x%08x  r9: 0x%08x r10: 0x%08x r11: 0x%08x\n", p_ctxt->gpr[8], p_ctxt->gpr[9], p_ctxt->gpr[10], p_ctxt->gpr[11]);
        kprintf("r12: 0x%08x r13: 0x%08x r14: 0x%08x r15: 0x%08x\n", p_ctxt->gpr[12], p_ctxt->gpr[13], p_ctxt->gpr[14], p_ctxt->gpr[15]);
        kprintf("r16: 0x%08x r17: 0x%08x r18: 0x%08x r19: 0x%08x\n", p_ctxt->gpr[16], p_ctxt->gpr[17], p_ctxt->gpr[18], p_ctxt->gpr[19]);
        kprintf("r20: 0x%08x r21: 0x%08x r22: 0x%08x r23: 0x%08x\n", p_ctxt->gpr[20], p_ctxt->gpr[21], p_ctxt->gpr[22], p_ctxt->gpr[23]);
        kprintf("r24: 0x%08x r25: 0x%08x r26: 0x%08x r27: 0x%08x\n", p_ctxt->gpr[24], p_ctxt->gpr[25], p_ctxt->gpr[26], p_ctxt->gpr[27]);
        kprintf("r28: 0x%08x r29: 0x%08x r30: 0x%08x r31: 0x%08x\n", p_ctxt->gpr[28], p_ctxt->gpr[29], p_ctxt->gpr[30], p_ctxt->gpr[31]);
        kprintf("NIP: 0x%08x MSR: 0x%08x irqNr: %d\n", p_ctxt->nip, p_ctxt->msr, p_ctxt->irqNr);
        kprintf("\n");
    }
    else if ((1 << 1) == event_mask)
    {
        /* Priviledged instruction exception */
        /* Could do something here */
    }
    else if ((1 << 0) == event_mask)
    {
        /* Trap Exception */
        kprintf("Trap !\n");
    }
    else
    {
        /* Unknown: not supposed to happen ! */
        /* Could do something here */
    }
}

/**
 * Spurious IRQ handler called when a PIC spurious IRQ occurs.
 *
 * @param p_ctxt - pointer to saved interrupt context
 * @param p_data - pointer to IRQ-specific data (always NULL in this case)
 */
void SpuriousIrqHandler(irqCtxt_t *p_ctxt, void *p_data)
{
    kprintf("Spurious interrupt ! Source unknown...\n");
}

/**
 * Default exception handler called when no handler is set.
 *
 * @param p_ctxt - pointer to saved exception context
 */
void UnexpectedExceptionHandler(irqCtxt_t *p_ctxt)
{
    kprintf("Unexpected Exception (offset = 0x%02x00)\n", p_ctxt->irqNr);
}

/**
 * Application entry point. This is called from start.S.
 *
 * ****** WARNING: DO NOT use the values of argc and argv if
 * *************** you did not start this application with the
 * *************** "go" command of U-Boot !!!
 *
 * @param argc - Argument count from U-Boot
 * @param argv - Argument string table from U-Boot
 * @return an exit code value
 */
int main(int argc, char **argv)
{
    /* Setup console for further use (optional) */
    init_output();

    /* Setup the IRQ test */
    setup_irq_test();

    kprintf("Hello World !\n");
    _________;

    /* Trigger the IRQ test */
    immr->im_pic.msgr0 = 0xDEADBEEF;
    asm __volatile__ ("" : : : "memory");
    _________;

    /* Trigger a trap */
    asm volatile("trap");
    _________;

    /* Trigger a system call prior to setting a handler for it.
     * The UnexpectedExceptionHandler() will be called. */
    asm volatile("sc");
    _________;

    /* Set the exception handler. The next syscall will be handled
     * correctly. */
    SetExceptionHandler(0x0c, DoSyscall);
    asm volatile("sc");
    _________;

    /* Trigger an illegal instruction exception */
    asm volatile(".long 0x00BADBAD");
    _________;

    kprintf("Done !\n");

    /* Return to _halt_system in start.S. The exit
     * code will be available in the _MainExitCode
     * global variable.
     */
    return 6502;
}
