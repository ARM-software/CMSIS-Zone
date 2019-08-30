<#compress>
<#include "helper.ftlinc"/>

</#compress>
/*
 * Copyright 2019 Arm Limited
 *
 * SPDX-License-Identifier: Apache 2.0
 */

#include "RTE_Components.h"
#include CMSIS_device_header

/*------------------- Memory Protection Controller -----------------------------*/
typedef struct /* see "ARM CoreLink SSE-200 Subsystem Technical Reference Manual r1p0" */
{
  __IOM  uint32_t CTRL;                     /* Offset: 0x000 (R/W) Control Register */
         uint32_t RESERVED0[3];
  __IM   uint32_t BLK_MAX;                  /* Offset: 0x010 (R/ ) Block Maximum Register */
  __IM   uint32_t BLK_CFG;                  /* Offset: 0x014 (R/ ) Block Configuration Register */
  __IOM  uint32_t BLK_IDX;                  /* Offset: 0x018 (R/W) Block Index Register */
  __IOM  uint32_t BLK_LUT;                  /* Offset: 0x01C (R/W) Block Lookup Tabe Register */
  __IM   uint32_t INT_STAT;                 /* Offset: 0x020 (R/ ) Interrupt Status Register */
  __OM   uint32_t INT_CLEAR;                /* Offset: 0x024 ( /W) Interrupt Clear Register */
  __IOM  uint32_t INT_EN;                   /* Offset: 0x028 (R/W) Interrupt Enable Register */
  __IM   uint32_t INT_INFO1;                /* Offset: 0x02C (R/ ) Interrupt Info1 Register */
  __IM   uint32_t INT_INFO2;                /* Offset: 0x030 (R/ ) Interrupt Info2 Register */
  __OM   uint32_t INT_SET;                  /* Offset: 0x034 ( /W) Interrupt Set Register */
} MPC_TypeDef;

#define MPC_SRAM0               ((MPC_TypeDef *) MUSCA_MPC_SRAM0_S_BASE     )
#define MPC_SRAM1               ((MPC_TypeDef *) MUSCA_MPC_SRAM1_S_BASE     )
#define MPC_SRAM2               ((MPC_TypeDef *) MUSCA_MPC_SRAM2_S_BASE     )
#define MPC_SRAM3               ((MPC_TypeDef *) MUSCA_MPC_SRAM3_S_BASE     )
#define MPC_CODE_SRAM           ((MPC_TypeDef *) MUSCA_CODE_SRAM_MPC_S_BASE )
#define MPC_QSPI                ((MPC_TypeDef *) MUSCA_QSPI_MPC_S_BASE      )


/*------------------- SPCTRL Peripheaal Protection Controller ------------------*/
typedef struct /* see "ARM CoreLink SSE-200 Subsystem Technical Reference Manual r1p0" */
{
  __IOM  uint32_t RESERVED[8];
  __IOM  uint32_t SECPPCINTSTAT;  /* Offset: 0x020 (R/W) Secure PPC Interrupt Status */
  __IOM  uint32_t SECPPCINTCLR;   /* Offset: 0x024 (R/W) Secure PPC Interrupt Clear */
  __IOM  uint32_t SECPPCINTEN;    /* Offset: 0x028 (R/W) Secure PPC Interrupt Enable */
  __IOM  uint32_t RESERVED1[9];
  __IOM  uint32_t AHBNSPPC0;      /* Offset: 0x050 (R/W) Non-Secure Access AHB slave Peripheral Protection Control 0 */
  __IOM  uint32_t RESERVED2[3];
  __IOM  uint32_t AHBNSPPCEXP0;   /* Offset: 0x060 (R/W) Expansion 0 Non_Secure Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t AHBNSPPCEXP1;   /* Offset: 0x064 (R/W) Expansion 1 Non_Secure Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t AHBNSPPCEXP2;   /* Offset: 0x068 (R/W) Expansion 2 Non_Secure Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t AHBNSPPCEXP3;   /* Offset: 0x06C (R/W) Expansion 3 Non_Secure Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t APBNSPPC0;      /* Offset: 0x070 (R/W) Non-Secure Access APB slave Peripheral Protection Control 0 */
  __IOM  uint32_t APBNSPPC1;      /* Offset: 0x074 (R/W) Non-Secure Access APB slave Peripheral Protection Control 1 */
  __IOM  uint32_t RESERVED3[2];
  __IOM  uint32_t APBNSPPCEXP0;   /* Offset: 0x080 (R/W) Expansion 0 Non_Secure Access APB slave Peripheral Protection Control */
  __IOM  uint32_t APBNSPPCEXP1;   /* Offset: 0x084 (R/W) Expansion 1 Non_Secure Access APB slave Peripheral Protection Control */
  __IOM  uint32_t APBNSPPCEXP2;   /* Offset: 0x088 (R/W) Expansion 2 Non_Secure Access APB slave Peripheral Protection Control */
  __IOM  uint32_t APBNSPPCEXP3;   /* Offset: 0x08C (R/W) Expansion 3 Non_Secure Access APB slave Peripheral Protection Control */
  __IOM  uint32_t AHBSPPPC0;      /* Offset: 0x090 (R/W) Secure Unprivileged Access AHB slave Peripheral Protection Control 0 */
  __IOM  uint32_t RESERVED4[3];
  __IOM  uint32_t AHBSPPPCEXP0;   /* Offset: 0x0A0 (R/W) Expansion 0 Secure Unprivileged Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t AHBSPPPCEXP1;   /* Offset: 0x0A4 (R/W) Expansion 1 Secure Unprivileged Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t AHBSPPPCEXP2;   /* Offset: 0x0A8 (R/W) Expansion 2 Secure Unprivileged Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t AHBSPPPCEXP3;   /* Offset: 0x0AC (R/W) Expansion 3 Secure Unprivileged Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t APBSPPPC0;      /* Offset: 0x0B0 (R/W) Secure Unprivileged Access APB slave Peripheral 0 */
  __IOM  uint32_t APBSPPPC1;      /* Offset: 0x0B4 (R/W) Secure Unprivileged Access APB slave Peripheral 1 */
  __IOM  uint32_t RESERVED5[2];
  __IOM  uint32_t APBSPPPCEXP0;   /* Offset: 0x0C0 (R/W) Expansion 0 Secure Unprivileged Access APB slave Peripheral Protection Control */
  __IOM  uint32_t APBSPPPCEXP1;   /* Offset: 0x0C4 (R/W) Expansion 1 Secure Unprivileged Access APB slave Peripheral Protection Control */
  __IOM  uint32_t APBSPPPCEXP2;   /* Offset: 0x0C8 (R/W) Expansion 2 Secure Unprivileged Access APB slave Peripheral Protection Control */
  __IOM  uint32_t APBSPPPCEXP3;   /* Offset: 0x0CC (R/W) Expansion 3 Secure Unprivileged AccessAPB slave Peripheral Protection Control */
} SPCTRL_PPC_TypeDef;

#define SPCTRL_PPC              ((SPCTRL_PPC_TypeDef  *) MUSCA_SPCTRL_S_BASE )


/*------------------- NSPCTRL Peripheaal Protection Controller -----------------*/
typedef struct /* see "ARM CoreLink SSE-200 Subsystem Technical Reference Manual r1p0" */
{
  __IOM  uint32_t RESERVED[36];
  __IOM  uint32_t AHBNSPPPC0;     /* Offset: 0x090 (R/W) Non-secure Unprivileged Access AHB slave Peripheral Protection Control 0 */
  __IOM  uint32_t RESERVED1[3];
  __IOM  uint32_t AHBNSPPPCEXP0;  /* Offset: 0x0A0 (R/W) Expansion 0 Non-Secure Unprivileged Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t AHBNSPPPCEXP1;  /* Offset: 0x0A4 (R/W) Expansion 1 Non-Secure Unprivileged Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t AHBNSPPPCEXP2;  /* Offset: 0x0A8 (R/W) Expansion 2 Non-Secure Unprivileged Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t AHBNSPPPCEXP3;  /* Offset: 0x0AC (R/W) Expansion 3 Non-Secure Unprivileged Access AHB slave Peripheral Protection Control */
  __IOM  uint32_t APBNSPPPC0;     /* Offset: 0x0B0 (R/W) Non-Secure Unprivileged Access APB slave Peripheral Protection Control 0 */
  __IOM  uint32_t APBNSPPPC1;     /* Offset: 0x0B4 (R/W) Non-Secure Unprivileged Access APB slave Peripheral Protection Control 1 */
  __IOM  uint32_t RESERVED2[2];
  __IOM  uint32_t APBNSPPPCEXP0;  /* Offset: 0x0C0 (R/W) Expansion 0 Non-secure Unprivileged Access APB slave Peripheral Protection Control */
  __IOM  uint32_t APBNSPPPCEXP1;  /* Offset: 0x0C4 (R/W) Expansion 1 Non-secure Unprivileged Access APB slave Peripheral Protection Control */
  __IOM  uint32_t APBNSPPPCEXP2;  /* Offset: 0x0C8 (R/W) Expansion 2 Non-secure Unprivileged Access APB slave Peripheral Protection Control */
  __IOM  uint32_t APBNSPPPCEXP3;  /* Offset: 0x0CC (R/W) Expansion 3 Non-secure Unprivileged Access APB slave Peripheral Protection Control */
} NSPCTRL_PPC_TypeDef;

#define NSPCTRL_PPC             ((NSPCTRL_PPC_TypeDef *) MUSCA_NSPCTRL_NS_BASE )



/* Setup Memory Protection Controller (MPC) */
void TZ_Config_MPC(void)
{
<#list system.mpc_setup as mpc>
  /* ${mpc.info} */
  <#assign idx = 0 />
  <#list 0..((mpc.S_bit?size-1)/32) as i>
  ${mpc.name}${"->BLK_IDX"} = ${idx};
  ${mpc.name}${"->BLK_LUT"} =
    <#list 0..31 as j>
      <#assign bit   = mpc.S_bit[i*32+j]!'1'>
      <#assign n_bit = (bit == '1')?then(0, 1)>
      <#assign lut   = n_bit*pow2(j)  />
      ${num2hex(lut)}U<#if j <= 30> |<#else>; </#if>      <#if mpc.bit_comment[i*32+j]?has_content && mpc.bit_comment[i*32+j] != "">/* ${mpc.bit_comment[i*32+j]} */</#if>
    </#list>
    <#assign idx += 1 />

  </#list>

</#list>
}


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
