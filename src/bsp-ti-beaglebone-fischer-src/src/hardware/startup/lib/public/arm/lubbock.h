/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"). You 
 * may not reproduce, modify or distribute this software except in 
 * compliance with the License. You may obtain a copy of the License 
 * at: http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as 
 * contributors under the License or as licensors under other terms.  
 * Please review this entire file for other proprietary rights or license 
 * notices, as well as the QNX Development Suite License Guide at 
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */




/*
 * Intel Lubbock Board
 *

 *
 */

#ifndef	ARM_LUBBOCK_H_INCLUDED
#define	ARM_LUBBOCK_H_INCLUDED

#define	LUBBOCK_REG_BASE		0x08000000		/* physical address */
#define	LUBBOCK_REG_SIZE		0x00000100		/* size of register space */

/*
 * Register offsets from LUBBOCK_REG_BASE
 */

#define	LUBBOCK_ID				0x00		/* system ID register */
#define	LUBBOCK_HEX_LED			0x10		/* hex led values */
#define	LUBBOCK_LED_CTRL		0x40		/* hex/discrete led control */
#define	LUBBOCK_CFG_SWTCH		0x50		/* configuration switches */
#define	LUBBOCK_USR_SWTCH		0x60		/* discrete/rotary switches */
#define	LUBBOCK_MISCW			0x80		/* misc write register */
#define	LUBBOCK_MISCR			0x90		/* misc read register */
#define	LUBBOCK_INT_MASK		0xc0		/* interrupt mask register */
#define	LUBBOCK_INT_SET			0xd0		/* interrupt set/clear */

/*
 * Configuration switch bits
 */
#define	LUBBOCK_CFG_nWRPT		0x0002		/* 0 = write-protected */
#define	LUBBOCK_CFG_nROMBOOT	0x0001		/* 0 = boot from ROM */

/*
 * Misc write register bits
 */
#define	LUBBOCK_MISCW_SYS_RST	0x0001		/* reset processor board  */
#define	LUBBOCK_MISCW_PC_RST	0x0002		/* reset peripheral board */
#define	LUBBOCK_MISCW_nEN16		0x0004		/* ethernet data width */
#define	LUBBOCK_MISCW_GREEN_LED	0x0008
#define	LUBBOCK_MISCW_IRDA_FIR	0x0010		/* 0 = SIR, 1 = FIR */
#define	LUBBOCK_MISCW_LCD_DISP	0x0100		/* 1 = LCD panel on */
#define	LUBBOCK_MISCW_TS_nCS	0x0800		/* 0 = enable Burr Brown */
#define	LUBBOCK_MISCW_DTR		0x1000
#define	LUBBOCK_MISCW_S1_MASK	0xc000
#define	LUBBOCK_MISCW_S1_0V		0x0000		/* 0V   to CF socket */
#define	LUBBOCK_MISCW_S1_33V	0x4000		/* 3.3V to CF socket */
#define	LUBBOCK_MISCW_S1_50V	0x8000		/* 5.0V to CF socket */

/*
 * Interrupt control register bits
 */
#define	LUBBOCK_INT_MMC_IN		0x0001		/* MMC/SD inserted */
#define	LUBBOCK_INT_SA1111		0x0002		/* SA1111 interrupt */
#define	LUBBOCK_INT_USB			0x0004		/* USB client interrupt */
#define	LUBBOCK_INT_ENET		0x0008		/* ethernet interrupt */
#define	LUBBOCK_INT_UCB1400		0x0010		/* UCB1400 interrupt */
#define	LUBBOCK_INT_BB_PEN		0x0020		/* Burr Brown interrupt */

#endif

/* __SRCVERSION("lubbock.h $Rev: 655042 $"); */
