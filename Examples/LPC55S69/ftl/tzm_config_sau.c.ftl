/*
 * Copyright 2019 Arm Limited
 *
 * SPDX-License-Identifier: Apache 2.0
 */

#include "tzm_config.h" 
#include "fsl_common.h"

void TZM_Config_SAU(void)
{
    /* Disable SAU */
    SAU->CTRL = 0U;
    
<#list system.sau as region>
    /* Configure SAU region ${region?index} - ${region.info} */
    /* Set SAU region number */
    SAU->RNR = ${region?index};
    /* Region base address */   
    SAU->RBAR = ${region.start};
    /* Region end address */
    SAU->RLAR = (${region.end} & SAU_RLAR_LADDR_Msk) | 
                 /* Region memory attribute index */
                 ((${region.nsc}U << SAU_RLAR_NSC_Pos) & SAU_RLAR_NSC_Msk) |
                 /* Enable region */
                 ((1U << SAU_RLAR_ENABLE_Pos) & SAU_RLAR_ENABLE_Msk);
</#list>
                 
     /* Force memory writes before continuing */
    __DSB();
    /* Flush and refill pipeline with updated permissions */
    __ISB();     
    /* Enable SAU */
    SAU->CTRL = 1U;                    
}
