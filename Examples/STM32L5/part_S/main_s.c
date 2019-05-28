/*----------------------------------------------------------------------------
 * Name:    main_s.c
 * Purpose: Main function secure mode
 *----------------------------------------------------------------------------*/

#include <arm_cmse.h>
#include "RTE_Components.h"             // Component selection
#include  CMSIS_device_header           // Device header
#include "Board_LED.h"                  // ::Board Support:LED

#include "stm32l5xx_hal.h"

/* Start address of non-secure application */
#define NONSECURE_START (0x08040000U)

/* typedef for NonSecure callback functions */
typedef int32_t (*NonSecure_fpParam)(uint32_t) __attribute__((cmse_nonsecure_call));
typedef void    (*NonSecure_fpVoid) (void)     __attribute__((cmse_nonsecure_call));

/*----------------------------------------------------------------------------
  NonSecure callback functions
 *----------------------------------------------------------------------------*/
extern NonSecure_fpParam pfNonSecure_LED_On;
       NonSecure_fpParam pfNonSecure_LED_On  = (NonSecure_fpParam)NULL;
extern NonSecure_fpParam pfNonSecure_LED_Off;
       NonSecure_fpParam pfNonSecure_LED_Off = (NonSecure_fpParam)NULL;


/*----------------------------------------------------------------------------
  Secure functions exported to NonSecure application
 *----------------------------------------------------------------------------*/
int32_t Secure_LED_On (uint32_t num) __attribute__((cmse_nonsecure_entry));
int32_t Secure_LED_On (uint32_t num)
{
  return LED_On(num);
}

int32_t Secure_LED_Off (uint32_t num) __attribute__((cmse_nonsecure_entry)) ;
int32_t Secure_LED_Off (uint32_t num)
{
  return LED_Off(num);
}


/*----------------------------------------------------------------------------
  Secure function for NonSecure callbacks exported to NonSecure application
 *----------------------------------------------------------------------------*/
int32_t Secure_LED_On_callback(NonSecure_fpParam callback) __attribute__((cmse_nonsecure_entry));
int32_t Secure_LED_On_callback(NonSecure_fpParam callback)
{
  pfNonSecure_LED_On = cmse_nsfptr_create(callback);
  return 0;
}

int32_t Secure_LED_Off_callback(NonSecure_fpParam callback) __attribute__((cmse_nonsecure_entry));
int32_t Secure_LED_Off_callback(NonSecure_fpParam callback)
{
  pfNonSecure_LED_Off = cmse_nsfptr_create(callback);
  return 0;
}


/*----------------------------------------------------------------------------
  SysTick IRQ Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void);
void SysTick_Handler (void) {
  static uint32_t ticks = 0;

  switch (ticks++) {
    case 30:
      if (pfNonSecure_LED_On != NULL)
      {
        pfNonSecure_LED_On(0U);
      }
      break;
    case 50:
      if (pfNonSecure_LED_Off != NULL)
      {
        pfNonSecure_LED_Off(0U);
      }
      break;
    case 99:
      ticks = 0;
      break;
    default:
      if (ticks > 99) {
        ticks = 0;
      }
  }
}

/*----------------------------------------------------------------------------
  System Isolation Configuration
  This function is responsible for Memory and Peripheral isolation
  for secure and non-secure application parts
 *----------------------------------------------------------------------------*/
static void SystemIsolation_Config(void)
{
  MPCBB_ConfigTypeDef MPCBB_desc;

  /* At this stage  IDAU/SAU setup has already been done in SystemInit() */
  /* based on partition_stm32l5xx.h */

  /* Enable GTZC peripheral clock */
  __HAL_RCC_GTZC_CLK_ENABLE();

  /* -------------------------------------------------------------------------*/
  /*                   Memory isolation configuration                         */
  /* Initializes the memory that secure application books for non secure      */
  /* -------------------------------------------------------------------------*/

  /* -------------------------------------------------------------------------*/
  /* Internal RAM */
  /* The booking is done in both IDAU/SAU and GTZC MPCBB */

  /* GTZC MPCBB setup */
  /* based on non-secure RAM memory area starting from 0x20018000 */
  /* 0x20018000 is the start address of second SRAM1 half         */
  /* Internal SRAM is secured by default and configured by block  */
  /* of 256bytes.                                                 */
  /* Non-secure block-based memory starting from 0x20018000 means */
  /* 0x18000 / (256 * 32) = 12 bytes for secure block-based memory*/
  /* and remaining bytes set to 0 for all non-secure blocks       */
  if (HAL_GTZC_MPCBB_GetConfigMem(SRAM1_BASE_NS, &MPCBB_desc) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  MPCBB_desc.SecConfig.MPCBB_VCTR_array[12] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[13] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[14] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[15] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[16] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[17] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[18] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[19] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[20] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[21] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[22] = 0x00000000U;
  MPCBB_desc.SecConfig.MPCBB_VCTR_array[23] = 0x00000000U;

  if (HAL_GTZC_MPCBB_ConfigMem(SRAM1_BASE_NS, &MPCBB_desc) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* -------------------------------------------------------------------------*/
  /* Internal Flash */
  /* The booking is done in both IDAU/SAU and FLASH interface */

  /* Setup done based on Flash dual-bank mode described with 1 area per bank  */
  /* Non-secure Flash memory area starting from 0x08040000 (Bank2)            */
  /* Flash memory is secured by default and modified with Option Byte Loading */
  /* Insure SECWM2_PSTRT > SECWM2_PEND in order to have all Bank2 non-secure  */

  /* -------------------------------------------------------------------------*/
  /* External OctoSPI memory */
  /* The booking is done in both IDAU/SAU and GTZC MPCWM interface */

  /* Default secure configuration */
  /* Else need to use HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes() */

  /* -------------------------------------------------------------------------*/
  /* External NOR/FMC memory */
  /* The booking is done in both IDAU/SAU and GTZC MPCWM interface */

  /* Default secure configuration */
  /* Else need to use HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes() */

  /* -------------------------------------------------------------------------*/
  /* External NAND/FMC memory */
  /* The booking is done in both IDAU/SAU and GTZC MPCWM interface */

  /* Default secure configuration */
  /* Else need to use HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes() */


  /* -------------------------------------------------------------------------*/
  /*                   Peripheral isolation configuration                     */
  /* Initializes the peripherals and features that secure application books   */
  /* for secure (RCC, PWR, RTC, EXTI, DMA, OTFDEC, etc..) or leave them to    */
  /* non-secure (GPIO (secured by default))                                   */
  /* -------------------------------------------------------------------------*/

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


/*----------------------------------------------------------------------------
  System Clock Configuration
  The system Clock is configured as follows :
     System Clock source            = PLL (MSI)
     SYSCLK(Hz)                     = 110000000
     HCLK(Hz)                       = 110000000
     AHB Prescaler                  = 1
     APB1 Prescaler                 = 1
     APB2 Prescaler                 = 1
     MSI Frequency(Hz)              = 4000000
     PLL_M                          = 1
     PLL_N                          = 55
     PLL_Q                          = 2
     PLL_R                          = 2
     PLL_P                          = 2
     Flash Latency(WS)              = 5
 *----------------------------------------------------------------------------*/
static void SystemCoreClockConfig(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable voltage range 0 for frequency above 80 Mhz */
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE0);
  __HAL_RCC_PWR_CLK_DISABLE();

  /* MSI Oscillator enabled at reset (4Mhz), activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 55;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1);    /* Initialization Error */
  }

  /* Select PLL as system clock source with transition state */
  /* with AHB prescaler divider 2 as first step */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    while(1);    /* Initialization Error */
  }

  /* AHB prescaler divider at 1 as second step */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    while(1);    /* Initialization Error */
  }
}

/*----------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
int main (void)
{
  uint32_t         NonSecure_StackPointer=                   (*((uint32_t *)(NONSECURE_START + 0u)));
  NonSecure_fpVoid NonSecure_ResetHandler= (NonSecure_fpVoid)(*((uint32_t *)(NONSECURE_START + 4u)));

  /* Secure/Non-secure Memory and Peripheral isolation configuration */
  SystemIsolation_Config();

  /* Enable BusFault and SecureFault handlers (HardFault is default) */
  SCB->SHCSR |= (SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_SECUREFAULTENA_Msk);

  SystemCoreClockConfig();
  SystemCoreClockUpdate();

  LED_Initialize ();

  SysTick_Config(SystemCoreClock / 100);  /* Generate interrupt each 10 ms */

  SCB_NS->VTOR = NONSECURE_START;           /* Set non-secure vector table location */
  __TZ_set_MSP_NS(NonSecure_StackPointer);  /* Set non-secure stack pointer */
  NonSecure_ResetHandler();                 /* Start non-secure application */
}
