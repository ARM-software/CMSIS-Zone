
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
  ${p.start[0]!"not given "}<#rt>
  ${p.start_s[0]!"not given "}<#rt>
  ${p.start_ns[0]!"not given "}<#rt>
  ${p.size?right_pad(8)}<#rt>
  ${p.access.p} ${p.access.r} ${p.access.w} ${p.access.x}<#rt>
  ${p.security.s} ${p.security.n} ${p.security.c}<#rt>
     ${p.group[0]!"not given"}
</#list>

<#if system.interrupt?has_content>
Interrupt:                      security
  name                  number  s n
<#list system.interrupt?sort_by("irqn") as irq>
  ${irq.name?right_pad(20)}<#rt>
  ${irq.irqn?right_pad(4)}  <#rt>
  ${irq.security.s} ${irq.security.n}
</#list>
</#if>

<#if system.sau?has_content>
SAU entry:
  start       end         nsc  info
<#list system.sau?sort_by("start") as s>
  ${s.start}<#rt>
  ${s.end}<#rt>
  ${s.nsc?right_pad(3)}<#rt>
  ${s.info}
</#list>
</#if>

<#if system.mpc_setup?has_content>
MPC entry:
  name
<#list system.mpc_setup?sort_by("start") as mpc>
  ${mpc.name}  <#list mpc.S_bit as s>${s}</#list>
</#list>
</#if>

<#list zone as z>
  zone : ${z.name}
<#list z.* as c>
         - ${c?node_name}<#rt>
<#if ((c?node_name == "peripheral") || (c?node_name == "memory"))>
 : ${c.name}
<#else>

</#if>
</#list>
</#list>

<#list system.group as g>
    group - name:   ${g.name}
</#list>
