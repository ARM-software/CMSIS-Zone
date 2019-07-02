/*----------------------------------------------------------------------------
 * Name:    main_ns.c
 * Purpose: Main function non-secure mode
 *----------------------------------------------------------------------------*/

#include <arm_cmse.h>

#include "RTE_Components.h"             // Component selection
#include  CMSIS_device_header           // Device header
#include "Secure_Functions.h" 					// Secure Code Entry Points


/*----------------------------------------------------------------------------
  NonSecure functions used for callbacks
 *----------------------------------------------------------------------------*/
int32_t NonSecure_LED_On(uint32_t num);
int32_t NonSecure_LED_On(uint32_t num)
{
  return Secure_LED_On(num);
}

int32_t NonSecure_LED_Off(uint32_t num);
int32_t NonSecure_LED_Off(uint32_t num)
{
  return Secure_LED_Off(num);
}


/*----------------------------------------------------------------------------
  SysTick IRQ Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void);
void SysTick_Handler (void) {
  static uint32_t ticks;

  switch (ticks++) {
    case 20:
      Secure_LED_On(1U);
      break;
    case 50:
      Secure_LED_Off(1U);
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
  Main function
 *----------------------------------------------------------------------------*/
int main (void)
{
  uint32_t i;

  /* register NonSecure callbacks in Secure application */
  Secure_LED_On_callback(NonSecure_LED_On);
  Secure_LED_Off_callback(NonSecure_LED_Off);

  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 250);  /* Generate interrupt each 25 ms */

while (1) {
    Secure_LED_On (2U);
    for (i = 0; i < 0x400000; i++) __NOP();
    Secure_LED_Off(2U);
    for (i = 0; i < 0x400000; i++) __NOP();
  }
}
