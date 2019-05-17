/*
 * Copyright 2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "tzm_config.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*!
 * @brief TrustZone initialization
 */
void BOARD_InitTrustZone()
{
	TZM_Config_SAU();

	TZM_Config_MPC();

	TZM_Config_PPC();
    
    /* Enable AHB secure controller check and lock all rule registers */
    AHB_SECURE_CTRL->MISC_CTRL_DP_REG = (AHB_SECURE_CTRL->MISC_CTRL_DP_REG & ~(AHB_SECURE_CTRL_MISC_CTRL_DP_REG_WRITE_LOCK_MASK | 
                                                                               AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_SECURE_CHECKING_MASK)) |
                                        AHB_SECURE_CTRL_MISC_CTRL_DP_REG_WRITE_LOCK(0x1U) |
                                        AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_SECURE_CHECKING(0x1U);
}
