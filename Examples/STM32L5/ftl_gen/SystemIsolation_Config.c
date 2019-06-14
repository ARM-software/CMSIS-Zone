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
  WRITE_REG(GTZC_MPCBB1_S->VCTR[0], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[1], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[2], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[3], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[4], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[5], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[6], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[7], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[8], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[9], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[10], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[11], 0xFFFFFFFFU);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[12], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[13], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[14], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[15], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[16], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[17], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[18], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[19], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[20], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[21], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[22], 0x00000000U);
  WRITE_REG(GTZC_MPCBB1_S->VCTR[23], 0x00000000U);
  /* SRAM2 */
  WRITE_REG(GTZC_MPCBB2_S->VCTR[0], 0x00000000U);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[1], 0x00000000U);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[2], 0x00000000U);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[3], 0x00000000U);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[4], 0x00000000U);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[5], 0x00000000U);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[6], 0x00000000U);
  WRITE_REG(GTZC_MPCBB2_S->VCTR[7], 0x00000000U);
  
  /* Setup Peripheral Protection Controller (PPC) */
  WRITE_REG(DMA1_Channel1_S->CCR,
    0x00020000 | /* DMA1_CH1 */
    0x00100000   /* DMA1_CH1 */
  );
  WRITE_REG(DMA1_Channel2_S->CCR,
    0x00020000 | /* DMA1_CH2 */
    0x00100000   /* DMA1_CH2 */
  );
  WRITE_REG(GPIOA_S->SECCFGR,
    0x00000002   /* GPIOA1 */
  );
  WRITE_REG(GPIOG_S->SECCFGR,
    0x00000080   /* GPIOG7 */
  );
  WRITE_REG(GTZC_TZSC->PRIVCFGR1,
    0x40000000 | /* TIM1 */
    0x00000400   /* USART2 */
  );
  WRITE_REG(GTZC_TZSC->PRIVCFGR2,
    0x00000002 | /* USART1 */
    0x00000800   /* ADC */
  );
  WRITE_REG(GTZC_TZSC->SECCFGR1,
    0x40000000   /* TIM1 */
  );
  WRITE_REG(GTZC_TZSC->SECCFGR2,
    0x00000002 | /* USART1 */
    0x00000800   /* ADC */
  );

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
