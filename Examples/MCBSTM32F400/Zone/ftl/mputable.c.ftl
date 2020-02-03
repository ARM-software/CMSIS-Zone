<#compress>
<#include "helper.ftlinc"/>
</#compress>
/*
 * MPU Table Source File generated by CMSIS-Zone 
 */
 
#include "mputable.h"

const ARM_MPU_Region_t mpuTable[${zone?filter(x -> x.privilege.u == "1")?size}u][8u] = {
{<#rt>
 <#list zone?filter(x -> x.privilege.u == "1") as z><#rt>
  <#lt> /* Execution Zone '${z.name}' */ 
    <#list z.mpu_setup.region as r>
  // ${r.info} (${r.start}..${r.end})
  { .RBAR = ARM_MPU_RBAR(${r?index}u, ${r.addr_v7M}), <#rt>
    <#lt>.RASR = ARM_MPU_RASR_EX(<#rt>
    	<#lt>${(r.access.x == '1')?then('0', '1')}u, <#rt> 
    	<#lt>ARM_MPU_AP_FULL, <#rt>
    	<#lt>ARM_MPU_ACCESS_${(r.access.p == '1')?then('DEVICE('+r.shared+'u)', 'NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, '+r.shared+'u)')}, <#rt> 
    	<#lt>${r.srd_v7M}u, <#rt>
    	<#lt>ARM_MPU_REGION_SIZE_${pow2str(hex2num(r.size_v7M)+1)}B<#rt>
	<#lt>) }<#rt>
    <#lt><#sep>,
    </#list><#rt>
    <#list z.mpu_setup.region?size..!8><#lt>,
      <#items as r>
  { .RBAR = ARM_MPU_RBAR(${r}u, 0u), .RASR = 0u }<#sep>,
      </#items>
    </#list>

  <#sep>
  <#lt>},{<#rt>
</#list>
}};