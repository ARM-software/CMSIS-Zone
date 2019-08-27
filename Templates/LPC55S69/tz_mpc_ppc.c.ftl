<#compress>
<#include "helper.ftlinc"/>

<#function mpcRegs mpc>
    <#assign regs = [] />
    <#list 0..((mpc.S_bit?size-1)/8) as i>
        <#assign reg = 0 />
        <#list 0..7 as j>
            <#assign reg += (mpc.P_bit[i*8+j]!"0")?number*pow2(j*4)   />
            <#assign reg += (mpc.S_bit[i*8+j]!"0")?number*pow2(j*4+1) />
        </#list>
        <#assign regs += [reg] />
    </#list>
    <#return regs />
</#function>
</#compress>
/*
 * Copyright 2019 Arm Limited
 *
 * SPDX-License-Identifier: Apache 2.0
 */

#include "tz_config.h" 
#include "fsl_common.h"


<#--
void TZM_Config_MPC(void)
{
  /* Setup Memory Protection Controller (MPC) */
<#list system.mpc_setup as mpc>
    /* ${mpc.info} */
    <#list mpcRegs(mpc) as reg>
    ${mpc.name}[${reg?index}] = ${num2hex(reg)}U;
    </#list>
</#list>
}
-->
/* Setup Memory Protection Controller (MPC) */
void TZ_Config_MPC(void)
{
<#list system.mpc_setup as mpc>
  /* ${mpc.info} */
  <#assign idx = 0 />
  <#list 0..((mpc.S_bit?size-1)/8) as i>
  ${mpc.name}[${idx}]=
    <#list 0..7 as j>
      <#assign b4  = (mpc.P_bit[i*8+j]!"0")?number*pow2(j*4)   />
      <#assign b4 += (mpc.S_bit[i*8+j]!"0")?number*pow2(j*4+1)  />
      ${num2hex(b4)}U<#if j <= 6> |<#else>; </#if>      <#if mpc.bit_comment[i*8+j]?has_content && mpc.bit_comment[i*8+j] != "">/* ${mpc.bit_comment[i*8+j]} */</#if>
    </#list>
    <#assign idx += 1 />
  </#list>

</#list>
}


<#--
void TZM_Config_PPC(void)
{
  /* Setup Peripheral Protection Controller (PPC) */
<#list system.reg_setup as reg>
    <#assign value = 0 />
    <#list reg.value as v>
        <#assign value += hex2num(v) />
    </#list>
    ${reg.name} = ${num2hex(value)}U;
</#list>
}
-->
/* Setup Peripheral Protection Controller (PPC) */
void TZ_Config_PPC(void)
{
<#list system.reg_setup as reg>
  ${reg.name} =
  <#list reg.value as v>
    <#if v?is_last><#rt></#if>
      ${v}U<#if v?is_last>; <#else> |</#if>      /* ${reg.peripheral[v?index]} */
  </#list>

</#list>
}
