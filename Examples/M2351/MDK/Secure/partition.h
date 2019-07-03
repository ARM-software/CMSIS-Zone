/**************************************************************************//**
 * @file     partition.h
 * @brief    CMSIS-Core(M) Initial Setup for Secure / Non-Secure Zones for 
 *           Nuvoton M2351
 * @version  V1.0.0      (FreeMarker generated)
 * @date     03-Jul-2019 11:09:46
 ******************************************************************************/
/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PARTITION_H
#define PARTITION_H

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
*/

/*
// <e>Initialize Non-secure Base Address
*/
#define FMC_INIT_NSBA          1

/*
//     <o>Secure Flash ROM Size <0x800-0x7FFFF:0x800>
*/
#define FMC_SECURE_ROM_SIZE      0x00040000

#define FMC_NON_SECURE_BASE     (0x10000000 + FMC_SECURE_ROM_SIZE)

/*
// </e>
*/

__STATIC_INLINE void FMC_NSBA_Setup(void)
{
    /* Skip NSBA Setupt according config */
    if(FMC_INIT_NSBA == 0)
        return;

    /* Check if NSBA value with current active NSBA */
    if(SCU->FNSADDR != FMC_SECURE_ROM_SIZE)
    {
        /* Unlock Protected Register */
        SYS_UnlockReg();

        /* Enable ISP and config update */
        FMC->ISPCTL = FMC_ISPCTL_ISPEN_Msk | FMC_ISPCTL_CFGUEN_Msk;

        /* Config Base of NSBA */
        FMC->ISPADDR = 0x200800;

        /* Read Non-secure base address config */
        FMC->ISPCMD = FMC_ISPCMD_READ;
        FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;
        while(FMC->ISPTRG);

        /* Setting NSBA when it is empty */
        if(FMC->ISPDAT == 0xfffffffful)
        {
            FMC->ISPDAT = FMC_SECURE_ROM_SIZE;
            FMC->ISPCMD = FMC_ISPCMD_PROGRAM;
            FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;
            while(FMC->ISPTRG);

            /* Force Chip Reset to valid new setting */
            SYS->IPRST0 = SYS_IPRST0_CHIPRST_Msk;
        }

        /* Fatal Error:
           FMC NSBA setting is different to FMC_INIT_NSBA_VAL.
           User must double confirm which one is wrong.

           If user need to change NSBA config of FMC, user must do Mess-erase by
           ISP or ICP.
        */
        while(1);
    }

}

/*--------------------------------------------------------------------------------------------------------*/

/*
// <e>Initialize Security Attribution Unit (SAU) CTRL register
*/
#define SAU_INIT_CTRL          1

/*
//   <q> Enable SAU
//   <i> Value for SAU->CTRL register bit ENABLE
*/
#define SAU_INIT_CTRL_ENABLE   1

/*
//   <o> When SAU is disabled
//     <0=> All Memory is Secure
//     <1=> All Memory is Non-Secure
//   <i> Value for SAU->CTRL register bit ALLNS
//   <i> When all Memory is Non-Secure (ALLNS is 1), IDAU can override memory map configuration.
*/
#define SAU_INIT_CTRL_ALLNS  0

/*
// </e>
*/

/*
// <h>Initialize Security Attribution Unit (SAU) Address Regions
// <i>SAU configuration specifies regions to be one of:
// <i> - Secure and Non-Secure Callable
// <i> - Non-Secure
// <i>Note: All memory regions not configured by SAU are Secure
*/
#define SAU_REGIONS_MAX   8   /* Max. number of SAU regions */

/*
//   <e>Initialize SAU Region 0
//   <i> Setup SAU Region  0 memory attributes
*/
#define SAU_INIT_REGION0       1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START0       0x50000000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END0       0x5FFFFFFF      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC0       0
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 1
//   <i> Setup SAU Region  1 memory attributes
*/
#define SAU_INIT_REGION1       1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START1       0x10040000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END1       0x1007FFFF      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC1       0
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 2
//   <i> Setup SAU Region  2 memory attributes
*/
#define SAU_INIT_REGION2       1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START2       0x30008000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END2       0x30017FFF      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC2       0
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 3
//   <i> Setup SAU Region  3 memory attributes
*/
#define SAU_INIT_REGION3       1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START3       0x3F800      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END3       0x3FFFF      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC3       1
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 4
//   <i> Setup SAU Region  4 memory attributes
*/
#define SAU_INIT_REGION4       0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START4       0x00000000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END4       0x00000000      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC4       0
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 5
//   <i> Setup SAU Region  5 memory attributes
*/
#define SAU_INIT_REGION5       0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START5       0x00000000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END5       0x00000000      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC5       0
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 6
//   <i> Setup SAU Region  6 memory attributes
*/
#define SAU_INIT_REGION6       0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START6       0x00000000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END6       0x00000000      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC6       0
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 7
//   <i> Setup SAU Region  7 memory attributes
*/
#define SAU_INIT_REGION7       0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START7       0x00000000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END7       0x00000000      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC7       0
/*
//   </e>
*/

/*
// </h>
*/

/*
// <e>Setup behaviour of Sleep and Exception Handling
*/
#define SCB_CSR_AIRCR_INIT  1

/*
//   <o> Deep Sleep can be enabled by
//     <0=>Secure and Non-Secure state
//     <1=>Secure state only
//   <i> Value for SCB->CSR register bit DEEPSLEEPS
*/
#define SCB_CSR_DEEPSLEEPS_VAL  1

/*
//   <o>System reset request accessible from
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for SCB->AIRCR register bit SYSRESETREQS
*/
#define SCB_AIRCR_SYSRESETREQS_VAL  1

/*
//   <o>Priority of Non-Secure exceptions is
//     <0=> Not altered
//     <1=> Lowered to 0x80-0xFF
//   <i> Value for SCB->AIRCR register bit PRIS
*/
#define SCB_AIRCR_PRIS_VAL      1

/*
// </e>
*/

/*
// <h>Setup Interrupt Target
*/


/*
//   <e>Initialize ITNS 0 (Interrupts 0..31)
*/
#define NVIC_INIT_ITNS0    1

/*
// Interrupts 0..31
//   <o.0>  Interrupt   0 <0=> Secure state <1=> Non-Secure state
//   <o.1>  Interrupt   1 <0=> Secure state <1=> Non-Secure state
//   <o.2>  Interrupt   2 <0=> Secure state <1=> Non-Secure state
//   <o.3>  Interrupt   3 <0=> Secure state <1=> Non-Secure state
//   <o.4>  Interrupt   4 <0=> Secure state <1=> Non-Secure state
//   <o.5>  Interrupt   5 <0=> Secure state <1=> Non-Secure state
//   <o.6>  Interrupt   6: RTC_INT <0=> Secure state <1=> Non-Secure state
//   <o.7>  Interrupt   7 <0=> Secure state <1=> Non-Secure state
//   <o.8>  Interrupt   8 <0=> Secure state <1=> Non-Secure state
//   <o.9>  Interrupt   9 <0=> Secure state <1=> Non-Secure state
//   <o.10>  Interrupt  10: EINT0 <0=> Secure state <1=> Non-Secure state
//   <o.11>  Interrupt  11: EINT1 <0=> Secure state <1=> Non-Secure state
//   <o.12>  Interrupt  12: EINT2 <0=> Secure state <1=> Non-Secure state
//   <o.13>  Interrupt  13: EINT3 <0=> Secure state <1=> Non-Secure state
//   <o.14>  Interrupt  14: EINT4 <0=> Secure state <1=> Non-Secure state
//   <o.15>  Interrupt  15: EINT5 <0=> Secure state <1=> Non-Secure state
//   <o.16>  Interrupt  16: GPA_INT <0=> Secure state <1=> Non-Secure state
//   <o.17>  Interrupt  17: GPB_INT <0=> Secure state <1=> Non-Secure state
//   <o.18>  Interrupt  18: GPC_INT <0=> Secure state <1=> Non-Secure state
//   <o.19>  Interrupt  19: GPD_INT <0=> Secure state <1=> Non-Secure state
//   <o.20>  Interrupt  20: GPE_INT <0=> Secure state <1=> Non-Secure state
//   <o.21>  Interrupt  21: GPF_INT <0=> Secure state <1=> Non-Secure state
//   <o.22>  Interrupt  22: QSPI0_INT <0=> Secure state <1=> Non-Secure state
//   <o.23>  Interrupt  23: SPI0_INT <0=> Secure state <1=> Non-Secure state
//   <o.24>  Interrupt  24: BRAKE0_INT <0=> Secure state <1=> Non-Secure state
//   <o.25>  Interrupt  25: EPWM0_P0_INT <0=> Secure state <1=> Non-Secure state
//   <o.26>  Interrupt  26: EPWM0_P1_INT <0=> Secure state <1=> Non-Secure state
//   <o.27>  Interrupt  27: EPWM0_P2_INT <0=> Secure state <1=> Non-Secure state
//   <o.28>  Interrupt  28: BRAKE1_INT <0=> Secure state <1=> Non-Secure state
//   <o.29>  Interrupt  29: EPWM1_P0_INT <0=> Secure state <1=> Non-Secure state
//   <o.30>  Interrupt  30: EPWM1_P1_INT <0=> Secure state <1=> Non-Secure state
//   <o.31>  Interrupt  31: EPWM1_P2_INT <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS0_VAL      0x00040000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 1 (Interrupts 32..63)
*/
#define NVIC_INIT_ITNS1    1

/*
// Interrupts 32..63
//   <o.0>  Interrupt  32: TMR0_INT <0=> Secure state <1=> Non-Secure state
//   <o.1>  Interrupt  33: TMR1_INT <0=> Secure state <1=> Non-Secure state
//   <o.2>  Interrupt  34: TMR2_INT <0=> Secure state <1=> Non-Secure state
//   <o.3>  Interrupt  35: TMR3_INT <0=> Secure state <1=> Non-Secure state
//   <o.4>  Interrupt  36: UART0_INT <0=> Secure state <1=> Non-Secure state
//   <o.5>  Interrupt  37: UART1_INT <0=> Secure state <1=> Non-Secure state
//   <o.6>  Interrupt  38: I2C0_INT <0=> Secure state <1=> Non-Secure state
//   <o.7>  Interrupt  39: I2C1_INT <0=> Secure state <1=> Non-Secure state
//   <o.8>  Interrupt  40: PDMA0_INT <0=> Secure state <1=> Non-Secure state
//   <o.9>  Interrupt  41: DAC_INT <0=> Secure state <1=> Non-Secure state
//   <o.10>  Interrupt  42: EADC0_INT <0=> Secure state <1=> Non-Secure state
//   <o.11>  Interrupt  43: EADC1_INT <0=> Secure state <1=> Non-Secure state
//   <o.12>  Interrupt  44: ACMP01_INT <0=> Secure state <1=> Non-Secure state
//   <o.13>  Interrupt  45 <0=> Secure state <1=> Non-Secure state
//   <o.14>  Interrupt  46: EADC2_INT <0=> Secure state <1=> Non-Secure state
//   <o.15>  Interrupt  47: EADC3_INT <0=> Secure state <1=> Non-Secure state
//   <o.16>  Interrupt  48: UART2_INT <0=> Secure state <1=> Non-Secure state
//   <o.17>  Interrupt  49: UART3_INT <0=> Secure state <1=> Non-Secure state
//   <o.18>  Interrupt  50 <0=> Secure state <1=> Non-Secure state
//   <o.19>  Interrupt  51: SPI1_INT <0=> Secure state <1=> Non-Secure state
//   <o.20>  Interrupt  52: SPI2_INT <0=> Secure state <1=> Non-Secure state
//   <o.21>  Interrupt  53: USBD_INT <0=> Secure state <1=> Non-Secure state
//   <o.22>  Interrupt  54: USBH_INT <0=> Secure state <1=> Non-Secure state
//   <o.23>  Interrupt  55: USBOTG_INT <0=> Secure state <1=> Non-Secure state
//   <o.24>  Interrupt  56: CAN0_INT <0=> Secure state <1=> Non-Secure state
//   <o.25>  Interrupt  57 <0=> Secure state <1=> Non-Secure state
//   <o.26>  Interrupt  58: SC0_INT <0=> Secure state <1=> Non-Secure state
//   <o.27>  Interrupt  59: SC1_INT <0=> Secure state <1=> Non-Secure state
//   <o.28>  Interrupt  60: SC2_INT <0=> Secure state <1=> Non-Secure state
//   <o.29>  Interrupt  61 <0=> Secure state <1=> Non-Secure state
//   <o.30>  Interrupt  62: SPI3_INT <0=> Secure state <1=> Non-Secure state
//   <o.31>  Interrupt  63 <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS1_VAL      0x00000020

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 2 (Interrupts 64..95)
*/
#define NVIC_INIT_ITNS2    0

/*
// Interrupts 64..95
//   <o.0>  Interrupt  64: SDHOST0_INT <0=> Secure state <1=> Non-Secure state
//   <o.1>  Interrupt  65 <0=> Secure state <1=> Non-Secure state
//   <o.2>  Interrupt  66 <0=> Secure state <1=> Non-Secure state
//   <o.3>  Interrupt  67 <0=> Secure state <1=> Non-Secure state
//   <o.4>  Interrupt  68: I2S0_INT <0=> Secure state <1=> Non-Secure state
//   <o.5>  Interrupt  69 <0=> Secure state <1=> Non-Secure state
//   <o.6>  Interrupt  70 <0=> Secure state <1=> Non-Secure state
//   <o.7>  Interrupt  71: CRYPTO <0=> Secure state <1=> Non-Secure state
//   <o.8>  Interrupt  72: GPG_INT <0=> Secure state <1=> Non-Secure state
//   <o.9>  Interrupt  73: EINT6 <0=> Secure state <1=> Non-Secure state
//   <o.10>  Interrupt  74: UART4_INT <0=> Secure state <1=> Non-Secure state
//   <o.11>  Interrupt  75: UART5_INT <0=> Secure state <1=> Non-Secure state
//   <o.12>  Interrupt  76: USCI0_INT <0=> Secure state <1=> Non-Secure state
//   <o.13>  Interrupt  77: USCI1_INT <0=> Secure state <1=> Non-Secure state
//   <o.14>  Interrupt  78: BPWM0_INT <0=> Secure state <1=> Non-Secure state
//   <o.15>  Interrupt  79: BPWM1_INT <0=> Secure state <1=> Non-Secure state
//   <o.16>  Interrupt  80 <0=> Secure state <1=> Non-Secure state
//   <o.17>  Interrupt  81 <0=> Secure state <1=> Non-Secure state
//   <o.18>  Interrupt  82: I2C2_INT <0=> Secure state <1=> Non-Secure state
//   <o.19>  Interrupt  83 <0=> Secure state <1=> Non-Secure state
//   <o.20>  Interrupt  84: QEI0_INT <0=> Secure state <1=> Non-Secure state
//   <o.21>  Interrupt  85: QEI1_INT <0=> Secure state <1=> Non-Secure state
//   <o.22>  Interrupt  86: ECAP0_INT <0=> Secure state <1=> Non-Secure state
//   <o.23>  Interrupt  87: ECAP1_INT <0=> Secure state <1=> Non-Secure state
//   <o.24>  Interrupt  88: GPH_INT <0=> Secure state <1=> Non-Secure state
//   <o.25>  Interrupt  89: EINT7 <0=> Secure state <1=> Non-Secure state
//   <o.26>  Interrupt  90 <0=> Secure state <1=> Non-Secure state
//   <o.27>  Interrupt  91 <0=> Secure state <1=> Non-Secure state
//   <o.28>  Interrupt  92 <0=> Secure state <1=> Non-Secure state
//   <o.29>  Interrupt  93 <0=> Secure state <1=> Non-Secure state
//   <o.30>  Interrupt  94 <0=> Secure state <1=> Non-Secure state
//   <o.31>  Interrupt  95 <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS2_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 3 (Interrupts 96..127)
*/
#define NVIC_INIT_ITNS3    0

/*
// Interrupts 96..127
//   <o.0>  Interrupt  96 <0=> Secure state <1=> Non-Secure state
//   <o.1>  Interrupt  97 <0=> Secure state <1=> Non-Secure state
//   <o.2>  Interrupt  98: PDMA1_INT <0=> Secure state <1=> Non-Secure state
//   <o.3>  Interrupt  99 <0=> Secure state <1=> Non-Secure state
//   <o.4>  Interrupt 100 <0=> Secure state <1=> Non-Secure state
//   <o.5>  Interrupt 101: TRNG_INT <0=> Secure state <1=> Non-Secure state
//   <o.6>  Interrupt 102 <0=> Secure state <1=> Non-Secure state
//   <o.7>  Interrupt 103 <0=> Secure state <1=> Non-Secure state
//   <o.8>  Interrupt 104 <0=> Secure state <1=> Non-Secure state
//   <o.9>  Interrupt 105 <0=> Secure state <1=> Non-Secure state
//   <o.10>  Interrupt 106 <0=> Secure state <1=> Non-Secure state
//   <o.11>  Interrupt 107 <0=> Secure state <1=> Non-Secure state
//   <o.12>  Interrupt 108 <0=> Secure state <1=> Non-Secure state
//   <o.13>  Interrupt 109 <0=> Secure state <1=> Non-Secure state
//   <o.14>  Interrupt 110 <0=> Secure state <1=> Non-Secure state
//   <o.15>  Interrupt 111 <0=> Secure state <1=> Non-Secure state
//   <o.16>  Interrupt 112 <0=> Secure state <1=> Non-Secure state
//   <o.17>  Interrupt 113 <0=> Secure state <1=> Non-Secure state
//   <o.18>  Interrupt 114 <0=> Secure state <1=> Non-Secure state
//   <o.19>  Interrupt 115 <0=> Secure state <1=> Non-Secure state
//   <o.20>  Interrupt 116 <0=> Secure state <1=> Non-Secure state
//   <o.21>  Interrupt 117 <0=> Secure state <1=> Non-Secure state
//   <o.22>  Interrupt 118 <0=> Secure state <1=> Non-Secure state
//   <o.23>  Interrupt 119 <0=> Secure state <1=> Non-Secure state
//   <o.24>  Interrupt 120 <0=> Secure state <1=> Non-Secure state
//   <o.25>  Interrupt 121 <0=> Secure state <1=> Non-Secure state
//   <o.26>  Interrupt 122 <0=> Secure state <1=> Non-Secure state
//   <o.27>  Interrupt 123 <0=> Secure state <1=> Non-Secure state
//   <o.28>  Interrupt 124 <0=> Secure state <1=> Non-Secure state
//   <o.29>  Interrupt 125 <0=> Secure state <1=> Non-Secure state
//   <o.30>  Interrupt 126 <0=> Secure state <1=> Non-Secure state
//   <o.31>  Interrupt 127 <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS3_VAL      0x00000000

/*
//   </e>
*/

/*
// </h>
*/



/*
    max 128 SAU regions.
    SAU regions are defined in partition.h
 */

#define SAU_INIT_REGION(n) \
    SAU->RNR  =  (n                                     & SAU_RNR_REGION_Msk); \
    SAU->RBAR =  (SAU_INIT_START##n                     & SAU_RBAR_BADDR_Msk); \
    SAU->RLAR =  (SAU_INIT_END##n                       & SAU_RLAR_LADDR_Msk) | \
                ((SAU_INIT_NSC##n << SAU_RLAR_NSC_Pos)  & SAU_RLAR_NSC_Msk)   | 1U

/**
  \brief   Setup a SAU Region
  \details Writes the region information contained in SAU_Region to the
           registers SAU_RNR, SAU_RBAR, and SAU_RLAR
 */
__STATIC_INLINE void TZ_SAU_Setup (void)
{

#if defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U)
  #if defined (SAU_INIT_REGION0) && (SAU_INIT_REGION0 == 1U)
    SAU_INIT_REGION(0);
  #endif
  #if defined (SAU_INIT_REGION1) && (SAU_INIT_REGION1 == 1U)
    SAU_INIT_REGION(1);
  #endif
  #if defined (SAU_INIT_REGION2) && (SAU_INIT_REGION2 == 1U)
    SAU_INIT_REGION(2);
  #endif
  #if defined (SAU_INIT_REGION3) && (SAU_INIT_REGION3 == 1U)
    SAU_INIT_REGION(3);
  #endif
  #if defined (SAU_INIT_REGION4) && (SAU_INIT_REGION4 == 1U)
    SAU_INIT_REGION(4);
  #endif
  #if defined (SAU_INIT_REGION5) && (SAU_INIT_REGION5 == 1U)
    SAU_INIT_REGION(5);
  #endif
  #if defined (SAU_INIT_REGION6) && (SAU_INIT_REGION6 == 1U)
    SAU_INIT_REGION(6);
  #endif
  #if defined (SAU_INIT_REGION7) && (SAU_INIT_REGION7 == 1U)
    SAU_INIT_REGION(7);
  #endif
#endif /* defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U) */

  #if defined (SAU_INIT_CTRL) && (SAU_INIT_CTRL == 1U)
    SAU->CTRL = ((SAU_INIT_CTRL_ENABLE << SAU_CTRL_ENABLE_Pos) & SAU_CTRL_ENABLE_Msk) |
                ((SAU_INIT_CTRL_ALLNS  << SAU_CTRL_ALLNS_Pos)  & SAU_CTRL_ALLNS_Msk)   ;
  #endif

  #if defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U)
    SCB->SCR   = (SCB->SCR   & ~(SCB_SCR_SLEEPDEEPS_Msk    )) |
                   ((SCB_CSR_DEEPSLEEPS_VAL     << SCB_SCR_SLEEPDEEPS_Pos)     & SCB_SCR_SLEEPDEEPS_Msk);

    SCB->AIRCR = (SCB->AIRCR & ~(SCB_AIRCR_VECTKEY_Msk   | SCB_AIRCR_SYSRESETREQS_Msk |
                                 SCB_AIRCR_BFHFNMINS_Msk | SCB_AIRCR_PRIS_Msk          ))                    |
                   ((0x05FAU                    << SCB_AIRCR_VECTKEY_Pos)      & SCB_AIRCR_VECTKEY_Msk)      |
                   ((SCB_AIRCR_SYSRESETREQS_VAL << SCB_AIRCR_SYSRESETREQS_Pos) & SCB_AIRCR_SYSRESETREQS_Msk) |
                   ((SCB_AIRCR_PRIS_VAL         << SCB_AIRCR_PRIS_Pos)         & SCB_AIRCR_PRIS_Msk);
  #endif /* defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U) */

  #if defined (NVIC_INIT_ITNS0) && (NVIC_INIT_ITNS0 == 1U)
    NVIC->ITNS[0] = NVIC_INIT_ITNS0_VAL;
  #endif
  #if defined (NVIC_INIT_ITNS1) && (NVIC_INIT_ITNS1 == 1U)
    NVIC->ITNS[1] = NVIC_INIT_ITNS1_VAL;
  #endif
  #if defined (NVIC_INIT_ITNS2) && (NVIC_INIT_ITNS2 == 1U)
    NVIC->ITNS[2] = NVIC_INIT_ITNS2_VAL;
  #endif
  #if defined (NVIC_INIT_ITNS3) && (NVIC_INIT_ITNS3 == 1U)
    NVIC->ITNS[3] = NVIC_INIT_ITNS3_VAL;
  #endif
}



/**
  \brief   Setup SCU Configuration Unit
  \details

 */
__STATIC_INLINE void SCU_Setup(void)
{
  /* Setup Peripheral Protection Controller (PPC) */
    SCU->IONSSET = 0x00000004U;
    SCU->PNSSET[3] = 0x00020000U;

  /* Setup Memory Protection Controller (MPC) */
    /* SRAM Memory Protection Controller */
    SCU->SRAMNSSET = 0x00000FF0U;
}

#endif  /* PARTITION_H */
