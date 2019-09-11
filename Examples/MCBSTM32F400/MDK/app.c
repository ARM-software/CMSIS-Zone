
#include "main.h"
#include "rtx_os.h"                     // ARM::CMSIS:RTOS2:Keil RTX5

static IWDG_HandleTypeDef IwdgHandle;

volatile uint8_t Tamper __attribute((section(".bss.shared"))) = 0U;

/* Network state */
uint8_t net_state __attribute((section(".bss.shared")));

/* Message Queue IDs */
osMessageQueueId_t IncomingMsgId __attribute((section(".bss.shared")));
osMessageQueueId_t OutgoingMsgId __attribute((section(".bss.shared")));

/* Timer ID */
static osTimerId_t TimerId;

/* Thread IDs */
static osThreadId_t bsd_tid;
static osThreadId_t led_tid;
static osThreadId_t adc_tid;

/* Application watchdog thread stack */
static uint64_t app_wdog_stk[256/8];

/* Application watchdog thread attributes */
static const osThreadAttr_t app_wdog_attr = {
  .stack_mem  = &app_wdog_stk[0],
  .stack_size = sizeof(app_wdog_stk),
  .reserved   = MPUTABLE_MAIN
};

/* Application watchdog thread */
static __NO_RETURN void app_wdog (void *arg) {
  uint32_t flags;

  for (;;) {
    flags = osThreadFlagsWait(FLAG_LED_ALIVE | FLAG_ADC_ALIVE, osFlagsWaitAll, osWaitForever);
    if ((flags & osFlagsError) == 0U) {
      /* Kick Watchdog */
      HAL_IWDG_Refresh(&IwdgHandle);
    }
  }
}

/* Application main thread stack */
#define APP_MAIN_STK_SZ (1024U)
static uint64_t app_main_stk[APP_MAIN_STK_SZ/8];

/* Application main thread attributes */
const osThreadAttr_t app_main_attr = {
  .stack_mem  = &app_main_stk[0],
  .stack_size = sizeof(app_main_stk),
  .reserved   = MPUTABLE_MAIN
};

/* Application main thread */
__NO_RETURN void app_main (void *arg) {
  osThreadId_t main_tid;
  osThreadId_t wdog_tid;
  uint32_t flags;

  (void)arg;

  net_state = 0U;
  osDelay(2000U);

  /* Setup IWDG: 100ms timeout */
  IwdgHandle.Instance = IWDG;
  IwdgHandle.Init.Prescaler = IWDG_PRESCALER_32;
  IwdgHandle.Init.Reload = 100U;
  HAL_IWDG_Init(&IwdgHandle);

  /* Create message queues */
  IncomingMsgId = osMessageQueueNew(8U, 2U, NULL);
  OutgoingMsgId = osMessageQueueNew(8U, 2U, NULL);

  main_tid = osThreadGetId();

  /* Create watchdog thread */
  wdog_tid = osThreadNew(app_wdog, NULL, &app_wdog_attr);
  
  /* Create working threads */
  adc_tid = ADC_CreateThread(wdog_tid);
  led_tid = LED_CreateThread(wdog_tid);
  bsd_tid = BSD_CreateThread(main_tid);

  /* Create and run timer */
  TimerId = osTimerNew(TimerCallback, osTimerPeriodic, NULL, NULL);
  osTimerStart(TimerId, 40U);

  for (;;) {
    flags = osThreadFlagsWait(FLAG_NET_MASK, osFlagsWaitAny, 200U);
    if (((flags & osFlagsError) == 0U) && ((flags & FLAG_NET_ERROR) == 0U)) {
      net_state |= NET_ALIVE;
      if ((flags & FLAG_NET_CONNECT) != 0U) {
        net_state |=  NET_CONNECTED;
      }
      if ((flags & FLAG_NET_DISCONNECT) != 0U) {
        net_state &= ~NET_CONNECTED;
      }
    } else {
      net_state = 0U;
      osThreadTerminate(bsd_tid);
      osThreadFlagsClear(FLAG_NET_MASK);
      osDelay(3000U);
      bsd_tid = BSD_CreateThread(main_tid);
    }
  }
}

/* RTX MPU Load */
void osRtxMpuLoad(uint32_t pid) {
  if (pid > MPUTABLE_IDLE) {
    pid = MPUTABLE_IDLE;
  }
  ARM_MPU_Load(mpuTable[pid], 8u);
}

extern uint8_t NetInitialized;

/* Tamper BSD */
void TamperBSD (void) {

  switch (Tamper) {
    case 0x01U:  /* Dead loop */
      Tamper = 0U;
      for (;;);
      break;
    case 0x02U:  /* MemManage (access fault) */
      Tamper = 0U;
      ADC_Val = 0U;
      break;
    case 0x03U:  /* MemManage (derived stack error) */
      Tamper = 0U;
      __ASM volatile (
        "ldr sp,=0x20010000\n\t"
        "svc 255\n"
      );
      break;
    case 0x04U:  /* Stack overflow */
      Tamper = 0U;
      __ASM volatile (
        "ldr sp,=0x20018000\n\t"
      );
      osThreadYield();
      break;
    case 0x05U:  /* UsageFault (undefined instruction) */
      break;
    case 0x06U:  /* BusFault */
      break;
    case 0x07U:  /* HardFault */
      break;
    default:
      break;
  }
}

/* Tamper ADC */
void TamperADC (void) {

  switch (Tamper) {
    case 0x11U:  /* Dead loop */
      Tamper = 0U;
      for (;;);
      break;
    case 0x12U:  /* MemManage (access fault) */
      Tamper = 0U;
      NetInitialized = 0U;
      break;
    case 0x13U:  /* MemManage (derived stack error) */
      Tamper = 0U;
      __ASM volatile (
        "ldr sp,=0x20010000\n\t"
        "svc 255\n"
      );
      break;
    case 0x14U:  /* Stack overflow */
      Tamper = 0U;
      __ASM volatile (
        "ldr sp,=0x2001D000\n\t"
      );
      osThreadYield();
      break;
    case 0x15U:  /* UsageFault (undefined instruction) */
      break;
    case 0x16U:  /* BusFault */
      break;
    case 0x17U:  /* HardFault */
      break;
    default:
      break;
  }
}
