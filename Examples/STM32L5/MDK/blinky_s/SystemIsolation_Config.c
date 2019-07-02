/*----------------------------------------------------------------------------
  System Isolation Configuration
  This function is responsible for Memory and Peripheral isolation
  for secure and non-secure application parts
 *----------------------------------------------------------------------------*/

#include "stm32l5xx_hal.h"

void SystemIsolation_Config(void)
{
  /* Enable GTZC peripheral clock */
  __HAL_RCC_GTZC_CLK_ENABLE();

  /* Setup Memory Protection Controller (MPC) */
  /* SRAM1 */
  WRITE_REG(GTZC_MPCBB1_S->VCTR[0], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[1], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[2], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[3], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[4], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[5], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[6], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[7], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[8], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[9], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[10], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[11], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[12], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[13], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[14], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[15], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[16], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[17], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[18], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[19], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[20], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[21], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[22], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[23], 0xFFFFFFFFU);
  /* SRAM2 */
  WRITE_REG(GTZC_MPCBB2_S->VCTR[0], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[1], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[2], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[3], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[4], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[5], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[6], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[7], 0xFFFFFFFFU);
  
  /* Setup Peripheral Protection Controller (PPC) */

  /* Clear all illegal access pending interrupts in TZIC */
  if (HAL_GTZC_TZIC_ClearFlag(GTZC_PERIPH_ALL) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Enable all illegal access interrupts in TZIC */
  if(HAL_GTZC_TZIC_EnableIT(GTZC_PERIPH_ALL) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Enable TZIC secure interrupt */
  HAL_NVIC_SetPriority(TZIC_S_IRQn, 0, 0); /* Highest priority level */
  HAL_NVIC_ClearPendingIRQ(TZIC_S_IRQn);
  HAL_NVIC_EnableIRQ(TZIC_S_IRQn);
}
