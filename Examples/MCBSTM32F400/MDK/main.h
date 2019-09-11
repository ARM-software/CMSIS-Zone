/**
  ******************************************************************************
  * @file    Templates/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017-2018 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "mputable.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif

#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern uint8_t net_state;

extern const osThreadAttr_t app_main_attr;

extern osMessageQueueId_t IncomingMsgId;
extern osMessageQueueId_t OutgoingMsgId;

extern volatile uint8_t ADC_Val;

extern volatile uint8_t Tamper;

/* Exported macro ------------------------------------------------------------*/

/* Network state bits */
#define NET_ALIVE               0x01U
#define NET_CONNECTED           0x02U

/* Thread notification flags */
#define FLAG_LED_ALIVE          0x01U
#define FLAG_ADC_ALIVE          0x02U
#define FLAG_NET_ALIVE          0x10U
#define FLAG_NET_CONNECT        0x20U
#define FLAG_NET_DISCONNECT     0x40U
#define FLAG_NET_ERROR          0x80U
#define FLAG_NET_MASK           0xF0U

/* Exported functions ------------------------------------------------------- */
extern void app_main (void *arg);
extern osThreadId_t BSD_CreateThread (osThreadId_t notify_tid);
extern osThreadId_t LED_CreateThread (osThreadId_t notify_tid);
extern osThreadId_t ADC_CreateThread (osThreadId_t notify_tid);
extern void TimerCallback (void *arg);
extern void TamperBSD (void);
extern void TamperADC (void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
