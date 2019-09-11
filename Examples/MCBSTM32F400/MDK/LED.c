
#include "main.h"
#include "Board_LED.h"                  // ::Board Support:LED

static const uint8_t pattern[] = {
  0x01U, 0x02U, 0x04U, 0x08U, 0x04U, 0x02U
};

/* LED thread stack */
static uint64_t LED_Stack[256/8];

/* LED thread attributes */
static const osThreadAttr_t LED_ThreadAttr = {
  .stack_mem  = &LED_Stack,
  .stack_size = sizeof(LED_Stack),
  .reserved   = MPUTABLE_BLINKY,
  .priority = osPriorityAboveNormal2,
};

/* LED thread */
static __NO_RETURN void LED_Thread (void *arg) {
  osThreadId_t notify_tid = arg;
  uint8_t      period;
  uint8_t      count;
  uint8_t      state;
  uint32_t     tick;
  osStatus_t   status;
  uint8_t      msg[2];

  osDelay(100U);

  period = ADC_Val;
  count  = 1U;
  state  = 0xFFU;

  tick   = osKernelGetTickCount();

  for (;;) {
    if ((net_state & NET_CONNECTED) != 0U) {
      status = osMessageQueueGet(IncomingMsgId, msg, NULL, 0U);
      if (status == osOK) {
        if (msg[0] == 0x01U) {
          period = msg[1];
        }
      }
    } else {
      period = ADC_Val;
    }
    count--;
    if (count == 0U) {
      count = period / 2;
      if (count == 0U) {
        count = 1U;
      }
      state++;
      if (state == (sizeof(pattern) / sizeof(uint8_t))) {
        state = 0U;
      }
    }
    LED_SetOut(pattern[state] | (net_state << 6));
    osThreadFlagsSet(notify_tid, FLAG_LED_ALIVE);
    tick += 10U;
    osDelayUntil(tick);
  }
}

/* Create LED thread */
osThreadId_t LED_CreateThread (osThreadId_t notify_tid) {
  osThreadId_t tid;

  tid = osThreadNew(LED_Thread, notify_tid, &LED_ThreadAttr);
  return (tid);
}
