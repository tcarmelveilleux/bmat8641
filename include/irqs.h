/**
 * @file irqs.h
 *
 * @brief PIC IRQs and PowerPC Exception Table definitions for MPC8641 bare metal application
 *
 * @date Created on: 05/10/2010
 *
 * @author Tennessee Carmel-Veilleux (tennessee.carmelveilleux -at- gmail.com)
 *
 * @version 1.0 $Rev$
 *
 * PIC IRQs and PowerPC Exception Table definitions for MPC8641 bare metal application
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

#ifndef _IRQS_H_
#define _IRQS_H_

/** Number of hardware exceptions */
#define EXCEPTION_NR 32

/** Vector number to use for spurious IRQ */
#define IRQ_SPURIOUS_VECTOR 127

#include "ppc_reg.h"

#ifndef __ASSEMBLY__

typedef struct irqCtxt {
    uint32_t gpr[32]; /* General purpose registers */
    uint32_t nip; /* Return address (from SRR0) */
    uint32_t msr; /* Saved MSR (from SRR1) */
    /* Cause of exception/interrupt:
     * - For exceptions: number of handler, ie: 6 (instead of 0x0600) for alignment exception)
     * - For external interrupts coming for PIC: number of the interrupt (0 through PIC->FRR.NIRQ)
     *   (see core/ppc/board/start.S for table related to each board).
     */
    uint32_t irqNr;
    /* Saved SPRs */
    uint32_t ctr;
    uint32_t lr;
    uint32_t xer;
    uint32_t ccr;
    /* Fault registers */
    uint32_t dar;
    uint32_t dsisr;
    uint32_t result; /* Result of a system call (FIXME: Needed ?) */
    uint32_t error; /* Error condition to be reported if necessary */
} irqCtxt_t;

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef void (*irqHandler_t)(irqCtxt_t *, void *);
typedef void (*exceptionHandler_t)(irqCtxt_t *);

struct irqTabEntry {
    irqHandler_t handler;
    void *data;
};

extern struct irqTabEntry irqHandlerTab[128];
extern exceptionHandler_t exceptionHandlerTab[EXCEPTION_NR];

extern uint32_t *g_p_PIC_msir[CONFIG_PIC_NUM_MSIR];
extern uint32_t *g_p_PIC_irq2vpr[CONFIG_NO_HWIRQS];
extern uint32_t *g_p_PIC_irq2idr[CONFIG_NO_HWIRQS];
extern uint32_t g_PIC_irq_flags[CONFIG_NO_HWIRQS];
extern char *g_p_PIC_irq_names[CONFIG_NO_HWIRQS];

extern void DefaultIrqHandler(irqCtxt_t *p_ctxt, void *p_data);
extern void SpuriousIrqHandler(irqCtxt_t *p_ctxt, void *p_data);
extern void DoAlignment(irqCtxt_t *p_ctxt, uint32_t dar, uint32_t dsisr);
extern void DoDecrementer(irqCtxt_t *p_ctxt);
extern void UnexpectedExceptionHandler(irqCtxt_t *p_ctxt);
extern void DoProgramCheck(irqCtxt_t *p_ctxt);
extern void SetupIrqs(void);
extern irqHandler_t SetIrqHandler(int32_t irqNr, irqHandler_t irqHandler, void *p_data);
extern exceptionHandler_t SetExceptionHandler(int32_t exceptionNr, exceptionHandler_t exceptionHandler);
extern void DisableIrq(uint32_t irqNr);
extern void EnableIrq(uint32_t irqNr);
extern void SetPriorityIrq(uint32_t irqNr, uint32_t priority);

/**
 * Disable External Interrupts by setting MSR[EE] to 0
 */
static inline void GlobalIrqDisable(void)
{
    uint32_t msr = mfmsr();
    mtmsr(msr & ~MSR_EE);
}

/**
 * Enable External Interrupts by setting MSR[EE] to 1
 */
static inline void GlobalIrqEnable(void)
{
    uint32_t msr = mfmsr();
    mtmsr(msr | MSR_EE);
}

/**
 * Disable Interrupts, returning state of MSR[EE] before the disabling
 *
 * @return value containing at least a valid MSR[EE] bit in the right position
 */
static inline uint32_t __SaveFlagsIrqDis(void) {
    uint32_t msr = mfmsr();

    mtmsr(msr & ~MSR_EE);

    return msr;
}

/**
 * Saves interrupt enable flag before disabling interrupts.
 * Equivalent to "flags = __SaveFlagsIrqDis()".
 */
#define GlobalIrqDisableSaveFlags(flags) ((flags)=__SaveFlagsIrqDis())

/**
 * Restores MSR[EE] from a previously saved MSR
 *
 * @param flags - value containing MSR[EE] in its proper bit place
 */
static inline void GlobalIrqRestoreFlags(uint32_t flags)
{
    uint32_t msr = mfmsr();
    __asm__ __volatile__("rlwimi %0, %1, 0, " stringify(MSR_EE_BIT) "," stringify(MSR_EE_BIT) "\n\t" \
                         "mtmsr %0" : "+r" (msr) : "r" (flags) : "memory");
}

/** Sets "flags" to interrupt enable state */
#define GlobalIrqSaveFlags(flags) ((flags) = (mfmsr() & MSR_EE))

/** @return non-zero if interrupts are enabled */
static inline uint32_t IsGlobalIrqEnabled(void)
{
    return (0 != (mfmsr() & MSR_EE));
}

#endif /* !defined(__ASSEMBLY__) */

/** Whether the interrupt destination register has a sense flag */
#define PIC_HAS_SENSE_FLAG (1 << 0)

/** Whether the interrupt destination register has a polarity flag */
#define PIC_HAS_POLARITY_FLAG (1 << 1)

/** Whether the interrupt destination register has multicast capabilities */
#define PIC_IS_MULTICAST_FLAG (1 << 2)

/** Vector value for spurious interrupts (not currently initialized) */
#define PIC_VECTOR_SPURIOUS (127)

/* ---------- PIC_FRR: PIC Feature reporting register  ---------- */
#define PIC_FRR_OFFSET          0x41000
                                    /* Bits 0-4: Reserved, should be cleared.  */
#define PIC_FRR_NIRQ_LAST_BIT   16  /* Bits 5-15 (31-15 = 16): Number of interrupts */
                                    /* Bits 16-18: Reserved, should be cleared  */
#define PIC_FRR_NCPU_LAST_BIT   8   /* Bits 19-23 (31-23 = 8): Number of CPUs */
#define PIC_FRR_VID_LAST_BIT    0   /* Bits 24-31 (31-31 = 0): Version ID */

#define PIC_FRR_NIRQ_MASK   0x07FF0000  /* Bits 5-15: Number of interrupts */
#define PIC_FRR_NCPU_MASK   0x00001F00  /* Bits 19-23: Number of CPUs */
#define PIC_FRR_VID_MASK    0x000000FF  /* Bits 24-31: Version ID */

/* ---------- PIC_WHOAMI: PIC Who am I register  ---------- */
#define PIC_WHOAMI_OFFSET       0x40090

                                    /* Bits 0-26: Reserved, should be cleared. */
#define PIC_WHOAMI_ID_LAST_BIT  0   /* Bits 27-31 (31-31 = 0): Returns the ID of the processor core reading this register. */


#define PIC_WHOAMI_ID_MASK  0x0000001F  /* Bits 27-31: Returns the ID of the processor core reading this register. */

/* ---------- PIC_BRR1: Block Revision Register 1  ---------- */
#define PIC_BRR1_IPID_LAST_BIT  16  /* Bits 0-15 (31-15 = 16): IP block ID. */
#define PIC_BRR1_IPMJ_LAST_BIT  8   /* Bits 16-23 (31-23 = 8): The major revision of the IP block. */
#define PIC_BRR1_IPMN_LAST_BIT  0   /* Bits 24-31 (31-31 = 0): The minor revision of the IP block. */

#define PIC_BRR1_IPID_MASK  0xFFFF0000  /* Bits 0-15: IP block ID. */
#define PIC_BRR1_IPMJ_MASK  0x0000FF00  /* Bits 16-23: The major revision of the IP block. */
#define PIC_BRR1_IPMN_MASK  0x000000FF  /* Bits 24-31: The minor revision of the IP block. */

/* ---------- PIC_BRR2: Block Revision Register 2  ---------- */
                                    /* Bits 0-7: Reserved, shod be cleared.  */
#define PIC_BRR2_IPINTO_LAST_BIT    16  /* Bits 8-15 (31-15 = 16): IP block integration options */
                                    /* Bits 16-23: Reserved, should be cleared.  */
#define PIC_BRR2_IPCFGO_LAST_BIT    0   /* Bits 24-31 (31-31 = 0): IP block configuration options */

#define PIC_BRR2_IPINTO_MASK    0x00FF0000  /* Bits 8-15: IP block integration options */
#define PIC_BRR2_IPCFGO_MASK    0x000000FF  /* Bits 24-31: IP block configuration options */

/* ---------- PIC_GCR: Global Configuration Register  ---------- */
#define PIC_GCR_RST_BIT 31  /* Bit 0 (31-0 = 31): Reset. Setting RST forces the PIC to be reset. Cleared automatically when the reset sequence is complete */
                        /* Bit 1: Reserved, should be cleared.  */
#define PIC_GCR_M_BIT   29  /* Bit 2 (31-2 = 29): Mode. PIC operating mode. (0 Pass-through mode, 1 Mixed mode) */
                        /* Bits 3-31: Reserved, should be cleared. */

#define PIC_GCR_RST 0x80000000
#define PIC_GCR_M   0x20000000

/* ---------- PIC_VIR: Vendor Identification Register  ---------- */
                                    /* Bits 0-7: Reserved, should be cleared.  */
#define PIC_VIR_STEP_LAST_BIT   16  /* Bits 8-15 (31-15 = 16): Stepping. Indicates the silicon revision for this device. Has no meaning if VENDOR ID value is zero.  */
#define PIC_VIR_DEVICE_LAST_BIT 8   /* Bits 16-23 (31-23 = 8): ID Device identification. Vendor-specified identifier for this device. Has no meaning if VENDOR ID is zero. */
#define PIC_VIR_VENDOR_LAST_BIT 0   /* Bits 24-31 (31-31 = 0): ID Vendor identification. Specifies the manufacturer of this part. A value of zero implies a generic OpenPIC-compliant device.  */

#define PIC_VIR_STEP_MASK   0x00FF0000  /* Bits 8-15: Stepping. Indicates the silicon revision for this device. Has no meaning if VENDOR ID value is zero.  */
#define PIC_VIR_DEVICE_MASK 0x0000FF00  /* Bits 16-23: ID Device identification. Vendor-specified identifier for this device. Has no meaning if VENDOR ID is zero. */
#define PIC_VIR_VENDOR_MASK 0x000000FF  /* Bits 24-31: ID Vendor identification. Specifies the manufacturer of this part. A value of zero implies a generic OpenPIC-compliant device.  */

/* ---------- PIC_IPIVPR[0-3]: Interprocessor Interrupt Vector/Priority Registers  ---------- */
#define PIC_IPIVPR_MSK_BIT  31          /* Bit 0 (31-0 = 31): Mask. Mask interrupts from this source. MSK affects only interrupts routed to int.  */
#define PIC_IPIVPR_A_BIT    30          /* Bit 1 (31-1 = 30): Activity. Indicates an interrupt has been requested or is in service.  */
                                    /* Bits 2-11: Reserved, should be cleared.  */
#define PIC_IPIVPR_PRIORITY_LAST_BIT  16  /* Bits 12-15 (31-15 = 16): Priority. Specifies the interrupt priority. The lowest priority is 0 and the highest priority is 15. */
#define PIC_IPIVPR_VECTOR_LAST_BIT  0   /* Bits 16-31 (31-31 = 0): Vector (Affects only interrupts routed to  int). Contains the value returned when IACK is read and this interrupt  */

#define PIC_IPIVPR_MSK              0x80000000
#define PIC_IPIVPR_A                0x40000000
#define PIC_IPIVPR_PRIORITY_MASK    0x000F0000  /* Bits 12-15: Priority. Specifies the interrupt priority. The lowest priority is 0 and the highest priority is 15. */
#define PIC_IPIVPR_VECTOR_MASK      0x0000FFFF  /* Bits 16-31: Vector (Affects only interrupts routed to  int). Contains the value returned when IACK is read and this interrupt  */

/* ---------- PIC_SVR: Spurious Vector Register  ---------- */
                                    /* Bits 0-15: Reserved, should be cleared.  */
#define PIC_SVR_VECTOR_LAST_BIT 0   /* Bits 16-31 (31-31 = 0): Spurious interrupt vector. Value returned when IACK is read during a spurious vector fetch. */

#define PIC_SVR_VECTOR_MASK 0x0000FFFF  /* Bits 16-31: Spurious interrupt vector. Value returned when IACK is read during a spurious vector fetch. */

/* ---------- PIC_TFRR[A-B]: Timer Frequency Reporting Register  ---------- */
#define PIC_TFRR_FREQ_LAST_BIT  0   /* Bits 0-31 (31-31 = 0): Timer frequency (in ticks/second (Hz)). */

#define PIC_TFRR_FREQ_MASK  0xFFFFFFFF  /* Bits 0-31: Timer frequency (in ticks/second (Hz)). */

/* ---------- PIC_GTCCR[A-B][0-3]: Global Timer Current Count Registers ---------- */
#define PIC_GTCCR_TOG_BIT           31  /* Bit 0 (31-0 = 31): Toggle. Toggles when the current count decrements to zero. Cleared when GTBCRxn[CI] goes from 1 to 0.  */
#define PIC_GTCCR_COUNT_LAST_BIT    0   /* Bits 1-31 (31-31 = 0): Current count. Decremented while GTBCRxn[CI] is zero */

#define PIC_GTCCR_TOG           0x80000000
#define PIC_GTCCR_COUNT_MASK    0x7FFFFFFF  /* Bits 1-31: Current count. Decremented while GTBCRxn[CI] is zero */

/* ---------- PIC_GTBCR[A-B][0-3]: Global Timer Base Count Registers ---------- */
#define PIC_GTBCR_CI_BIT        31  /* Bit 0 (31-0 = 31): Count inhibit. Always set following reset. */
#define PIC_GTBCR_BASE_LAST_BIT 0   /* Bits 1-31 (31-31 = 0): CNT Base count. When CI transitions from 1 to 0, this value is copied into the corresponding GTCCRxn and the toggle bit is cleared.  */

#define PIC_GTBCR_CI        0x80000000
#define PIC_GTBCR_BASE_MASK 0x7FFFFFFF  /* Bits 1-31: CNT Base count. When CI transitions from 1 to 0, this value is copied into the corresponding GTCCRxn and the toggle bit is cleared.  */

/* ---------- PIC_GTVPR[A-B][0-3]: Global Timer Vector/Priority Registers ---------- */
#define PIC_GTVPR_MSK_BIT   31  /* Bit 0 (31-0 = 31): Mask. Mask interrupts from this source. MSK affects only interrupts routed to int.  */
#define PIC_GTVPR_A_BIT     30  /* Bit 1 (31-1 = 30): Activity. Indicates an interrupt has been requested or is in service.  */
                                    /* Bits 2-11: Reserved, should be cleared.  */
#define PIC_GTVPR_PRIORITY_LAST_BIT 16  /* Bits 12-15 (31-15 = 16): Priority. Specifies the interrupt priority. */
#define PIC_GTVPR_VECTOR_LAST_BIT   0   /* Bits 16-31 (31-31 = 0): Vector. Contains the value returned when IACK is read */

#define PIC_GTVPR_MSK           0x80000000
#define PIC_GTVPR_A             0x40000000
#define PIC_GTVPR_PRIORITY_MASK 0x000F0000  /* Bits 12-15: Priority. Specifies the interrupt priority. */
#define PIC_GTVPR_VECTOR_MASK   0x0000FFFF  /* Bits 16-31: Vector. Contains the value returned when IACK is read */

/* ---------- PIC_TCR: Timer Control Registers  ---------- */
                                    /* Bits 0-4: Reserved, should be cleared. */
#define PIC_TCR_ROVR_LAST_BIT   24  /* Bits 5-7 (31-7 = 24): Roll-over control for cascaded timers only */
                                    /* Bits 8-14: Reserved, should be cleared.  */
#define PIC_TCR_RTM_BIT         16  /* Bit 15 (31-15 = 16): Real time mode. Specifies the clock source for the PIC timers. */
                                    /* Bits 16-21: Reserved, should be cleared.  */
#define PIC_TCR_CLKR_LAST_BIT   8   /* Bits 22-23 (31-23 = 8): Clock ratio. Specifies the ratio of the timer frequency to the MPX clock.  */
                                    /* Bits 24-28: Reserved, should be cleared. */
#define PIC_TCR_CASC_LAST_BIT   0   /* Bits 29-31 (31-31 = 0): Cascade timers. Specifies the output of particular global timers as input to others. */

#define PIC_TCR_ROVR_MASK   0x07000000  /* Bits 5-7: Roll-over control for cascaded timers only */
#define PIC_TCR_RTM         0x00010000
#define PIC_TCR_CLKR_MASK   0x00000300  /* Bits 22-23: Clock ratio. Specifies the ratio of the timer frequency to the MPX clock.  */
#define PIC_TCR_CASC_MASK   0x00000007  /* Bits 29-31: Cascade timers. Specifies the output of particular global timers as input to others. */

/* ---------- PIC_IVPR: Interrupt Vector/Priority Register ([E/I]VPRnn)  ---------- */
#define PIC_IVPR_OFFSET 0

#define PIC_IVPR_MSK_BIT    31  /* Bit 0 (31-0 = 31): Mask. Mask interrupts from this source. MSK affects only interrupts routed to int.  */
#define PIC_IVPR_A_BIT      30  /* Bit 1 (31-1 = 30): Activity. Indicates an interrupt has been requested or is in service. */
                                /* Bits 2-7: Reserved, should be cleared.  */
#define PIC_IVPR_P_BIT      23  /* Bit 8 (31-8 = 23): Polarity. Specifies the polarity for the interrupt.  */
#define PIC_IVPR_S_BIT      22  /* Bit 9 (31-9 = 22): Sense. (ONLY for external interrupts) Specifies the sense for external interrupts. */
                                /* Bits 10-11: Reserved, should be cleared.  */
#define PIC_IVPR_PRIORITY_LAST_BIT  16  /* Bits 12-15 (31-15 = 16): Priority. Specifies the interrupt priority. */
#define PIC_IVPR_VECTOR_LAST_BIT    0   /* Bits 16-31 (31-31 = 0): Vector. Contains the value returned when IACK is read */

#define PIC_IVPR_MSK            0x80000000
#define PIC_IVPR_A              0x40000000
#define PIC_IVPR_P              0x00800000
#define PIC_IVPR_S              0x00400000
#define PIC_IVPR_PRIORITY_MASK  0x000F0000  /* Bits 12-15: Priority. Specifies the interrupt priority. */
#define PIC_IVPR_VECTOR_MASK    0x0000FFFF  /* Bits 16-31: Vector. Contains the value returned when IACK is read */

/* PIC Hardware IRQ source names */
#define HWIRQ_INTERPROCESSOR0                   (0)
#define HWIRQ_INTERPROCESSOR1                   (1)
#define HWIRQ_INTERPROCESSOR2                   (2)
#define HWIRQ_INTERPROCESSOR3                   (3)
#define HWIRQ_GLOBAL_TIMER_A0                   (4)
#define HWIRQ_GLOBAL_TIMER_A1                   (5)
#define HWIRQ_GLOBAL_TIMER_A2                   (6)
#define HWIRQ_GLOBAL_TIMER_A3                   (7)
#define HWIRQ_GLOBAL_TIMER_B0                   (8)
#define HWIRQ_GLOBAL_TIMER_B1                   (9)
#define HWIRQ_GLOBAL_TIMER_B2                   (10)
#define HWIRQ_GLOBAL_TIMER_B3                   (11)
#define HWIRQ_EXTERNAL0                         (12)
#define HWIRQ_EXTERNAL1                         (13)
#define HWIRQ_EXTERNAL2                         (14)
#define HWIRQ_EXTERNAL3                         (15)
#define HWIRQ_EXTERNAL4                         (16)
#define HWIRQ_EXTERNAL5                         (17)
#define HWIRQ_EXTERNAL6                         (18)
#define HWIRQ_EXTERNAL7                         (19)
#define HWIRQ_EXTERNAL8                         (20)
#define HWIRQ_EXTERNAL9                         (21)
#define HWIRQ_EXTERNAL10                        (22)
#define HWIRQ_EXTERNAL11                        (23)
#define HWIRQ_INTERNAL_UNWIRED_24               (24)
#define HWIRQ_INTERNAL_MCM                      (25)
#define HWIRQ_INTERNAL_DDR_DRAM_CONTROLLERS     (26)
#define HWIRQ_INTERNAL_LBC_CONTROLLER           (27)
#define HWIRQ_INTERNAL_DMA_CHANNEL_1            (28)
#define HWIRQ_INTERNAL_DMA_CHANNEL_2            (29)
#define HWIRQ_INTERNAL_DMA_CHANNEL_3            (30)
#define HWIRQ_INTERNAL_DMA_CHANNEL_4            (31)
#define HWIRQ_INTERNAL_PCI_EXPRESS_PORT1        (32)
#define HWIRQ_INTERNAL_PCI_EXPRESS_PORT2        (33)
#define HWIRQ_INTERNAL_UNWIRED_34               (34)
#define HWIRQ_INTERNAL_UNWIRED_35               (35)
#define HWIRQ_INTERNAL_UART2                    (36)
#define HWIRQ_INTERNAL_ETSEC_1_TRANSMIT         (37)
#define HWIRQ_INTERNAL_ETSEC_1_RECEIVE          (38)
#define HWIRQ_INTERNAL_ETSEC_3_TRANSMIT         (39)
#define HWIRQ_INTERNAL_ETSEC_3_RECEIVE          (40)
#define HWIRQ_INTERNAL_ETSEC_3_ERROR            (41)
#define HWIRQ_INTERNAL_ETSEC_1_ERROR            (42)
#define HWIRQ_INTERNAL_ETSEC_2_TRANSMIT         (43)
#define HWIRQ_INTERNAL_ETSEC_2_RECEIVE          (44)
#define HWIRQ_INTERNAL_ETSEC_4_TRANSMIT         (45)
#define HWIRQ_INTERNAL_ETSEC_4_RECEIVE          (46)
#define HWIRQ_INTERNAL_ETSEC_4_ERROR            (47)
#define HWIRQ_INTERNAL_ETSEC_2_ERROR            (48)
#define HWIRQ_INTERNAL_UNWIRED_49               (49)
#define HWIRQ_INTERNAL_UART1                    (50)
#define HWIRQ_INTERNAL_I2C_CONTROLLERS          (51)
#define HWIRQ_INTERNAL_PERFORMANCE_MONITOR      (52)
#define HWIRQ_INTERNAL_UNWIRED_53               (53)
#define HWIRQ_INTERNAL_UNWIRED_54               (54)
#define HWIRQ_INTERNAL_UNWIRED_55               (55)
#define HWIRQ_INTERNAL_SRIO_ERROR_WRITE         (56)
#define HWIRQ_INTERNAL_SRIO_OUTBOUND_DOORBELL   (57)
#define HWIRQ_INTERNAL_SRIO_INBOUND_DOORBELL    (58)
#define HWIRQ_INTERNAL_UNWIRED_59               (59)
#define HWIRQ_INTERNAL_UNWIRED_60               (60)
#define HWIRQ_INTERNAL_SRIO_OUTBOUND_MESSAGE1   (61)
#define HWIRQ_INTERNAL_SRIO_INBOUND_MESSAGE1    (62)
#define HWIRQ_INTERNAL_SRIO_OUTBOUND_MESSAGE2   (63)
#define HWIRQ_INTERNAL_SRIO_INBOUND_MESSAGE2    (64)
#define HWIRQ_INTERNAL_UNWIRED_65               (65)
#define HWIRQ_INTERNAL_UNWIRED_66               (66)
#define HWIRQ_INTERNAL_UNWIRED_67               (67)
#define HWIRQ_INTERNAL_UNWIRED_68               (68)
#define HWIRQ_INTERNAL_UNWIRED_69               (69)
#define HWIRQ_INTERNAL_UNWIRED_70               (70)
#define HWIRQ_INTERNAL_UNWIRED_71               (71)
#define HWIRQ_MESSAGING0                        (72)
#define HWIRQ_MESSAGING1                        (73)
#define HWIRQ_MESSAGING2                        (74)
#define HWIRQ_MESSAGING3                        (75)
#define HWIRQ_SHARED_MESSAGE_SIGNALED0          (76)
#define HWIRQ_SHARED_MESSAGE_SIGNALED1          (77)
#define HWIRQ_SHARED_MESSAGE_SIGNALED2          (78)
#define HWIRQ_SHARED_MESSAGE_SIGNALED3          (79)
#define HWIRQ_SHARED_MESSAGE_SIGNALED4          (80)
#define HWIRQ_SHARED_MESSAGE_SIGNALED5          (81)
#define HWIRQ_SHARED_MESSAGE_SIGNALED6          (82)
#define HWIRQ_SHARED_MESSAGE_SIGNALED7          (83)

#endif /* !defined(_IRQS_H_) */
