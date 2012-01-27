/**
 * @file immap_86xx.h
 *
 * @brief MPC86xx Internal Memory Map from U-Boot 10-03
 *
 * @date Created on: 19/08/2010
 *
 * @author Tennessee Carmel-Veilleux (tennessee.carmelveilleux -at- gmail.com)
 *
 * @version 1.0 $Rev$
 *
 * MPC86xx Internal Memory Map from U-Boot 10-03
 * - Based on earlier versions by Gleb Natapov <gnatapov@mrv.com>,
 *   Xianghua Xiao <x.xiao@motorola.com>, Eran Liberty (liberty@freescale.com),
 *   and Jeff Brown.
 * - Some bits are taken from linux drivers written by adrian@humboldt.co.uk.
 * - Some formatting and major corrections to the PIC memory map by Tennessee
 *   Carmel-Veilleux.
 */
/**
 * Copyright(c) 2004 Freescale Semiconductor
 * Jeff Brown (Jeffrey@freescale.com)
 * Srikanth Srinivasan (srikanth.srinivasan@freescale.com)
 *
 * I2C portions:
 * Copyright 2006 Freescale Semiconductor, Inc.
 *
 * DMA portions:
 * Copyright 2006 Freescale Semiconductor, Inc.
 *
 * Leftover:
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

#ifndef __IMMAP_86xx__
#define __IMMAP_86xx__

/* Local-Access Registers and MCM Registers(0x0000-0x2000) */
typedef struct ccsr_local_mcm {
        uint32_t	ccsrbar;	/* 0x0 - Control Configuration Status Registers Base Address Register */
        uint8_t	res1[4];
        uint32_t	altcbar;	/* 0x8 - Alternate Configuration Base Address Register */
        uint8_t	res2[4];
        uint32_t	altcar;		/* 0x10 - Alternate Configuration Attribute Register */
        uint8_t	res3[12];
        uint32_t	bptr;		/* 0x20 - Boot Page Translation Register */
        uint8_t	res4[3044];
        uint32_t	lawbar0;	/* 0xc08 - Local Access Window 0 Base Address Register */
        uint8_t	res5[4];
        uint32_t	lawar0;		/* 0xc10 - Local Access Window 0 Attributes Register */
        uint8_t	res6[20];
        uint32_t	lawbar1;	/* 0xc28 - Local Access Window 1 Base Address Register */
        uint8_t	res7[4];
        uint32_t	lawar1;		/* 0xc30 - Local Access Window 1 Attributes Register */
        uint8_t	res8[20];
        uint32_t	lawbar2;	/* 0xc48 - Local Access Window 2 Base Address Register */
        uint8_t	res9[4];
        uint32_t	lawar2;		/* 0xc50 - Local Access Window 2 Attributes Register */
        uint8_t	res10[20];
        uint32_t	lawbar3;	/* 0xc68 - Local Access Window 3 Base Address Register */
        uint8_t	res11[4];
        uint32_t	lawar3;		/* 0xc70 - Local Access Window 3 Attributes Register */
        uint8_t	res12[20];
        uint32_t	lawbar4;	/* 0xc88 - Local Access Window 4 Base Address Register */
        uint8_t	res13[4];
        uint32_t	lawar4;		/* 0xc90 - Local Access Window 4 Attributes Register */
        uint8_t	res14[20];
        uint32_t	lawbar5;	/* 0xca8 - Local Access Window 5 Base Address Register */
        uint8_t	res15[4];
        uint32_t	lawar5;		/* 0xcb0 - Local Access Window 5 Attributes Register */
        uint8_t	res16[20];
        uint32_t	lawbar6;	/* 0xcc8 - Local Access Window 6 Base Address Register */
        uint8_t	res17[4];
        uint32_t	lawar6;		/* 0xcd0 - Local Access Window 6 Attributes Register */
        uint8_t	res18[20];
        uint32_t	lawbar7;	/* 0xce8 - Local Access Window 7 Base Address Register */
        uint8_t	res19[4];
        uint32_t	lawar7;		/* 0xcf0 - Local Access Window 7 Attributes Register */
        uint8_t	res20[20];
        uint32_t	lawbar8;	/* 0xd08 - Local Access Window 8 Base Address Register */
        uint8_t	res21[4];
        uint32_t	lawar8;		/* 0xd10 - Local Access Window 8 Attributes Register */
        uint8_t	res22[20];
        uint32_t	lawbar9;	/* 0xd28 - Local Access Window 9 Base Address Register */
        uint8_t	res23[4];
        uint32_t	lawar9;		/* 0xd30 - Local Access Window 9 Attributes Register */
        uint8_t	res24[716];
        uint32_t	abcr;		/* 0x1000 - MCM CCB Address Configuration Register */
        uint8_t	res25[4];
        uint32_t    dbcr;           /* 0x1008 - MCM MPX data bus Configuration Register */
        uint8_t	res26[4];
        uint32_t	pcr;		/* 0x1010 - MCM CCB Port Configuration Register */
        uint8_t	res27[44];
        uint32_t	hpmr0;		/* 0x1040 - MCM HPM Threshold Count Register 0 */
        uint32_t	hpmr1;		/* 0x1044 - MCM HPM Threshold Count Register 1 */
        uint32_t	hpmr2;		/* 0x1048 - MCM HPM Threshold Count Register 2 */
        uint32_t	hpmr3;		/* 0x104c - MCM HPM Threshold Count Register 3 */
        uint8_t	res28[16];
        uint32_t	hpmr4;		/* 0x1060 - MCM HPM Threshold Count Register 4 */
        uint32_t	hpmr5;		/* 0x1064 - MCM HPM Threshold Count Register 5 */
        uint32_t	hpmccr;		/* 0x1068 - MCM HPM Cycle Count Register */
        uint8_t	res29[3476];
        uint32_t	edr;		/* 0x1e00 - MCM Error Detect Register */
        uint8_t	res30[4];
        uint32_t	eer;		/* 0x1e08 - MCM Error Enable Register */
        uint32_t	eatr;		/* 0x1e0c - MCM Error Attributes Capture Register */
        uint32_t	eladr;		/* 0x1e10 - MCM Error Low Address Capture Register */
        uint32_t	ehadr;		/* 0x1e14 - MCM Error High Address Capture Register */
        uint8_t	res31[488];
} ccsr_local_mcm_t;

/* DDR memory controller registers(0x2000-0x3000) and (0x6000-0x7000) */

typedef struct ccsr_ddr {
        uint32_t	cs0_bnds;		/* 0x2000 - DDR Chip Select 0 Memory Bounds */
        uint8_t	res1[4];
        uint32_t	cs1_bnds;		/* 0x2008 - DDR Chip Select 1 Memory Bounds */
        uint8_t	res2[4];
        uint32_t	cs2_bnds;		/* 0x2010 - DDR Chip Select 2 Memory Bounds */
        uint8_t	res3[4];
        uint32_t	cs3_bnds;		/* 0x2018 - DDR Chip Select 3 Memory Bounds */
        uint8_t	res4[4];
        uint32_t	cs4_bnds;		/* 0x2020 - DDR Chip Select 4 Memory Bounds */
        uint8_t	res5[4];
        uint32_t	cs5_bnds;		/* 0x2028 - DDR Chip Select 5 Memory Bounds */
        uint8_t	res6[84];
        uint32_t	cs0_config;		/* 0x2080 - DDR Chip Select Configuration */
        uint32_t	cs1_config;		/* 0x2084 - DDR Chip Select Configuration */
        uint32_t	cs2_config;		/* 0x2088 - DDR Chip Select Configuration */
        uint32_t	cs3_config;		/* 0x208c - DDR Chip Select Configuration */
        uint32_t	cs4_config;		/* 0x2090 - DDR Chip Select Configuration */
        uint32_t	cs5_config;		/* 0x2094 - DDR Chip Select Configuration */
        uint8_t	res7[104];
        uint32_t	timing_cfg_3;		/* 0x2100 - DDR SDRAM Timing Configuration Register 3 */
        uint32_t	timing_cfg_0;		/* 0x2104 - DDR SDRAM Timing Configuration Register 0 */
        uint32_t	timing_cfg_1;		/* 0x2108 - DDR SDRAM Timing Configuration Register 1 */
        uint32_t	timing_cfg_2;		/* 0x210c - DDR SDRAM Timing Configuration Register 2 */
        uint32_t	sdram_cfg;		/* 0x2110 - DDR SDRAM Control Configuration 1 */
        uint32_t    sdram_cfg_2;            /* 0x2114 - DDR SDRAM Control Configuration 2 */
        uint32_t	sdram_mode;		/* 0x2118 - DDR SDRAM Mode Configuration 1 */
        uint32_t    sdram_mode_2;		/* 0x211c - DDR SDRAM Mode Configuration 2 */
        uint32_t    sdram_mode_cntl;        /* 0x2120 - DDR SDRAM Mode Control */
        uint32_t	sdram_interval;		/* 0x2124 - DDR SDRAM Interval Configuration */
        uint32_t    sdram_data_init;	/* 0x2128 - DDR SDRAM Data Initialization */
        uint8_t	res8[4];
        uint32_t	sdram_clk_cntl;		/* 0x2130 - DDR SDRAM Clock Control */
        uint8_t    res9[12];
        uint32_t    sdram_ocd_cntl;		/* 0x2140 - DDR SDRAM OCD Control */
        uint32_t    sdram_ocd_status;	/* 0x2144 - DDR SDRAM OCD Status */
        uint32_t    init_addr;		/* 0x2148 - DDR training initialzation address */
        uint32_t    init_ext_addr;		/* 0x214C - DDR training initialzation extended address */
        uint8_t    res10[2728];
        uint32_t    ip_rev1;		/* 0x2BF8 - DDR IP Block Revision 1 */
        uint32_t    ip_rev2;		/* 0x2BFC - DDR IP Block Revision 2 */
        uint8_t	res11[512];
        uint32_t	data_err_inject_hi;	/* 0x2e00 - DDR Memory Data Path Error Injection Mask High */
        uint32_t	data_err_inject_lo;	/* 0x2e04 - DDR Memory Data Path Error Injection Mask Low */
        uint32_t	ecc_err_inject;		/* 0x2e08 - DDR Memory Data Path Error Injection Mask ECC */
        uint8_t	res12[20];
        uint32_t	capture_data_hi;	/* 0x2e20 - DDR Memory Data Path Read Capture High */
        uint32_t	capture_data_lo;	/* 0x2e24 - DDR Memory Data Path Read Capture Low */
        uint32_t	capture_ecc;		/* 0x2e28 - DDR Memory Data Path Read Capture ECC */
        uint8_t	res13[20];
        uint32_t	err_detect;		/* 0x2e40 - DDR Memory Error Detect */
        uint32_t	err_disable;		/* 0x2e44 - DDR Memory Error Disable */
        uint32_t	err_int_en;		/* 0x2e48 - DDR Memory Error Interrupt Enable */
        uint32_t	capture_attributes;	/* 0x2e4c - DDR Memory Error Attributes Capture */
        uint32_t	capture_address;	/* 0x2e50 - DDR Memory Error Address Capture */
        uint32_t	capture_ext_address;	/* 0x2e54 - DDR Memory Error Extended Address Capture */
        uint32_t	err_sbe;		/* 0x2e58 - DDR Memory Single-Bit ECC Error Management */
        uint8_t	res14[164];
        uint32_t	debug_1;		/* 0x2f00 */
        uint32_t	debug_2;
        uint32_t	debug_3;
        uint32_t	debug_4;
        uint32_t	debug_5;
        uint8_t	res15[236];
} ccsr_ddr_t;

typedef struct fsl_i2c {

        uint8_t adr;		/* I2C slave address */
        uint8_t res0[3];
#define I2C_ADR		0xFE
#define I2C_ADR_SHIFT	1
#define I2C_ADR_RES	~(I2C_ADR)

        uint8_t fdr;		/* I2C frequency divider register */
        uint8_t res1[3];
#define IC2_FDR		0x3F
#define IC2_FDR_SHIFT	0
#define IC2_FDR_RES	~(IC2_FDR)

        uint8_t cr;		/* I2C control redister	*/
        uint8_t res2[3];
#define I2C_CR_MEN	0x80
#define I2C_CR_MIEN	0x40
#define I2C_CR_MSTA	0x20
#define I2C_CR_MTX	0x10
#define I2C_CR_TXAK	0x08
#define I2C_CR_RSTA	0x04
#define I2C_CR_BCST	0x01

        uint8_t sr;		/* I2C status register */
        uint8_t res3[3];
#define I2C_SR_MCF	0x80
#define I2C_SR_MAAS	0x40
#define I2C_SR_MBB	0x20
#define I2C_SR_MAL	0x10
#define I2C_SR_BCSTM	0x08
#define I2C_SR_SRW	0x04
#define I2C_SR_MIF	0x02
#define I2C_SR_RXAK	0x01

        uint8_t dr;		/* I2C data register */
        uint8_t res4[3];
#define I2C_DR		0xFF
#define I2C_DR_SHIFT	0
#define I2C_DR_RES	~(I2C_DR)

        uint8_t dfsrr;	/* I2C digital filter sampling rate register */
        uint8_t res5[3];
#define I2C_DFSRR	0x3F
#define I2C_DFSRR_SHIFT	0
#define I2C_DFSRR_RES	~(I2C_DR)

        /* Fill out the reserved block */
        uint8_t res6[0xE8];
} fsl_i2c_t;

/* Dual I2C Registers(0x3000-0x4000) */
typedef struct ccsr_i2c {
        struct fsl_i2c	i2c[2];
        uint8_t	res[4096 - 2 * sizeof(struct fsl_i2c)];
} ccsr_i2c_t;

/* DUART Registers(0x4000-0x5000) */
typedef struct ccsr_duart {
        uint8_t	res1[1280];
        uint8_t	urbr1_uthr1_udlb1;/* 0x4500 - URBR1, UTHR1, UDLB1 with the same address offset of 0x04500 */
        uint8_t	uier1_udmb1;	/* 0x4501 - UIER1, UDMB1 with the same address offset of 0x04501 */
        uint8_t	uiir1_ufcr1_uafr1;/* 0x4502 - UIIR1, UFCR1, UAFR1 with the same address offset of 0x04502 */
        uint8_t	ulcr1;		/* 0x4503 - UART1 Line Control Register */
        uint8_t	umcr1;		/* 0x4504 - UART1 Modem Control Register */
        uint8_t	ulsr1;		/* 0x4505 - UART1 Line Status Register */
        uint8_t	umsr1;		/* 0x4506 - UART1 Modem Status Register */
        uint8_t	uscr1;		/* 0x4507 - UART1 Scratch Register */
        uint8_t	res2[8];
        uint8_t	udsr1;		/* 0x4510 - UART1 DMA Status Register */
        uint8_t	res3[239];
        uint8_t	urbr2_uthr2_udlb2;/* 0x4600 - URBR2, UTHR2, UDLB2 with the same address offset of 0x04600 */
        uint8_t	uier2_udmb2;	/* 0x4601 - UIER2, UDMB2 with the same address offset of 0x04601 */
        uint8_t	uiir2_ufcr2_uafr2;/* 0x4602 - UIIR2, UFCR2, UAFR2 with the same address offset of 0x04602 */
        uint8_t	ulcr2;		/* 0x4603 - UART2 Line Control Register */
        uint8_t	umcr2;		/* 0x4604 - UART2 Modem Control Register */
        uint8_t	ulsr2;		/* 0x4605 - UART2 Line Status Register */
        uint8_t	umsr2;		/* 0x4606 - UART2 Modem Status Register */
        uint8_t	uscr2;		/* 0x4607 - UART2 Scratch Register */
        uint8_t	res4[8];
        uint8_t	udsr2;		/* 0x4610 - UART2 DMA Status Register */
        uint8_t	res5[2543];
} ccsr_duart_t;


/* Local Bus Controller Registers(0x5000-0x6000) */
typedef struct ccsr_lbc {
        uint32_t	br0;		/* 0x5000 - LBC Base Register 0 */
        uint32_t	or0;		/* 0x5004 - LBC Options Register 0 */
        uint32_t	br1;		/* 0x5008 - LBC Base Register 1 */
        uint32_t	or1;		/* 0x500c - LBC Options Register 1 */
        uint32_t	br2;		/* 0x5010 - LBC Base Register 2 */
        uint32_t	or2;		/* 0x5014 - LBC Options Register 2 */
        uint32_t	br3;		/* 0x5018 - LBC Base Register 3 */
        uint32_t	or3;		/* 0x501c - LBC Options Register 3 */
        uint32_t	br4;		/* 0x5020 - LBC Base Register 4 */
        uint32_t	or4;		/* 0x5024 - LBC Options Register 4 */
        uint32_t	br5;		/* 0x5028 - LBC Base Register 5 */
        uint32_t	or5;		/* 0x502c - LBC Options Register 5 */
        uint32_t	br6;		/* 0x5030 - LBC Base Register 6 */
        uint32_t	or6;		/* 0x5034 - LBC Options Register 6 */
        uint32_t	br7;		/* 0x5038 - LBC Base Register 7 */
        uint32_t	or7;		/* 0x503c - LBC Options Register 7 */
        uint8_t	res1[40];
        uint32_t	mar;		/* 0x5068 - LBC UPM Address Register */
        uint8_t	res2[4];
        uint32_t	mamr;		/* 0x5070 - LBC UPMA Mode Register */
        uint32_t	mbmr;		/* 0x5074 - LBC UPMB Mode Register */
        uint32_t	mcmr;		/* 0x5078 - LBC UPMC Mode Register */
        uint8_t	res3[8];
        uint32_t	mrtpr;		/* 0x5084 - LBC Memory Refresh Timer Prescaler Register */
        uint32_t	mdr;		/* 0x5088 - LBC UPM Data Register */
        uint8_t	res4[8];
        uint32_t	lsdmr;		/* 0x5094 - LBC SDRAM Mode Register */
        uint8_t	res5[8];
        uint32_t	lurt;		/* 0x50a0 - LBC UPM Refresh Timer */
        uint32_t	lsrt;		/* 0x50a4 - LBC SDRAM Refresh Timer */
        uint8_t	res6[8];
        uint32_t	ltesr;		/* 0x50b0 - LBC Transfer Error Status Register */
        uint32_t	ltedr;		/* 0x50b4 - LBC Transfer Error Disable Register */
        uint32_t	lteir;		/* 0x50b8 - LBC Transfer Error Interrupt Register */
        uint32_t	lteatr;		/* 0x50bc - LBC Transfer Error Attributes Register */
        uint32_t	ltear;		/* 0x50c0 - LBC Transfer Error Address Register */
        uint8_t	res7[12];
        uint32_t	lbcr;		/* 0x50d0 - LBC Configuration Register */
        uint32_t	lcrr;		/* 0x50d4 - LBC Clock Ratio Register */
        uint8_t	res8[3880];
} ccsr_lbc_t;

/* PCI Express Registers(0x8000-0x9000) and (0x9000-0xA000) */
typedef struct ccsr_pex {
        uint32_t	cfg_addr;	/* 0x8000 - PEX Configuration Address Register */
        uint32_t	cfg_data;	/* 0x8004 - PEX Configuration Data Register */
        uint8_t	res1[4];
        uint32_t	out_comp_to;	/* 0x800C - PEX Outbound Completion Timeout Register */
        uint8_t	res2[16];
        uint32_t	pme_msg_det;	/* 0x8020 - PEX PME & message detect register */
        uint32_t    pme_msg_int_en;	/* 0x8024 - PEX PME & message interrupt enable register */
        uint32_t    pme_msg_dis;	/* 0x8028 - PEX PME & message disable register */
        uint32_t    pm_command;	/* 0x802c - PEX PM Command register */
        uint8_t	res3[3016];
        uint32_t    block_rev1;	/* 0x8bf8 - PEX Block Revision register 1 */
        uint32_t    block_rev2;	/* 0x8bfc - PEX Block Revision register 2 */
        uint32_t	potar0;	        /* 0x8c00 - PEX Outbound Transaction Address Register 0 */
        uint32_t	potear0;	/* 0x8c04 - PEX Outbound Translation Extended Address Register 0 */
        uint8_t	res4[8];
        uint32_t	powar0;	        /* 0x8c10 - PEX Outbound Window Attributes Register 0 */
        uint8_t	res5[12];
        uint32_t	potar1;	        /* 0x8c20 - PEX Outbound Transaction Address Register 1 */
        uint32_t	potear1;	/* 0x8c24 - PEX Outbound Translation Extended Address Register 1 */
        uint32_t	powbar1;	/* 0x8c28 - PEX Outbound Window Base Address Register 1 */
        uint8_t	res6[4];
        uint32_t	powar1;	        /* 0x8c30 - PEX Outbound Window Attributes Register 1 */
        uint8_t	res7[12];
        uint32_t	potar2;	        /* 0x8c40 - PEX Outbound Transaction Address Register 2 */
        uint32_t	potear2;	/* 0x8c44 - PEX Outbound Translation Extended Address Register 2 */
        uint32_t	powbar2;	/* 0x8c48 - PEX Outbound Window Base Address Register 2 */
        uint8_t	res8[4];
        uint32_t	powar2;	        /* 0x8c50 - PEX Outbound Window Attributes Register 2 */
        uint8_t	res9[12];
        uint32_t	potar3;	        /* 0x8c60 - PEX Outbound Transaction Address Register 3 */
        uint32_t	potear3;	/* 0x8c64 - PEX Outbound Translation Extended Address Register 3 */
        uint32_t	powbar3;	/* 0x8c68 - PEX Outbound Window Base Address Register 3 */
        uint8_t	res10[4];
        uint32_t	powar3;	        /* 0x8c70 - PEX Outbound Window Attributes Register 3 */
        uint8_t	res11[12];
        uint32_t	potar4;	        /* 0x8c80 - PEX Outbound Transaction Address Register 4 */
        uint32_t	potear4;	/* 0x8c84 - PEX Outbound Translation Extended Address Register 4 */
        uint32_t	powbar4;	/* 0x8c88 - PEX Outbound Window Base Address Register 4 */
        uint8_t	res12[4];
        uint32_t	powar4;	        /* 0x8c90 - PEX Outbound Window Attributes Register 4 */
        uint8_t	res13[12];
        uint8_t	res14[256];
        uint32_t	pitar3;	        /* 0x8da0 - PEX Inbound Translation Address Register 3  */
        uint8_t	res15[4];
        uint32_t	piwbar3;	/* 0x8da8 - PEX Inbound Window Base Address Register 3 */
        uint32_t	piwbear3;	/* 0x8dac - PEX Inbound Window Base Extended Address Register 3 */
        uint32_t	piwar3;	        /* 0x8db0 - PEX Inbound Window Attributes Register 3 */
        uint8_t	res16[12];
        uint32_t	pitar2;	        /* 0x8dc0 - PEX Inbound Translation Address Register 2  */
        uint8_t	res17[4];
        uint32_t	piwbar2;	/* 0x8dc8 - PEX Inbound Window Base Address Register 2 */
        uint32_t	piwbear2;	/* 0x8dcc - PEX Inbound Window Base Extended Address Register 2 */
        uint32_t	piwar2;	        /* 0x8dd0 - PEX Inbound Window Attributes Register 2 */
        uint8_t	res18[12];
        uint32_t	pitar1;	        /* 0x8de0 - PEX Inbound Translation Address Register 1  */
        uint8_t	res19[4];
        uint32_t	piwbar1;	/* 0x8de8 - PEX Inbound Window Base Address Register 1 */
        uint32_t	piwbear1;
        uint32_t	piwar1;	        /* 0x8df0 - PEX Inbound Window Attributes Register 1 */
        uint8_t	res20[12];
        uint32_t	pedr;		/* 0x8e00 - PEX Error Detect Register */
        uint8_t    res21[4];
        uint32_t	peer;		/* 0x8e08 - PEX Error Interrupt Enable Register */
        uint8_t    res22[4];
        uint32_t	pecdr;		/* 0x8e10 - PEX Error Disable Register */
        uint8_t    res23[12];
        uint32_t	peer_stat;	/* 0x8e20 - PEX Error Capture Status Register */
        uint8_t    res24[4];
        uint32_t	perr_cap0;	/* 0x8e28 - PEX Error Capture Register 0 */
        uint32_t	perr_cap1;	/* 0x8e2c - PEX Error Capture Register 1 */
        uint32_t	perr_cap2;	/* 0x8e30 - PEX Error Capture Register 2 */
        uint32_t	perr_cap3;	/* 0x8e34 - PEX Error Capture Register 3 */
        uint8_t	res25[452];
        uint8_t    res26[4];
} ccsr_pex_t;

/* Hyper Transport Register Block (0xA000-0xB000) */
typedef struct ccsr_ht {
        uint32_t    hcfg_addr;      /* 0xa000 - HT Configuration Address register */
        uint32_t    hcfg_data;      /* 0xa004 - HT Configuration Data register */
        uint8_t	res1[3064];
        uint32_t    howtar0;        /* 0xac00 - HT Outbound Window 0 Translation register */
        uint8_t	res2[12];
        uint32_t    howar0;         /* 0xac10 - HT Outbound Window 0 Attributes register */
        uint8_t	res3[12];
        uint32_t    howtar1;        /* 0xac20 - HT Outbound Window 1 Translation register */
        uint8_t	res4[4];
        uint32_t    howbar1;        /* 0xac28 - HT Outbound Window 1 Base Address register */
        uint8_t	res5[4];
        uint32_t    howar1;         /* 0xac30 - HT Outbound Window 1 Attributes register */
        uint8_t	res6[12];
        uint32_t    howtar2;        /* 0xac40 - HT Outbound Window 2 Translation register */
        uint8_t	res7[4];
        uint32_t    howbar2;        /* 0xac48 - HT Outbound Window 2 Base Address register */
        uint8_t	res8[4];
        uint32_t    howar2;         /* 0xac50 - HT Outbound Window 2 Attributes register */
        uint8_t	res9[12];
        uint32_t    howtar3;        /* 0xac60 - HT Outbound Window 3 Translation register */
        uint8_t	res10[4];
        uint32_t    howbar3;        /* 0xac68 - HT Outbound Window 3 Base Address register */
        uint8_t	res11[4];
        uint32_t    howar3;         /* 0xac70 - HT Outbound Window 3 Attributes  register */
        uint8_t	res12[12];
        uint32_t    howtar4;        /* 0xac80 - HT Outbound Window 4 Translation register */
        uint8_t	res13[4];
        uint32_t    howbar4;        /* 0xac88 - HT Outbound Window 4 Base Address register */
        uint8_t	res14[4];
        uint32_t    howar4;         /* 0xac90 - HT Outbound Window 4 Attributes register */
        uint8_t	res15[236];
        uint32_t    hiwtar4;        /* 0xad80 - HT Inbound Window 4 Translation register */
        uint8_t	res16[4];
        uint32_t    hiwbar4;        /* 0xad88 - HT Inbound Window 4 Base Address register */
        uint8_t	res17[4];
        uint32_t    hiwar4;         /* 0xad90 - HT Inbound Window 4 Attributes register */
        uint8_t	res18[12];
        uint32_t    hiwtar3;        /* 0xada0 - HT Inbound Window 3 Translation register */
        uint8_t	res19[4];
        uint32_t    hiwbar3;        /* 0xada8 - HT Inbound Window 3 Base Address register */
        uint8_t	res20[4];
        uint32_t    hiwar3;         /* 0xadb0 - HT Inbound Window 3 Attributes register */
        uint8_t	res21[12];
        uint32_t    hiwtar2;        /* 0xadc0 - HT Inbound Window 2 Translation register */
        uint8_t	res22[4];
        uint32_t    hiwbar2;        /* 0xadc8 - HT Inbound Window 2 Base Address register */
        uint8_t	res23[4];
        uint32_t    hiwar2;         /* 0xadd0 - HT Inbound Window 2 Attributes register */
        uint8_t	res24[12];
        uint32_t    hiwtar1;        /* 0xade0 - HT Inbound Window 1 Translation register */
        uint8_t	res25[4];
        uint32_t    hiwbar1;        /* 0xade8 - HT Inbound Window 1 Base Address register */
        uint8_t	res26[4];
        uint32_t    hiwar1;         /* 0xadf0 - HT Inbound Window 1 Attributes register */
        uint8_t	res27[12];
        uint32_t    hedr;           /* 0xae00 - HT Error Detect register */
        uint8_t	res28[4];
        uint32_t    heier;          /* 0xae08 - HT Error Interrupt Enable register */
        uint8_t	res29[4];
        uint32_t    hecdr;          /* 0xae10 - HT Error Capture Disbale register */
        uint8_t	res30[12];
        uint32_t    hecsr;          /* 0xae20 - HT Error Capture Status register */
        uint8_t	res31[4];
        uint32_t    hec0;           /* 0xae28 - HT Error Capture 0 register */
        uint32_t    hec1;           /* 0xae2c - HT Error Capture 1 register */
        uint32_t    hec2;           /* 0xae30 - HT Error Capture 2 register */
        uint8_t    res32[460];
} ccsr_ht_t;

typedef struct fsl_dma {
        uint32_t	mr;		/* DMA mode register */
#define FSL_DMA_MR_CS		0x00000001	/* Channel start */
#define FSL_DMA_MR_CC		0x00000002	/* Channel continue */
#define FSL_DMA_MR_CTM		0x00000004	/* Channel xfer mode */
#define FSL_DMA_MR_CTM_DIRECT	0x00000004	/* Direct channel xfer mode */
#define FSL_DMA_MR_CA		0x00000008	/* Channel abort */
#define FSL_DMA_MR_CDSM		0x00000010
#define FSL_DMA_MR_XFE		0x00000020	/* Extended features en */
#define FSL_DMA_MR_EIE		0x00000040	/* Error interrupt en */
#define FSL_DMA_MR_EOLSIE	0x00000080	/* End-of-lists interrupt en */
#define FSL_DMA_MR_EOLNIE	0x00000100	/* End-of-links interrupt en */
#define FSL_DMA_MR_EOSIE	0x00000200	/* End-of-seg interrupt en */
#define FSL_DMA_MR_SRW		0x00000400	/* Single register write */
#define FSL_DMA_MR_SAHE		0x00001000	/* Source addr hold enable */
#define FSL_DMA_MR_DAHE		0x00002000	/* Dest addr hold enable */
#define FSL_DMA_MR_SAHTS_MASK	0x0000c000	/* Source addr hold xfer size */
#define FSL_DMA_MR_DAHTS_MASK	0x00030000	/* Dest addr hold xfer size */
#define FSL_DMA_MR_EMS_EN	0x00040000	/* Ext master start en */
#define FSL_DMA_MR_EMP_EN	0x00200000	/* Ext master pause en */
#define FSL_DMA_MR_BWC_MASK	0x0f000000	/* Bandwidth/pause ctl */
#define FSL_DMA_MR_BWC_DIS	0x0f000000	/* Bandwidth/pause ctl disable */
        uint32_t	sr;		/* DMA status register */
#define FSL_DMA_SR_EOLSI	0x00000001	/* End-of-list interrupt */
#define FSL_DMA_SR_EOSI		0x00000002	/* End-of-segment interrupt */
#define FSL_DMA_SR_CB		0x00000004	/* Channel busy */
#define FSL_DMA_SR_EOLNI	0x00000008	/* End-of-links interrupt */
#define FSL_DMA_SR_PE		0x00000010	/* Programming error */
#define FSL_DMA_SR_CH		0x00000020	/* Channel halted */
#define FSL_DMA_SR_TE		0x00000080	/* Transfer error */
        uint8_t	res0[4];
        uint32_t	clndar;		/* DMA current link descriptor address register */
        uint32_t	satr;		/* DMA source attributes register */
#define FSL_DMA_SATR_ESAD_MASK		0x000001ff	/* Extended source addr */
#define FSL_DMA_SATR_SREAD_NO_SNOOP	0x00040000	/* Read, don't snoop */
#define FSL_DMA_SATR_SREAD_SNOOP	0x00050000	/* Read, snoop */
#define FSL_DMA_SATR_SREAD_UNLOCK	0x00070000	/* Read, unlock l2 */
#define FSL_DMA_SATR_STRAN_MASK		0x00f00000	/* Source interface  */
#define FSL_DMA_SATR_SSME		0x01000000	/* Source stride en */
#define FSL_DMA_SATR_SPCIORDER		0x02000000	/* PCI transaction order */
#define FSL_DMA_SATR_STFLOWLVL_MASK	0x0c000000	/* RIO flow level */
#define FSL_DMA_SATR_SBPATRMU		0x20000000	/* Bypass ATMU */
        uint32_t	sar;		/* DMA source address register */
        uint32_t	datr;		/* DMA destination attributes register */
#define FSL_DMA_DATR_EDAD_MASK		0x000001ff	/* Extended dest addr */
#define FSL_DMA_DATR_DWRITE_NO_SNOOP	0x00040000	/* Write, don't snoop */
#define FSL_DMA_DATR_DWRITE_SNOOP	0x00050000	/* Write, snoop */
#define FSL_DMA_DATR_DWRITE_ALLOC	0x00060000	/* Write, alloc l2 */
#define FSL_DMA_DATR_DWRITE_LOCK	0x00070000	/* Write, lock l2 */
#define FSL_DMA_DATR_DTRAN_MASK		0x00f00000	/* Dest interface  */
#define FSL_DMA_DATR_DSME		0x01000000	/* Dest stride en */
#define FSL_DMA_DATR_DPCIORDER		0x02000000	/* PCI transaction order */
#define FSL_DMA_DATR_DTFLOWLVL_MASK	0x0c000000	/* RIO flow level */
#define FSL_DMA_DATR_DBPATRMU		0x20000000	/* Bypass ATMU */
        uint32_t	dar;		/* DMA destination address register */
        uint32_t	bcr;		/* DMA byte count register */
        uint8_t	res1[4];
        uint32_t	nlndar;		/* DMA next link descriptor address register */
        uint8_t	res2[8];
        uint32_t	clabdar;	/* DMA current List - alternate base descriptor address Register */
        uint8_t	res3[4];
        uint32_t	nlsdar;		/* DMA next list descriptor address register */
        uint32_t	ssr;		/* DMA source stride register */
        uint32_t	dsr;		/* DMA destination stride register */
        uint8_t	res4[56];
} fsl_dma_t;

/* DMA Registers(0x2_1000-0x2_2000) */
typedef struct ccsr_dma {
        uint8_t	res1[256];
        struct fsl_dma dma[4];
        uint32_t	dgsr;		/* 0x21300 - DMA General Status Register */
        uint8_t	res2[3324];
} ccsr_dma_t;

/* tsec1-4: 24000-28000 */
typedef struct ccsr_tsec {
        uint32_t    id;		/* 0x24000 - Controller ID Register */
        uint8_t	res1[12];
        uint32_t	ievent;		/* 0x24010 - Interrupt Event Register */
        uint32_t	imask;		/* 0x24014 - Interrupt Mask Register */
        uint32_t	edis;		/* 0x24018 - Error Disabled Register */
        uint8_t	res2[4];
        uint32_t	ecntrl;		/* 0x24020 - Ethernet Control Register */
        uint8_t    res2_1[4];
        uint32_t	ptv;		/* 0x24028 - Pause Time Value Register */
        uint32_t	dmactrl;	/* 0x2402c - DMA Control Register */
        uint32_t	tbipa;		/* 0x24030 - TBI PHY Address Register */
        uint8_t	res3[88];
        uint32_t	fifo_tx_thr;	/* 0x2408c - FIFO transmit threshold register */
        uint8_t	res4[8];
        uint32_t	fifo_tx_starve;	/* 0x24098 - FIFO transmit starve register */
        uint32_t	fifo_tx_starve_shutoff;/* 0x2409c - FIFO transmit starve shutoff register */
        uint8_t    res4_1[4];
        uint32_t    fifo_rx_pause;  /* 0x240a4 - FIFO receive pause threshold register */
        uint32_t    fifo_rx_alarm;  /* 0x240a8 - FIFO receive alarm threshold register */
        uint8_t	res5[84];
        uint32_t	tctrl;		/* 0x24100 - Transmit Control Register */
        uint32_t	tstat;		/* 0x24104 - Transmit Status Register */
        uint32_t    dfvlan;		/* 0x24108 - Default VLAN control word */
        uint8_t    res6[4];
        uint32_t    txic;		/* 0x24110 - Transmit interrupt coalescing Register */
        uint32_t    tqueue;         /* 0x24114 - Transmit Queue Control Register */
        uint8_t	res7[40];
        uint32_t    tr03wt;         /* 0x24140 - TxBD Rings 0-3 round-robin weightings */
        uint32_t    tw47wt;         /* 0x24144 - TxBD Rings 4-7 round-robin weightings */
        uint8_t    res8[52];
        uint32_t	tbdbph;	        /* 0x2417c - Transmit Data Buffer Pointer High Register */
        uint8_t    res9[4];
        uint32_t    tbptr0;         /* 0x24184 - Transmit Buffer Descriptor Pointer for Ring 0 */
        uint8_t    res10[4];
        uint32_t    tbptr1;         /* 0x2418C - Transmit Buffer Descriptor Pointer for Ring 1 */
        uint8_t    res11[4];
        uint32_t    tbptr2;         /* 0x24194 - Transmit Buffer Descriptor Pointer for Ring 2 */
        uint8_t    res12[4];
        uint32_t    tbptr3;         /* 0x2419C - Transmit Buffer Descriptor Pointer for Ring 3 */
        uint8_t    res13[4];
        uint32_t    tbptr4;         /* 0x241A4 - Transmit Buffer Descriptor Pointer for Ring 4 */
        uint8_t    res14[4];
        uint32_t    tbptr5;         /* 0x241AC - Transmit Buffer Descriptor Pointer for Ring 5 */
        uint8_t    res15[4];
        uint32_t    tbptr6;         /* 0x241B4 - Transmit Buffer Descriptor Pointer for Ring 6 */
        uint8_t    res16[4];
        uint32_t    tbptr7;         /* 0x241BC - Transmit Buffer Descriptor Pointer for Ring 7 */
        uint8_t    res17[64];
        uint32_t	tbaseh;		/* 0x24200 - Transmit Descriptor Base Address High Register */
        uint32_t	tbase0;		/* 0x24204 - Transmit Descriptor Base Address Register of Ring 0 */
        uint8_t    res18[4];
        uint32_t    tbase1;         /* 0x2420C - Transmit Descriptor base address of Ring 1 */
        uint8_t    res19[4];
        uint32_t    tbase2;         /* 0x24214 - Transmit Descriptor base address of Ring 2 */
        uint8_t    res20[4];
        uint32_t    tbase3;         /* 0x2421C - Transmit Descriptor base address of Ring 3 */
        uint8_t    res21[4];
        uint32_t    tbase4;         /* 0x24224 - Transmit Descriptor base address of Ring 4 */
        uint8_t    res22[4];
        uint32_t    tbase5;         /* 0x2422C - Transmit Descriptor base address of Ring 5 */
        uint8_t    res23[4];
        uint32_t    tbase6;         /* 0x24234 - Transmit Descriptor base address of Ring 6 */
        uint8_t    res24[4];
        uint32_t    tbase7;         /* 0x2423C - Transmit Descriptor base address of Ring 7 */
        uint8_t    res25[192];
        uint32_t	rctrl;		/* 0x24300 - Receive Control Register */
        uint32_t	rstat;		/* 0x24304 - Receive Status Register */
        uint8_t	res26[8];
        uint32_t    rxic;           /* 0x24310 - Receive Interrupt Coalecing Register */
        uint32_t    rqueue;         /* 0x24314 - Receive queue control register */
        uint8_t	res27[24];
        uint32_t    rbifx;		/* 0x24330 - Receive bit field extract control Register */
        uint32_t    rqfar;		/* 0x24334 - Receive queue filing table address Register */
        uint32_t    rqfcr;		/* 0x24338 - Receive queue filing table control Register */
        uint32_t    rqfpr;		/* 0x2433c - Receive queue filing table property Register */
        uint32_t	mrblr;		/* 0x24340 - Maximum Receive Buffer Length Register */
        uint8_t	res28[56];
        uint32_t    rbdbph;		/* 0x2437C - Receive Data Buffer Pointer High */
        uint8_t    res29[4];
        uint32_t	rbptr0;		/* 0x24384 - Receive Buffer Descriptor Pointer for Ring 0 */
        uint8_t    res30[4];
        uint32_t	rbptr1;		/* 0x2438C - Receive Buffer Descriptor Pointer for Ring 1 */
        uint8_t    res31[4];
        uint32_t	rbptr2;		/* 0x24394 - Receive Buffer Descriptor Pointer for Ring 2 */
        uint8_t    res32[4];
        uint32_t	rbptr3;		/* 0x2439C - Receive Buffer Descriptor Pointer for Ring 3 */
        uint8_t    res33[4];
        uint32_t	rbptr4;		/* 0x243A4 - Receive Buffer Descriptor Pointer for Ring 4 */
        uint8_t    res34[4];
        uint32_t	rbptr5;		/* 0x243AC - Receive Buffer Descriptor Pointer for Ring 5 */
        uint8_t    res35[4];
        uint32_t	rbptr6;		/* 0x243B4 - Receive Buffer Descriptor Pointer for Ring 6 */
        uint8_t    res36[4];
        uint32_t	rbptr7;		/* 0x243BC - Receive Buffer Descriptor Pointer for Ring 7 */
        uint8_t    res37[64];
        uint32_t	rbaseh;		/* 0x24400 - Receive Descriptor Base Address High 0 */
        uint32_t	rbase0;		/* 0x24404 - Receive Descriptor Base Address of Ring 0 */
        uint8_t    res38[4];
        uint32_t	rbase1;		/* 0x2440C - Receive Descriptor Base Address of Ring 1 */
        uint8_t    res39[4];
        uint32_t	rbase2;		/* 0x24414 - Receive Descriptor Base Address of Ring 2 */
        uint8_t    res40[4];
        uint32_t	rbase3;		/* 0x2441C - Receive Descriptor Base Address of Ring 3 */
        uint8_t    res41[4];
        uint32_t	rbase4;		/* 0x24424 - Receive Descriptor Base Address of Ring 4 */
        uint8_t    res42[4];
        uint32_t	rbase5;		/* 0x2442C - Receive Descriptor Base Address of Ring 5 */
        uint8_t    res43[4];
        uint32_t	rbase6;		/* 0x24434 - Receive Descriptor Base Address of Ring 6 */
        uint8_t    res44[4];
        uint32_t	rbase7;		/* 0x2443C - Receive Descriptor Base Address of Ring 7 */
        uint8_t    res45[192];
        uint32_t	maccfg1;	/* 0x24500 - MAC Configuration 1 Register */
        uint32_t	maccfg2;	/* 0x24504 - MAC Configuration 2 Register */
        uint32_t	ipgifg;		/* 0x24508 - Inter Packet Gap/Inter Frame Gap Register */
        uint32_t	hafdup;		/* 0x2450c - Half Duplex Register */
        uint32_t	maxfrm;		/* 0x24510 - Maximum Frame Length Register */
        uint8_t	res46[12];
        uint32_t	miimcfg;	/* 0x24520 - MII Management Configuration Register */
        uint32_t	miimcom;	/* 0x24524 - MII Management Command Register */
        uint32_t	miimadd;	/* 0x24528 - MII Management Address Register */
        uint32_t	miimcon;	/* 0x2452c - MII Management Control Register */
        uint32_t	miimstat;	/* 0x24530 - MII Management Status Register */
        uint32_t	miimind;	/* 0x24534 - MII Management Indicator Register */
        uint32_t    ifctrl;		/* 0x24538 - Interface Contrl Register */
        uint32_t	ifstat;		/* 0x2453c - Interface Status Register */
        uint32_t	macstnaddr1;	/* 0x24540 - Station Address Part 1 Register */
        uint32_t	macstnaddr2;	/* 0x24544 - Station Address Part 2 Register */
        uint32_t    mac01addr1;     /* 0x24548 - MAC exact match address 1, part 1 */
        uint32_t    mac01addr2;     /* 0x2454C - MAC exact match address 1, part 2 */
        uint32_t    mac02addr1;     /* 0x24550 - MAC exact match address 2, part 1 */
        uint32_t    mac02addr2;     /* 0x24554 - MAC exact match address 2, part 2 */
        uint32_t    mac03addr1;     /* 0x24558 - MAC exact match address 3, part 1 */
        uint32_t    mac03addr2;     /* 0x2455C - MAC exact match address 3, part 2 */
        uint32_t    mac04addr1;     /* 0x24560 - MAC exact match address 4, part 1 */
        uint32_t    mac04addr2;     /* 0x24564 - MAC exact match address 4, part 2 */
        uint32_t    mac05addr1;     /* 0x24568 - MAC exact match address 5, part 1 */
        uint32_t    mac05addr2;     /* 0x2456C - MAC exact match address 5, part 2 */
        uint32_t    mac06addr1;     /* 0x24570 - MAC exact match address 6, part 1 */
        uint32_t    mac06addr2;     /* 0x24574 - MAC exact match address 6, part 2 */
        uint32_t    mac07addr1;     /* 0x24578 - MAC exact match address 7, part 1 */
        uint32_t    mac07addr2;     /* 0x2457C - MAC exact match address 7, part 2 */
        uint32_t    mac08addr1;     /* 0x24580 - MAC exact match address 8, part 1 */
        uint32_t    mac08addr2;     /* 0x24584 - MAC exact match address 8, part 2 */
        uint32_t    mac09addr1;     /* 0x24588 - MAC exact match address 9, part 1 */
        uint32_t    mac09addr2;     /* 0x2458C - MAC exact match address 9, part 2 */
        uint32_t    mac10addr1;     /* 0x24590 - MAC exact match address 10, part 1 */
        uint32_t    mac10addr2;     /* 0x24594 - MAC exact match address 10, part 2 */
        uint32_t    mac11addr1;     /* 0x24598 - MAC exact match address 11, part 1 */
        uint32_t    mac11addr2;     /* 0x2459C - MAC exact match address 11, part 2 */
        uint32_t    mac12addr1;     /* 0x245A0 - MAC exact match address 12, part 1 */
        uint32_t    mac12addr2;     /* 0x245A4 - MAC exact match address 12, part 2 */
        uint32_t    mac13addr1;     /* 0x245A8 - MAC exact match address 13, part 1 */
        uint32_t    mac13addr2;     /* 0x245AC - MAC exact match address 13, part 2 */
        uint32_t    mac14addr1;     /* 0x245B0 - MAC exact match address 14, part 1 */
        uint32_t    mac14addr2;     /* 0x245B4 - MAC exact match address 14, part 2 */
        uint32_t    mac15addr1;     /* 0x245B8 - MAC exact match address 15, part 1 */
        uint32_t    mac15addr2;     /* 0x245BC - MAC exact match address 15, part 2 */
        uint8_t	res48[192];
        uint32_t	tr64;		/* 0x24680 - Transmit and Receive 64-byte Frame Counter */
        uint32_t	tr127;		/* 0x24684 - Transmit and Receive 65-127 byte Frame Counter */
        uint32_t	tr255;		/* 0x24688 - Transmit and Receive 128-255 byte Frame Counter */
        uint32_t	tr511;		/* 0x2468c - Transmit and Receive 256-511 byte Frame Counter */
        uint32_t	tr1k;		/* 0x24690 - Transmit and Receive 512-1023 byte Frame Counter */
        uint32_t	trmax;		/* 0x24694 - Transmit and Receive 1024-1518 byte Frame Counter */
        uint32_t	trmgv;		/* 0x24698 - Transmit and Receive 1519-1522 byte Good VLAN Frame */
        uint32_t	rbyt;		/* 0x2469c - Receive Byte Counter */
        uint32_t	rpkt;		/* 0x246a0 - Receive Packet Counter */
        uint32_t	rfcs;		/* 0x246a4 - Receive FCS Error Counter */
        uint32_t	rmca;		/* 0x246a8 - Receive Multicast Packet Counter */
        uint32_t	rbca;		/* 0x246ac - Receive Broadcast Packet Counter */
        uint32_t	rxcf;		/* 0x246b0 - Receive Control Frame Packet Counter */
        uint32_t	rxpf;		/* 0x246b4 - Receive Pause Frame Packet Counter */
        uint32_t	rxuo;		/* 0x246b8 - Receive Unknown OP Code Counter */
        uint32_t	raln;		/* 0x246bc - Receive Alignment Error Counter */
        uint32_t	rflr;		/* 0x246c0 - Receive Frame Length Error Counter */
        uint32_t	rcde;		/* 0x246c4 - Receive Code Error Counter */
        uint32_t	rcse;		/* 0x246c8 - Receive Carrier Sense Error Counter */
        uint32_t	rund;		/* 0x246cc - Receive Undersize Packet Counter */
        uint32_t	rovr;		/* 0x246d0 - Receive Oversize Packet Counter */
        uint32_t	rfrg;		/* 0x246d4 - Receive Fragments Counter */
        uint32_t	rjbr;		/* 0x246d8 - Receive Jabber Counter */
        uint32_t	rdrp;		/* 0x246dc - Receive Drop Counter */
        uint32_t	tbyt;		/* 0x246e0 - Transmit Byte Counter Counter */
        uint32_t	tpkt;		/* 0x246e4 - Transmit Packet Counter */
        uint32_t	tmca;		/* 0x246e8 - Transmit Multicast Packet Counter */
        uint32_t	tbca;		/* 0x246ec - Transmit Broadcast Packet Counter */
        uint32_t	txpf;		/* 0x246f0 - Transmit Pause Control Frame Counter */
        uint32_t	tdfr;		/* 0x246f4 - Transmit Deferral Packet Counter */
        uint32_t	tedf;		/* 0x246f8 - Transmit Excessive Deferral Packet Counter */
        uint32_t	tscl;		/* 0x246fc - Transmit Single Collision Packet Counter */
        uint32_t	tmcl;		/* 0x24700 - Transmit Multiple Collision Packet Counter */
        uint32_t	tlcl;		/* 0x24704 - Transmit Late Collision Packet Counter */
        uint32_t	txcl;		/* 0x24708 - Transmit Excessive Collision Packet Counter */
        uint32_t	tncl;		/* 0x2470c - Transmit Total Collision Counter */
        uint8_t	res49[4];
        uint32_t	tdrp;		/* 0x24714 - Transmit Drop Frame Counter */
        uint32_t	tjbr;		/* 0x24718 - Transmit Jabber Frame Counter */
        uint32_t	tfcs;		/* 0x2471c - Transmit FCS Error Counter */
        uint32_t	txcf;		/* 0x24720 - Transmit Control Frame Counter */
        uint32_t	tovr;		/* 0x24724 - Transmit Oversize Frame Counter */
        uint32_t	tund;		/* 0x24728 - Transmit Undersize Frame Counter */
        uint32_t	tfrg;		/* 0x2472c - Transmit Fragments Frame Counter */
        uint32_t	car1;		/* 0x24730 - Carry Register One */
        uint32_t	car2;		/* 0x24734 - Carry Register Two */
        uint32_t	cam1;		/* 0x24738 - Carry Mask Register One */
        uint32_t	cam2;		/* 0x2473c - Carry Mask Register Two */
        uint32_t    rrej;	        /* 0x24740 - Receive filer rejected packet counter */
        uint8_t	res50[188];
        uint32_t	iaddr0;		/* 0x24800 - Individual address register 0 */
        uint32_t	iaddr1;		/* 0x24804 - Individual address register 1 */
        uint32_t	iaddr2;		/* 0x24808 - Individual address register 2 */
        uint32_t	iaddr3;		/* 0x2480c - Individual address register 3 */
        uint32_t	iaddr4;		/* 0x24810 - Individual address register 4 */
        uint32_t	iaddr5;		/* 0x24814 - Individual address register 5 */
        uint32_t	iaddr6;		/* 0x24818 - Individual address register 6 */
        uint32_t	iaddr7;		/* 0x2481c - Individual address register 7 */
        uint8_t	res51[96];
        uint32_t	gaddr0;		/* 0x24880 - Global address register 0 */
        uint32_t	gaddr1;		/* 0x24884 - Global address register 1 */
        uint32_t	gaddr2;		/* 0x24888 - Global address register 2 */
        uint32_t	gaddr3;		/* 0x2488c - Global address register 3 */
        uint32_t	gaddr4;		/* 0x24890 - Global address register 4 */
        uint32_t	gaddr5;		/* 0x24894 - Global address register 5 */
        uint32_t	gaddr6;		/* 0x24898 - Global address register 6 */
        uint32_t	gaddr7;		/* 0x2489c - Global address register 7 */
        uint8_t	res52[352];
        uint32_t    fifocfg;        /* 0x24A00 - FIFO interface configuration register */
        uint8_t    res53[500];
        uint32_t    attr;           /* 0x24BF8 - DMA Attribute register */
        uint32_t    attreli;        /* 0x24BFC - DMA Attribute extract length and index register */
        uint8_t    res54[1024];
} ccsr_tsec_t;

/* PIC Registers(0x4_0000-0x6_1000) */

typedef struct ccsr_pic {
        uint8_t	res1[64];
        uint32_t	ipidr0;		/* 0x40040 - Interprocessor Interrupt Dispatch Register 0 */
        uint8_t	res2[12];
        uint32_t	ipidr1;		/* 0x40050 - Interprocessor Interrupt Dispatch Register 1 */
        uint8_t	res3[12];
        uint32_t	ipidr2;		/* 0x40060 - Interprocessor Interrupt Dispatch Register 2 */
        uint8_t	res4[12];
        uint32_t	ipidr3;		/* 0x40070 - Interprocessor Interrupt Dispatch Register 3 */
        uint8_t	res5[12];
        uint32_t	ctpr;		/* 0x40080 - Current Task Priority Register */
        uint8_t	res6[12];
        uint32_t	whoami;		/* 0x40090 - Who Am I Register */
        uint8_t	res7[12];
        uint32_t	iack;		/* 0x400a0 - Interrupt Acknowledge Register */
        uint8_t	res8[12];
        uint32_t	eoi;		/* 0x400b0 - End Of Interrupt Register */
        uint8_t	res9[3916];
        uint32_t	frr;		/* 0x41000 - Feature Reporting Register */
        uint8_t	res10[28];
        uint32_t	gcr;		/* 0x41020 - Global Configuration Register */
#define MPC86xx_PICGCR_RST	0x80000000
#define MPC86xx_PICGCR_MODE	0x20000000
        uint8_t	res11[92];
        uint32_t	vir;		/* 0x41080 - Vendor Identification Register */
        uint8_t	res12[12];
        uint32_t	pir;		/* 0x41090 - Processor Initialization Register */
        uint8_t	res13a[4];
        uint32_t    prr;        /* 0x41098 - Processor Reset Register */
        uint8_t    res13b[4];
        uint32_t	ipivpr0;	/* 0x410a0 - IPI Vector/Priority Register 0 */
        uint8_t	res14[12];
        uint32_t	ipivpr1;	/* 0x410b0 - IPI Vector/Priority Register 1 */
        uint8_t	res15[12];
        uint32_t	ipivpr2;	/* 0x410c0 - IPI Vector/Priority Register 2 */
        uint8_t	res16[12];
        uint32_t	ipivpr3;	/* 0x410d0 - IPI Vector/Priority Register 3 */
        uint8_t	res17[12];
        uint32_t	svr;		/* 0x410e0 - Spurious Vector Register */
        uint8_t	res18[12];
        uint32_t	tfrra;		/* 0x410f0 - Timer (Group A) Frequency Reporting Register */
        uint8_t	res19[12];
        uint32_t	gtccra0;		/* 0x41100 - Global Timer Current Count Register group A 0 */
        uint8_t	res20[12];
        uint32_t	gtbcra0;		/* 0x41110 - Global Timer Base Count Register group A 0 */
        uint8_t	res21[12];
        uint32_t	gtvpra0;		/* 0x41120 - Global Timer Vector/Priority Register group A 0 */
        uint8_t	res22[12];
        uint32_t	gtdra0;		/* 0x41130 - Global Timer Destination Register group A 0 */
        uint8_t	res23[12];
        uint32_t	gtccra1;		/* 0x41140 - Global Timer Current Count Register group A 1 */
        uint8_t	res24[12];
        uint32_t	gtbcra1;		/* 0x41150 - Global Timer Base Count Register group A 1 */
        uint8_t	res25[12];
        uint32_t	gtvpra1;		/* 0x41160 - Global Timer Vector/Priority Register group A 1 */
        uint8_t	res26[12];
        uint32_t	gtdra1;		/* 0x41170 - Global Timer Destination Register group A 1 */
        uint8_t	res27[12];
        uint32_t	gtccra2;		/* 0x41180 - Global Timer Current Count Register group A 2 */
        uint8_t	res28[12];
        uint32_t	gtbcra2;		/* 0x41190 - Global Timer Base Count Register group A 2 */
        uint8_t	res29[12];
        uint32_t	gtvpra2;		/* 0x411a0 - Global Timer Vector/Priority Register group A 2 */
        uint8_t	res30[12];
        uint32_t	gtdra2;		/* 0x411b0 - Global Timer Destination Register group A 2 */
        uint8_t	res31[12];
        uint32_t	gtccra3;		/* 0x411c0 - Global Timer Current Count Register group A 3 */
        uint8_t	res32[12];
        uint32_t	gtbcra3;		/* 0x411d0 - Global Timer Base Count Register group A 3 */
        uint8_t	res33[12];
        uint32_t	gtvpra3;		/* 0x411e0 - Global Timer Vector/Priority Register group A 3 */
        uint8_t	res34[12];
        uint32_t	gtdra3;		/* 0x411f0 - Global Timer Destination Register group A 3 */
        uint8_t	res35[268];
        uint32_t	tcra;		/* 0x41300 - Timer Group A Control Register */
        uint8_t	res36[12];
        uint32_t	irqsr0;		/* 0x41310 - IRQ_OUT Summary Register 0 */
        uint8_t	res37[12];
        uint32_t	irqsr1;		/* 0x41320 - IRQ_OUT Summary Register 1 */
        uint8_t	res38[12];
        uint32_t	cisr0;		/* 0x41330 - Critical Interrupt Summary Register 0 */
        uint8_t	res39[12];
        uint32_t	cisr1;		/* 0x41340 - Critical Interrupt Summary Register 1 */
        uint8_t	res40[12];
        uint32_t	pm0mr0;		/* 0x41350 - Performance monitor 0 mask register 0  */
        uint8_t	res41[12];
        uint32_t	pm0mr1;		/* 0x41360 - Performance monitor 0 mask register 1  */
        uint8_t	res42[12];
        uint32_t	pm1mr0;		/* 0x41370 - Performance monitor 1 mask register 0  */
        uint8_t	res43[12];
        uint32_t	pm1mr1;		/* 0x41380 - Performance monitor 1 mask register 1  */
        uint8_t	res44[12];
        uint32_t	pm2mr0;		/* 0x41390 - Performance monitor 2 mask register 0  */
        uint8_t	res45[12];
        uint32_t	pm2mr1;		/* 0x413A0 - Performance monitor 2 mask register 1  */
        uint8_t	res46[12];
        uint32_t	pm3mr0;		/* 0x413B0 - Performance monitor 3 mask register 0  */
        uint8_t	res47[12];
        uint32_t	pm3mr1;		/* 0x413C0 - Performance monitor 3 mask register 1  */
        uint8_t	res48[60];
        uint32_t	msgr0;		/* 0x41400 - Message Register 0 */
        uint8_t	res49[12];
        uint32_t	msgr1;		/* 0x41410 - Message Register 1 */
        uint8_t	res50[12];
        uint32_t	msgr2;		/* 0x41420 - Message Register 2 */
        uint8_t	res51[12];
        uint32_t	msgr3;		/* 0x41430 - Message Register 3 */
        uint8_t res51a[12];
        uint8_t	res52[192];     /* 0x41440-0x414ff - Reserved */
        uint32_t	mer;		/* 0x41500 - Message Enable Register */
        uint8_t	res53[12];
        uint32_t	msr;		/* 0x41510 - Message Status Register */
        uint8_t	res53a[12];
        uint8_t res54[224];     /* 0x4_1520-0x4_15FF Reserved */
    uint32_t    msir0;      /* 0x41600 - Shared message signaled interrupt register 0 */
    uint8_t res54a[12];
    uint32_t    msir1;      /* 0x41610 - Shared message signaled interrupt register 1 */
    uint8_t res54b[12];
    uint32_t    msir2;      /* 0x41620 - Shared message signaled interrupt register 2 */
    uint8_t res54c[12];
    uint32_t    msir3;      /* 0x41630 - Shared message signaled interrupt register 3 */
    uint8_t res54d[12];
    uint32_t    msir4;      /* 0x41640 - Shared message signaled interrupt register 4 */
    uint8_t res54e[12];
    uint32_t    msir5;      /* 0x41650 - Shared message signaled interrupt register 5 */
    uint8_t res54f[12];
    uint32_t    msir6;      /* 0x41660 - Shared message signaled interrupt register 6 */
    uint8_t res54g[12];
    uint32_t    msir7;      /* 0x41670 - Shared message signaled interrupt register 7 */
    uint8_t res54h[12];
    uint8_t  res54h2[160];  /* 0x4_1680-0x4_171f Reserved */
    uint32_t    msisr;      /* 0x41720 - Shared message signaled interrupt status register */
    uint8_t res54i[28];
    uint32_t    msiir;      /* 0x41740 - Shared message signaled interrupt index register */
    uint8_t res54j[12];
    uint8_t  res54j2[2464]; /* 0x4_1750-0x4_20EF Reserved */
    uint32_t    tfrrb;      /* 0x420F0 - Timer frequency reporting register group B */
    uint8_t res54k[12];
    uint32_t    gtccrb0;    /* 0x42100 - Global timer current count register group B 0 */
    uint8_t res54l[12];
    uint32_t    gtbcrb0;    /* 0x42110 - Global timer base count register group B 0 */
    uint8_t res54m[12];
    uint32_t    gtvprb0;    /* 0x42120 - Global timer vector/priority register group B 0 */
    uint8_t res54n[12];
    uint32_t    gtdrb0;     /* 0x42130 - Global timer destination register group B 0 */
    uint8_t res54o[12];
    uint32_t    gtccrb1;    /* 0x42140 - Global timer current count register group B 1 */
    uint8_t res54p[12];
    uint32_t    gtbcrb1;    /* 0x42150 - Global timer base count register group B 1 */
    uint8_t res54q[12];
    uint32_t    gtvprb1;    /* 0x42160 - Global timer vector/priority register group B 1 */
    uint8_t res54r[12];
    uint32_t    gtdrb1;     /* 0x42170 - Global timer destination register group B 1 */
    uint8_t res54s[12];
    uint32_t    gtccrb2;    /* 0x42180 - Global timer current count register group B 2 */
    uint8_t res54t[12];
    uint32_t    gtbcrb2;    /* 0x42190 - Global timer base count register group B 2 */
    uint8_t res54u[12];
    uint32_t    gtvprb2;    /* 0x421A0 - Global timer vector/priority register group B 2 */
    uint8_t res54v[12];
    uint32_t    gtdrb2;     /* 0x421B0 - Global timer destination register group B 2 */
    uint8_t res54w[12];
    uint32_t    gtccrb3;    /* 0x421C0 - Global timer current count register group B 3 */
    uint8_t res54x[12];
    uint32_t    gtbcrb3;    /* 0x421D0 - Global timer base count register group B 3 */
    uint8_t res54y[12];
    uint32_t    gtvprb3;    /* 0x421E0 - Global timer vector/priority register group B 3 */
    uint8_t res54z[12];
    uint32_t    gtdrb3;     /* 0x421F0 - Global timer destination register group B 3 */
    uint8_t res54aa[12];
    uint8_t res54aa2[256];  /* 0x4_2200-0x4_22FF Reserved */
    uint32_t    tcrb;       /* 0x42300 - Timer control register (Group B) */
    uint8_t res54ab[12];
    uint8_t res54ab2[56560]; /* 0x4_2310-0x4_FFF0 Reserved */
        uint32_t	eivpr0;		/* 0x50000 - External Interrupt Vector/Priority Register 0 */
        uint8_t	res55[12];
        uint32_t	eidr0;		/* 0x50010 - External Interrupt Destination Register 0 */
        uint8_t	res56[12];
        uint32_t	eivpr1;		/* 0x50020 - External Interrupt Vector/Priority Register 1 */
        uint8_t	res57[12];
        uint32_t	eidr1;		/* 0x50030 - External Interrupt Destination Register 1 */
        uint8_t	res58[12];
        uint32_t	eivpr2;		/* 0x50040 - External Interrupt Vector/Priority Register 2 */
        uint8_t	res59[12];
        uint32_t	eidr2;		/* 0x50050 - External Interrupt Destination Register 2 */
        uint8_t	res60[12];
        uint32_t	eivpr3;		/* 0x50060 - External Interrupt Vector/Priority Register 3 */
        uint8_t	res61[12];
        uint32_t	eidr3;		/* 0x50070 - External Interrupt Destination Register 3 */
        uint8_t	res62[12];
        uint32_t	eivpr4;		/* 0x50080 - External Interrupt Vector/Priority Register 4 */
        uint8_t	res63[12];
        uint32_t	eidr4;		/* 0x50090 - External Interrupt Destination Register 4 */
        uint8_t	res64[12];
        uint32_t	eivpr5;		/* 0x500a0 - External Interrupt Vector/Priority Register 5 */
        uint8_t	res65[12];
        uint32_t	eidr5;		/* 0x500b0 - External Interrupt Destination Register 5 */
        uint8_t	res66[12];
        uint32_t	eivpr6;		/* 0x500c0 - External Interrupt Vector/Priority Register 6 */
        uint8_t	res67[12];
        uint32_t	eidr6;		/* 0x500d0 - External Interrupt Destination Register 6 */
        uint8_t	res68[12];
        uint32_t	eivpr7;		/* 0x500e0 - External Interrupt Vector/Priority Register 7 */
        uint8_t	res69[12];
        uint32_t	eidr7;		/* 0x500f0 - External Interrupt Destination Register 7 */
        uint8_t	res70[12];
        uint32_t	eivpr8;		/* 0x50100 - External Interrupt Vector/Priority Register 8 */
        uint8_t	res71[12];
        uint32_t	eidr8;		/* 0x50110 - External Interrupt Destination Register 8 */
        uint8_t	res72[12];
        uint32_t	eivpr9;		/* 0x50120 - External Interrupt Vector/Priority Register 9 */
        uint8_t	res73[12];
        uint32_t	eidr9;		/* 0x50130 - External Interrupt Destination Register 9 */
        uint8_t	res74[12];
        uint32_t	eivpr10;	/* 0x50140 - External Interrupt Vector/Priority Register 10 */
        uint8_t	res75[12];
        uint32_t	eidr10;		/* 0x50150 - External Interrupt Destination Register 10 */
        uint8_t	res76[12];
        uint32_t	eivpr11;	/* 0x50160 - External Interrupt Vector/Priority Register 11 */
        uint8_t	res77[12];
        uint32_t	eidr11;		/* 0x50170 - External Interrupt Destination Register 11 */
        uint8_t	res78[140];
        uint32_t	iivpr0;		/* 0x50200 - Internal Interrupt Vector/Priority Register 0 */
        uint8_t	res79[12];
        uint32_t	iidr0;		/* 0x50210 - Internal Interrupt Destination Register 0 */
        uint8_t	res80[12];
        uint32_t	iivpr1;		/* 0x50220 - Internal Interrupt Vector/Priority Register 1 */
        uint8_t	res81[12];
        uint32_t	iidr1;		/* 0x50230 - Internal Interrupt Destination Register 1 */
        uint8_t	res82[12];
        uint32_t	iivpr2;		/* 0x50240 - Internal Interrupt Vector/Priority Register 2 */
        uint8_t	res83[12];
        uint32_t	iidr2;		/* 0x50250 - Internal Interrupt Destination Register 2 */
        uint8_t	res84[12];
        uint32_t	iivpr3;		/* 0x50260 - Internal Interrupt Vector/Priority Register 3 */
        uint8_t	res85[12];
        uint32_t	iidr3;		/* 0x50270 - Internal Interrupt Destination Register 3 */
        uint8_t	res86[12];
        uint32_t	iivpr4;		/* 0x50280 - Internal Interrupt Vector/Priority Register 4 */
        uint8_t	res87[12];
        uint32_t	iidr4;		/* 0x50290 - Internal Interrupt Destination Register 4 */
        uint8_t	res88[12];
        uint32_t	iivpr5;		/* 0x502a0 - Internal Interrupt Vector/Priority Register 5 */
        uint8_t	res89[12];
        uint32_t	iidr5;		/* 0x502b0 - Internal Interrupt Destination Register 5 */
        uint8_t	res90[12];
        uint32_t	iivpr6;		/* 0x502c0 - Internal Interrupt Vector/Priority Register 6 */
        uint8_t	res91[12];
        uint32_t	iidr6;		/* 0x502d0 - Internal Interrupt Destination Register 6 */
        uint8_t	res92[12];
        uint32_t	iivpr7;		/* 0x502e0 - Internal Interrupt Vector/Priority Register 7 */
        uint8_t	res93[12];
        uint32_t	iidr7;		/* 0x502f0 - Internal Interrupt Destination Register 7 */
        uint8_t	res94[12];
        uint32_t	iivpr8;		/* 0x50300 - Internal Interrupt Vector/Priority Register 8 */
        uint8_t	res95[12];
        uint32_t	iidr8;		/* 0x50310 - Internal Interrupt Destination Register 8 */
        uint8_t	res96[12];
        uint32_t	iivpr9;		/* 0x50320 - Internal Interrupt Vector/Priority Register 9 */
        uint8_t	res97[12];
        uint32_t	iidr9;		/* 0x50330 - Internal Interrupt Destination Register 9 */
        uint8_t	res98[12];
        uint32_t	iivpr10;	/* 0x50340 - Internal Interrupt Vector/Priority Register 10 */
        uint8_t	res99[12];
        uint32_t	iidr10;		/* 0x50350 - Internal Interrupt Destination Register 10 */
        uint8_t	res100[12];
        uint32_t	iivpr11;	/* 0x50360 - Internal Interrupt Vector/Priority Register 11 */
        uint8_t	res101[12];
        uint32_t	iidr11;		/* 0x50370 - Internal Interrupt Destination Register 11 */
        uint8_t	res102[12];
        uint32_t	iivpr12;	/* 0x50380 - Internal Interrupt Vector/Priority Register 12 */
        uint8_t	res103[12];
        uint32_t	iidr12;		/* 0x50390 - Internal Interrupt Destination Register 12 */
        uint8_t	res104[12];
        uint32_t	iivpr13;	/* 0x503a0 - Internal Interrupt Vector/Priority Register 13 */
        uint8_t	res105[12];
        uint32_t	iidr13;		/* 0x503b0 - Internal Interrupt Destination Register 13 */
        uint8_t	res106[12];
        uint32_t	iivpr14;	/* 0x503c0 - Internal Interrupt Vector/Priority Register 14 */
        uint8_t	res107[12];
        uint32_t	iidr14;		/* 0x503d0 - Internal Interrupt Destination Register 14 */
        uint8_t	res108[12];
        uint32_t	iivpr15;	/* 0x503e0 - Internal Interrupt Vector/Priority Register 15 */
        uint8_t	res109[12];
        uint32_t	iidr15;		/* 0x503f0 - Internal Interrupt Destination Register 15 */
        uint8_t	res110[12];
        uint32_t	iivpr16;	/* 0x50400 - Internal Interrupt Vector/Priority Register 16 */
        uint8_t	res111[12];
        uint32_t	iidr16;		/* 0x50410 - Internal Interrupt Destination Register 16 */
        uint8_t	res112[12];
        uint32_t	iivpr17;	/* 0x50420 - Internal Interrupt Vector/Priority Register 17 */
        uint8_t	res113[12];
        uint32_t	iidr17;		/* 0x50430 - Internal Interrupt Destination Register 17 */
        uint8_t	res114[12];
        uint32_t	iivpr18;	/* 0x50440 - Internal Interrupt Vector/Priority Register 18 */
        uint8_t	res115[12];
        uint32_t	iidr18;		/* 0x50450 - Internal Interrupt Destination Register 18 */
        uint8_t	res116[12];
        uint32_t	iivpr19;	/* 0x50460 - Internal Interrupt Vector/Priority Register 19 */
        uint8_t	res117[12];
        uint32_t	iidr19;		/* 0x50470 - Internal Interrupt Destination Register 19 */
        uint8_t	res118[12];
        uint32_t	iivpr20;	/* 0x50480 - Internal Interrupt Vector/Priority Register 20 */
        uint8_t	res119[12];
        uint32_t	iidr20;		/* 0x50490 - Internal Interrupt Destination Register 20 */
        uint8_t	res120[12];
        uint32_t	iivpr21;	/* 0x504a0 - Internal Interrupt Vector/Priority Register 21 */
        uint8_t	res121[12];
        uint32_t	iidr21;		/* 0x504b0 - Internal Interrupt Destination Register 21 */
        uint8_t	res122[12];
        uint32_t	iivpr22;	/* 0x504c0 - Internal Interrupt Vector/Priority Register 22 */
        uint8_t	res123[12];
        uint32_t	iidr22;		/* 0x504d0 - Internal Interrupt Destination Register 22 */
        uint8_t	res124[12];
        uint32_t	iivpr23;	/* 0x504e0 - Internal Interrupt Vector/Priority Register 23 */
        uint8_t	res125[12];
        uint32_t	iidr23;		/* 0x504f0 - Internal Interrupt Destination Register 23 */
        uint8_t	res126[12];
        uint32_t	iivpr24;	/* 0x50500 - Internal Interrupt Vector/Priority Register 24 */
        uint8_t	res127[12];
        uint32_t	iidr24;		/* 0x50510 - Internal Interrupt Destination Register 24 */
        uint8_t	res128[12];
        uint32_t	iivpr25;	/* 0x50520 - Internal Interrupt Vector/Priority Register 25 */
        uint8_t	res129[12];
        uint32_t	iidr25;		/* 0x50530 - Internal Interrupt Destination Register 25 */
        uint8_t	res130[12];
        uint32_t	iivpr26;	/* 0x50540 - Internal Interrupt Vector/Priority Register 26 */
        uint8_t	res131[12];
        uint32_t	iidr26;		/* 0x50550 - Internal Interrupt Destination Register 26 */
        uint8_t	res132[12];
        uint32_t	iivpr27;	/* 0x50560 - Internal Interrupt Vector/Priority Register 27 */
        uint8_t	res133[12];
        uint32_t	iidr27;		/* 0x50570 - Internal Interrupt Destination Register 27 */
        uint8_t	res134[12];
        uint32_t	iivpr28;	/* 0x50580 - Internal Interrupt Vector/Priority Register 28 */
        uint8_t	res135[12];
        uint32_t	iidr28;		/* 0x50590 - Internal Interrupt Destination Register 28 */
        uint8_t	res136[12];
        uint32_t	iivpr29;	/* 0x505a0 - Internal Interrupt Vector/Priority Register 29 */
        uint8_t	res137[12];
        uint32_t	iidr29;		/* 0x505b0 - Internal Interrupt Destination Register 29 */
        uint8_t	res138[12];
        uint32_t	iivpr30;	/* 0x505c0 - Internal Interrupt Vector/Priority Register 30 */
        uint8_t	res139[12];
        uint32_t	iidr30;		/* 0x505d0 - Internal Interrupt Destination Register 30 */
        uint8_t	res140[12];
        uint32_t	iivpr31;	/* 0x505e0 - Internal Interrupt Vector/Priority Register 31 */
        uint8_t	res141[12];
        uint32_t	iidr31;		/* 0x505f0 - Internal Interrupt Destination Register 31 */
        uint8_t rest141x[12];
    uint32_t    iivpr32;    /* 0x50600 - Internal interrupt 32 vector/priority register  */
    uint8_t res141y[12];
        uint32_t    iidr32; /* 0x50610 - Internal interrupt 32 destination register */
    uint8_t res141a1[12];
    uint32_t    iivpr33; /* 0x50620 - Internal interrupt 33 vector/priority register */
    uint8_t res141a2[12];
    uint32_t    iidr33; /* 0x50630 - Internal interrupt 33 destination register */
    uint8_t res141a3[12];
    uint32_t    iivpr34; /* 0x50640 - Internal interrupt 34 vector/priority register */
    uint8_t res141a4[12];
    uint32_t    iidr34; /* 0x50650 - Internal interrupt 34 destination register */
    uint8_t res141a5[12];
    uint32_t    iivpr35; /* 0x50660 - Internal interrupt 35 vector/priority register */
    uint8_t res141a6[12];
    uint32_t    iidr35; /* 0x50670 - Internal interrupt 35 destination register */
    uint8_t res141a7[12];
    uint32_t    iivpr36; /* 0x50680 - Internal interrupt 36 vector/priority register */
    uint8_t res141a8[12];
    uint32_t    iidr36; /* 0x50690 - Internal interrupt 36 destination register */
    uint8_t res141a9[12];
    uint32_t    iivpr37; /* 0x506A0 - Internal interrupt 37 vector/priority register */
    uint8_t res141b1[12];
    uint32_t    iidr37; /* 0x506B0 - Internal interrupt 37 destination register */
    uint8_t res141b2[12];
    uint32_t    iivpr38; /* 0x506C0 - Internal interrupt 38 vector/priority register */
    uint8_t res141b3[12];
    uint32_t    iidr38; /* 0x506D0 - Internal interrupt 38 destination register */
    uint8_t res141b4[12];
    uint32_t    iivpr39; /* 0x506E0 - Internal interrupt 39 vector/priority register */
    uint8_t res141b5[12];
    uint32_t    iidr39; /* 0x506F0 - Internal interrupt 39 destination register */
    uint8_t res141b6[12];
    uint32_t    iivpr40; /* 0x50700 - Internal interrupt 40 vector/priority register */
    uint8_t res141b7[12];
    uint32_t    iidr40; /* 0x50710 - Internal interrupt 40 destination register */
    uint8_t res141b8[12];
    uint32_t    iivpr41; /* 0x50720 - Internal interrupt 41 vector/priority register */
    uint8_t res141b9[12];
    uint32_t    iidr41; /* 0x50730 - Internal interrupt 41 destination register */
    uint8_t res141c1[12];
    uint32_t    iivpr42; /* 0x50740 - Internal interrupt 42 vector/priority register */
    uint8_t res141c2[12];
    uint32_t    iidr42; /* 0x50750 - Internal interrupt 42 destination register */
    uint8_t res141c3[12];
    uint32_t    iivpr43; /* 0x50760 - Internal interrupt 43 vector/priority register */
    uint8_t res141c4[12];
    uint32_t    iidr43; /* 0x50770 - Internal interrupt 43 destination register */
    uint8_t res141c5[12];
    uint32_t    iivpr44; /* 0x50780 - Internal interrupt 44 vector/priority register */
    uint8_t res141c6[12];
    uint32_t    iidr44; /* 0x50790 - Internal interrupt 44 destination register */
    uint8_t res141c7[12];
    uint32_t    iivpr45; /* 0x507A0 - Internal interrupt 45 vector/priority register  */
    uint8_t res141c8[12];
    uint32_t    iidr45; /* 0x507B0 - Internal interrupt 45 destination register */
    uint8_t res141c9[12];
    uint32_t    iivpr46; /* 0x507C0 - Internal interrupt 46 vector/priority register */
    uint8_t res141d1[12];
    uint32_t    iidr46; /* 0x507D0 - Internal interrupt 46 destination register */
    uint8_t res141d2[12];
    uint32_t    iivpr47; /* 0x507E0 - Internal interrupt 47 vector/priority register */
    uint8_t res141d3[12];
    uint32_t    iidr47; /* 0x507F0 - Internal interrupt 47 destination register */
    uint8_t res141d4[12];
        uint8_t	res142[3584]; /* 0x5_0800 - 0x5_15FF Reserved */
        uint32_t	mivpr0;		/* 0x51600 - Messaging Interrupt Vector/Priority Register 0 */
        uint8_t	res143[12];
        uint32_t	midr0;		/* 0x51610 - Messaging Interrupt Destination Register 0 */
        uint8_t	res144[12];
        uint32_t	mivpr1;		/* 0x51620 - Messaging Interrupt Vector/Priority Register 1 */
        uint8_t	res145[12];
        uint32_t	midr1;		/* 0x51630 - Messaging Interrupt Destination Register 1 */
        uint8_t	res146[12];
        uint32_t	mivpr2;		/* 0x51640 - Messaging Interrupt Vector/Priority Register 2 */
        uint8_t	res147[12];
        uint32_t	midr2;		/* 0x51650 - Messaging Interrupt Destination Register 2 */
        uint8_t	res148[12];
        uint32_t	mivpr3;		/* 0x51660 - Messaging Interrupt Vector/Priority Register 3 */
        uint8_t	res149[12];
        uint32_t	midr3;		/* 0x51670 - Messaging Interrupt Destination Register 3 */
        uint8_t res149aa[12];
        uint8_t res149ab[1408]; /* 0x5_1680-0x5_1BFF Reserved */
        uint32_t    msivpr0; /* 0x51C00 - Shared message signaled interrupt vector/priority register 0 */
    uint8_t res149a1[12];
        uint32_t    msidr0; /* 0x51C10 - Shared message signaled interrupt destination register 0 */
    uint8_t res149a2[12];
        uint32_t    msivpr1; /* 0x51C20 - Shared message signaled interrupt vector/priority register 1 */
    uint8_t res149a3[12];
        uint32_t    msidr1; /* 0x51C30 - Shared message signaled interrupt destination register 1 */
    uint8_t res149a4[12];
        uint32_t    msivpr2; /* 0x51C40 - Shared message signaled interrupt vector/priority register 2 */
    uint8_t res149a5[12];
        uint32_t    msidr2; /* 0x51C50 - Shared message signaled interrupt destination register 2 */
    uint8_t res149a6[12];
        uint32_t    msivpr3; /* 0x51C60 - Shared message signaled interrupt vector/priority register 3 */
    uint8_t res149a7[12];
        uint32_t    msidr3; /* 0x51C70 - Shared message signaled interrupt destination register 3 */
    uint8_t res149a8[12];
        uint32_t    msivpr4; /* 0x51C80 - Shared message signaled interrupt vector/priority register 4 */
    uint8_t res149a9[12];
        uint32_t    msidr4; /* 0x51C90 - Shared message signaled interrupt destination register 4 */
    uint8_t res149b1[12];
        uint32_t    msivpr5; /* 0x51CA0 - Shared message signaled interrupt vector/priority register 5 */
    uint8_t res149b2[12];
        uint32_t    msidr5; /* 0x51CB0 - Shared message signaled interrupt destination register 5 */
    uint8_t res149b3[12];
        uint32_t    msivpr6; /* 0x51CC0 - Shared message signaled interrupt vector/priority register 6 */
    uint8_t res149b4[12];
        uint32_t    msidr6; /* 0x51CD0 - Shared message signaled interrupt destination register 6 */
    uint8_t res149b5[12];
        uint32_t    msivpr7; /* 0x51CE0 - Shared message signaled interrupt vector/priority register 7 */
    uint8_t res149b6[12];
        uint32_t    msidr7; /* 0x51CF0 - Shared message signaled interrupt destination register 7 */
    uint8_t res149b7[12];
        uint8_t	res150[58176]; /* 0x5_1D00-0x6_003F Reserved */
        uint32_t	ipi0dr0;	/* 0x60040 - Processor 0 Interprocessor Interrupt Dispatch Register 0 */
        uint8_t	res151[12];
        uint32_t	ipi0dr1;	/* 0x60050 - Processor 0 Interprocessor Interrupt Dispatch Register 1 */
        uint8_t	res152[12];
        uint32_t	ipi0dr2;	/* 0x60060 - Processor 0 Interprocessor Interrupt Dispatch Register 2 */
        uint8_t	res153[12];
        uint32_t	ipi0dr3;	/* 0x60070 - Processor 0 Interprocessor Interrupt Dispatch Register 3 */
        uint8_t	res154[12];
        uint32_t	ctpr0;		/* 0x60080 - Current Task Priority Register for Processor 0 */
        uint8_t	res155[12];
        uint32_t	whoami0;	/* 0x60090 - Who Am I Register for Processor 0 */
        uint8_t	res156[12];
        uint32_t	iack0;		/* 0x600a0 - Interrupt Acknowledge Register for Processor 0 */
        uint8_t	res157[12];
        uint32_t	eoi0;		/* 0x600b0 - End Of Interrupt Register for Processor 0 */
        uint8_t	res158[3916];
} ccsr_pic_t;

/* RapidIO Registers(0xc_0000-0xe_0000) */

typedef struct ccsr_rio {
        uint32_t	didcar;		/* 0xc0000 - Device Identity Capability Register */
        uint32_t	dicar;		/* 0xc0004 - Device Information Capability Register */
        uint32_t	aidcar;		/* 0xc0008 - Assembly Identity Capability Register */
        uint32_t	aicar;		/* 0xc000c - Assembly Information Capability Register */
        uint32_t	pefcar;		/* 0xc0010 - Processing Element Features Capability Register */
        uint32_t	spicar;		/* 0xc0014 - Switch Port Information Capability Register */
        uint32_t	socar;		/* 0xc0018 - Source Operations Capability Register */
        uint32_t	docar;		/* 0xc001c - Destination Operations Capability Register */
        uint8_t	res1[32];
        uint32_t	msr;		/* 0xc0040 - Mailbox Command And Status Register */
        uint32_t	pwdcsr;		/* 0xc0044 - Port-Write and Doorbell Command And Status Register */
        uint8_t	res2[4];
        uint32_t	pellccsr;	/* 0xc004c - Processing Element Logic Layer Control Command and Status Register */
        uint8_t	res3[12];
        uint32_t	lcsbacsr;	/* 0xc005c - Local Configuration Space Base Address Command and Status Register */
        uint32_t	bdidcsr;	/* 0xc0060 - Base Device ID Command and Status Register */
        uint8_t	res4[4];
        uint32_t	hbdidlcsr;	/* 0xc0068 - Host Base Device ID Lock Command and Status Register */
        uint32_t	ctcsr;		/* 0xc006c - Component Tag Command and Status Register */
        uint8_t	res5[144];
        uint32_t	pmbh0csr;	/* 0xc0100 - 8/16 LP-LVDS Port Maintenance Block Header 0 Command and Status Register */
        uint8_t	res6[28];
        uint32_t	pltoccsr;	/* 0xc0120 - Port Link Time-out Control Command and Status Register */
        uint32_t	prtoccsr;	/* 0xc0124 - Port Response Time-out Control Command and Status Register */
        uint8_t	res7[20];
        uint32_t	pgccsr;		/* 0xc013c - Port General Command and Status Register */
        uint32_t	plmreqcsr;	/* 0xc0140 - Port Link Maintenance Request Command and Status Register */
        uint32_t	plmrespcsr;	/* 0xc0144 - Port Link Maintenance Response Command and Status Register */
        uint32_t	plascsr;	/* 0xc0148 - Port Local Ackid Status Command and Status Register */
        uint8_t	res8[12];
        uint32_t	pescsr;		/* 0xc0158 - Port Error and Status Command and Status Register */
        uint32_t	pccsr;		/* 0xc015c - Port Control Command and Status Register */
        uint8_t	res9[1184];
        uint32_t	erbh;		/* 0xc0600 - Error Reporting Block Header Register */
        uint8_t	res10[4];
        uint32_t	ltledcsr;	/* 0xc0608 - Logical/Transport layer error detect status register */
        uint32_t	ltleecsr;	/* 0xc060c - Logical/Transport layer error enable register */
        uint8_t	res11[4];
        uint32_t	ltlaccsr;	/* 0xc0614 - Logical/Transport layer addresss capture register */
        uint32_t	ltldidccsr;	/* 0xc0618 - Logical/Transport layer device ID capture register */
        uint32_t	ltlcccsr;	/* 0xc061c - Logical/Transport layer control capture register */
        uint8_t	res12[32];
        uint32_t	edcsr;	        /* 0xc0640 - Port 0 error detect status register */
        uint32_t	erecsr;	        /* 0xc0644 - Port 0 error rate enable status register */
        uint32_t	ecacsr;	        /* 0xc0648 - Port 0 error capture attributes register */
        uint32_t	pcseccsr0;	/* 0xc064c - Port 0 packet/control symbol error capture register 0 */
        uint32_t	peccsr1;	/* 0xc0650 - Port 0 error capture command and status register 1 */
        uint32_t	peccsr2;	/* 0xc0654 - Port 0 error capture command and status register 2 */
        uint32_t	peccsr3;	/* 0xc0658 - Port 0 error capture command and status register 3 */
        uint8_t	res13[12];
        uint32_t	ercsr;	        /* 0xc0668 - Port 0 error rate command and status register */
        uint32_t	ertcsr;	        /* 0xc066C - Port 0 error rate threshold status register*/
        uint8_t	res14[63892];
        uint32_t	llcr;		/* 0xd0004 - Logical Layer Configuration Register */
        uint8_t	res15[12];
        uint32_t	epwisr;		/* 0xd0010 - Error / Port-Write Interrupt Status Register */
        uint8_t	res16[12];
        uint32_t	lretcr;		/* 0xd0020 - Logical Retry Error Threshold Configuration Register */
        uint8_t	res17[92];
        uint32_t	pretcr;		/* 0xd0080 - Physical Retry Erorr Threshold Configuration Register */
        uint8_t	res18[124];
        uint32_t	adidcsr;	/* 0xd0100 - Port 0 Alt. Device ID Command and Status Register */
        uint8_t	res19[28];
        uint32_t	ptaacr;	        /* 0xd0120 - Port 0 Pass-Through/Accept-All Configuration Register */
        uint8_t	res20[12];
        uint32_t	iecsr;	        /* 0xd0130 - Port 0 Implementation Error Status Register */
        uint8_t	res21[12];
        uint32_t	pcr;		/* 0xd0140 - Port 0 Phsyical Configuration RegisterRegister */
        uint8_t	res22[20];
        uint32_t	slcsr;	        /* 0xd0158 - Port 0 Serial Link Command and Status Register */
        uint8_t	res23[4];
        uint32_t	sleir;	        /* 0xd0160 - Port 0 Serial Link Error Injection Register */
        uint8_t	res24[2716];
        uint32_t	rowtar0;	/* 0xd0c00 - RapidIO Outbound Window Translation Address Register 0 */
        uint32_t	rowtear0;	/* 0xd0c04 - RapidIO Outbound Window Translation Ext. Address Register 0 */
        uint8_t	res25[8];
        uint32_t	rowar0;		/* 0xd0c10 - RapidIO Outbound Attributes Register 0 */
        uint8_t	res26[12];
        uint32_t	rowtar1;	/* 0xd0c20 - RapidIO Outbound Window Translation Address Register 1 */
        uint32_t	rowtear1;	/* 0xd0c24 - RapidIO Outbound Window Translation Ext. Address Register 1 */
        uint32_t	rowbar1;	/* 0xd0c28 - RapidIO Outbound Window Base Address Register 1 */
        uint8_t	res27[4];
        uint32_t	rowar1;		/* 0xd0c30 - RapidIO Outbound Attributes Register 1 */
        uint32_t	rows1r1;	/* 0xd0c34 - RapidIO Outbound Window Segment 1 Register 1 */
        uint32_t	rows2r1;	/* 0xd0c38 - RapidIO Outbound Window Segment 2 Register 1 */
        uint32_t	rows3r1;	/* 0xd0c3c - RapidIO Outbound Window Segment 3 Register 1 */
        uint32_t	rowtar2;	/* 0xd0c40 - RapidIO Outbound Window Translation Address Register 2 */
        uint32_t	rowtear2;	/* 0xd0c44 - RapidIO Outbound Window Translation Ext. Address Register 2 */
        uint32_t	rowbar2;	/* 0xd0c48 - RapidIO Outbound Window Base Address Register 2 */
        uint8_t	res28[4];
        uint32_t	rowar2;		/* 0xd0c50 - RapidIO Outbound Attributes Register 2 */
        uint32_t	rows1r2;	/* 0xd0c54 - RapidIO Outbound Window Segment 1 Register 2 */
        uint32_t	rows2r2;	/* 0xd0c58 - RapidIO Outbound Window Segment 2 Register 2 */
        uint32_t	rows3r2;	/* 0xd0c5c - RapidIO Outbound Window Segment 3 Register 2 */
        uint32_t	rowtar3;	/* 0xd0c60 - RapidIO Outbound Window Translation Address Register 3 */
        uint32_t	rowtear3;	/* 0xd0c64 - RapidIO Outbound Window Translation Ext. Address Register 3 */
        uint32_t	rowbar3;	/* 0xd0c68 - RapidIO Outbound Window Base Address Register 3 */
        uint8_t	res29[4];
        uint32_t	rowar3;		/* 0xd0c70 - RapidIO Outbound Attributes Register 3 */
        uint32_t	rows1r3;	/* 0xd0c74 - RapidIO Outbound Window Segment 1 Register 3 */
        uint32_t	rows2r3;	/* 0xd0c78 - RapidIO Outbound Window Segment 2 Register 3 */
        uint32_t	rows3r3;	/* 0xd0c7c - RapidIO Outbound Window Segment 3 Register 3 */
        uint32_t	rowtar4;	/* 0xd0c80 - RapidIO Outbound Window Translation Address Register 4 */
        uint32_t	rowtear4;	/* 0xd0c84 - RapidIO Outbound Window Translation Ext. Address Register 4 */
        uint32_t	rowbar4;	/* 0xd0c88 - RapidIO Outbound Window Base Address Register 4 */
        uint8_t	res30[4];
        uint32_t	rowar4;		/* 0xd0c90 - RapidIO Outbound Attributes Register 4 */
        uint32_t	rows1r4;	/* 0xd0c94 - RapidIO Outbound Window Segment 1 Register 4 */
        uint32_t	rows2r4;	/* 0xd0c98 - RapidIO Outbound Window Segment 2 Register 4 */
        uint32_t	rows3r4;	/* 0xd0c9c - RapidIO Outbound Window Segment 3 Register 4 */
        uint32_t	rowtar5;	/* 0xd0ca0 - RapidIO Outbound Window Translation Address Register 5 */
        uint32_t	rowtear5;	/* 0xd0ca4 - RapidIO Outbound Window Translation Ext. Address Register 5 */
        uint32_t	rowbar5;	/* 0xd0ca8 - RapidIO Outbound Window Base Address Register 5 */
        uint8_t	res31[4];
        uint32_t	rowar5;		/* 0xd0cb0 - RapidIO Outbound Attributes Register 5 */
        uint32_t	rows1r5;	/* 0xd0cb4 - RapidIO Outbound Window Segment 1 Register 5 */
        uint32_t	rows2r5;	/* 0xd0cb8 - RapidIO Outbound Window Segment 2 Register 5 */
        uint32_t	rows3r5;	/* 0xd0cbc - RapidIO Outbound Window Segment 3 Register 5 */
        uint32_t	rowtar6;	/* 0xd0cc0 - RapidIO Outbound Window Translation Address Register 6 */
        uint32_t	rowtear6;	/* 0xd0cc4 - RapidIO Outbound Window Translation Ext. Address Register 6 */
        uint32_t	rowbar6;	/* 0xd0cc8 - RapidIO Outbound Window Base Address Register 6 */
        uint8_t	res32[4];
        uint32_t	rowar6;		/* 0xd0cd0 - RapidIO Outbound Attributes Register 6 */
        uint32_t	rows1r6;	/* 0xd0cd4 - RapidIO Outbound Window Segment 1 Register 6 */
        uint32_t	rows2r6;	/* 0xd0cd8 - RapidIO Outbound Window Segment 2 Register 6 */
        uint32_t	rows3r6;	/* 0xd0cdc - RapidIO Outbound Window Segment 3 Register 6 */
        uint32_t	rowtar7;	/* 0xd0ce0 - RapidIO Outbound Window Translation Address Register 7 */
        uint32_t	rowtear7;	/* 0xd0ce4 - RapidIO Outbound Window Translation Ext. Address Register 7 */
        uint32_t	rowbar7;	/* 0xd0ce8 - RapidIO Outbound Window Base Address Register 7 */
        uint8_t	res33[4];
        uint32_t	rowar7;		/* 0xd0cf0 - RapidIO Outbound Attributes Register 7 */
        uint32_t	rows1r7;	/* 0xd0cf4 - RapidIO Outbound Window Segment 1 Register 7 */
        uint32_t	rows2r7;	/* 0xd0cf8 - RapidIO Outbound Window Segment 2 Register 7 */
        uint32_t	rows3r7;	/* 0xd0cfc - RapidIO Outbound Window Segment 3 Register 7 */
        uint32_t	rowtar8;	/* 0xd0d00 - RapidIO Outbound Window Translation Address Register 8 */
        uint32_t	rowtear8;	/* 0xd0d04 - RapidIO Outbound Window Translation Ext. Address Register 8 */
        uint32_t	rowbar8;	/* 0xd0d08 - RapidIO Outbound Window Base Address Register 8 */
        uint8_t	res34[4];
        uint32_t	rowar8;		/* 0xd0d10 - RapidIO Outbound Attributes Register 8 */
        uint32_t	rows1r8;	/* 0xd0d14 - RapidIO Outbound Window Segment 1 Register 8 */
        uint32_t	rows2r8;	/* 0xd0d18 - RapidIO Outbound Window Segment 2 Register 8 */
        uint32_t	rows3r8;	/* 0xd0d1c - RapidIO Outbound Window Segment 3 Register 8 */
        uint8_t	res35[64];
        uint32_t	riwtar4;	/* 0xd0d60 - RapidIO Inbound Window Translation Address Register 4 */
        uint32_t	riwbar4;	/* 0xd0d68 - RapidIO Inbound Window Base Address Register 4 */
        uint8_t	res36[4];
        uint32_t	riwar4;		/* 0xd0d70 - RapidIO Inbound Attributes Register 4 */
        uint8_t	res37[12];
        uint32_t	riwtar3;	/* 0xd0d80 - RapidIO Inbound Window Translation Address Register 3 */
        uint8_t	res38[4];
        uint32_t	riwbar3;	/* 0xd0d88 - RapidIO Inbound Window Base Address Register 3 */
        uint8_t	res39[4];
        uint32_t	riwar3;		/* 0xd0d90 - RapidIO Inbound Attributes Register 3 */
        uint8_t	res40[12];
        uint32_t	riwtar2;	/* 0xd0da0 - RapidIO Inbound Window Translation Address Register 2 */
        uint8_t	res41[4];
        uint32_t	riwbar2;	/* 0xd0da8 - RapidIO Inbound Window Base Address Register 2 */
        uint8_t	res42[4];
        uint32_t	riwar2;		/* 0xd0db0 - RapidIO Inbound Attributes Register 2 */
        uint8_t	res43[12];
        uint32_t	riwtar1;	/* 0xd0dc0 - RapidIO Inbound Window Translation Address Register 1 */
        uint8_t	res44[4];
        uint32_t	riwbar1;	/* 0xd0dc8 - RapidIO Inbound Window Base Address Register 1 */
        uint8_t	res45[4];
        uint32_t	riwar1;		/* 0xd0dd0 - RapidIO Inbound Attributes Register 1 */
        uint8_t	res46[12];
        uint32_t	riwtar0;	/* 0xd0de0 - RapidIO Inbound Window Translation Address Register 0 */
        uint8_t	res47[12];
        uint32_t	riwar0;		/* 0xd0df0 - RapidIO Inbound Attributes Register 0 */
        uint8_t	res48[12];
        uint32_t	pnfedr;		/* 0xd0e00 - Port Notification/Fatal Error Detect Register */
        uint32_t	pnfedir;	/* 0xd0e04 - Port Notification/Fatal Error Detect Register */
        uint32_t	pnfeier;	/* 0xd0e08 - Port Notification/Fatal Error Interrupt Enable Register */
        uint32_t	pecr;		/* 0xd0e0c - Port Error Control Register */
        uint32_t	pepcsr0;	/* 0xd0e10 - Port Error Packet/Control Symbol Register 0 */
        uint32_t	pepr1;		/* 0xd0e14 - Port Error Packet Register 1 */
        uint32_t	pepr2;		/* 0xd0e18 - Port Error Packet Register 2 */
        uint8_t	res49[4];
        uint32_t	predr;		/* 0xd0e20 - Port Recoverable Error Detect Register */
        uint8_t	res50[4];
        uint32_t	pertr;		/* 0xd0e28 - Port Error Recovery Threshold Register */
        uint32_t	prtr;		/* 0xd0e2c - Port Retry Threshold Register */
        uint8_t	res51[8656];
        uint32_t	omr;		/* 0xd3000 - Outbound Mode Register */
        uint32_t	osr;		/* 0xd3004 - Outbound Status Register */
        uint32_t	eodqtpar;	/* 0xd3008 - Extended Outbound Descriptor Queue Tail Pointer Address Register */
        uint32_t	odqtpar;	/* 0xd300c - Outbound Descriptor Queue Tail Pointer Address Register */
        uint32_t	eosar;		/* 0xd3010 - Extended Outbound Unit Source Address Register */
        uint32_t	osar;		/* 0xd3014 - Outbound Unit Source Address Register */
        uint32_t	odpr;		/* 0xd3018 - Outbound Destination Port Register */
        uint32_t	odatr;		/* 0xd301c - Outbound Destination Attributes Register */
        uint32_t	odcr;		/* 0xd3020 - Outbound Doubleword Count Register */
        uint32_t	eodqhpar;	/* 0xd3024 - Extended Outbound Descriptor Queue Head Pointer Address Register */
        uint32_t	odqhpar;	/* 0xd3028 - Outbound Descriptor Queue Head Pointer Address Register */
        uint32_t	oretr;	        /* 0xd302C - Outbound Retry Error Threshold Register */
        uint32_t	omgr;	        /* 0xd3030 - Outbound Multicast Group Register */
        uint32_t	omlr;	        /* 0xd3034 - Outbound Multicast List Register */
        uint8_t	res52[40];
        uint32_t	imr;		/* 0xd3060 - Outbound Mode Register */
        uint32_t	isr;		/* 0xd3064 - Inbound Status Register */
        uint32_t	eidqtpar;	/* 0xd3068 - Extended Inbound Descriptor Queue Tail Pointer Address Register */
        uint32_t	idqtpar;	/* 0xd306c - Inbound Descriptor Queue Tail Pointer Address Register */
        uint32_t	eifqhpar;	/* 0xd3070 - Extended Inbound Frame Queue Head Pointer Address Register */
        uint32_t	ifqhpar;	/* 0xd3074 - Inbound Frame Queue Head Pointer Address Register */
        uint32_t	imirir;	        /* 0xd3078 - Inbound Maximum Interrutp Report Interval Register */
        uint8_t	res53[900];
        uint32_t	oddmr;		/* 0xd3400 - Outbound Doorbell Mode Register */
        uint32_t	oddsr;		/* 0xd3404 - Outbound Doorbell Status Register */
        uint8_t	res54[16];
        uint32_t	oddpr;		/* 0xd3418 - Outbound Doorbell Destination Port Register */
        uint32_t	oddatr;		/* 0xd341C - Outbound Doorbell Destination Attributes Register */
        uint8_t	res55[12];
        uint32_t	oddretr;	/* 0xd342C - Outbound Doorbell Retry Threshold Configuration Register */
        uint8_t	res56[48];
        uint32_t	idmr;		/* 0xd3460 - Inbound Doorbell Mode Register */
        uint32_t	idsr;		/* 0xd3464 - Inbound Doorbell Status Register */
        uint32_t	iedqtpar;	/* 0xd3468 - Extended Inbound Doorbell Queue Tail Pointer Address Register */
        uint32_t	iqtpar;	        /* 0xd346c - Inbound Doorbell Queue Tail Pointer Address Register */
        uint32_t	iedqhpar;	/* 0xd3470 - Extended Inbound Doorbell Queue Head Pointer Address Register */
        uint32_t	idqhpar;	/* 0xd3474 - Inbound Doorbell Queue Head Pointer Address Register */
        uint32_t	idmirir;	/* 0xd3478 - Inbound Doorbell Max Interrupt Report Interval Register */
        uint8_t	res57[100];
        uint32_t	pwmr;		/* 0xd34e0 - Port-Write Mode Register */
        uint32_t	pwsr;		/* 0xd34e4 - Port-Write Status Register */
        uint32_t	epwqbar;	/* 0xd34e8 - Extended Port-Write Queue Base Address Register */
        uint32_t	pwqbar;		/* 0xd34ec - Port-Write Queue Base Address Register */
        uint8_t	res58[51984];
} ccsr_rio_t;

/* Global Utilities Register Block(0xe_0000-0xf_ffff) */
typedef struct ccsr_gur {
        uint32_t	porpllsr;	/* 0xe0000 - POR PLL ratio status register */
        uint32_t	porbmsr;	/* 0xe0004 - POR boot mode status register */
#define MPC8610_PORBMSR_HA      0x00070000
#define MPC8610_PORBMSR_HA_SHIFT	16
#define MPC8641_PORBMSR_HA      0x00060000
#define MPC8641_PORBMSR_HA_SHIFT	17
        uint32_t	porimpscr;	/* 0xe0008 - POR I/O impedance status and control register */
        uint32_t	pordevsr;	/* 0xe000c - POR I/O device status regsiter */
#define MPC8610_PORDEVSR_IO_SEL		0x00380000
#define MPC8610_PORDEVSR_IO_SEL_SHIFT		19
#define MPC8641_PORDEVSR_IO_SEL		0x000F0000
#define MPC8641_PORDEVSR_IO_SEL_SHIFT		16
#define MPC86xx_PORDEVSR_CORE1TE	0x00000080 /* ASMP (Core1 addr trans) */
        uint32_t	pordbgmsr;	/* 0xe0010 - POR debug mode status register */
        uint8_t	res1[12];
        uint32_t	gpporcr;	/* 0xe0020 - General-purpose POR configuration register */
        uint8_t	res2[12];
        uint32_t	gpiocr;		/* 0xe0030 - GPIO control register */
        uint8_t	res3[12];
        uint32_t	gpoutdr;	/* 0xe0040 - General-purpose output data register */
        uint8_t	res4[12];
        uint32_t	gpindr;		/* 0xe0050 - General-purpose input data register */
        uint8_t	res5[12];
        uint32_t	pmuxcr;		/* 0xe0060 - Alternate function signal multiplex control */
        uint8_t	res6[12];
        uint32_t	devdisr;	/* 0xe0070 - Device disable control */
#define MPC86xx_DEVDISR_PCIEX1	0x80000000
#define MPC86xx_DEVDISR_PCIEX2	0x40000000
#define MPC86xx_DEVDISR_PCI1	0x80000000
#define MPC86xx_DEVDISR_PCIE1	0x40000000
#define MPC86xx_DEVDISR_PCIE2	0x20000000
        uint8_t	res7[12];
        uint32_t	powmgtcsr;	/* 0xe0080 - Power management status and control register */
        uint8_t	res8[12];
        uint32_t	mcpsumr;	/* 0xe0090 - Machine check summary register */
        uint32_t	rstrscr;	/* 0xe0094 - Reset request status and control register */
        uint8_t	res9[8];
        uint32_t	pvr;		/* 0xe00a0 - Processor version register */
        uint32_t	svr;		/* 0xe00a4 - System version register */
        uint8_t	res10a[8];
        uint32_t	rstcr;		/* 0xe00b0 - Reset control register */
#define MPC86xx_RSTCR_HRST_REQ	0x00000002
        uint8_t	res10b[1868];
        uint32_t	clkdvdr;	/* 0xe0800 - Clock Divide register */
        uint8_t	res10c[796];
        uint32_t	ddr1clkdr;	/* 0xe0b20 - DDRC1 Clock Disable register */
        uint8_t	res10d[4];
        uint32_t	ddr2clkdr;	/* 0xe0b28 - DDRC2 Clock Disable register */
        uint8_t	res10e[724];
        uint32_t	clkocr;		/* 0xe0e00 - Clock out select register */
        uint8_t	res11[12];
        uint32_t	ddrdllcr;	/* 0xe0e10 - DDR DLL control register */
        uint8_t	res12[12];
        uint32_t	lbcdllcr;	/* 0xe0e20 - LBC DLL control register */
        uint8_t	res13a[224];
        uint32_t	srds1cr0;	/* 0xe0f04 - SerDes1 control register 0 */
        uint8_t	res13b[4];
        uint32_t	srds1cr1;	/* 0xe0f08 - SerDes1 control register 1 */
        uint8_t	res14[24];
        uint32_t	ddrioovcr;	/* 0xe0f24 - DDR IO Overdrive Control register */
        uint8_t	res15a[24];
        uint32_t	srds2cr0;	/* 0xe0f40 - SerDes2 control register 0 */
        uint32_t	srds2cr1;	/* 0xe0f44 - SerDes2 control register 1 */
        uint8_t	res16[184];
} ccsr_gur_t;

/*
 * Watchdog register block(0xe_4000-0xe_4fff)
 */
typedef struct ccsr_wdt {
        uint32_t	res0;
        uint32_t	swcrr; /* System watchdog control register */
        uint32_t	swcnr; /* System watchdog count register */
        uint8_t	res1[2];
        uint16_t	swsrr; /* System watchdog service register */
        uint8_t	res2[4080];
} ccsr_wdt_t;

typedef struct immap {
        ccsr_local_mcm_t	im_local_mcm;
        ccsr_ddr_t		im_ddr1;
        ccsr_i2c_t		im_i2c;
        ccsr_duart_t		im_duart;
        ccsr_lbc_t		im_lbc;
        ccsr_ddr_t		im_ddr2;
        uint8_t                    res1[4096];
        ccsr_pex_t		im_pex1;
        ccsr_pex_t		im_pex2;
        ccsr_ht_t               im_ht;
        uint8_t                    res2[90112];
        ccsr_dma_t		im_dma;
        uint8_t                    res3[8192];
        ccsr_tsec_t		im_tsec1;
        ccsr_tsec_t		im_tsec2;
        ccsr_tsec_t             im_tsec3;
        ccsr_tsec_t             im_tsec4;
        uint8_t                    res4[98304];
        ccsr_pic_t		im_pic;
        uint8_t                    res5[389120];
        ccsr_rio_t		im_rio;
        ccsr_gur_t		im_gur;
        uint8_t			res6[12288];
        ccsr_wdt_t		im_wdt;
} immap_t;

#define immr ((volatile immap_t *)(CONFIG_CCSR_BASE))

#endif /*__IMMAP_86xx__*/
