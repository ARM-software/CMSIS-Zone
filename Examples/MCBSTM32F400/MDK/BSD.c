
#include <string.h>
#include "main.h"
#include "rl_net.h"                     // Keil.MDK-Pro::Network:CORE

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

//   <o>Server Local Port <1-65535>
//   <i> Do not set number of port too small,
//   <i> maybe it is already used.
//   <i> Default: 1001
#define SERVER_LOCAL_PORT       1001

//------------- <<< end of configuration section >>> -----------------------

/* Initialization flag */
       uint8_t  NetInitialized = 0U;

/* BSD thread stack */
static uint64_t BSD_Stack[512/8];

/* BSD thread attributes */
static const osThreadAttr_t BSD_ThreadAttr = {
  .stack_mem  = &BSD_Stack,
  .stack_size = sizeof(BSD_Stack),
  .reserved   = MPUTABLE_NET
};

/* BSD thread */
static __NO_RETURN void BSD_Thread (void *arg) {
  osThreadId_t   notify_tid = arg;
  SOCKADDR_IN    addr;
  int            sock, sd;
  int            rc;
  struct fd_set  read_fds;
  struct timeval tv;
  char           buf[2];
  netStatus      net_stat;
  osStatus_t     status;

#ifdef RTE_Compiler_EventRecorder
  EventRecorderEnable(EventRecordError, 0xC0U, 0xDCU);    /* Net Events     */
  EventRecorderEnable(EventRecordAll,   0xCAU, 0xCAU);    /* DHCP Events    */
  EventRecorderEnable(EventRecordAll,   0xD2U, 0xD2U);    /* BSD Events     */
#endif

  /* Start network stack */
  if (NetInitialized != 0U) {
    net_stat = netUninitialize();
    if (net_stat != netOK) {
      osThreadFlagsSet(notify_tid, FLAG_NET_ERROR);
      osDelay(osWaitForever);
    }
    NetInitialized = 0U;
  }
  net_stat = netInitialize();
  if (net_stat != netOK) {
    osThreadFlagsSet(notify_tid, FLAG_NET_ERROR);
    osDelay(osWaitForever);
  }
  NetInitialized = 1U;

  /* Setup network parameters */
  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_port   = htons(SERVER_LOCAL_PORT);

  /* Create socket */
  sock = socket(addr.sin_family, SOCK_STREAM, 0);
  if (sock < 0) {
    osThreadFlagsSet(notify_tid, FLAG_NET_ERROR);
    osDelay(osWaitForever);
  }

  /* Bind address and port to socket */
  rc = bind(sock, (SOCKADDR *)&addr, sizeof(addr));
  if (rc < 0) {
    osThreadFlagsSet(notify_tid, FLAG_NET_ERROR);
    osDelay(osWaitForever);
  }

  /* Put socket in listening mode */
  rc = listen(sock, 1);
  if (rc < 0) {
    osThreadFlagsSet(notify_tid, FLAG_NET_ERROR);
    osDelay(osWaitForever);
  }

  for (;;) {
    osThreadFlagsSet(notify_tid, FLAG_NET_ALIVE);

    FD_ZERO(&read_fds);
    FD_SET(sock, &read_fds);

    /* 100ms timeout for select */
    tv.tv_sec  = 0U;
    tv.tv_usec = 100000U;

    /* Check if socket is readable */
    rc = select(sock + 1, &read_fds, NULL, NULL, &tv);
    if (rc < 0) {
      osThreadFlagsSet(notify_tid, FLAG_NET_ERROR);
      osDelay(osWaitForever);
    }

    TamperBSD();

    if (FD_ISSET(sock, &read_fds)) {

      /* Accept connection */
      sd = accept(sock, NULL, NULL);
      if (sd < 0) {
        if (sd == BSD_ECONNRESET) {
          continue;
        }
        osThreadFlagsSet(notify_tid, FLAG_NET_ERROR);
        osDelay(osWaitForever);
      }
      osThreadFlagsSet(notify_tid, FLAG_NET_CONNECT);

      /* Enable Keep Alive */
      char bval = 1;
      rc = setsockopt(sd, SOL_SOCKET, SO_KEEPALIVE, &bval, sizeof(bval));
      if (rc < 0) {
        osThreadFlagsSet(notify_tid, FLAG_NET_ERROR);
        osDelay(osWaitForever);
      }

      for (;;) {
        TamperBSD();

        /* Receive data */
        rc = recv(sd, buf, 2, MSG_DONTWAIT);
        if (rc == 2) {
          osMessageQueuePut(IncomingMsgId, buf, 0U, 0U);
        } else if (rc != BSD_EWOULDBLOCK) {
          break;
        }

        /* Send data */
        status = osMessageQueueGet(OutgoingMsgId, buf, NULL, 0U);
        if (status == osOK) {
          rc = send(sd, buf, 2, MSG_DONTWAIT);
          if (rc != 2) {
            break;
          }
        }

        osDelay(50U);
        osThreadFlagsSet(notify_tid, FLAG_NET_ALIVE);
      }

      /* Close connection */
      rc = closesocket(sd);
      if (rc < 0) {
        osThreadFlagsSet(notify_tid, FLAG_NET_ERROR);
        osDelay(osWaitForever);
      }
      osThreadFlagsSet(notify_tid, FLAG_NET_DISCONNECT);
    }
  }
}

/* Create BSD thread */
osThreadId_t BSD_CreateThread (osThreadId_t notify_tid) {
  osThreadId_t tid;

  tid = osThreadNew(BSD_Thread, notify_tid, &BSD_ThreadAttr);
  return (tid);
}
