<#include "helper.ftlinc"/>
<#list zone.memory as mem>
  <#if mem.name?contains("APP_S")> 
    <#assign app_s = hex2num(mem.start)>
    <#lt>APP_S   Specified@: ${mem.start} 		Size: ${mem.size}
  </#if>
  <#if mem.name?contains("APP_NSC")> 
      <#assign app_nsc = hex2num(mem.start)>
      <#lt>APP_NSC Specified@: ${mem.start} 		Size: ${mem.size}
  </#if>
  <#if mem.name?contains("APP_NS")> 
      <#assign app_ns = hex2num(mem.start)>
      <#lt>APP_NS  Specified@: ${mem.start} 		Size: ${mem.size}
  </#if>
  <#if mem.name?contains("RAM_S")> 
      <#assign ram_s = hex2num(mem.start)>
      <#lt>RAM_S   Specified@: ${mem.start} 	Size: ${mem.size}
  </#if>
  <#if mem.name?contains("RAM_NS")>
      <#assign ram_ns = hex2num(mem.start)>
      <#lt>RAM_NS  Specified@: ${mem.start} 	Size: ${mem.size}
  </#if>
  <#if mem.name?contains("DATA_S")> 
      <#assign data_s = hex2num(mem.start)>
      <#lt>DATA_S  Specified@: ${mem.start} 	Size: ${mem.size}
  </#if>
  <#if mem.name?contains("DATA_NS")>
      <#assign data_ns = hex2num(mem.start)>
      <#lt>DATA_NS Specified@: ${mem.start} 	Size: ${mem.size}
  </#if>
</#list>

<#if app_ns??>
  <#assign idau_as = (app_ns / 256)>
  <#lt>AS   = ${idau_as}
  <#if app_nsc??> 
    <#assign idau_ansc = (app_ns - app_nsc ) / 32> 
    <#lt>ANSC = ${idau_ansc}
  </#if>
</#if>
<#if ram_ns??>
  <#assign idau_rs = (536887296 - ram_ns) / 128>
  <#lt>RS   = ${idau_rs}
</#if>
<#if data_ns??>
  <#assign idau_ds = (4196352 - data_ns) / 128>
  <#lt>DS   = ${idau_ds}
</#if>
<#assign urow2 = idau_as + (idau_ansc * pow2(8)) + (idau_rs * pow2(24)) + (idau_ds * pow2(16))>
UROW2 = ${num2hex(urow2)}

