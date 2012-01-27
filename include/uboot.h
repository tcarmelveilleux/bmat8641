/**
 * @file uboot.h
 *
 * @brief U-Boot interface description for U-Boot 1.3.0 on MPC8641HPCN (Simics 4.0.60)
 *
 * @date Created on: 2010-05-14
 *
 * @author Tennessee Carmel-Veilleux (tennessee.carmelveilleux -at- gmail.com)
 *
 * @version XM-PPC-2.2.2 rev $Rev$
 *
 * U-Boot public interface description for U-Boot 1.3.0 on MPC8641HPCN (Simics 4.0.60)
 *
 * This file contains the required definitions of external structures to
 * interface with U-Boot 1.3.0 as provided with Simics 4.0.60
 * (mpc8641-simple model).
 *
 * Originally obtained by preprocessing the global_data.h file from U-Boot 1.3.0
 * and then manually editing it for formatting and commenting.
 * U-Boot 1.3.0 can be found in the extras/u-boot-1.3.0.zip. U-Boot is licensed
 * under the GPL.
 *
 * Note that the U-Boot 1.3.0 sources in the extras/ directory are NOT the
 * Virtutech-modified files. However, the patches made by Virtutech do not
 * affect the public interface provided by U-Boot.
 *
 * Steps run to create this file:
 * 1- Start within u-boot-1.3.0 source root
 * 2- '$ export CROSS_COMPILE=powerpc-eabi-'
 * 3- '$ make MPC8641HPCN_config'
 * 4- '$ cd include'
 * 5- '$ gcc -include config.h -I. -E asm-ppc/global_data.h | grep "^[^#].*" > uboot_global.h'
 * 6- '$ gcc -include config.h -I. -E asm-ppc/u-boot.h | grep "^[^#].*" > uboot_uboot.h'
 * 7- '$ gcc -include config.h -I. -E exports.h | grep "^[^#].*" > uboot_exports.h'
 * 8- NOTE: 'grep "^[^#].*"' in pipelines is to remove preprocessor line
 *    number comments
 * 9- EDIT: Files uboot_global.h, uboot_uboot.h and uboot_exports.h were
 *    manually combined to create this file.
 * 9a- From uboot_uboot.h, the 'bd_t' type was extracted first. It was renamed
 *     as UBOOT_board_data_t.
 * 9b- From uboot_global.h, the 'gd_t' type was extracted next. It was renamed
 *     as UBOOT_global_data_t.
 * 9c- From uboot_exports.h, the enum at the end of the file, containing
 *     every UBOOT_EXPORT_* entry were extracted. They were renamed as
 *     UBOOT_EXPORT_*.
 * 10- The following function signatures were extracted from uboot_exports.h:
 *     get_version, getc, tstc, putc, puts, udelay, do_reset, getenv, setenv.
 *     They were renamed as UBOOT_*. */
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

#ifndef _UBOOT_H_
#define _UBOOT_H_

#ifdef __ASSEMBLY__

#define GLOBAL_DATA_POINTER_REG r29

#else
typedef struct uboot_bd_info {
    unsigned long bi_memstart;
    unsigned long bi_memsize;
    unsigned long bi_flashstart;
    unsigned long bi_flashsize;
    unsigned long bi_flashoffset;
    unsigned long bi_sramstart;
    unsigned long bi_sramsize;
    unsigned long bi_immr_base;
    unsigned long bi_bootflags;
    unsigned long bi_ip_addr;
    unsigned char bi_enetaddr[6];
    unsigned short bi_ethspeed;
    unsigned long bi_intfreq;
    unsigned long bi_busfreq;
    unsigned long bi_baudrate;
    unsigned char bi_enet1addr[6];
    unsigned char bi_enet2addr[6];
    unsigned char bi_enet3addr[6];
} UBOOT_board_data_t;

enum {
    UBOOT_EXPORT_get_version ,
    UBOOT_EXPORT_getc ,
    UBOOT_EXPORT_tstc ,
    UBOOT_EXPORT_putc ,
    UBOOT_EXPORT_puts ,
    UBOOT_EXPORT_printf ,
    UBOOT_EXPORT_install_hdlr ,
    UBOOT_EXPORT_free_hdlr ,
    UBOOT_EXPORT_malloc ,
    UBOOT_EXPORT_free ,
    UBOOT_EXPORT_udelay ,
    UBOOT_EXPORT_get_timer ,
    UBOOT_EXPORT_vprintf ,
    UBOOT_EXPORT_do_reset ,
    UBOOT_EXPORT_getenv ,
    UBOOT_EXPORT_setenv ,
    UBOOT_EXPORT_simple_strtoul ,
    UBOOT_EXPORT_simple_strtol ,
    UBOOT_EXPORT_strcmp ,
    UBOOT_EXPORT_i2c_write ,
    UBOOT_EXPORT_i2c_read ,
    UBOOT_EXPORT_MAX
};

typedef struct uboot_global_data {
    UBOOT_board_data_t *bd; /* Board data */
    unsigned long flags;
    unsigned long baudrate;
    unsigned long cpu_clk;
    unsigned long bus_clk;
    unsigned long ram_size;
    unsigned long reloc_off;
    unsigned long reset_status;
    unsigned long env_addr;
    unsigned long env_valid;
    unsigned long have_console;
    unsigned long fb_base;
    unsigned long kbd_status;
    unsigned long asmp;
    void *(*jt)[UBOOT_EXPORT_MAX]; /* Exports jump-table */
} UBOOT_global_data_t;
#endif /* !defined(__ASSEMBLY__) */

#endif /* _UBOOT_H_ */
