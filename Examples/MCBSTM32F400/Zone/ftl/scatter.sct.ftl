<#compress>
<#include "helper.ftlinc"/>
<#-- Prepare code and data regions -->
<#assign code={}>
<#assign data={}>
<#list zone as z>
  <#list z.memory as m>
  	<#if m.access.w?number == 1>
      <#if !data?keys?seq_contains(m.name)>
        <#assign data += { m.name: m }>
      </#if>
  	<#else>
      <#if !code?keys?seq_contains(m.name)>
        <#assign code += { m.name: m }>
      </#if>
    </#if>
  </#list>
</#list>
</#compress>
<#assign resetRegion = false/>
<#assign dataRegions = false/>
#! armclang -E --target=arm-arm-none-eabi -mcpu=cortex-m3 -xc

#include "mem_layout.h"

<#-- Generate code regions -->
<#list code?values?sort_by("start") as m>
LR_${m.name} REGION_${m.name?upper_case}_START REGION_${m.name?upper_case}_SIZE {
<#if m.access.x?number == 1>
  ER_${m.name} REGION_${m.name?upper_case}_START REGION_${m.name?upper_case}_SIZE {
  <#-- Add reset vector and root sections to first code regiono -->
  <#if !resetRegion>
  	<#assign resetRegion = true/>
  	* (RESET,+FIRST)
    * (InRoot$$Sections)
    .ANY (+RO, +XO)
  </#if>
  }
</#if>
<#-- Add all data regions to first load region -->
<#if !dataRegions>
  <#assign dataRegions = true/>
  <#list data?values?sort_by("start") as m>
  RW_${m.name} REGION_${m.name?upper_case}_START <#if m.uninit == '1'>UNINIT </#if>REGION_${m.name?upper_case}_SIZE {
    .ANY (+RW +ZI)
  }
  </#list>
</#if>
}
</#list>
