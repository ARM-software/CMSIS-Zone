/*----------------------------------------------------------------------------
 * Name:    main_s.c
 * Purpose: Main function secure mode
 *----------------------------------------------------------------------------*/

#include <arm_cmse.h>
#include "RTE_Components.h"             // Component selection
#include  CMSIS_device_header           // Device header
#include "Board_LED.h"                  // ::Board Support:LED

#include "stm32l5xx_hal.h"
#include "mem_layout.h"

/* Start address of non-secure application */
#define NONSECURE_START REGION_CODE_NS_START

/*----------------------------------------------------------------------------
  System Isolation Configuration
  This function is responsible for Memory and Peripheral isolation
  for secure and non-secure application parts
 *----------------------------------------------------------------------------*/
extern void SystemIsolation_Config(void);

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
