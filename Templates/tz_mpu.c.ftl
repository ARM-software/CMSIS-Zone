<#compress>
<#include "helper.ftlinc"/>

<#assign mpu_valid = zone.mpu_setup?has_content>
</#compress>
/*
 * Copyright 2019 Arm Limited
 *
 * SPDX-License-Identifier: Apache 2.0
 */
<#if mpu_valid>

#include "RTE_Components.h"
#include CMSIS_device_header

/* MPU Memory Attributes */
static const uint8_t mpu_attr[8] = { 
  /* (0) Device (e.g.: Peripherals) : 
   * - non gathering
   * - non re-ordering
   * - early write acknowledgement
   */
  ARM_MPU_ATTR(ARM_MPU_ATTR_DEVICE, ARM_MPU_ATTR_DEVICE_nGnRE), 
  
  /* (1) Code memory (e.g: Flash memory, Internal SRAM) with same outer/inner cache policy:
   * - non-transient
   * - no write-back
   * - read allocate
   * - no write allocate
   */
  ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(1, 0, 1, 0), ARM_MPU_ATTR_MEMORY_(1, 0, 1, 0)),
  
  /* (2) Data memory (e.g.: External SRAM) with same outer/inner cache policy:
   * - transient
   * - write-back
   * - read allocate
   * - write allocate
   */
  ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(1, 1, 1, 1), ARM_MPU_ATTR_MEMORY_(1, 1, 1, 1)),
  
  /* (3)-(7) unused */
  0, 0, 0, 0, 0
};
</#if>

<#list zone as z>
  <#if z.mpu_setup?has_content>
    <#assign mrt = []/>        <#-- MPU region table -->
    <#assign mrt_entries = 0>  <#-- MPU region table entries -->
<#compress>
    <#list z.mpu_setup.region?sort_by("start") as mr>
      <#assign mr_ro = ((mr.access.w == '0') && (mr.access.r == '1'))?then(1, 0)> <#-- MPU region Read only -->
      <#assign mr_sh = ((mr.shared   == '1') || (mr.dma      == '1'))?then(3, 0)> <#-- MPU region sharability -->
      <#assign mr_np = (mr.privileged == '1')?then(0, 1)>                         <#-- MPU region non privileged -->
      <#assign mr_xn = (mr.access.x   == '1')?then(0, 1)>                         <#-- MPU region Execute Never -->
      <#if     (hex2num(mr.start) >= hex2num("0x00000000")) && (hex2num(mr.end) < hex2num("0x1FFFFFFF"))>
        <#assign mr_idx = 1>                                                      <#-- Code -->
      <#elseif (hex2num(mr.start) >= hex2num("0x20000000")) && (hex2num(mr.end) < hex2num("0x3FFFFFFF"))>
        <#assign mr_idx = 1>                                                      <#-- RAM -->
      <#elseif (hex2num(mr.start) >= hex2num("0x40000000")) && (hex2num(mr.end) < hex2num("0x5FFFFFFF"))>
        <#assign mr_idx = 0>                                                      <#-- Peripherals -->
      <#elseif (hex2num(mr.start) >= hex2num("0x60000000")) && (hex2num(mr.end) < hex2num("0x9FFFFFFF"))>
        <#assign mr_idx = 2>                                                      <#-- external memory -->
      <#else>
        <#assign mr_idx = 2>                                                      <#-- default -->
      </#if>      
      <#assign mrt += [{"info":mr.info, "base":num2hex(hex2num(mr.start)), "limit":num2hex(hex2num(mr.end)), "sh":mr_sh, "ro":mr_ro, "np":mr_np, "xn":mr_xn, "idx":mr_idx}]/>
      <#assign mrt_entries += 1>
    </#list>
</#compress>
/* 
 * ${z.name} MPU table
 */
ARM_MPU_Region_t mpu_table_${z.name}[1][${mrt_entries}] = {
{
<#list mrt as mrt_entry>
  /* MPU region <#rt>
     ${mrt_entry.info}:<#lt>
   * <#rt>
     ${(mrt_entry.sh == 3)?then("inner-shareable","non-shareable")}, <#lt><#rt>
     ${(mrt_entry.ro == 1)?then("read-only","read/write")}, <#lt><#rt>
     ${(mrt_entry.np == 0)?then("privileged","non-privileged")}, <#lt><#rt>
     ${(mrt_entry.xn == 0)?then("executable","non-executable")} <#lt>
   */
  {
    .RBAR = ARM_MPU_RBAR(${mrt_entry.base}U, ${(mrt_entry.sh == 3)?then("ARM_MPU_SH_INNER","ARM_MPU_SH_NON")}, ${mrt_entry.ro}U, ${mrt_entry.np}U, ${mrt_entry.xn}U),
    .RLAR = ARM_MPU_RLAR(${mrt_entry.limit}U, ${mrt_entry.idx}U)
  }<#if (mrt_entry?has_next)>;</#if>

</#list>
}

// Add further configurations below for TF-M Level 3

};

  </#if>
</#list>

<#if mpu_valid>
/*
 * Initial MPU configuration
 * Load static MPU regions for Level 2
 */
void TZ_Config_MPU(void)
{
  ARM_MPU_Disable();
  
  for(uint32_t i=0U; i<8; i++) {
    ARM_MPU_SetMemAttr(i, mpu_attr[i]);
    ARM_MPU_ClrRegion(i);
  }
  
  ARM_MPU_Load(0U, mpu_table[0U], 4U);
  
  ARM_MPU_Enable(1U);
}
</#if>
