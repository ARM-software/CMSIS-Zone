/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2018 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    net_rtos2.h
 * Purpose: Network CMSIS-RTOS2 abstraction layer
 * Rev.:    V7.7.1
 *----------------------------------------------------------------------------*/

#include "cmsis_os2.h"
#include "rl_net_lib.h"

/* Avoid syntax-checker errors in editor */
#ifndef NET_THREAD_STACK_SIZE
  #define NET_THREAD_STACK_SIZE 1024
  #define NET_THREAD_PRIORITY   osPriorityNormal
#endif

/* Network core resources */
#ifdef RTE_CMSIS_RTOS2_RTX5
  #include "rtx_os.h"
  static osRtxMutex_t  net_lock_cb    __attribute__((section(".bss.os.mutex.cb")));
  static osRtxMutex_t  mem_lock_cb    __attribute__((section(".bss.os.mutex.cb")));
  static osRtxThread_t net_thread_cb  __attribute__((section(".bss.os.thread.cb")));
  static uint64_t      net_stack[NET_THREAD_STACK_SIZE/8]
                                      __attribute__((section(".bss.os.thread.stack.mw_net")));
  #define __NET_LOCK   &net_lock_cb,   sizeof(net_lock_cb)
  #define __MEM_LOCK   &mem_lock_cb,   sizeof(mem_lock_cb)
  #define __NET_TCB    &net_thread_cb, sizeof(net_thread_cb)
  #define __NET_STACK  &net_stack,     sizeof(net_stack)
#else
  #define __NET_LOCK   NULL, 0
  #define __MEM_LOCK   NULL, 0
  #define __NET_TCB    NULL, 0
  #define __NET_STACK  NULL, NET_THREAD_STACK_SIZE
#endif

static const osMutexAttr_t net_lock = {
  "netCoreMutex",
  osMutexPrioInherit | osMutexRecursive | osMutexRobust,
  __NET_LOCK
};

static const osMutexAttr_t mem_lock = {
  "netMemoryMutex",
  osMutexPrioInherit | osMutexRobust,
  __MEM_LOCK
};

static const osThreadAttr_t net_thread = {
  "netCoreThread",
  osThreadDetached,
  __NET_TCB,
  __NET_STACK,
  NET_THREAD_PRIORITY,
  0U,
#if defined(NET_PID)
  (uint32_t)NET_PID
#else
  0U
#endif
};

/* Ethernet interface resources */
#if (ETH0_ENABLE)
#ifdef RTE_CMSIS_RTOS2_RTX5
  static osRtxSemaphore_t eth0_lock_cb   __attribute__((section(".bss.os.semaphore.cb")));
  static osRtxThread_t    eth0_thread_cb __attribute__((section(".bss.os.thread.cb")));
  static uint64_t         eth0_stack[ETH0_THREAD_STACK_SIZE/8]
                                         __attribute__((section(".bss.os.thread.stack.mw_net")));
  #define __ETH0_LOCK     &eth0_lock_cb,   sizeof(eth0_lock_cb)
  #define __ETH0_TCB      &eth0_thread_cb, sizeof(eth0_thread_cb)
  #define __ETH0_STACK    &eth0_stack,     sizeof(eth0_stack)
#else
  #define __ETH0_LOCK     NULL, 0
  #define __ETH0_TCB      NULL, 0
  #define __ETH0_STACK    NULL, ETH0_THREAD_STACK_SIZE
#endif

static const osSemaphoreAttr_t eth0_lock = {
  "netEth0_Semaphore",
  0,
  __ETH0_LOCK
};

static const osThreadAttr_t eth0_thread = {
  "netEth0_Thread",
  osThreadDetached,
  __ETH0_TCB,
  __ETH0_STACK,
  ETH0_THREAD_PRIORITY,
  0U,
#if defined(NET_PID)
  (uint32_t)NET_PID
#else
  0U
#endif
};
#endif

/* PPP interface resources */
#if (PPP_ENABLE)
#ifdef RTE_CMSIS_RTOS2_RTX5
  static osRtxSemaphore_t ppp_lock_cb    __attribute__((section(".bss.os.semaphore.cb")));
  static osRtxThread_t    ppp_thread_cb  __attribute__((section(".bss.os.thread.cb")));
  static uint64_t         ppp_stack[PPP_THREAD_STACK_SIZE/8]
                                         __attribute__((section(".bss.os.thread.stack.mw_net")));
  #define __PPP_LOCK      &ppp_lock_cb,   sizeof(ppp_lock_cb)
  #define __PPP_TCB       &ppp_thread_cb, sizeof(ppp_thread_cb)
  #define __PPP_STACK     &ppp_stack,     sizeof(ppp_stack)
#else
  #define __PPP_LOCK      NULL, 0
  #define __PPP_TCB       NULL, 0
  #define __PPP_STACK     NULL, PPP_THREAD_STACK_SIZE
#endif

static const osSemaphoreAttr_t ppp_lock = {
  "netPPP_Semaphore",
  0,
  __PPP_LOCK
};

static const osThreadAttr_t ppp_thread = {
  "netPPP_Thread",
  osThreadDetached,
  __PPP_TCB,
  __PPP_STACK,
  PPP_THREAD_PRIORITY,
#if defined(NET_PID)
  (uint32_t)NET_PID
#else
  0U
#endif
};
#endif

/* SLIP interface resources */
#if (SLIP_ENABLE)
#ifdef RTE_CMSIS_RTOS2_RTX5
  static osRtxSemaphore_t slip_lock_cb   __attribute__((section(".bss.os.semaphore.cb")));
  static osRtxThread_t    slip_thread_cb __attribute__((section(".bss.os.thread.cb")));
  static uint64_t         slip_stack[SLIP_THREAD_STACK_SIZE/8]
                                         __attribute__((section(".bss.os.thread.stack.mw_net")));
  #define __SLIP_LOCK     &slip_lock_cb,   sizeof(slip_lock_cb)
  #define __SLIP_TCB      &slip_thread_cb, sizeof(slip_thread_cb)
  #define __SLIP_STACK    &slip_stack,     sizeof(slip_stack)
#else
  #define __SLIP_LOCK     NULL, 0
  #define __SLIP_TCB      NULL, 0
  #define __SLIP_STACK    NULL, SLIP_THREAD_STACK_SIZE
#endif

static const osSemaphoreAttr_t slip_lock = {
  "netSLIP_Semaphore",
  0,
  __SLIP_LOCK
};

static const osThreadAttr_t slip_thread = {
  "netSLIP_Thread",
  osThreadDetached,
  __SLIP_TCB,
  __SLIP_STACK,
  SLIP_THREAD_PRIORITY,
#if defined(NET_PID)
  (uint32_t)NET_PID
#else
  0U
#endif
};
#endif


/* Create network core thread */
NETOS_ID netos_thread_create (void) {
  return (osThreadNew ((osThreadFunc_t)&netCore_Thread, NULL, &net_thread));
}

/* Delete network thread */
void netos_thread_delete (NETOS_ID thread) {
  osThreadTerminate (thread);
}

/* Get running thread identifier */
NETOS_ID netos_thread_id (void) {
  return (osThreadGetId ());
}

/* Pass control to next ready thread */
void netos_thread_pass (void) {
  osThreadYield ();
}

/* Create periodic tick timer */
NETOS_ID netos_timer_create (void) {
  return (osTimerNew ((osTimerFunc_t)&net_sys_tick, osTimerPeriodic, NULL, NULL));
}

/* Delete periodic tick timer */
void netos_timer_delete (NETOS_ID timer) {
  osTimerDelete (timer);
}

/* Start periodic tick timer */
void netos_timer_start (NETOS_ID timer, uint32_t interval_ms) {
  osTimerStart (timer, interval_ms);
}

/* Create network protection mutex */
NETOS_ID netos_mutex_create (uint8_t sys_id) {
  switch (sys_id) {
    case 0:  return (osMutexNew (&net_lock));
    default: return (osMutexNew (&mem_lock));
  }
}

/* Delete network protection mutex */
void netos_mutex_delete (NETOS_ID mutex) {
  osMutexDelete (mutex);
}

/* Lock network protection mutex */
void netos_lock (NETOS_ID mutex) {
  osMutexAcquire (mutex, osWaitForever);
}

/* Unlock network protection mutex */
void netos_unlock (NETOS_ID mutex) {
  osMutexRelease (mutex);
}

/* Wait for thread signal/event flag */
void netos_flag_wait (uint32_t flag, uint32_t ms) {
  osThreadFlagsWait (flag, osFlagsWaitAny, ms);
}

/* Set thread signal/event flag */
void netos_flag_set (NETOS_ID thread, uint32_t flag) {
  osThreadFlagsSet (thread, flag);
}

/* Clear thread signal/event flag */
void netos_flag_clear (NETOS_ID thread, uint32_t flag) {
  (void)thread;
  osThreadFlagsClear (flag);
}

/* Delay thread execution */
void netos_delay (uint32_t ms) {
  osDelay (ms);
}

/* Create network interface thread and semaphore */
NETOS_ID netif_create (uint8_t netif, NETOS_ID *semaphore) {
  switch (netif) {
#if (ETH0_ENABLE)
    case  NETIF_ETH:
      *semaphore = osSemaphoreNew (1, 1, &eth0_lock);
      return (osThreadNew ((osThreadFunc_t)&netETH_Thread, NULL, &eth0_thread));
#endif
#if (PPP_ENABLE)
    case NETIF_PPP:
      *semaphore = osSemaphoreNew (1, 1, &ppp_lock);
      return (osThreadNew ((osThreadFunc_t)&netPPP_Thread, NULL, &ppp_thread));
#endif
#if (SLIP_ENABLE)
    case NETIF_SLIP:
      *semaphore = osSemaphoreNew (1, 1, &slip_lock);
      return (osThreadNew ((osThreadFunc_t)&netSLIP_Thread, NULL, &slip_thread));
#endif
  }
  return (NULL);
}

/* Delete network interface thread and semaphore */
void netif_delete (NETOS_ID thread, NETOS_ID semaphore) {
  osSemaphoreDelete (semaphore);
  osThreadTerminate (thread);
}

/* Lock interface protection semaphore */
void netif_lock (NETOS_ID semaphore) {
  osSemaphoreAcquire (semaphore, osWaitForever);
}

/* Unlock interface protection semaphore */
void netif_unlock (NETOS_ID semaphore) {
  osSemaphoreRelease (semaphore);
}
