<#compress>
<#include "helper.ftlinc"/>

<#assign aDateTime = .now>

<#-- Prepare SAU entries -->
<#assign sau_entries = 0>
<#assign sau_table = []/>

<#if system.sau?has_content>
  <#list system.sau?sort_by("start") as s>
    <#assign sau_table += [{"start_address":s.start,      "end_address":s.end,        "nsc":s.nsc, "init":1}]/>
    <#assign sau_entries += 1>
  </#list>
</#if>
  <#list sau_entries..7 as i>
    <#assign sau_table += [{"start_address":"0x00000000", "end_address":"0x00000000", "nsc":0,     "init":0}]/>
  </#list>

<#-- Prepare Non-Secure Interrupt Entries -->
<#assign itns_entries = 0>
<#assign itns_table = []/>
<#assign maxirq = 0/>
<#assign it = {}/>
<#assign itns = {}/>

<#if system.interrupt?has_content>
  <#list system.interrupt?sort_by("irqn") as irq>
    <#assign it += { irq.irqn?number : irq } />  
    <#if (irq.irqn?number > maxirq)>
	  <#assign maxirq = irq.irqn?number>
    </#if>
    <#if irq.security.n == "1">
      <#assign itns += { irq.irqn?number : irq } />
    </#if>
  </#list>
</#if>

<#list 0..(maxirq/32)?floor as i>
  <#assign itns_val  = 0>
  <#assign itns_init = 0>
  <#list 0..31 as j>
    <#if itns?keys?seq_contains((i * 32 + j)?c)>
      <#assign itns_init = 1>
      <#assign itns_val += pow2(j)>
    </#if>
  </#list>
  <#assign itns_table += [{"val" : num2hex(itns_val, "0x", 8), "init" : itns_init}]/>
</#list>
</#compress>
/**************************************************************************//**
 * @file     partition_stm32l5xx.h
 * @brief    CMSIS-CORE Initial Setup for Secure / Non-Secure Zones for STM32L5xx Device
 * @version  V1.0.0      (FreeMarker generated)
 * @date     ${aDateTime?date} ${aDateTime?time}
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
#define SAU_REGIONS_MAX   ${sau_table?size} 	/* Max. number of SAU regions */

<#list sau_table as sau_entry>
/*
//   <e>Initialize SAU Region ${sau_entry?index}
//   <i> Setup SAU Region  ${sau_entry?index} memory attributes
*/
#define SAU_INIT_REGION${sau_entry?index}       ${sau_entry.init}

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START${sau_entry?index}       ${sau_entry.start_address}      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END${sau_entry?index}       ${sau_entry.end_address}      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC${sau_entry?index}       ${sau_entry.nsc}
/*
//   </e>
*/
</#list>

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

<#list itns_table as itns_entry>

/*
//   <e>Initialize ITNS ${itns_entry?index} (Interrupts ${itns_entry?index*32}..${itns_entry?index*32+31})
*/
#define NVIC_INIT_ITNS${itns_entry?index}    ${itns_entry.init}

/*
// Interrupts ${itns_entry?index*32}..${itns_entry?index*32+31}
<#list 0..31 as i>
//   <o.${i}>  Interrupt ${(itns_entry?index*32+i)?left_pad(3)}<#if it?keys?seq_contains((itns_entry?index*32+i)?c)>: ${it[(itns_entry?index*32+i)?c].name}</#if> <0=> Secure state <1=> Non-Secure state
</#list>
*/
#define NVIC_INIT_ITNS${itns_entry?index}_VAL      ${itns_entry.val}

/*
//   </e>
*/
</#list>

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
  <#list 0..(sau_table?size-1) as i>
  #if defined (SAU_INIT_REGION${i}) && (SAU_INIT_REGION${i} == 1U)
    SAU_INIT_REGION(${i});
  #endif
  </#list>
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

  <#list 0..(itns_table?size-1) as i>
  #if defined (NVIC_INIT_ITNS${i}) && (NVIC_INIT_ITNS${i} == 1U)
    NVIC->ITNS[${i}] = NVIC_INIT_ITNS${i}_VAL;
  #endif
  </#list>
}

#endif  /* PARTITION_H */
