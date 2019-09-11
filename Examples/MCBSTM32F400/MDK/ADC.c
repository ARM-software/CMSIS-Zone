
#include "main.h"
#include "Board_ADC.h"                  // ::Board Support:A/D Converter

volatile uint8_t ADC_Val = 0U;

/* ADC thread stack */
static uint64_t ADC_Stack[256/8];

/* ADC thread attributes */
static const osThreadAttr_t ADC_ThreadAttr = {
  .stack_mem  = &ADC_Stack,
  .stack_size = sizeof(ADC_Stack),
  .reserved   = MPUTABLE_BLINKY,
  .priority = osPriorityAboveNormal1,
};

/* ADC thread */
static __NO_RETURN void ADC_Thread (void *arg) {
  osThreadId_t notify_tid = arg;
  uint32_t     adc_last = 0xFFFFFFFFU;
  uint8_t      msg[2];

  for (;;) {
    ADC_StartConversion();
    osDelay(50U);
    ADC_Val = (uint8_t)(ADC_GetValue() >> 4);
    TamperADC();
    osThreadFlagsSet(notify_tid, FLAG_ADC_ALIVE);
    if ((net_state & NET_CONNECTED) != 0U) {
      if (ADC_Val != adc_last) {
        adc_last = ADC_Val;
        msg[0] = 0x01U;
        msg[1] = ADC_Val;
        osMessageQueuePut(OutgoingMsgId, msg, 0U, 0U);
      }
    } else {
      adc_last = 0xFFFFFFFFU;
    }
  }
}

/* Create ADC thread */
osThreadId_t ADC_CreateThread (osThreadId_t notify_tid) {
  osThreadId_t tid;

  tid = osThreadNew(ADC_Thread, notify_tid, &ADC_ThreadAttr);
  return (tid);
}
