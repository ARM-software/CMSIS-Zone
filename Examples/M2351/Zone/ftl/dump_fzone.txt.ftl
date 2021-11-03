<#compress>
<#include "helper.ftlinc"/>
</#compress>
// Model dump

Memory:                                         access   security
  name                  start       size        p r w x  s n c
<#list system.memory?sort_by("start") as m>
  ${m.name?right_pad(20)}<#rt>
  ${m.start?right_pad(8)}<#rt>
  ${m.size?right_pad(8)}<#rt>
  ${m.access.p} ${m.access.r} ${m.access.w} ${m.access.x}<#rt>
  ${m.security.s} ${m.security.n} ${m.security.c}
</#list>

Peripheral:                                                           access   security
  name                  start       start_s     start_ns    size      p r w x  s n c     group
<#list system.peripheral?sort_by("name") as p>
  ${p.name?right_pad(20)}<#rt>
  ${(p.start!"not given")?right_pad(10)}<#rt>
  ${p.start_s[0]!"not given "}<#rt>
  ${p.start_ns[0]!"not given "}<#rt>
  ${p.size?right_pad(8)}<#rt>
  ${p.access.p} ${p.access.r} ${p.access.w} ${p.access.x}<#rt>
  ${p.security.s} ${p.security.n} ${p.security.c}   <#rt>
  ${p.group[0]!"not given"}
</#list>

<#if system.interrupt?has_content>
Interrupt:                      security
  name                  number  s n
<#list system.interrupt as irq>
  ${irq.name?right_pad(20)}<#rt>
  ${irq.irqn?number?left_pad(4)}  <#rt>
  ${irq.security.s} ${irq.security.n}
</#list>
</#if>

<#if system.sau?has_content>
SAU entry:
  start       end         nsc  info
<#list system.sau?sort_by("start") as s>
  ${num2hex(hex2num(s.start))}<#rt>
  ${num2hex(hex2num(s.end))}<#rt>
  ${s.nsc?right_pad(3)}<#rt>
  ${s.info}
</#list>
</#if>

<#if system.mpc_setup?has_content>
MPC entry:
  name                                                                              Type
<#list system.mpc_setup?sort_by("start") as mpc>
  ${mpc.name?right_pad(80)}<#rt>
  ${mpc.type?right_pad(4)}
  <#if mpc.S_bit?has_content>
  S-bits: <#rt>
    <#lt><#list mpc.S_bit as s>${s}</#list>
  </#if>
  <#if mpc.P_bit?has_content>
  P-bits: <#rt>
    <#lt><#list mpc.P_bit as p>${p}</#list>
  </#if>

</#list>
</#if>

<#--
<#if system.mpc_setup?has_content>
MPC entry:
  name                                                                              start       size
<#list system.mpc_setup?sort_by("start") as mpc>
  ${mpc.name?right_pad(80)}<#rt>
  ${mpc.start}<#rt>
  ${mpc.size}
  s-bits
<#list mpc.S_bit?chunk(32) as s_word>
  [${(s_word?index)?left_pad(2)}]<#rt>
  <#list s_word as s_bit>${s_bit}</#list>
</#list>

</#list>
</#if>
-->

<#if system.reg_setup?has_content>
Register Setup:
  Register                                                                          Value       Peripheral
<#list system.reg_setup as reg>
  <#assign val=0>
  <#assign name=reg.name />
  <#if reg.index?length gt 0>
    <#assign name += "["+reg.index+"]" />
  </#if>
  ${name?right_pad(80)}<#rt>
  <#list reg.value as v>
  <#assign val += hex2num(v)>
  ${v}  ${(reg.peripheral[v?index])?right_pad(20)}  ${reg.slot[v?index]}
  <#sep>${""?right_pad(80)}<#rt>
  </#list>
                                                                                  ----------
                                                                                    ${num2hex(val)}

</#list>
</#if>

Zones:
<#list zone as z>
  ${z.name}
<#list z.* as c>
  - ${c?node_name?right_pad(10)}: <#rt>
<#if ((c?node_name == "peripheral") || (c?node_name == "memory"))>
${c.name?right_pad(20)} (${num2hex(hex2num(c.start))} : ${c.size})
<#elseif c?node_name == "security">
<#if c.s=="1">secure<#elseif c.n=="1">non-secure<#elseif c.c=="1">non-secure callable<#else>unknown</#if>
<#elseif c?node_name == "privilege">
<#if c.p=="1">privileged<#elseif c.u=="1">unprivileged<#else>unknown</#if>
<#elseif c?node_name == "mpu_setup">
${c.type}
<#list c.region?sort_by("start") as mpu_region>
${" "?right_pad(4)}- ${mpu_region.info?right_pad(31)} ${num2hex(hex2num(mpu_region.start))} .. ${num2hex(hex2num(mpu_region.end))}<#rt>
<#if c.type == "v7M">
  (${mpu_region.addr_v7M} : ${mpu_region.size_v7M}, ${mpu_region.srd_v7M})
<#else>

</#if>
</#list>
<#else>
${c}
</#if>
</#list>

</#list>

