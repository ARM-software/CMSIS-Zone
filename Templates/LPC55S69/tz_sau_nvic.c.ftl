<#compress>
<#include "helper.ftlinc"/>

<#-- Prepare SAU entries -->
<#assign sau_entries = 0>
<#assign sau_table = []/>

<#if system.sau?has_content>
  <#list system.sau?sort_by("start") as s>
    <#assign sau_table += [{"start_address":num2hex(hex2num(s.start)), "end_address":num2hex(hex2num(s.end)), "nsc":s.nsc, "init":1}]/>
    <#assign sau_entries += 1>
  </#list>
</#if>
  <#list sau_entries..7 as i>
    <#assign sau_table += [{"start_address":"0x00000000",              "end_address":"0x00000000",            "nsc":0,     "init":0}]/>
  </#list>

<#-- Prepare Non-Secure Interrupt Entries -->
<#assign itns_entries = 0>
<#assign itns_table = []/>
<#assign maxirq = 0/>
<#assign it = {}/>
<#assign itns = {}/>
<#assign it_na = "---">

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
</#compress>
/*
 * Copyright 2019 Arm Limited
 *
 * SPDX-License-Identifier: Apache 2.0
 */

#include "tz_config.h" 


void TZ_Config_SAU(void)
{

<#list sau_table as sau_entry>
  /* Initialize SAU Region ${sau_entry?index} */
  SAU->RNR  =  (${sau_entry?index}U                      & SAU_RNR_REGION_Msk);
  SAU->RBAR =  (${sau_entry.start_address}U             & SAU_RBAR_BADDR_Msk);
  SAU->RLAR =  (${sau_entry.end_address}U             & SAU_RLAR_LADDR_Msk) |
              ((${sau_entry.nsc}U << SAU_RLAR_NSC_Pos) & SAU_RLAR_NSC_Msk)   | 1U;

</#list>
  /* Configure SAU Control */
  SAU->CTRL = ((1U << SAU_CTRL_ENABLE_Pos) & SAU_CTRL_ENABLE_Msk) |         /* enable SAU */
              ((0U << SAU_CTRL_ALLNS_Pos)  & SAU_CTRL_ALLNS_Msk)   ;
}

void TZ_Config_NVIC(void)
{
<#list 0..(maxirq/32)?floor as i>
  /* Initialize ITNS ${i} (Interrupts ${i*32}..${i*32+31}) */
  NVIC->ITNS[${i}] =
  <#list 0..31 as j>
    <#if itns?keys?seq_contains((i * 32 + j)?c)>
      <#assign sec = 1>
      ${num2hex(pow2(j))}<#if j <= 30> |<#else>; </#if><#rt>
    <#else>
      <#assign sec = 0>
      0x00000000<#if j <= 30> |<#else>; </#if><#rt>
    </#if>
      /* Interrupt ${(i*32+j)?left_pad(3)}: <#if it?keys?seq_contains((i*32+j)?c)>${it[(i*32+j)?c].name?right_pad(20)} <#else>${it_na?right_pad(20)} </#if> is <#if sec == 1>secure<#else>non-secure</#if> */
  </#list>

</#list>
#if defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AICR_INIT == 1U)
  SCB->SCR   = (SCB->SCR   & ~(SCB_SCR_SLEEPDEEPS_Msk    )) |
                 ((SCB_CSR_DEEPSLEEPS_VAL     << SCB_SCR_SLEEPDEEPS_Pos)     & SCB_SCR_SLEEPDEEPS_Msk);

  SCB->AIRCR = (SCB->AIRCR & ~(SCB_AIRCR_VECTKEY_Msk   | SCB_AIRCR_SYSRESETREQS_Msk |
                               SCB_AIRCR_BFHFNMINS_Msk | SCB_AIRCR_PRIS_Msk          ))                    |
                 ((0x05FAU                    << SCB_AIRCR_VECTKEY_Pos)      & SCB_AIRCR_VECTKEY_Msk)      |
                 ((SCB_AIRCR_SYSRESETREQS_VAL << SCB_AIRCR_SYSRESETREQS_Pos) & SCB_AIRCR_SYSRESETREQS_Msk) |
                 ((SCB_AIRCR_PRIS_VAL         << SCB_AIRCR_PRIS_Pos)         & SCB_AIRCR_PRIS_Msk)         |
                 ((SCB_AIRCR_BFHFNMINS_VAL    << SCB_AIRCR_BFHFNMINS_Pos)    & SCB_AIRCR_BFHFNMINS_Msk);
#endif /* defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U) */

}
