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
<#assign veneerRegion = false/>
<#assign dataRegions = false/>
<#-- Generate code regions -->
<#list code?values?sort_by("start") as m>
LR_${m.name} ${m.start} ${m.size} {
<#if m.access.x?number == 1>
  ER_${m.name} ${m.start} ${m.size} {
  <#-- Add reset vector and root sections to first code regiono -->
  <#if !resetRegion>
  	<#assign resetRegion = true/>
  	* (RESET,+FIRST)
    * (InRoot$$Sections)
    .ANY (+RO, +XO)
  </#if>
  <#-- Add all secure gateways to first veneer region -->
  <#if m.security.c?number == 1 && !veneerRegion>
    <#assign veneerRegion = true/>
  	*(Veneer$$CMSE)
  </#if>
  }
</#if>
<#-- Add all data regions to first load region -->
<#if !dataRegions>
  <#assign dataRegions = true/>
  <#list data?values?sort_by("start") as m>
    <#-- Add magic HEAP region if defined -->
    <#if m.name == "HEAP">
  ARM_LIB_HEAP ${m.start} EMPTY ${m.size} {
  }
    <#-- Add magic STACK region if defined -->
    <#elseif m.name == "STACK">
  ARM_LIB_STACK ${m.start} EMPTY ${m.size} {
  }
    <#else>
  RW_${m.name} ${m.start} ${m.size} {
    .ANY (+RW +ZI)
  }
    </#if>
  </#list>
</#if>
}
</#list>
