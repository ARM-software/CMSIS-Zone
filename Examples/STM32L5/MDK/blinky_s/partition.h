/**************************************************************************//**
 * @file     partition_stm32l5xx.h
 * @brief    CMSIS-CORE Initial Setup for Secure / Non-Secure Zones for STM32L5xx Device
 * @version  V1.0.0      (FreeMarker generated)
 * @date     02-Jul-2019 13:24:24
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
#define SAU_REGIONS_MAX   8 	/* Max. number of SAU regions */

/*
//   <e>Initialize SAU Region 0
//   <i> Setup SAU Region  0 memory attributes
*/
#define SAU_INIT_REGION0       1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START0       0x40000000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END0       0x4FFFFFFF      /* end address of SAU region 0 */

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
#define SAU_INIT_START1       0x20000000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END1       0x2001FFFF      /* end address of SAU region 0 */

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
#define SAU_INIT_START2       0x8040000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END2       0x807FFFF      /* end address of SAU region 0 */

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
#define SAU_INIT_START3       0xC03E000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END3       0xC03FFFF      /* end address of SAU region 0 */

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
//   <o>BusFault, HardFault, and NMI target
//     <0=> Secure state
//     <1=> Non-Secure state
//   <i> Value for SCB->AIRCR register bit BFHFNMINS
*/
#define SCB_AIRCR_BFHFNMINS_VAL 0

/*
// </e>
*/

/*
// <e>Setup behaviour of Floating Point Unit
*/
#define TZ_FPU_NS_USAGE 1

/*
// <o>Floating Point Unit usage
//     <0=> Secure state only
//     <3=> Secure and Non-Secure state
//   <i> Value for SCB->NSACR register bits CP10, CP11
*/
#define SCB_NSACR_CP10_11_VAL       3

/*
// <o>Treat floating-point registers as Secure
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit TS
*/
#define FPU_FPCCR_TS_VAL            0

/*
// <o>Clear on return (CLRONRET) accessibility
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for FPU->FPCCR register bit CLRONRETS
*/
#define FPU_FPCCR_CLRONRETS_VAL     0

/*
// <o>Clear floating-point caller saved registers on exception return
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit CLRONRET
*/
#define FPU_FPCCR_CLRONRET_VAL      1

/*
// </e>
*/

/*
// <h>Setup Interrupt Target
*/


/*
//   <e>Initialize ITNS 0 (Interrupts 0..31)
*/
#define NVIC_INIT_ITNS0    0

/*
// Interrupts 0..31
//   <o.0>  Interrupt   0 <0=> Secure state <1=> Non-Secure state
//   <o.1>  Interrupt   1 <0=> Secure state <1=> Non-Secure state
//   <o.2>  Interrupt   2 <0=> Secure state <1=> Non-Secure state
//   <o.3>  Interrupt   3 <0=> Secure state <1=> Non-Secure state
//   <o.4>  Interrupt   4 <0=> Secure state <1=> Non-Secure state
//   <o.5>  Interrupt   5 <0=> Secure state <1=> Non-Secure state
//   <o.6>  Interrupt   6 <0=> Secure state <1=> Non-Secure state
//   <o.7>  Interrupt   7 <0=> Secure state <1=> Non-Secure state
//   <o.8>  Interrupt   8 <0=> Secure state <1=> Non-Secure state
//   <o.9>  Interrupt   9 <0=> Secure state <1=> Non-Secure state
//   <o.10>  Interrupt  10 <0=> Secure state <1=> Non-Secure state
//   <o.11>  Interrupt  11 <0=> Secure state <1=> Non-Secure state
//   <o.12>  Interrupt  12 <0=> Secure state <1=> Non-Secure state
//   <o.13>  Interrupt  13 <0=> Secure state <1=> Non-Secure state
//   <o.14>  Interrupt  14 <0=> Secure state <1=> Non-Secure state
//   <o.15>  Interrupt  15 <0=> Secure state <1=> Non-Secure state
//   <o.16>  Interrupt  16 <0=> Secure state <1=> Non-Secure state
//   <o.17>  Interrupt  17 <0=> Secure state <1=> Non-Secure state
//   <o.18>  Interrupt  18 <0=> Secure state <1=> Non-Secure state
//   <o.19>  Interrupt  19 <0=> Secure state <1=> Non-Secure state
//   <o.20>  Interrupt  20 <0=> Secure state <1=> Non-Secure state
//   <o.21>  Interrupt  21 <0=> Secure state <1=> Non-Secure state
//   <o.22>  Interrupt  22 <0=> Secure state <1=> Non-Secure state
//   <o.23>  Interrupt  23 <0=> Secure state <1=> Non-Secure state
//   <o.24>  Interrupt  24 <0=> Secure state <1=> Non-Secure state
//   <o.25>  Interrupt  25 <0=> Secure state <1=> Non-Secure state
//   <o.26>  Interrupt  26 <0=> Secure state <1=> Non-Secure state
//   <o.27>  Interrupt  27 <0=> Secure state <1=> Non-Secure state
//   <o.28>  Interrupt  28 <0=> Secure state <1=> Non-Secure state
//   <o.29>  Interrupt  29: DMA1_Channel1 <0=> Secure state <1=> Non-Secure state
//   <o.30>  Interrupt  30: DMA1_Channel2 <0=> Secure state <1=> Non-Secure state
//   <o.31>  Interrupt  31: DMA1_Channel3 <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS0_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 1 (Interrupts 32..63)
*/
#define NVIC_INIT_ITNS1    0

/*
// Interrupts 32..63
//   <o.0>  Interrupt  32: DMA1_Channel4 <0=> Secure state <1=> Non-Secure state
//   <o.1>  Interrupt  33: DMA1_Channel5 <0=> Secure state <1=> Non-Secure state
//   <o.2>  Interrupt  34: DMA1_Channel6 <0=> Secure state <1=> Non-Secure state
//   <o.3>  Interrupt  35: DMA1_Channel7 <0=> Secure state <1=> Non-Secure state
//   <o.4>  Interrupt  36: DMA1_Channel8 <0=> Secure state <1=> Non-Secure state
//   <o.5>  Interrupt  37: ADC1_2 <0=> Secure state <1=> Non-Secure state
//   <o.6>  Interrupt  38 <0=> Secure state <1=> Non-Secure state
//   <o.7>  Interrupt  39: FDCAN1_IT0 <0=> Secure state <1=> Non-Secure state
//   <o.8>  Interrupt  40: FDCAN1_IT1 <0=> Secure state <1=> Non-Secure state
//   <o.9>  Interrupt  41: TIM1_BRK <0=> Secure state <1=> Non-Secure state
//   <o.10>  Interrupt  42: TIM1_UP <0=> Secure state <1=> Non-Secure state
//   <o.11>  Interrupt  43: TIM1_TRG_COM <0=> Secure state <1=> Non-Secure state
//   <o.12>  Interrupt  44: TIM1_CC <0=> Secure state <1=> Non-Secure state
//   <o.13>  Interrupt  45: TIM2 <0=> Secure state <1=> Non-Secure state
//   <o.14>  Interrupt  46: TIM3 <0=> Secure state <1=> Non-Secure state
//   <o.15>  Interrupt  47: TIM4 <0=> Secure state <1=> Non-Secure state
//   <o.16>  Interrupt  48: TIM5 <0=> Secure state <1=> Non-Secure state
//   <o.17>  Interrupt  49: TIM6 <0=> Secure state <1=> Non-Secure state
//   <o.18>  Interrupt  50: TIM7 <0=> Secure state <1=> Non-Secure state
//   <o.19>  Interrupt  51: TIM8_BRK <0=> Secure state <1=> Non-Secure state
//   <o.20>  Interrupt  52: TIM8_UP <0=> Secure state <1=> Non-Secure state
//   <o.21>  Interrupt  53: TIM8_TRG_COM <0=> Secure state <1=> Non-Secure state
//   <o.22>  Interrupt  54: TIM8_CC <0=> Secure state <1=> Non-Secure state
//   <o.23>  Interrupt  55: I2C1_EV <0=> Secure state <1=> Non-Secure state
//   <o.24>  Interrupt  56: I2C1_ER <0=> Secure state <1=> Non-Secure state
//   <o.25>  Interrupt  57: I2C2_EV <0=> Secure state <1=> Non-Secure state
//   <o.26>  Interrupt  58: I2C2_ER <0=> Secure state <1=> Non-Secure state
//   <o.27>  Interrupt  59: SPI1 <0=> Secure state <1=> Non-Secure state
//   <o.28>  Interrupt  60: SPI2 <0=> Secure state <1=> Non-Secure state
//   <o.29>  Interrupt  61: USART1 <0=> Secure state <1=> Non-Secure state
//   <o.30>  Interrupt  62: USART2 <0=> Secure state <1=> Non-Secure state
//   <o.31>  Interrupt  63: USART3 <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS1_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 2 (Interrupts 64..95)
*/
#define NVIC_INIT_ITNS2    0

/*
// Interrupts 64..95
//   <o.0>  Interrupt  64: UART4 <0=> Secure state <1=> Non-Secure state
//   <o.1>  Interrupt  65: UART5 <0=> Secure state <1=> Non-Secure state
//   <o.2>  Interrupt  66: LPUART1 <0=> Secure state <1=> Non-Secure state
//   <o.3>  Interrupt  67: LPTIM1 <0=> Secure state <1=> Non-Secure state
//   <o.4>  Interrupt  68: LPTIM2 <0=> Secure state <1=> Non-Secure state
//   <o.5>  Interrupt  69: TIM15 <0=> Secure state <1=> Non-Secure state
//   <o.6>  Interrupt  70: TIM16 <0=> Secure state <1=> Non-Secure state
//   <o.7>  Interrupt  71: TIM17 <0=> Secure state <1=> Non-Secure state
//   <o.8>  Interrupt  72: COMP <0=> Secure state <1=> Non-Secure state
//   <o.9>  Interrupt  73 <0=> Secure state <1=> Non-Secure state
//   <o.10>  Interrupt  74 <0=> Secure state <1=> Non-Secure state
//   <o.11>  Interrupt  75 <0=> Secure state <1=> Non-Secure state
//   <o.12>  Interrupt  76: OCTOSPI1 <0=> Secure state <1=> Non-Secure state
//   <o.13>  Interrupt  77 <0=> Secure state <1=> Non-Secure state
//   <o.14>  Interrupt  78 <0=> Secure state <1=> Non-Secure state
//   <o.15>  Interrupt  79 <0=> Secure state <1=> Non-Secure state
//   <o.16>  Interrupt  80: DMA2_CH1 <0=> Secure state <1=> Non-Secure state
//   <o.17>  Interrupt  81: DMA2_CH2 <0=> Secure state <1=> Non-Secure state
//   <o.18>  Interrupt  82: DMA2_CH3 <0=> Secure state <1=> Non-Secure state
//   <o.19>  Interrupt  83: DMA2_CH4 <0=> Secure state <1=> Non-Secure state
//   <o.20>  Interrupt  84: DMA2_CH5 <0=> Secure state <1=> Non-Secure state
//   <o.21>  Interrupt  85: DMA2_CH6 <0=> Secure state <1=> Non-Secure state
//   <o.22>  Interrupt  86: DMA2_CH7 <0=> Secure state <1=> Non-Secure state
//   <o.23>  Interrupt  87: DMA2_CH8 <0=> Secure state <1=> Non-Secure state
//   <o.24>  Interrupt  88: I2C3_EV <0=> Secure state <1=> Non-Secure state
//   <o.25>  Interrupt  89: I2C3_ER <0=> Secure state <1=> Non-Secure state
//   <o.26>  Interrupt  90: SAI1 <0=> Secure state <1=> Non-Secure state
//   <o.27>  Interrupt  91: SAI2 <0=> Secure state <1=> Non-Secure state
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
//   <o.2>  Interrupt  98 <0=> Secure state <1=> Non-Secure state
//   <o.3>  Interrupt  99: SPI3 <0=> Secure state <1=> Non-Secure state
//   <o.4>  Interrupt 100: I2C4_ER <0=> Secure state <1=> Non-Secure state
//   <o.5>  Interrupt 101: I2C4_EV <0=> Secure state <1=> Non-Secure state
//   <o.6>  Interrupt 102: DFSDM1_FLT0 <0=> Secure state <1=> Non-Secure state
//   <o.7>  Interrupt 103: DFSDM1_FLT1 <0=> Secure state <1=> Non-Secure state
//   <o.8>  Interrupt 104: DFSDM1_FLT2 <0=> Secure state <1=> Non-Secure state
//   <o.9>  Interrupt 105: DFSDM1_FLT3 <0=> Secure state <1=> Non-Secure state
//   <o.10>  Interrupt 106: UCPD1 <0=> Secure state <1=> Non-Secure state
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
                   ((SCB_AIRCR_PRIS_VAL         << SCB_AIRCR_PRIS_Pos)         & SCB_AIRCR_PRIS_Msk)         |
                   ((SCB_AIRCR_BFHFNMINS_VAL    << SCB_AIRCR_BFHFNMINS_Pos)    & SCB_AIRCR_BFHFNMINS_Msk);
  #endif /* defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U) */

  #if defined (__FPU_USED) && (__FPU_USED == 1U) && \
      defined (TZ_FPU_NS_USAGE) && (TZ_FPU_NS_USAGE == 1U)

    SCB->NSACR = (SCB->NSACR & ~(SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk)) |
                   ((SCB_NSACR_CP10_11_VAL << SCB_NSACR_CP10_Pos) & (SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk));

    FPU->FPCCR = (FPU->FPCCR & ~(FPU_FPCCR_TS_Msk | FPU_FPCCR_CLRONRETS_Msk | FPU_FPCCR_CLRONRET_Msk)) |
                   ((FPU_FPCCR_TS_VAL        << FPU_FPCCR_TS_Pos       ) & FPU_FPCCR_TS_Msk       ) |
                   ((FPU_FPCCR_CLRONRETS_VAL << FPU_FPCCR_CLRONRETS_Pos) & FPU_FPCCR_CLRONRETS_Msk) |
                   ((FPU_FPCCR_CLRONRET_VAL  << FPU_FPCCR_CLRONRET_Pos ) & FPU_FPCCR_CLRONRET_Msk );
  #endif

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

#endif  /* PARTITION_H */
