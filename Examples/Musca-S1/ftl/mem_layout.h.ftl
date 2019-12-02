<#compress>
<#include "helper.ftlinc"/>

<#assign regions={}/>
<#list zone as z>
  <#list z.memory as m>
    <#if !regions?keys?seq_contains(m.name)>
      <#assign regions += { m.name: m }>
    </#if>
  </#list> 
</#list>
</#compress>
/*
 * Copyright 2019 Arm Limited
 *
 * SPDX-License-Identifier: Apache 2.0
 */

#ifndef MEM_LAYOUT_H
#define MEM_LAYOUT_H

<#list regions?values as r>
  <#assign r_start = "REGION_"+r.name?upper_case+"_START">
  <#assign r_size  = "REGION_"+r.name?upper_case+"_SIZE">
#define ${r_start?right_pad(25)}  ${num2hex(hex2num(r.start))}U
#define ${r_size?right_pad(25)}  ${num2hex(hex2num(r.size))}U
</#list>

#endif /* MEM_LAYOUT_H */
