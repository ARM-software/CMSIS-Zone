<#compress>
<#include "helper.ftlinc"/>

<#-- Prepare Non-Secure Interrupt Entries -->
<#assign itns_entries = 0>
<#assign itns_table = []/>
<#assign maxirq = system.processor.DnumInterrupts?number - 1>
<#assign it = {}/>
<#assign itns = {}/>
<#assign it_na = "---">
<#assign maxsauregions = system.processor.DnumSauRegions?number - 1>

<#if system.interrupt?has_content>
  <#list system.interrupt?sort_by("irqn") as irq>
    <#assign it += { irq.irqn?number : irq } />
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
    /* Disable SAU */
    SAU->CTRL = 0U;

<#list system.sau as region>
  <#if region?index <= maxsauregions>
    /* Configure SAU region ${region?index} - ${region.info} (${region.start}..${region.end}) */
    SAU->RNR = ${region?index}U;
    SAU->RBAR = ${region.start}U;
    SAU->RLAR = (${region.end}U & SAU_RLAR_LADDR_Msk) |
                 /* Region memory attribute index */
                 ((${region.nsc}U << SAU_RLAR_NSC_Pos) & SAU_RLAR_NSC_Msk) |
                 /* Enable region */
                 ((1U << SAU_RLAR_ENABLE_Pos) & SAU_RLAR_ENABLE_Msk);

  </#if>
</#list>
<#if system.sau?size < maxsauregions>
  <#list system.sau?size..maxsauregions as idx>
    /* Configure SAU region ${idx} - unused */
    SAU->RNR = ${idx}U;
    SAU->RBAR = 0U;
    SAU->RLAR = 0U;

  </#list>
</#if>
    /* Force memory writes before continuing */
    __DSB();
    /* Flush and refill pipeline with updated permissions */
    __ISB();

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
