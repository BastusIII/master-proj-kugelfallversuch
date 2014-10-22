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
 * TI OMAP2420 processor with ARM1136JF-S core
 */

#ifndef	__ARM_OMAP2420_H_INCLUDED
#define	__ARM_OMAP2420_H_INCLUDED

/* 
 * System Control module
 */
#define	OMAP2420_SYSCTL_BASE		0x48000000
#define	OMAP2420_SYSCTL_SIZE		0x1000

/* 
 * System Control Registers, offset from base
 */
#define	OMAP2420_SYSCTL_REVISION	0x000
#define	OMAP2420_SYSCTL_SYSCONFIG	0x010
#define	OMAP2420_SYSCTL_PADCONF(x)	(0x030 + (x) * 4)
#define	OMAP2420_SYSCTL_DEBOBS		0x270
#define	OMAP2420_SYSCTL_DEVCONF		0x274
#define	OMAP2420_SYSCTL_SUPPORT		0x28C
#define	OMAP2420_SYSCTL_MSUSPENDMUX_0	0x290
#define	OMAP2420_SYSCTL_MSUSPENDMUX_1	0x294
#define	OMAP2420_SYSCTL_MSUSPENDMUX_2	0x298
#define	OMAP2420_SYSCTL_MSUSPENDMUX_3	0x29C
#define	OMAP2420_SYSCTL_MSUSPENDMUX_4	0x2A0
#define	OMAP2420_SYSCTL_MSUSPENDMUX_5	0x2A4
#define	OMAP2420_SYSCTL_SEC_CTRL	0x2B0
#define	OMAP2420_SYSCTL_SEC_TEST	0x2B4
#define	OMAP2420_SYSCTL_PSA_CTRL	0x2B8
#define	OMAP2420_SYSCTL_PSA_CMD		0x2BC
#define	OMAP2420_SYSCTL_PSA_VALUE	0x2C0
#define	OMAP2420_SYSCTL_SEC_EMU		0x2D0
#define	OMAP2420_SYSCTL_SEC_TAP		0x2D4
#define	OMAP2420_SYSCTL_OCM_RAM_PERM	0x2D8
#define	OMAP2420_SYSCTL_OCM_PUB_RAM_ADD	0x2DC
#define	OMAP2420_SYSCTL_EXT_SEC_RAM_START_ADD	0x2E0
#define	OMAP2420_SYSCTL_EXT_SEC_RAM_STOP_ADD	0x2E4
#define	OMAP2420_SYSCTL_SEC_STATUS	0x2F0
#define	OMAP2420_SYSCTL_SEC_ERR_STATUS	0x2F4
#define	OMAP2420_SYSCTL_STATUS		0x2F8
#define	OMAP2420_SYSCTL_GENERAL_PURPOSE_STATUS	0x2FC
#define	OMAP2420_SYSCTL_RPUB_KEY_H_0	0x300
#define OMAP2420_SYSCTL_RPUB_KEY_H_1	0x304
#define	OMAP2420_SYSCTL_RPUB_KEY_H_2	0x308
#define	OMAP2420_SYSCTL_RPUB_KEY_H_3	0x30C
#define	OMAP2420_SYSCTL_RAND_KEY_0		0x310
#define	OMAP2420_SYSCTL_RAND_KEY_1		0x314
#define	OMAP2420_SYSCTL_RAND_KEY_2		0x318
#define	OMAP2420_SYSCTL_RAND_KEY_3		0x31C
#define	OMAP2420_SYSCTL_CUST_KEY_0		0x320
#define	OMAP2420_SYSCTL_CUST_KEY_1		0x324
#define	OMAP2420_SYSCTL_TEST_KEY_0		0x330
#define	OMAP2420_SYSCTL_TEST_KEY_1		0x334
#define	OMAP2420_SYSCTL_TEST_KEY_2		0x338
#define	OMAP2420_SYSCTL_TEST_KEY_3		0x33C
#define	OMAP2420_SYSCTL_TEST_KEY_4		0x340
#define	OMAP2420_SYSCTL_TEST_KEY_5		0x344
#define	OMAP2420_SYSCTL_TEST_KEY_6		0x348
#define	OMAP2420_SYSCTL_TEST_KEY_7		0x34C
#define	OMAP2420_SYSCTL_TEST_KEY_8		0x350
#define	OMAP2420_SYSCTL_TEST_KEY_9		0x354


/* 
 * Power, reset and clock management module
 */
#define	OMAP2420_PRCM_BASE			0x48008000
#define	OMAP2420_PRCM_SIZE			0x1000

/* 
 * Power, reset and Clock management Registers, offset from base
 */
#define	OMAP2420_PRCM_REVISION		0x000
#define	OMAP2420_PRCM_SYSCONFIG		0x010
#define	OMAP2420_PRCM_IRQSTATUS_MPU	0x018
#define	OMAP2420_PRCM_IRQENABLE_MPU	0x01C
#define	OMAP2420_PRCM_VOLTCTRL		0x050
#define	OMAP2420_PRCM_VOLTST		0x054
#define	OMAP2420_PRCM_CLKSRC_CTRL	0x060
#define	OMAP2420_PRCM_CLKOUT_CTRL	0x070
#define	OMAP2420_PRCM_CLKEMUL_CTRL	0x078
#define	OMAP2420_PRCM_CLKCFG_CTRL	0x080
#define	OMAP2420_PRCM_CLKCFG_STATUS	0x084
#define	OMAP2420_PRCM_VOLTSETUP		0x090
#define	OMAP2420_PRCM_CLKSSETUP		0x094
#define	OMAP2420_PRCM_POLCTRL		0x098
#define	OMAP2420_GENERAL_PURPOSE1	0x0B0
#define	OMAP2420_GENERAL_PURPOSE2	0x0B4
#define	OMAP2420_GENERAL_PURPOSE3	0x0B8
#define	OMAP2420_GENERAL_PURPOSE4	0x0BC
#define	OMAP2420_GENERAL_PURPOSE5	0x0C0
#define	OMAP2420_GENERAL_PURPOSE6	0x0C4
#define	OMAP2420_GENERAL_PURPOSE7	0x0C8
#define	OMAP2420_GENERAL_PURPOSE8	0x0CC
#define	OMAP2420_GENERAL_PURPOSE9	0x0D0
#define	OMAP2420_GENERAL_PURPOSE10	0x0D4
#define	OMAP2420_GENERAL_PURPOSE11	0x0D8
#define	OMAP2420_GENERAL_PURPOSE12	0x0DC
#define	OMAP2420_GENERAL_PURPOSE13	0x0E0
#define	OMAP2420_GENERAL_PURPOSE14	0x0E4
#define	OMAP2420_GENERAL_PURPOSE15	0x0E8
#define	OMAP2420_GENERAL_PURPOSE16	0x0EC
#define	OMAP2420_GENERAL_PURPOSE17	0x0F0
#define	OMAP2420_GENERAL_PURPOSE18	0x0F4
#define	OMAP2420_GENERAL_PURPOSE19	0x0F8
#define	OMAP2420_GENERAL_PURPOSE20	0x0FC
#define	OMAP2420_CM_CLKSEL_MPU		0x140
#define	OMAP2420_CM_CLKSTCTRL_MPU	0x148
#define	OMAP2420_RM_RSTST_MPU		0x158
#define	OMAP2420_PM_WKDEP_MPU		0x1C8
#define	OMAP2420_PM_EVGENCTRL_MPU	0x1D4
#define	OMAP2420_PM_EVEGENONTIM_MPU	0x1D8
#define	OMAP2420_PM_EVEGENOFFTIM_MPU	0x1DC
#define	OMAP2420_PM_PWSTCTRL_MPU	0x1E0
#define	OMAP2420_PM_PWSTST_MPU		0x1E4
#define	OMAP2420_CM_FCLKEN1_CORE	0x200
#define	OMAP2420_CM_FCLKEN2_CORE	0x204
#define	OMAP2420_CM_ICLKEN1_CORE	0x210
#define	OMAP2420_CM_ICLKEN2_CORE	0x214
#define	OMAP2420_CM_ICLKEN4_CORE	0x21C
#define	OMAP2420_CM_IDLEST1_CORE	0x220
#define	OMAP2420_CM_IDLEST2_CORE	0x224
#define	OMAP2420_CM_IDLEST4_CORE	0x22C
#define	OMAP2420_CM_AUTOIDLE1_CORE	0x230
#define	OMAP2420_CM_AUTOIDLE2_CORE	0x234
#define	OMAP2420_CM_AUTOIDLE3_CORE	0x238
#define	OMAP2420_CM_AUTOIDLE4_CORE	0x23C
#define	OMAP2420_CM_CLKSEL1_CORE	0x240
#define	OMAP2420_CM_CLKSEL2_CORE	0x244
#define	OMAP2420_CM_CLKSTCTRL_CORE	0x248
#define	OMAP2420_PM_WKEN1_CORE		0x2A0
#define	OMAP2420_PM_WKEN2_CORE		0x2A4
#define	OMAP2420_PM_WKST1_CORE		0x2B0
#define	OMAP2420_PM_WKST2_CORE		0x2B4
#define	OMAP2420_PM_WKDEP_CORE		0x2C8
#define	OMAP2420_PM_PWSTCTRL_CORE	0x2E0
#define	OMAP2420_PM_PWSTST_CORE		0x2E4
#define	OMAP2420_CM_FCLKEN_GFX		0x300
#define	OMAP2420_CM_ICLKEN_GFX		0x310
#define	OMAP2420_CM_IDLEST_GFX		0x320
#define	OMAP2420_CM_CLKSEL_GFX		0x340
#define	OMAP2420_CM_CLKSTCTRL_GFX	0x348
#define	OMAP2420_RM_RSTCTRL_GFX		0x350
#define	OMAP2420_RM_RSTST_GFX		0x358
#define	OMAP2420_PM_WKDEP_GFX		0x3C8
#define	OMAP2420_PM_PWSTCTRL_GFX	0x3E0
#define	OMAP2420_PM_PWSTST_GFX		0x3E4
#define	OMAP2420_CM_FCLKEN_WKUP		0x400
#define	OMAP2420_CM_ICLKEN_WKUP		0x410
#define	OMAP2420_CM_IDLEST_WKUP		0x420
#define	OMAP2420_CM_AUTOIDLE_WKUP	0x430
#define	OMAP2420_CM_CLKSEL_WKUP		0x440
#define	OMAP2420_RM_RSTCTRL_WKUP	0x450
#define	OMAP2420_RM_RSTTIME_WKUP	0x454
#define	OMAP2420_RM_RSTST_WKUP		0x458
#define	OMAP2420_PM_WKEN_WKUP		0x4A0
#define	OMAP2420_PM_WKST_WKUP		0x4B0
#define	OMAP2420_CM_CLKEN_PLL		0x500
#define	OMAP2420_CM_IDLEST_CKGEN	0x520
#define	OMAP2420_CM_AUTOIDLE_PLL	0x530
#define	OMAP2420_CM_CLKSEL1_PLL		0x540
#define	OMAP2420_CM_CLKSEL2_PLL		0x544
#define	OMAP2420_CM_FCLKEN_DSP		0x800
#define	OMAP2420_CM_ICLKEN_DSP		0x810
#define	OMAP2420_CM_IDLEST_DSP		0x820
#define	OMAP2420_CM_AUTOIDLE_DSP	0x830
#define	OMAP2420_CM_CLKSEL_DSP		0x840
#define	OMAP2420_CM_CLKSTCTRL_DSP	0x848
#define	OMAP2420_RM_RSTCTRL_DSP		0x850
#define	OMAP2420_RM_RSTST_DSP		0x858
#define	OMAP2420_PM_WKDEP_DSP		0x8C8
#define	OMAP2420_PM_PWSTCTRL_DSP	0x8E0
#define	OMAP2420_PM_PWSTST_DSP		0x8E4
#define	OMAP2420_PRCM_IRQSTATUS_DSP	0x8F0
#define	OMAP2420_PRCM_IRQENABLE_DSP	0x8F4
#define	OMAP2420_PRCM_IRQSTATUS_IVA	0x8F8
#define	OMAP2420_PRCM_IRQENABLE_IVA	0x8FC

/*
 * Watchdog Timer
 */
#define	OMAP2420_WDT1_BASE			0x48020000
#define	OMAP2420_WDT2_BASE			0x48022000
#define	OMAP2420_WDT3_BASE			0x48024000
#define	OMAP2420_WDT4_BASE			0x48026000
#define	OMAP2420_WDT_SIZE			0x1000

/*
 * Watchdog Timer Registers, offset from base
 */
#define	OMAP2420_WIDR				0x00
#define	OMAP2420_WD_SYSCONFIG		0x10
#define	OMAP2420_WD_SYSSTATUS		0x14
#define	OMAP2420_WCLR				0x24
#define	OMAP2420_WCRR				0x28
#define	OMAP2420_WLDR				0x2C
#define	OMAP2420_WTGR				0x30
#define	OMAP2420_WWPS				0x34
#define	OMAP2420_WSPR				0x48


/*
 * General-Purpose Timer
 */
#define	OMAP2420_GPT1_BASE			0x48028000
#define	OMAP2420_GPT2_BASE			0x4802A000
#define	OMAP2420_GPT3_BASE			0x48078000
#define	OMAP2420_GPT4_BASE			0x4807A000
#define	OMAP2420_GPT5_BASE			0x4807C000
#define	OMAP2420_GPT6_BASE			0x4807E000
#define	OMAP2420_GPT7_BASE			0x48080000
#define	OMAP2420_GPT8_BASE			0x48082000
#define	OMAP2420_GPT9_BASE			0x48084000
#define	OMAP2420_GPT10_BASE			0x48086000
#define	OMAP2420_GPT11_BASE			0x48088000
#define	OMAP2420_GPT12_BASE			0x4808A000
#define	OMAP2420_GPT_SIZE			0x1000

/*
 * General-Purpose Timer Registers, offset from base
 */
#define	OMAP2420_GPT_TIDR			0x00
#define	OMAP2420_GPT_TIOCP_CFG		0x10
#define	OMAP2420_GPT_TISTAT			0x14
#define	OMAP2420_GPT_TISR			0x18
#define	OMAP2420_GPT_TIER			0x1C
#define	OMAP2420_GPT_TWER			0x20
#define	OMAP2420_GPT_TCLR			0x24
#define	OMAP2420_GPT_TCRR			0x28
#define	OMAP2420_GPT_TLDR			0x2C
#define	OMAP2420_GPT_TTGR			0x30
#define	OMAP2420_GPT_TWPS			0x34
#define	OMAP2420_GPT_TMAR			0x38
#define	OMAP2420_GPT_TCAR1			0x3C
#define	OMAP2420_GPT_TSICR			0x40
#define	OMAP2420_GPT_TCAR2			0x44

/*
 * USB
 */
#define	OMAP2420_USB_BASE			0x4805E000
#define	OMAP2420_USB_SIZE			0x1000

/*
 * UARTs
 */
#define	OMAP2420_UART1_BASE			0x4806A000
#define	OMAP2420_UART2_BASE			0x4806C000
#define	OMAP2420_UART3_BASE			0x4806E000
#define	OMAP2420_UART_SIZE			0x1000

/* 
 * Interrupt Controller
 */
#define	OMAP2420_INTC_BASE	0x480FE000
#define	OMAP2420_INTC_SIZE	0x280

/* 
 * Interrupt controller registers,
 * offset from base
 */

#define	OMAP2420_INTC_REVISION		0x000
#define	OMAP2420_INTC_SYSCONFIG		0x010
#define	OMAP2420_INTC_SYSSTATUS		0x014
#define	OMAP2420_INTC_SIR_IRQ		0x040
#define	OMAP2420_INTC_SIR_FIQ		0x044
#define	OMAP2420_INTC_CONTROL		0x048
#define	OMAP2420_INTC_PROTECTION	0x04C
#define	OMAP2420_INTC_IDLE			0x050
#define	OMAP2420_INTC_ITR0			0x080
#define	OMAP2420_INTC_MIR0			0x084
#define	OMAP2420_INTC_MIR_CLEAR0	0x088
#define	OMAP2420_INTC_MIR_SET0		0x08C
#define	OMAP2420_INTC_ISR_SET0		0x090
#define	OMAP2420_INTC_ISR_CLEAR0	0x094
#define	OMAP2420_INTC_PENDING_IRQ0	0x098
#define	OMAP2420_INTC_PENDING_FIQ0	0x09C
#define	OMAP2420_INTC_ITR1			0x0A0
#define	OMAP2420_INTC_MIR1			0x0A4
#define	OMAP2420_INTC_MIR_CLEAR1	0x0A8
#define	OMAP2420_INTC_MIR_SET1		0x0AC
#define	OMAP2420_INTC_ISR_SET1		0x0B0
#define	OMAP2420_INTC_ISR_CLEAR1	0x0B4
#define	OMAP2420_INTC_PENDING_IRQ1	0x0B8
#define	OMAP2420_INTC_PENDING_FIQ1	0x0BC
#define	OMAP2420_INTC_ITR2			0x0C0
#define	OMAP2420_INTC_MIR2			0x0C4
#define	OMAP2420_INTC_MIR_CLEAR2	0x0C8
#define	OMAP2420_INTC_MIR_SET2		0x0CC
#define	OMAP2420_INTC_ISR_SET2		0x0D0
#define	OMAP2420_INTC_ISR_CLEAR2	0x0D4
#define	OMAP2420_INTC_PENDING_IRQ2	0x0D8
#define	OMAP2420_INTC_PENDING_FIQ2	0x0DC
#define	OMAP2420_INTC_ILR(n)		(0x100 + (n) * 4)

/*
 * GPIOs 
 */
#define	OMAP2420_GPIO1_BASE			0x48018000
#define	OMAP2420_GPIO2_BASE			0x4801A000
#define	OMAP2420_GPIO3_BASE			0x4801C000
#define	OMAP2420_GPIO4_BASE			0x4801E000
#define	OMAP2420_GPIO_SIZE			0x100

#define	OMAP2420_GPIO_REVISION		0x00
#define	OMAP2420_GPIO_SYSCONFIG		0x10
#define	OMAP2420_GPIO_SYSSTATUS		0x14
#define	OMAP2420_GPIO_IRQSTATUS1	0x18
#define	OMAP2420_GPIO_IRQENABLE1	0x1C
#define	OMAP2420_GPIO_WAKEUPENABLE	0x20
#define	OMAP2420_GPIO_IRQSTATUS2	0x28
#define	OMAP2420_GPIO_IRQENABLE2	0x2C
#define	OMAP2420_GPIO_CTRL			0x30
#define	OMAP2420_GPIO_OE			0x34
#define	OMAP2420_GPIO_DATAIN		0x38
#define	OMAP2420_GPIO_DATAOUT		0x3C
#define	OMAP2420_GPIO_LEVELDETECT0	0x40
#define	OMAP2420_GPIO_LEVELDETECT1	0x44
#define	OMAP2420_GPIO_RISINGDETECT	0x48
#define	OMAP2420_GPIO_FALLINGDETECT	0x4C
#define	OMAP2420_GPIO_DEBOUNCENABLE	0x50
#define	OMAP2420_GPIO_DEBOUNCINGTIME	0x54
#define	OMAP2420_GPIO_CLEARIRQENABLE1	0x60
#define	OMAP2420_GPIO_SETIRQENABLE1	0x64
#define	OMAP2420_GPIO_CLEARIRQENABLE2	0x70
#define	OMAP2420_GPIO_SETIRQENABLE2	0x74
#define	OMAP2420_GPIO_CLEARWKUENA	0x80
#define	OMAP2420_GPIO_SETWKUENA		0x84
#define	OMAP2420_GPIO_CLEARDATAOUT	0x90
#define	OMAP2420_GPIO_SETDATAOUT	0x94

/*
 * SMS
 */
#define	OMAP2420_SMS_BASE			0x68008000
#define	OMAP2420_SMS_SIZE			0x1000


/*
 * SDRC
 */
#define	OMAP2420_SDRC_BASE			0x68009000
#define	OMAP2420_SDRC_SIZE			0x1000

/* SDRC Registers, offset from base */
#define	OMAP2420_SDRC_REVISION		0x00
#define	OMAP2420_SDRC_SYSCONFIG		0x10
#define	OMAP2420_SDRC_SYSSTATUS		0x14
#define	OMAP2420_SDRC_CS_CFG		0x40
#define	OMAP2420_SDRC_SHARING		0x44
#define	OMAP2420_SDRC_ERR_ADDR		0x48
#define	OMAP2420_SDRC_ERR_TYPE		0x4C
#define	OMAP2420_SDRC_DLLA_CTRL		0x60
#define	OMAP2420_SDRC_DLLA_STATUS	0x64
#define	OMAP2420_SDRC_DLLB_CTRL		0x68
#define	OMAP2420_SDRC_DLLB_STATUS	0x6C
#define	OMAP2420_SDRC_POWER			0x70
#define	OMAP2420_SDRC_MCFG_0		0x80
#define	OMAP2420_SDRC_MR_0			0x84
#define	OMAP2420_SDRC_EMR1_0		0x88
#define	OMAP2420_SDRC_EMR2_0		0x8C
#define	OMAP2420_SDRC_EMR3_0		0x90
#define	OMAP2420_SDRC_DCDL1_CTRL	0x94
#define	OMAP2420_SDRC_DCDL2_CTRL	0x98
#define	OMAP2420_SDRC_ACTIM_CTRLA_0	0x9C
#define	OMAP2420_SDRC_ACTIM_CTRLB_0	0xA0
#define	OMAP2420_SDRC_RFR_CTRL_0	0xA4
#define	OMAP2420_SDRC_MANUAL_0		0xA8
#define	OMAP2420_SDRC_MCFG_1		0xB0
#define	OMAP2420_SDRC_MR_1			0xB4
#define	OMAP2420_SDRC_EMR1_1		0xB8
#define	OMAP2420_SDRC_EMR2_1		0xBC
#define	OMAP2420_SDRC_EMR3_1		0xC0
#define	OMAP2420_SDRC_ACTIM_CTRLA_1	0xC4
#define	OMAP2420_SDRC_ACTIM_CTRLB_1	0xC8
#define	OMAP2420_SDRC_RFR_CTRL_1	0xD4
#define	OMAP2420_SDRC_MANUAL_1		0xD8

/*
 * GPMC
 */
#define	OMAP2420_GPMC_BASE			0x6800A000
#define	OMAP2420_GPMC_SIZE			0x1000

/*
 * GPMC registers, offset from base address
 */
#define	OMAP2420_GPMC_REVISION		0x000
#define	OMAP2420_GPMC_SYSCONFIG		0x010
#define	OMAP2420_GPMC_SYSSTATUS		0x014
#define	OMAP2420_GPMC_IRQSTATUS		0x018
#define	OMAP2420_GPMC_IRQENABLE		0x01C
#define	OMAP2420_GPMC_TIMEOUT_CONTROL	0x040
#define	OMAP2420_GPMC_ERR_0DDRESS	0x044
#define	OMAP2420_GPMC_ERR_TYPE		0x048
#define	OMAP2420_GPMC_CONFIG		0x050
#define	OMAP2420_GPMC_STATUS		0x054
#define	OMAP2420_GPMC_CS0			0x060
#define	OMAP2420_GPMC_CS1			0x090
#define	OMAP2420_GPMC_CS2			0x0C0
#define	OMAP2420_GPMC_CS3			0x0F0
#define	OMAP2420_GPMC_CS4			0x120
#define	OMAP2420_GPMC_CS5			0x150
#define	OMAP2420_GPMC_CS6			0x180
#define	OMAP2420_GPMC_CS7			0x1B0
	#define	OMAP2420_GPMC_CONFIG1	0x00
	#define	OMAP2420_GPMC_CONFIG2	0x04
	#define	OMAP2420_GPMC_CONFIG3	0x08
	#define	OMAP2420_GPMC_CONFIG4	0x0C
	#define	OMAP2420_GPMC_CONFIG5	0x10
	#define	OMAP2420_GPMC_CONFIG6	0x14
	#define	OMAP2420_GPMC_CONFIG7	0x18
	#define	OMAP2420_GPMC_NAND_COMMAND	0x01C
	#define	OMAP2420_GPMC_NAND_ADDRESS	0x020
	#define	OMAP2420_GPMC_NAND_DATA		0x024
#define	OMAP2420_GPMC_PREFETCH_CONFIG1	0x1E0
#define	OMAP2420_GPMC_PREFETCH_CONFIG2	0x1E4
#define	OMAP2420_GPMC_PREFETCH_CONTROL	0x1EC
#define	OMAP2420_GPMC_PREFETCH_STATUS	0x1F0
#define	OMAP2420_GPMC_ECC_CONFIG	0x1F4
#define	OMAP2420_GPMC_ECC_CONTROL	0x1F8
#define	OMAP2420_GPMC_ECC_SIZE_CONFIG	0x1FC
#define	OMAP2420_GPMC_ECC1_RESULT	0x200
#define	OMAP2420_GPMC_ECC2_RESULT	0x204
#define	OMAP2420_GPMC_ECC3_RESULT	0x208
#define	OMAP2420_GPMC_ECC4_RESULT	0x20C
#define	OMAP2420_GPMC_ECC5_RESULT	0x210
#define	OMAP2420_GPMC_ECC6_RESULT	0x214
#define	OMAP2420_GPMC_ECC7_RESULT	0x218
#define	OMAP2420_GPMC_ECC8_RESULT	0x21C
#define	OMAP2420_GPMC_ECC9_RESULT	0x220
#define	OMAP2420_GPMC_TESTMODE_CTRL	0x230
#define	OMAP2420_GPMC_PSA_LSB		0x234
#define	OMAP2420_GPMC_PSA_MSB		0x238

#endif

/* __SRCVERSION("omap2420.h $Rev: 655042 $"); */
