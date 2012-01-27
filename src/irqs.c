/**
 * @file irqs.c
 *
 * @brief PIC and PowerPC exceptions support for MPC8641 bare metal application
 *
 * @date Created on: 05/10/2010
 *
 * @author Tennessee Carmel-Veilleux (tennessee.carmelveilleux -at- gmail.com)
 *
 * @version 1.0 $Rev$
 *
 * PIC and PowerPC exceptions support for MPC8641 bare metal application
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

#include "processor.h"
#include "irqs.h"
#include "immap_86xx.h"

static void PIC_init(void);
static void PIC_reset_interrupts(void);
static void PIC_reset_interrupts_local(void);

/** IRQ Handler table */
struct irqTabEntry irqHandlerTab[128];

/** Exception handler table */
exceptionHandler_t exceptionHandlerTab[EXCEPTION_NR];

/** MSIR registers table */
uint32_t *g_p_PIC_msir[CONFIG_PIC_NUM_MSIR] =
{
    [0] = (uint32_t *)&(immr->im_pic.msir0), /* MSIR0: 0x41600 - Shared message signaled interrupt register 0  */
    [1] = (uint32_t *)&(immr->im_pic.msir1), /* MSIR1: 0x41610 - Shared message signaled interrupt register 1  */
    [2] = (uint32_t *)&(immr->im_pic.msir2), /* MSIR2: 0x41620 - Shared message signaled interrupt register 2  */
    [3] = (uint32_t *)&(immr->im_pic.msir3), /* MSIR3: 0x41630 - Shared message signaled interrupt register 3  */
    [4] = (uint32_t *)&(immr->im_pic.msir4), /* MSIR4: 0x41640 - Shared message signaled interrupt register 4  */
    [5] = (uint32_t *)&(immr->im_pic.msir5), /* MSIR5: 0x41650 - Shared message signaled interrupt register 5  */
    [6] = (uint32_t *)&(immr->im_pic.msir6), /* MSIR6: 0x41660 - Shared message signaled interrupt register 6  */
    [7] = (uint32_t *)&(immr->im_pic.msir7), /* MSIR7: 0x41670 - Shared message signaled interrupt register 7  */
};

/** IRQ number to VPR register table */
uint32_t *g_p_PIC_irq2vpr[CONFIG_NO_HWIRQS] =
{
    [0] = (uint32_t *)&(immr->im_pic.ipivpr0), /* Source 0: 0x410a0 - IPI Vector/Priority Register 0  */
    [1] = (uint32_t *)&(immr->im_pic.ipivpr1), /* Source 1: 0x410b0 - IPI Vector/Priority Register 1  */
    [2] = (uint32_t *)&(immr->im_pic.ipivpr2), /* Source 2: 0x410c0 - IPI Vector/Priority Register 2  */
    [3] = (uint32_t *)&(immr->im_pic.ipivpr3), /* Source 3: 0x410d0 - IPI Vector/Priority Register 3  */
    [4] = (uint32_t *)&(immr->im_pic.gtvpra0), /* Source 4: 0x41120 - Global Timer Vector/Priority Register group A 0  */
    [5] = (uint32_t *)&(immr->im_pic.gtvpra1), /* Source 5: 0x41160 - Global Timer Vector/Priority Register group A 1  */
    [6] = (uint32_t *)&(immr->im_pic.gtvpra2), /* Source 6: 0x411a0 - Global Timer Vector/Priority Register group A 2  */
    [7] = (uint32_t *)&(immr->im_pic.gtvpra3), /* Source 7: 0x411e0 - Global Timer Vector/Priority Register group A 3  */
    [8] = (uint32_t *)&(immr->im_pic.gtvprb0), /* Source 8: 0x42120 - Global timer vector/priority register group B 0  */
    [9] = (uint32_t *)&(immr->im_pic.gtvprb1), /* Source 9: 0x42160 - Global timer vector/priority register group B 1  */
    [10] = (uint32_t *)&(immr->im_pic.gtvprb2), /* Source 10: 0x421A0 - Global timer vector/priority register group B 2  */
    [11] = (uint32_t *)&(immr->im_pic.gtvprb3), /* Source 11: 0x421E0 - Global timer vector/priority register group B 3  */
    [12] = (uint32_t *)&(immr->im_pic.eivpr0), /* Source 12: 0x50000 - External Interrupt Vector/Priority Register 0  */
    [13] = (uint32_t *)&(immr->im_pic.eivpr1), /* Source 13: 0x50020 - External Interrupt Vector/Priority Register 1  */
    [14] = (uint32_t *)&(immr->im_pic.eivpr2), /* Source 14: 0x50040 - External Interrupt Vector/Priority Register 2  */
    [15] = (uint32_t *)&(immr->im_pic.eivpr3), /* Source 15: 0x50060 - External Interrupt Vector/Priority Register 3  */
    [16] = (uint32_t *)&(immr->im_pic.eivpr4), /* Source 16: 0x50080 - External Interrupt Vector/Priority Register 4  */
    [17] = (uint32_t *)&(immr->im_pic.eivpr5), /* Source 17: 0x500a0 - External Interrupt Vector/Priority Register 5  */
    [18] = (uint32_t *)&(immr->im_pic.eivpr6), /* Source 18: 0x500c0 - External Interrupt Vector/Priority Register 6  */
    [19] = (uint32_t *)&(immr->im_pic.eivpr7), /* Source 19: 0x500e0 - External Interrupt Vector/Priority Register 7  */
    [20] = (uint32_t *)&(immr->im_pic.eivpr8), /* Source 20: 0x50100 - External Interrupt Vector/Priority Register 8  */
    [21] = (uint32_t *)&(immr->im_pic.eivpr9), /* Source 21: 0x50120 - External Interrupt Vector/Priority Register 9  */
    [22] = (uint32_t *)&(immr->im_pic.eivpr10), /* Source 22: 0x50140 - External Interrupt Vector/Priority Register 10  */
    [23] = (uint32_t *)&(immr->im_pic.eivpr11), /* Source 23: 0x50160 - External Interrupt Vector/Priority Register 11  */
    [24] = (uint32_t *)&(immr->im_pic.iivpr0), /* Source 24: 0x50200 - Internal Interrupt Vector/Priority Register 0  */
    [25] = (uint32_t *)&(immr->im_pic.iivpr1), /* Source 25: 0x50220 - Internal Interrupt Vector/Priority Register 1  */
    [26] = (uint32_t *)&(immr->im_pic.iivpr2), /* Source 26: 0x50240 - Internal Interrupt Vector/Priority Register 2  */
    [27] = (uint32_t *)&(immr->im_pic.iivpr3), /* Source 27: 0x50260 - Internal Interrupt Vector/Priority Register 3  */
    [28] = (uint32_t *)&(immr->im_pic.iivpr4), /* Source 28: 0x50280 - Internal Interrupt Vector/Priority Register 4  */
    [29] = (uint32_t *)&(immr->im_pic.iivpr5), /* Source 29: 0x502a0 - Internal Interrupt Vector/Priority Register 5  */
    [30] = (uint32_t *)&(immr->im_pic.iivpr6), /* Source 30: 0x502c0 - Internal Interrupt Vector/Priority Register 6  */
    [31] = (uint32_t *)&(immr->im_pic.iivpr7), /* Source 31: 0x502e0 - Internal Interrupt Vector/Priority Register 7  */
    [32] = (uint32_t *)&(immr->im_pic.iivpr8), /* Source 32: 0x50300 - Internal Interrupt Vector/Priority Register 8  */
    [33] = (uint32_t *)&(immr->im_pic.iivpr9), /* Source 33: 0x50320 - Internal Interrupt Vector/Priority Register 9  */
    [34] = (uint32_t *)&(immr->im_pic.iivpr10), /* Source 34: 0x50340 - Internal Interrupt Vector/Priority Register 10  */
    [35] = (uint32_t *)&(immr->im_pic.iivpr11), /* Source 35: 0x50360 - Internal Interrupt Vector/Priority Register 11  */
    [36] = (uint32_t *)&(immr->im_pic.iivpr12), /* Source 36: 0x50380 - Internal Interrupt Vector/Priority Register 12  */
    [37] = (uint32_t *)&(immr->im_pic.iivpr13), /* Source 37: 0x503a0 - Internal Interrupt Vector/Priority Register 13  */
    [38] = (uint32_t *)&(immr->im_pic.iivpr14), /* Source 38: 0x503c0 - Internal Interrupt Vector/Priority Register 14  */
    [39] = (uint32_t *)&(immr->im_pic.iivpr15), /* Source 39: 0x503e0 - Internal Interrupt Vector/Priority Register 15  */
    [40] = (uint32_t *)&(immr->im_pic.iivpr16), /* Source 40: 0x50400 - Internal Interrupt Vector/Priority Register 16  */
    [41] = (uint32_t *)&(immr->im_pic.iivpr17), /* Source 41: 0x50420 - Internal Interrupt Vector/Priority Register 17  */
    [42] = (uint32_t *)&(immr->im_pic.iivpr18), /* Source 42: 0x50440 - Internal Interrupt Vector/Priority Register 18  */
    [43] = (uint32_t *)&(immr->im_pic.iivpr19), /* Source 43: 0x50460 - Internal Interrupt Vector/Priority Register 19  */
    [44] = (uint32_t *)&(immr->im_pic.iivpr20), /* Source 44: 0x50480 - Internal Interrupt Vector/Priority Register 20  */
    [45] = (uint32_t *)&(immr->im_pic.iivpr21), /* Source 45: 0x504a0 - Internal Interrupt Vector/Priority Register 21  */
    [46] = (uint32_t *)&(immr->im_pic.iivpr22), /* Source 46: 0x504c0 - Internal Interrupt Vector/Priority Register 22  */
    [47] = (uint32_t *)&(immr->im_pic.iivpr23), /* Source 47: 0x504e0 - Internal Interrupt Vector/Priority Register 23  */
    [48] = (uint32_t *)&(immr->im_pic.iivpr24), /* Source 48: 0x50500 - Internal Interrupt Vector/Priority Register 24  */
    [49] = (uint32_t *)&(immr->im_pic.iivpr25), /* Source 49: 0x50520 - Internal Interrupt Vector/Priority Register 25  */
    [50] = (uint32_t *)&(immr->im_pic.iivpr26), /* Source 50: 0x50540 - Internal Interrupt Vector/Priority Register 26  */
    [51] = (uint32_t *)&(immr->im_pic.iivpr27), /* Source 51: 0x50560 - Internal Interrupt Vector/Priority Register 27  */
    [52] = (uint32_t *)&(immr->im_pic.iivpr28), /* Source 52: 0x50580 - Internal Interrupt Vector/Priority Register 28  */
    [53] = (uint32_t *)&(immr->im_pic.iivpr29), /* Source 53: 0x505a0 - Internal Interrupt Vector/Priority Register 29  */
    [54] = (uint32_t *)&(immr->im_pic.iivpr30), /* Source 54: 0x505c0 - Internal Interrupt Vector/Priority Register 30  */
    [55] = (uint32_t *)&(immr->im_pic.iivpr31), /* Source 55: 0x505e0 - Internal Interrupt Vector/Priority Register 31  */
    [56] = (uint32_t *)&(immr->im_pic.iivpr32), /* Source 56: 0x50600 - Internal interrupt 32 vector/priority register   */
    [57] = (uint32_t *)&(immr->im_pic.iivpr33), /* Source 57: 0x50620 - Internal interrupt 33 vector/priority register  */
    [58] = (uint32_t *)&(immr->im_pic.iivpr34), /* Source 58: 0x50640 - Internal interrupt 34 vector/priority register  */
    [59] = (uint32_t *)&(immr->im_pic.iivpr35), /* Source 59: 0x50660 - Internal interrupt 35 vector/priority register  */
    [60] = (uint32_t *)&(immr->im_pic.iivpr36), /* Source 60: 0x50680 - Internal interrupt 36 vector/priority register  */
    [61] = (uint32_t *)&(immr->im_pic.iivpr37), /* Source 61: 0x506A0 - Internal interrupt 37 vector/priority register  */
    [62] = (uint32_t *)&(immr->im_pic.iivpr38), /* Source 62: 0x506C0 - Internal interrupt 38 vector/priority register  */
    [63] = (uint32_t *)&(immr->im_pic.iivpr39), /* Source 63: 0x506E0 - Internal interrupt 39 vector/priority register  */
    [64] = (uint32_t *)&(immr->im_pic.iivpr40), /* Source 64: 0x50700 - Internal interrupt 40 vector/priority register  */
    [65] = (uint32_t *)&(immr->im_pic.iivpr41), /* Source 65: 0x50720 - Internal interrupt 41 vector/priority register  */
    [66] = (uint32_t *)&(immr->im_pic.iivpr42), /* Source 66: 0x50740 - Internal interrupt 42 vector/priority register  */
    [67] = (uint32_t *)&(immr->im_pic.iivpr43), /* Source 67: 0x50760 - Internal interrupt 43 vector/priority register  */
    [68] = (uint32_t *)&(immr->im_pic.iivpr44), /* Source 68: 0x50780 - Internal interrupt 44 vector/priority register  */
    [69] = (uint32_t *)&(immr->im_pic.iivpr45), /* Source 69: 0x507A0 - Internal interrupt 45 vector/priority register   */
    [70] = (uint32_t *)&(immr->im_pic.iivpr46), /* Source 70: 0x507C0 - Internal interrupt 46 vector/priority register  */
    [71] = (uint32_t *)&(immr->im_pic.iivpr47), /* Source 71: 0x507E0 - Internal interrupt 47 vector/priority register  */
    [72] = (uint32_t *)&(immr->im_pic.mivpr0), /* Source 72: 0x51600 - Messaging Interrupt Vector/Priority Register 0  */
    [73] = (uint32_t *)&(immr->im_pic.mivpr1), /* Source 73: 0x51620 - Messaging Interrupt Vector/Priority Register 1  */
    [74] = (uint32_t *)&(immr->im_pic.mivpr2), /* Source 74: 0x51640 - Messaging Interrupt Vector/Priority Register 2  */
    [75] = (uint32_t *)&(immr->im_pic.mivpr3), /* Source 75: 0x51660 - Messaging Interrupt Vector/Priority Register 3  */
    [76] = (uint32_t *)&(immr->im_pic.msivpr0), /* Source 76: 0x51C00 - Shared message signaled interrupt vector/priority register 0  */
    [77] = (uint32_t *)&(immr->im_pic.msivpr1), /* Source 77: 0x51C20 - Shared message signaled interrupt vector/priority register 1  */
    [78] = (uint32_t *)&(immr->im_pic.msivpr2), /* Source 78: 0x51C40 - Shared message signaled interrupt vector/priority register 2  */
    [79] = (uint32_t *)&(immr->im_pic.msivpr3), /* Source 79: 0x51C60 - Shared message signaled interrupt vector/priority register 3  */
    [80] = (uint32_t *)&(immr->im_pic.msivpr4), /* Source 80: 0x51C80 - Shared message signaled interrupt vector/priority register 4  */
    [81] = (uint32_t *)&(immr->im_pic.msivpr5), /* Source 81: 0x51CA0 - Shared message signaled interrupt vector/priority register 5  */
    [82] = (uint32_t *)&(immr->im_pic.msivpr6), /* Source 82: 0x51CC0 - Shared message signaled interrupt vector/priority register 6  */
    [83] = (uint32_t *)&(immr->im_pic.msivpr7), /* Source 83: 0x51CE0 - Shared message signaled interrupt vector/priority register 7  */
};

/** IRQ number to IDR register table */
uint32_t *g_p_PIC_irq2idr[CONFIG_NO_HWIRQS] =
{
    [0] = (uint32_t *)&(immr->im_pic.ipidr0), /* Source 0: 0x40040 - Interprocessor Interrupt Dispatch Register 0  */
    [1] = (uint32_t *)&(immr->im_pic.ipidr1), /* Source 1: 0x40050 - Interprocessor Interrupt Dispatch Register 1  */
    [2] = (uint32_t *)&(immr->im_pic.ipidr2), /* Source 2: 0x40060 - Interprocessor Interrupt Dispatch Register 2  */
    [3] = (uint32_t *)&(immr->im_pic.ipidr3), /* Source 3: 0x40070 - Interprocessor Interrupt Dispatch Register 3  */
    [4] = (uint32_t *)&(immr->im_pic.gtdra0), /* Source 4: 0x41130 - Global Timer Destination Register group A 0  */
    [5] = (uint32_t *)&(immr->im_pic.gtdra1), /* Source 5: 0x41170 - Global Timer Destination Register group A 1  */
    [6] = (uint32_t *)&(immr->im_pic.gtdra2), /* Source 6: 0x411b0 - Global Timer Destination Register group A 2  */
    [7] = (uint32_t *)&(immr->im_pic.gtdra3), /* Source 7: 0x411f0 - Global Timer Destination Register group A 3  */
    [8] = (uint32_t *)&(immr->im_pic.gtdrb0), /* Source 8: 0x42130 - Global timer destination register group B 0  */
    [9] = (uint32_t *)&(immr->im_pic.gtdrb1), /* Source 9: 0x42170 - Global timer destination register group B 1  */
    [10] = (uint32_t *)&(immr->im_pic.gtdrb2), /* Source 10: 0x421B0 - Global timer destination register group B 2  */
    [11] = (uint32_t *)&(immr->im_pic.gtdrb3), /* Source 11: 0x421F0 - Global timer destination register group B 3  */
    [12] = (uint32_t *)&(immr->im_pic.eidr0), /* Source 12: 0x50010 - External Interrupt Destination Register 0  */
    [13] = (uint32_t *)&(immr->im_pic.eidr1), /* Source 13: 0x50030 - External Interrupt Destination Register 1  */
    [14] = (uint32_t *)&(immr->im_pic.eidr2), /* Source 14: 0x50050 - External Interrupt Destination Register 2  */
    [15] = (uint32_t *)&(immr->im_pic.eidr3), /* Source 15: 0x50070 - External Interrupt Destination Register 3  */
    [16] = (uint32_t *)&(immr->im_pic.eidr4), /* Source 16: 0x50090 - External Interrupt Destination Register 4  */
    [17] = (uint32_t *)&(immr->im_pic.eidr5), /* Source 17: 0x500b0 - External Interrupt Destination Register 5  */
    [18] = (uint32_t *)&(immr->im_pic.eidr6), /* Source 18: 0x500d0 - External Interrupt Destination Register 6  */
    [19] = (uint32_t *)&(immr->im_pic.eidr7), /* Source 19: 0x500f0 - External Interrupt Destination Register 7  */
    [20] = (uint32_t *)&(immr->im_pic.eidr8), /* Source 20: 0x50110 - External Interrupt Destination Register 8  */
    [21] = (uint32_t *)&(immr->im_pic.eidr9), /* Source 21: 0x50130 - External Interrupt Destination Register 9  */
    [22] = (uint32_t *)&(immr->im_pic.eidr10), /* Source 22: 0x50150 - External Interrupt Destination Register 10  */
    [23] = (uint32_t *)&(immr->im_pic.eidr11), /* Source 23: 0x50170 - External Interrupt Destination Register 11  */
    [24] = (uint32_t *)&(immr->im_pic.iidr0), /* Source 24: 0x50210 - Internal Interrupt Destination Register 0  */
    [25] = (uint32_t *)&(immr->im_pic.iidr1), /* Source 25: 0x50230 - Internal Interrupt Destination Register 1  */
    [26] = (uint32_t *)&(immr->im_pic.iidr2), /* Source 26: 0x50250 - Internal Interrupt Destination Register 2  */
    [27] = (uint32_t *)&(immr->im_pic.iidr3), /* Source 27: 0x50270 - Internal Interrupt Destination Register 3  */
    [28] = (uint32_t *)&(immr->im_pic.iidr4), /* Source 28: 0x50290 - Internal Interrupt Destination Register 4  */
    [29] = (uint32_t *)&(immr->im_pic.iidr5), /* Source 29: 0x502b0 - Internal Interrupt Destination Register 5  */
    [30] = (uint32_t *)&(immr->im_pic.iidr6), /* Source 30: 0x502d0 - Internal Interrupt Destination Register 6  */
    [31] = (uint32_t *)&(immr->im_pic.iidr7), /* Source 31: 0x502f0 - Internal Interrupt Destination Register 7  */
    [32] = (uint32_t *)&(immr->im_pic.iidr8), /* Source 32: 0x50310 - Internal Interrupt Destination Register 8  */
    [33] = (uint32_t *)&(immr->im_pic.iidr9), /* Source 33: 0x50330 - Internal Interrupt Destination Register 9  */
    [34] = (uint32_t *)&(immr->im_pic.iidr10), /* Source 34: 0x50350 - Internal Interrupt Destination Register 10  */
    [35] = (uint32_t *)&(immr->im_pic.iidr11), /* Source 35: 0x50370 - Internal Interrupt Destination Register 11  */
    [36] = (uint32_t *)&(immr->im_pic.iidr12), /* Source 36: 0x50390 - Internal Interrupt Destination Register 12  */
    [37] = (uint32_t *)&(immr->im_pic.iidr13), /* Source 37: 0x503b0 - Internal Interrupt Destination Register 13  */
    [38] = (uint32_t *)&(immr->im_pic.iidr14), /* Source 38: 0x503d0 - Internal Interrupt Destination Register 14  */
    [39] = (uint32_t *)&(immr->im_pic.iidr15), /* Source 39: 0x503f0 - Internal Interrupt Destination Register 15  */
    [40] = (uint32_t *)&(immr->im_pic.iidr16), /* Source 40: 0x50410 - Internal Interrupt Destination Register 16  */
    [41] = (uint32_t *)&(immr->im_pic.iidr17), /* Source 41: 0x50430 - Internal Interrupt Destination Register 17  */
    [42] = (uint32_t *)&(immr->im_pic.iidr18), /* Source 42: 0x50450 - Internal Interrupt Destination Register 18  */
    [43] = (uint32_t *)&(immr->im_pic.iidr19), /* Source 43: 0x50470 - Internal Interrupt Destination Register 19  */
    [44] = (uint32_t *)&(immr->im_pic.iidr20), /* Source 44: 0x50490 - Internal Interrupt Destination Register 20  */
    [45] = (uint32_t *)&(immr->im_pic.iidr21), /* Source 45: 0x504b0 - Internal Interrupt Destination Register 21  */
    [46] = (uint32_t *)&(immr->im_pic.iidr22), /* Source 46: 0x504d0 - Internal Interrupt Destination Register 22  */
    [47] = (uint32_t *)&(immr->im_pic.iidr23), /* Source 47: 0x504f0 - Internal Interrupt Destination Register 23  */
    [48] = (uint32_t *)&(immr->im_pic.iidr24), /* Source 48: 0x50510 - Internal Interrupt Destination Register 24  */
    [49] = (uint32_t *)&(immr->im_pic.iidr25), /* Source 49: 0x50530 - Internal Interrupt Destination Register 25  */
    [50] = (uint32_t *)&(immr->im_pic.iidr26), /* Source 50: 0x50550 - Internal Interrupt Destination Register 26  */
    [51] = (uint32_t *)&(immr->im_pic.iidr27), /* Source 51: 0x50570 - Internal Interrupt Destination Register 27  */
    [52] = (uint32_t *)&(immr->im_pic.iidr28), /* Source 52: 0x50590 - Internal Interrupt Destination Register 28  */
    [53] = (uint32_t *)&(immr->im_pic.iidr29), /* Source 53: 0x505b0 - Internal Interrupt Destination Register 29  */
    [54] = (uint32_t *)&(immr->im_pic.iidr30), /* Source 54: 0x505d0 - Internal Interrupt Destination Register 30  */
    [55] = (uint32_t *)&(immr->im_pic.iidr31), /* Source 55: 0x505f0 - Internal Interrupt Destination Register 31  */
    [56] = (uint32_t *)&(immr->im_pic.iidr32), /* Source 56: 0x50610 - Internal interrupt 32 destination register  */
    [57] = (uint32_t *)&(immr->im_pic.iidr33), /* Source 57: 0x50630 - Internal interrupt 33 destination register  */
    [58] = (uint32_t *)&(immr->im_pic.iidr34), /* Source 58: 0x50650 - Internal interrupt 34 destination register  */
    [59] = (uint32_t *)&(immr->im_pic.iidr35), /* Source 59: 0x50670 - Internal interrupt 35 destination register  */
    [60] = (uint32_t *)&(immr->im_pic.iidr36), /* Source 60: 0x50690 - Internal interrupt 36 destination register  */
    [61] = (uint32_t *)&(immr->im_pic.iidr37), /* Source 61: 0x506B0 - Internal interrupt 37 destination register  */
    [62] = (uint32_t *)&(immr->im_pic.iidr38), /* Source 62: 0x506D0 - Internal interrupt 38 destination register  */
    [63] = (uint32_t *)&(immr->im_pic.iidr39), /* Source 63: 0x506F0 - Internal interrupt 39 destination register  */
    [64] = (uint32_t *)&(immr->im_pic.iidr40), /* Source 64: 0x50710 - Internal interrupt 40 destination register  */
    [65] = (uint32_t *)&(immr->im_pic.iidr41), /* Source 65: 0x50730 - Internal interrupt 41 destination register  */
    [66] = (uint32_t *)&(immr->im_pic.iidr42), /* Source 66: 0x50750 - Internal interrupt 42 destination register  */
    [67] = (uint32_t *)&(immr->im_pic.iidr43), /* Source 67: 0x50770 - Internal interrupt 43 destination register  */
    [68] = (uint32_t *)&(immr->im_pic.iidr44), /* Source 68: 0x50790 - Internal interrupt 44 destination register  */
    [69] = (uint32_t *)&(immr->im_pic.iidr45), /* Source 69: 0x507B0 - Internal interrupt 45 destination register  */
    [70] = (uint32_t *)&(immr->im_pic.iidr46), /* Source 70: 0x507D0 - Internal interrupt 46 destination register  */
    [71] = (uint32_t *)&(immr->im_pic.iidr47), /* Source 71: 0x507F0 - Internal interrupt 47 destination register  */
    [72] = (uint32_t *)&(immr->im_pic.midr0), /* Source 72: 0x51610 - Messaging Interrupt Destination Register 0  */
    [73] = (uint32_t *)&(immr->im_pic.midr1), /* Source 73: 0x51630 - Messaging Interrupt Destination Register 1  */
    [74] = (uint32_t *)&(immr->im_pic.midr2), /* Source 74: 0x51650 - Messaging Interrupt Destination Register 2  */
    [75] = (uint32_t *)&(immr->im_pic.midr3), /* Source 75: 0x51670 - Messaging Interrupt Destination Register 3  */
    [76] = (uint32_t *)&(immr->im_pic.msidr0), /* Source 76: 0x51C10 - Shared message signaled interrupt destination register 0  */
    [77] = (uint32_t *)&(immr->im_pic.msidr1), /* Source 77: 0x51C30 - Shared message signaled interrupt destination register 1  */
    [78] = (uint32_t *)&(immr->im_pic.msidr2), /* Source 78: 0x51C50 - Shared message signaled interrupt destination register 2  */
    [79] = (uint32_t *)&(immr->im_pic.msidr3), /* Source 79: 0x51C70 - Shared message signaled interrupt destination register 3  */
    [80] = (uint32_t *)&(immr->im_pic.msidr4), /* Source 80: 0x51C90 - Shared message signaled interrupt destination register 4  */
    [81] = (uint32_t *)&(immr->im_pic.msidr5), /* Source 81: 0x51CB0 - Shared message signaled interrupt destination register 5  */
    [82] = (uint32_t *)&(immr->im_pic.msidr6), /* Source 82: 0x51CD0 - Shared message signaled interrupt destination register 6  */
    [83] = (uint32_t *)&(immr->im_pic.msidr7), /* Source 83: 0x51CF0 - Shared message signaled interrupt destination register 7  */
};

/** Flags table for each IRQ source */
uint32_t g_PIC_irq_flags[CONFIG_NO_HWIRQS] =
{
    [0] = (PIC_IS_MULTICAST_FLAG), /* Source 0: Interprocessor Interrupt 0  */
    [1] = (PIC_IS_MULTICAST_FLAG), /* Source 1: Interprocessor Interrupt 1  */
    [2] = (PIC_IS_MULTICAST_FLAG), /* Source 2: Interprocessor Interrupt 2  */
    [3] = (PIC_IS_MULTICAST_FLAG), /* Source 3: Interprocessor Interrupt 3  */
    [4] = (PIC_IS_MULTICAST_FLAG), /* Source 4: Global Timer  group A 0  */
    [5] = (PIC_IS_MULTICAST_FLAG), /* Source 5: Global Timer  group A 1  */
    [6] = (PIC_IS_MULTICAST_FLAG), /* Source 6: Global Timer  group A 2  */
    [7] = (PIC_IS_MULTICAST_FLAG), /* Source 7: Global Timer  group A 3  */
    [8] = (PIC_IS_MULTICAST_FLAG), /* Source 8: Global timer  group B 0  */
    [9] = (PIC_IS_MULTICAST_FLAG), /* Source 9: Global timer  group B 1  */
    [10] = (PIC_IS_MULTICAST_FLAG), /* Source 10: Global timer  group B 2  */
    [11] = (PIC_IS_MULTICAST_FLAG), /* Source 11: Global timer  group B 3  */
    [12] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 12: External Interrupt  0  */
    [13] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 13: External Interrupt  1  */
    [14] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 14: External Interrupt  2  */
    [15] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 15: External Interrupt  3  */
    [16] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 16: External Interrupt  4  */
    [17] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 17: External Interrupt  5  */
    [18] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 18: External Interrupt  6  */
    [19] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 19: External Interrupt  7  */
    [20] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 20: External Interrupt  8  */
    [21] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 21: External Interrupt  9  */
    [22] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 22: External Interrupt  10  */
    [23] = (PIC_HAS_SENSE_FLAG | PIC_HAS_POLARITY_FLAG), /* Source 23: External Interrupt  11  */
    [24] = (PIC_HAS_POLARITY_FLAG), /* Source 24: Internal Interrupt  0  */
    [25] = (PIC_HAS_POLARITY_FLAG), /* Source 25: Internal Interrupt  1  */
    [26] = (PIC_HAS_POLARITY_FLAG), /* Source 26: Internal Interrupt  2  */
    [27] = (PIC_HAS_POLARITY_FLAG), /* Source 27: Internal Interrupt  3  */
    [28] = (PIC_HAS_POLARITY_FLAG), /* Source 28: Internal Interrupt  4  */
    [29] = (PIC_HAS_POLARITY_FLAG), /* Source 29: Internal Interrupt  5  */
    [30] = (PIC_HAS_POLARITY_FLAG), /* Source 30: Internal Interrupt  6  */
    [31] = (PIC_HAS_POLARITY_FLAG), /* Source 31: Internal Interrupt  7  */
    [32] = (PIC_HAS_POLARITY_FLAG), /* Source 32: Internal Interrupt  8  */
    [33] = (PIC_HAS_POLARITY_FLAG), /* Source 33: Internal Interrupt  9  */
    [34] = (PIC_HAS_POLARITY_FLAG), /* Source 34: Internal Interrupt  10  */
    [35] = (PIC_HAS_POLARITY_FLAG), /* Source 35: Internal Interrupt  11  */
    [36] = (PIC_HAS_POLARITY_FLAG), /* Source 36: Internal Interrupt  12  */
    [37] = (PIC_HAS_POLARITY_FLAG), /* Source 37: Internal Interrupt  13  */
    [38] = (PIC_HAS_POLARITY_FLAG), /* Source 38: Internal Interrupt  14  */
    [39] = (PIC_HAS_POLARITY_FLAG), /* Source 39: Internal Interrupt  15  */
    [40] = (PIC_HAS_POLARITY_FLAG), /* Source 40: Internal Interrupt  16  */
    [41] = (PIC_HAS_POLARITY_FLAG), /* Source 41: Internal Interrupt  17  */
    [42] = (PIC_HAS_POLARITY_FLAG), /* Source 42: Internal Interrupt  18  */
    [43] = (PIC_HAS_POLARITY_FLAG), /* Source 43: Internal Interrupt  19  */
    [44] = (PIC_HAS_POLARITY_FLAG), /* Source 44: Internal Interrupt  20  */
    [45] = (PIC_HAS_POLARITY_FLAG), /* Source 45: Internal Interrupt  21  */
    [46] = (PIC_HAS_POLARITY_FLAG), /* Source 46: Internal Interrupt  22  */
    [47] = (PIC_HAS_POLARITY_FLAG), /* Source 47: Internal Interrupt  23  */
    [48] = (PIC_HAS_POLARITY_FLAG), /* Source 48: Internal Interrupt  24  */
    [49] = (PIC_HAS_POLARITY_FLAG), /* Source 49: Internal Interrupt  25  */
    [50] = (PIC_HAS_POLARITY_FLAG), /* Source 50: Internal Interrupt  26  */
    [51] = (PIC_HAS_POLARITY_FLAG), /* Source 51: Internal Interrupt  27  */
    [52] = (PIC_HAS_POLARITY_FLAG), /* Source 52: Internal Interrupt  28  */
    [53] = (PIC_HAS_POLARITY_FLAG), /* Source 53: Internal Interrupt  29  */
    [54] = (PIC_HAS_POLARITY_FLAG), /* Source 54: Internal Interrupt  30  */
    [55] = (PIC_HAS_POLARITY_FLAG), /* Source 55: Internal Interrupt  31  */
    [56] = (PIC_HAS_POLARITY_FLAG), /* Source 56: Internal interrupt 32   */
    [57] = (PIC_HAS_POLARITY_FLAG), /* Source 57: Internal interrupt 33   */
    [58] = (PIC_HAS_POLARITY_FLAG), /* Source 58: Internal interrupt 34   */
    [59] = (PIC_HAS_POLARITY_FLAG), /* Source 59: Internal interrupt 35   */
    [60] = (PIC_HAS_POLARITY_FLAG), /* Source 60: Internal interrupt 36   */
    [61] = (PIC_HAS_POLARITY_FLAG), /* Source 61: Internal interrupt 37   */
    [62] = (PIC_HAS_POLARITY_FLAG), /* Source 62: Internal interrupt 38   */
    [63] = (PIC_HAS_POLARITY_FLAG), /* Source 63: Internal interrupt 39   */
    [64] = (PIC_HAS_POLARITY_FLAG), /* Source 64: Internal interrupt 40   */
    [65] = (PIC_HAS_POLARITY_FLAG), /* Source 65: Internal interrupt 41   */
    [66] = (PIC_HAS_POLARITY_FLAG), /* Source 66: Internal interrupt 42   */
    [67] = (PIC_HAS_POLARITY_FLAG), /* Source 67: Internal interrupt 43   */
    [68] = (PIC_HAS_POLARITY_FLAG), /* Source 68: Internal interrupt 44   */
    [69] = (PIC_HAS_POLARITY_FLAG), /* Source 69: Internal interrupt 45   */
    [70] = (PIC_HAS_POLARITY_FLAG), /* Source 70: Internal interrupt 46   */
    [71] = (PIC_HAS_POLARITY_FLAG), /* Source 71: Internal interrupt 47   */
    [72] = 0, /* Source 72: Messaging Interrupt  0  */
    [73] = 0, /* Source 73: Messaging Interrupt  1  */
    [74] = 0, /* Source 74: Messaging Interrupt  2  */
    [75] = 0, /* Source 75: Messaging Interrupt  3  */
    [76] = 0, /* Source 76: Shared message signaled interrupt  0  */
    [77] = 0, /* Source 77: Shared message signaled interrupt  1  */
    [78] = 0, /* Source 78: Shared message signaled interrupt  2  */
    [79] = 0, /* Source 79: Shared message signaled interrupt  3  */
    [80] = 0, /* Source 80: Shared message signaled interrupt  4  */
    [81] = 0, /* Source 81: Shared message signaled interrupt  5  */
    [82] = 0, /* Source 82: Shared message signaled interrupt  6  */
    [83] = 0, /* Source 83: Shared message signaled interrupt  7  */
};

/** IRQ source names */
char *g_p_PIC_irq_names[CONFIG_NO_HWIRQS] =
{
    [0] = "Interprocessor Interrupt 0",
    [1] = "Interprocessor Interrupt 1",
    [2] = "Interprocessor Interrupt 2",
    [3] = "Interprocessor Interrupt 3",
    [4] = "Global Timer Group A 0",
    [5] = "Global Timer Group A 1",
    [6] = "Global Timer Group A 2",
    [7] = "Global Timer Group A 3",
    [8] = "Global Timer Group B 0",
    [9] = "Global Timer Group B 1",
    [10] = "Global Timer Group B 2",
    [11] = "Global Timer Group B 3",
    [12] = "External Interrupt 0",
    [13] = "External Interrupt 1",
    [14] = "External Interrupt 2",
    [15] = "External Interrupt 3",
    [16] = "External Interrupt 4",
    [17] = "External Interrupt 5",
    [18] = "External Interrupt 6",
    [19] = "External Interrupt 7",
    [20] = "External Interrupt 8",
    [21] = "External Interrupt 9",
    [22] = "External Interrupt 10",
    [23] = "External Interrupt 11",
    [24] = "Internal Interrupt 0 (Unwired)",
    [25] = "Internal Interrupt 1 (MCM)",
    [26] = "Internal Interrupt 2 (DDR DRAM controllers 1 and 2)",
    [27] = "Internal Interrupt 3 (LBC controller)",
    [28] = "Internal Interrupt 4 (DMA channel 1)",
    [29] = "Internal Interrupt 5 (DMA channel 2)",
    [30] = "Internal Interrupt 6 (DMA channel 3 )",
    [31] = "Internal Interrupt 7 (DMA channel 4 )",
    [32] = "Internal Interrupt 8 (PCI Express Port1)",
    [33] = "Internal Interrupt 9 (PCI Express Port2)",
    [34] = "Internal Interrupt 10 (Unwired)",
    [35] = "Internal Interrupt 11 (Unwired)",
    [36] = "Internal Interrupt 12 (UART2)",
    [37] = "Internal Interrupt 13 (eTSEC 1 transmit)",
    [38] = "Internal Interrupt 14 (eTSEC 1 receive)",
    [39] = "Internal Interrupt 15 (eTSEC 3 transmit)",
    [40] = "Internal Interrupt 16 (eTSEC 3 receive)",
    [41] = "Internal Interrupt 17 (eTSEC 3 error)",
    [42] = "Internal Interrupt 18 (eTSEC 1 error)",
    [43] = "Internal Interrupt 19 (eTSEC 2 transmit)",
    [44] = "Internal Interrupt 20 (eTSEC 2 receive)",
    [45] = "Internal Interrupt 21 (eTSEC 4 transmit)",
    [46] = "Internal Interrupt 22 (eTSEC 4 receive)",
    [47] = "Internal Interrupt 23 (eTSEC 4 error)",
    [48] = "Internal Interrupt 24 (eTSEC 2 error)",
    [49] = "Internal Interrupt 25 (Unwired)",
    [50] = "Internal Interrupt 26 (UART1)",
    [51] = "Internal Interrupt 27 (I2C controllers)",
    [52] = "Internal Interrupt 28 (Performance monitor)",
    [53] = "Internal Interrupt 29 (Unwired)",
    [54] = "Internal Interrupt 30 (Unwired)",
    [55] = "Internal Interrupt 31 (Unwired)",
    [56] = "Internal Interrupt 32 (SRIO error/write-port unit)",
    [57] = "Internal Interrupt 33 (SRIO outbound doorbell )",
    [58] = "Internal Interrupt 34 (SRIO inbound doorbell )",
    [59] = "Internal Interrupt 35 (Unwired)",
    [60] = "Internal Interrupt 36 (Unwired)",
    [61] = "Internal Interrupt 37 (SRIO outbound message unit1)",
    [62] = "Internal Interrupt 38 (SRIO inbound message unit 1)",
    [63] = "Internal Interrupt 39 (SRIO outbound message unit 2)",
    [64] = "Internal Interrupt 40 (SRIO inbound message unit 2)",
    [65] = "Internal Interrupt 41 (Unwired)",
    [66] = "Internal Interrupt 42 (Unwired)",
    [67] = "Internal Interrupt 43 (Unwired)",
    [68] = "Internal Interrupt 44 (Unwired)",
    [69] = "Internal Interrupt 45 (Unwired)",
    [70] = "Internal Interrupt 46 (Unwired)",
    [71] = "Internal Interrupt 47 (Unwired)",
    [72] = "Messaging Interrupt 0",
    [73] = "Messaging Interrupt 1",
    [74] = "Messaging Interrupt 2",
    [75] = "Messaging Interrupt 3",
    [76] = "Shared Message Signaled Interrupt 0",
    [77] = "Shared Message Signaled Interrupt 1",
    [78] = "Shared Message Signaled Interrupt 2",
    [79] = "Shared Message Signaled Interrupt 3",
    [80] = "Shared Message Signaled Interrupt 4",
    [81] = "Shared Message Signaled Interrupt 5",
    [82] = "Shared Message Signaled Interrupt 6",
    [83] = "Shared Message Signaled Interrupt 7",
};

/**
 * Default IRQ handler called when no handler is set.
 *
 * @param p_ctxt - pointer to saved interrupt context
 * @param p_data - pointer to IRQ-specific data (always NULL in this case)
 */
void __attribute__ ((weak)) DefaultIrqHandler(irqCtxt_t *p_ctxt, void *p_data)
{

}

/**
 * Alignment exception handler.
 *
 * @param p_ctxt - pointer to saved interrupt context
 * @param dar - value of DAR on exception entry
 * @param dsisr - value of DSISR on exception entry
 */
void __attribute__ ((weak)) DoAlignment(irqCtxt_t *p_ctxt, uint32_t dar, uint32_t dsisr)
{

}

/**
 * Decrementer exception handler.
 *
 * @param p_ctxt - pointer to saved interrupt context
 */
void __attribute__ ((weak)) DoDecrementer(irqCtxt_t *p_ctxt)
{

}

/**
 * Spurious IRQ handler called when a PIC spurious IRQ occurs.
 *
 * @param p_ctxt - pointer to saved interrupt context
 * @param p_data - pointer to IRQ-specific data (always NULL in this case)
 */
void __attribute__ ((weak)) SpuriousIrqHandler(irqCtxt_t *p_ctxt, void *p_data)
{

}

/**
 * Default exception handler called when no handler is set.
 *
 * @param p_ctxt - pointer to saved exception context
 */
void __attribute__ ((weak)) UnexpectedExceptionHandler(irqCtxt_t *p_ctxt)
{

}

/**
 * Handle a program check exception on the PowerPC.
 *
 * @param p_ctxt - pointer to interrupt saved context.
 */
void __attribute__ ((weak)) DoProgramCheck(irqCtxt_t *p_ctxt)
{

}

/* ---------- MCM_BPTR: Boot page translation register  ---------- */
#define MCM_BPTR_OFFSET 0x0020
#define MCM_BPTR_EN_BIT 31              /* Bit 0 (31-0 = 31): Boot page translation enable */
                                        /* Bits 1-7: Write reserved, read = 0 */
#define MCM_BPTR_BOOT_PAGE_LAST_BIT 8   /* Bits 8-23 (31-23 = 8): Translation for boot page. */
                                        /* Bits 23-31: Write reserved, read = 0 */
#define MCM_BPTR_EN             0x80000000
#define MCM_BPTR_BOOT_PAGE_MASK 0x00FFFF00  /* Bits 8-23: Translation for boot page. */

/**
 * Initialize the entire IRQ and exception subsystem.
 *
 * This sets up the handler tables as well at the PIC.
 */
void SetupIrqs(void)
{
    int32_t irqNr;

    /* Setup IRQ handler tables */
    for (irqNr = 0; irqNr < CONFIG_NO_HWIRQS; irqNr++)
    {
        irqHandlerTab[irqNr] = (struct irqTabEntry)
        {
            .handler=DefaultIrqHandler,
            .data=0,
        };
    }

    irqHandlerTab[IRQ_SPURIOUS_VECTOR] = (struct irqTabEntry)
    {
        .handler=SpuriousIrqHandler,
        .data=0,
    };

    for (irqNr=0; irqNr < EXCEPTION_NR; irqNr++)
    {
        exceptionHandlerTab[irqNr] = UnexpectedExceptionHandler;
    }

    /* Set BPTR to relocate the high-addressed exception table to our table */
    sync();
    immr->im_local_mcm.bptr = MCM_BPTR_EN | ((CONFIG_START_ADDRESS >> 12) & MCM_BPTR_BOOT_PAGE_MASK);
    eieio();
    isync();

    /* Initialize and reset PIC. All IRQs will be vectored
     * to their source number.
     */
    PIC_init();
}

/**
 * Set the IRQ handler for one of the PIC's interrupt sources.
 *
 * @param irqNr - PIC IRQ source number (0-127)
 * @param irqHandler - IRQ handler function pointer
 * @param p_data - Pointer to IRQ-specific data structure that gets passed at every handler invokation
 * @return a pointer to the previously set IRQ handler
 */
irqHandler_t SetIrqHandler(int32_t irqNr, irqHandler_t irqHandler, void *p_data)
{
    irqHandler_t old_handler = irqHandlerTab[irqNr].handler;

    if (irqHandler)
    {
        irqHandlerTab[irqNr] = (struct irqTabEntry)
        {
            .handler = irqHandler,
            .data = p_data,
        };
    }
    else
    {
        irqHandlerTab[irqNr]=(struct irqTabEntry)
        {
            .handler = DefaultIrqHandler,
            .data = 0,
        };
    }

    return old_handler;
}

/**
 * Set the exception handler for one of the internal exceptions.
 *
 * @param exceptionNr - Exception number (0-31)
 * @param exceptionHandler - Exception handler function pointer
 * @return a pointer to the previously set exception handler.
 */
exceptionHandler_t SetExceptionHandler(int32_t exceptionNr, exceptionHandler_t exceptionHandler)
{
    exceptionHandler_t old_handler = exceptionHandlerTab[exceptionNr];

    if (exceptionHandler)
        exceptionHandlerTab[exceptionNr] = exceptionHandler;
    else
        exceptionHandlerTab[exceptionNr] = UnexpectedExceptionHandler;

    return old_handler;
}

/**
 * Disable (mask) the specified IRQ at the controller.
 * @param irqNr - Hardware IRQ number
 */
void DisableIrq(uint32_t irqNr)
{
    /* Set the source's VPR[MSK] bit, thus disabling it */
    if (irqNr < CONFIG_NO_HWIRQS)
        *g_p_PIC_irq2vpr[irqNr] |= PIC_IVPR_MSK;
}

/**
 * Enable (unmask) the specified IRQ at the controller.
 * @param irqNr - Hardware IRQ number
 */
void EnableIrq(uint32_t irqNr)
{
    /* Clear the source's VPR[MSK] bit, thus enabling it */
    if (irqNr < CONFIG_NO_HWIRQS)
        *g_p_PIC_irq2vpr[irqNr] &= ~PIC_IVPR_MSK;
}

/**
 * Set the priority of the specified IRQ at the controller.
 *
 * The priority value is architecture-specific.
 *
 * @param irqNr - Hardware IRQ number
 * @param priority - Priority to set for the IRQ
 */
void SetPriorityIrq(uint32_t irqNr, uint32_t priority)
{
    /* Set the priority field of the interrupt's VPR register */
    if (irqNr < CONFIG_NO_HWIRQS)
        *g_p_PIC_irq2vpr[irqNr] |= ((priority << PIC_IVPR_PRIORITY_LAST_BIT) & PIC_IVPR_PRIORITY_MASK);
}

/**
 * IRQ dispatcher, called from the IRQ template
 *
 * @param p_ctxt - pointer to interrupt saved context.
 */
void DoIrq(irqCtxt_t *p_ctxt)
{
    /* Dispatch to the configured IRQ handler */
    if (NULL != irqHandlerTab[p_ctxt->irqNr].handler)
        (*(irqHandlerTab[p_ctxt->irqNr].handler))(p_ctxt, irqHandlerTab[p_ctxt->irqNr].data);
    else
        DefaultIrqHandler(p_ctxt, 0);
}

/**
 * Exception dispatcher, called from the exception template
 *
 * @param p_ctxt - pointer to interrupt saved context.
 */
void DoException(irqCtxt_t *p_ctxt)
{
    /* Dispatch to the configured IRQ handler */
    if (NULL != exceptionHandlerTab[p_ctxt->irqNr])
        (*(exceptionHandlerTab[p_ctxt->irqNr]))(p_ctxt);
    else
        UnexpectedExceptionHandler(p_ctxt);
}

/**
 * Resets the PIC interrupt subsystem
 */
static void PIC_reset_interrupts(void)
{
    int irq_index = 0;

    /* Following the steps from MPC8641DRM sec 9.5.1.1 */
    /* Step 1- Write the vector, priority, and polarity values in each interrupt’s
     * vector/priority register, leaving their MSK (mask) bit set.
     */

    /* Default VPR value is masked (disabled), priority = 0 (inhibited),
     * vector = irq number and polarity = high */
    for (irq_index = 0; irq_index < CONFIG_NO_HWIRQS; irq_index++)
    {
        uint32_t default_vpr = PIC_IVPR_MSK | (irq_index & PIC_IVPR_VECTOR_MASK);
        *((volatile uint32_t *)(g_p_PIC_irq2vpr[irq_index])) =
            (g_PIC_irq_flags[irq_index] & PIC_HAS_POLARITY_FLAG) ?
                                    (default_vpr | PIC_IVPR_P) :
                                    (default_vpr);
    }

    eieio();

    /* Make CPU0 the default destination for all interrupts */
    for (irq_index = 0; irq_index < CONFIG_NO_HWIRQS; irq_index++)
    {
        *g_p_PIC_irq2idr[irq_index] = (1 << 0);
    }

    /* Set spurious interrupt register */
    immr->im_pic.svr = ((PIC_VECTOR_SPURIOUS) << PIC_IVPR_VECTOR_LAST_BIT) & PIC_IVPR_VECTOR_MASK;

    /* Step 2- Clear CTPR (Current Task Priority Register) */
    io_out32be(&immr->im_pic.ctpr, 0);

    /* Step 3- Program the PIC to mixed mode by setting GCR[M]. */
    io_out32be(&immr->im_pic.gcr, PIC_GCR_M);

    /* Step 4- Clear the MSK bit in the vector/priority registers to be used. */
    /* ==== Skipped: Done when configuring the sources themselves ==== */

    /* Step 5- Perform a software loop to clear all pending interrupts */
    PIC_reset_interrupts_local();

    /* Step 6- Set the processor core CTPR values to the desired values. */
    /* ==== Skipped: left at 0 to enable all priorities (see step 2 above) */

    /* Step 7- Read the MSIRs to clear any pending message signaled interrupts
     * that may have been pending before a soft reset.
     */
    for (int msir_index = 0; msir_index < CONFIG_PIC_NUM_MSIR; msir_index ++)
    {
        (void)(*g_p_PIC_msir[msir_index]);
    }

    /* Step 8- Set MER to 0x0000_000F. See Section 9.3.5.2, "Message Enable Register (MER)"
     * of the MPC8641DRM for more information.
     */
    immr->im_pic.mer = 0x0000000F;
}

/**
 * Resets the PIC interrupt system for the local (current) processor using the
 * per-cpu registers. Calling this function prevents any spurious interrupts
 * and keeps the current CPU ready to receive further interrupts.
 *
 * Follows the steps from MPC8641DRM sec 9.5.1.1, although only those that
 * affect a local CPU after the global init.
 */
static void PIC_reset_interrupts_local(void)
{
    /* Step 2- Clear CTPR (Current Task Priority Register) */
    io_out32be(&immr->im_pic.ctpr, 0);

    /* Step 5- Perform a software loop to clear all pending interrupts:
     *  — Load counter with FRR[NIRQ].
     *  — While counter > 0, read IACK and write EOI to guarantee all the IPR and ISR bits are cleared.
     */
    for (int irq_index = 0; irq_index < CONFIG_NO_HWIRQS; irq_index++)
    {
        io_in32be(&immr->im_pic.iack);
        io_out32be(&immr->im_pic.eoi, 0);
    }
}

/**
 * Initialize the PIC. This resets the entire PIC module and sets
 * the vector of every IRQ to sane values
 */
static void PIC_init(void)
{
    /* Time-out on operations to prevent full hanging. This value is much
     * causes a time-out time longer than any of the following operations
     * could take to finish.
     */
    int32_t timeout = 1000;

    /* Force reset in PIC memory map, even if absent */
    immr->im_pic.gcr |= PIC_GCR_RST;
    eieio();

    /* Wait for GCR to automatically return to 0 (with time-out to prevent hanging */
    while(!(0 == (immr->im_pic.gcr & PIC_GCR_RST)) &&
           (timeout-- > 0))
    {
        /* Busy wait */
    }

    /* Reset other aspects of the PIC that are not reset by GCR[RST] */
    PIC_reset_interrupts();
}
