;/*****************************************************************************
; * @file     startup_saml11.s
; * @brief    CMSIS Cortex-M23 Core Device Startup File for
; *           Atmel SAML11 Device Series
; * @version  V1.0.0
; * @date     07. November 2017
; *
; * @note
; * Copyright (C) 2017 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                IF      Heap_Size != 0                ; Heap is provided
                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit
                ELSE
                IMPORT __use_no_heap                  ; generate warning if heap is required
                ENDIF


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ;    Top of Stack
                DCD     Reset_Handler             ;    Reset Handler
                DCD     NMI_Handler               ;    NMI Handler
                DCD     HardFault_Handler         ;    Hard Fault Handler
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     SVC_Handler               ;    SVCall Handler
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     PendSV_Handler            ;    PendSV Handler
                DCD     SysTick_Handler           ;    SysTick Handler

                ; Configurable interrupts
                DCD     SYSTEM_Handler            ;  0 MCLK, OSCCTRL, OSC32KCTRL, PM, SUPC
                DCD     WDT_Handler               ;  1 Watchdog Timer
                DCD     RTC_Handler               ;  2 Real-Time Counter
                DCD     EIC_0_Handler             ;  3 EIC_EXTINT_0
                DCD     EIC_1_Handler             ;  4 EIC_EXTINT_1
                DCD     EIC_2_Handler             ;  5 EIC_EXTINT_2
                DCD     EIC_3_Handler             ;  6 EIC_EXTINT_3
                DCD     EIC_4_Handler             ;  7 EIC_EXTINT_4, EIC_EXTINT_5, EIC_EXTINT_6, EIC_EXTINT_7, EIC_NSCHK
                DCD     FREQM_Handler             ;  8 Frequency Meter
                DCD     NVMCTRL_Handler           ;  9 Non-Volatile Memory Controller
                DCD     PORT_Handler              ; 10 Port Module
                DCD     DMAC_0_Handler            ; 11 DMAC_SUSP_0, DMAC_TCMPL_0, DMAC_TERR_0
                DCD     DMAC_1_Handler            ; 12 DMAC_SUSP_1, DMAC_TCMPL_1, DMAC_TERR_1
                DCD     DMAC_2_Handler            ; 13 DMAC_SUSP_2, DMAC_TCMPL_2, DMAC_TERR_2
                DCD     DMAC_3_Handler            ; 14 DMAC_SUSP_3, DMAC_TCMPL_3, DMAC_TERR_3
                DCD     DMAC_4_Handler            ; 15 DMAC_SUSP_4, DMAC_SUSP_5, DMAC_SUSP_6, DMAC_SUSP_7, DMAC_TCMPL_4, DMAC_TCMPL_5, DMAC_TCMPL_6, DMAC_TCMPL_7, DMAC_TERR_4, DMAC_TERR_5, DMAC_TERR_6, DMAC_TERR_7
                DCD     EVSYS_0_Handler           ; 16 EVSYS_EVD_0, EVSYS_OVR_0
                DCD     EVSYS_1_Handler           ; 17 EVSYS_EVD_1, EVSYS_OVR_1
                DCD     EVSYS_2_Handler           ; 18 EVSYS_EVD_2, EVSYS_OVR_2
                DCD     EVSYS_3_Handler           ; 19 EVSYS_EVD_3, EVSYS_OVR_3
                DCD     EVSYS_4_Handler           ; 20 EVSYS_NSCHK
                DCD     PAC_Handler               ; 21 Peripheral Access Controller
                DCD     SERCOM0_0_Handler         ; 22 SERCOM0_0
                DCD     SERCOM0_1_Handler         ; 23 SERCOM0_1
                DCD     SERCOM0_2_Handler         ; 24 SERCOM0_2
                DCD     SERCOM0_3_Handler         ; 25 SERCOM0_3, SERCOM0_4, SERCOM0_5, SERCOM0_6
                DCD     SERCOM1_0_Handler         ; 26 SERCOM1_0
                DCD     SERCOM1_1_Handler         ; 27 SERCOM1_1
                DCD     SERCOM1_2_Handler         ; 28 SERCOM1_2
                DCD     SERCOM1_3_Handler         ; 29 SERCOM1_3, SERCOM1_4, SERCOM1_5, SERCOM1_6
                DCD     SERCOM2_0_Handler         ; 30 SERCOM2_0
                DCD     SERCOM2_1_Handler         ; 31 SERCOM2_1
                DCD     SERCOM2_2_Handler         ; 32 SERCOM2_2
                DCD     SERCOM2_3_Handler         ; 33 SERCOM2_3, SERCOM2_4, SERCOM2_5, SERCOM2_6
                DCD     TC0_Handler               ; 34 Basic Timer Counter 0
                DCD     TC1_Handler               ; 35 Basic Timer Counter 1
                DCD     TC2_Handler               ; 36 Basic Timer Counter 2
                DCD     ADC_0_Handler             ; 37 ADC_OVERRUN, ADC_WINMON
                DCD     ADC_1_Handler             ; 38 ADC_RESRDY
                DCD     AC_Handler                ; 39 Analog Comparators
                DCD     DAC_0_Handler             ; 40 DAC_UNDERRUN_A
                DCD     DAC_1_Handler             ; 41 DAC_EMPTY
                DCD     PTC_Handler               ; 42 Peripheral Touch Controller
                DCD     TRNG_Handler              ; 43 True Random Generator
                DCD     TRAM_Handler              ; 44 TrustRAM
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =Stack_Mem
                MSR     MSPLIM, R0                ; Non-secure version of MSPLIM is RAZ/WI
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  SYSTEM_Handler            [WEAK]
                EXPORT  WDT_Handler               [WEAK]
                EXPORT  RTC_Handler               [WEAK]
                EXPORT  EIC_0_Handler             [WEAK]
                EXPORT  EIC_1_Handler             [WEAK]
                EXPORT  EIC_2_Handler             [WEAK]
                EXPORT  EIC_3_Handler             [WEAK]
                EXPORT  EIC_4_Handler             [WEAK]
                EXPORT  FREQM_Handler             [WEAK]
                EXPORT  NVMCTRL_Handler           [WEAK]
                EXPORT  PORT_Handler              [WEAK]
                EXPORT  DMAC_0_Handler            [WEAK]
                EXPORT  DMAC_1_Handler            [WEAK]
                EXPORT  DMAC_2_Handler            [WEAK]
                EXPORT  DMAC_3_Handler            [WEAK]
                EXPORT  DMAC_4_Handler            [WEAK]
                EXPORT  EVSYS_0_Handler           [WEAK]
                EXPORT  EVSYS_1_Handler           [WEAK]
                EXPORT  EVSYS_2_Handler           [WEAK]
                EXPORT  EVSYS_3_Handler           [WEAK]
                EXPORT  EVSYS_4_Handler           [WEAK]
                EXPORT  PAC_Handler               [WEAK]
                EXPORT  SERCOM0_0_Handler         [WEAK]
                EXPORT  SERCOM0_1_Handler         [WEAK]
                EXPORT  SERCOM0_2_Handler         [WEAK]
                EXPORT  SERCOM0_3_Handler         [WEAK]
                EXPORT  SERCOM1_0_Handler         [WEAK]
                EXPORT  SERCOM1_1_Handler         [WEAK]
                EXPORT  SERCOM1_2_Handler         [WEAK]
                EXPORT  SERCOM1_3_Handler         [WEAK]
                EXPORT  SERCOM2_0_Handler         [WEAK]
                EXPORT  SERCOM2_1_Handler         [WEAK]
                EXPORT  SERCOM2_2_Handler         [WEAK]
                EXPORT  SERCOM2_3_Handler         [WEAK]
                EXPORT  TC0_Handler               [WEAK]
                EXPORT  TC1_Handler               [WEAK]
                EXPORT  TC2_Handler               [WEAK]
                EXPORT  ADC_0_Handler             [WEAK]
                EXPORT  ADC_1_Handler             [WEAK]
                EXPORT  AC_Handler                [WEAK]
                EXPORT  DAC_0_Handler             [WEAK]
                EXPORT  DAC_1_Handler             [WEAK]
                EXPORT  PTC_Handler               [WEAK]
                EXPORT  TRNG_Handler              [WEAK]
                EXPORT  TRAM_Handler              [WEAK]

SYSTEM_Handler
WDT_Handler
RTC_Handler
EIC_0_Handler
EIC_1_Handler
EIC_2_Handler
EIC_3_Handler
EIC_4_Handler
FREQM_Handler
NVMCTRL_Handler
PORT_Handler
DMAC_0_Handler
DMAC_1_Handler
DMAC_2_Handler
DMAC_3_Handler
DMAC_4_Handler
EVSYS_0_Handler
EVSYS_1_Handler
EVSYS_2_Handler
EVSYS_3_Handler
EVSYS_4_Handler
PAC_Handler
SERCOM0_0_Handler
SERCOM0_1_Handler
SERCOM0_2_Handler
SERCOM0_3_Handler
SERCOM1_0_Handler
SERCOM1_1_Handler
SERCOM1_2_Handler
SERCOM1_3_Handler
SERCOM2_0_Handler
SERCOM2_1_Handler
SERCOM2_2_Handler
SERCOM2_3_Handler
TC0_Handler
TC1_Handler
TC2_Handler
ADC_0_Handler
ADC_1_Handler
AC_Handler
DAC_0_Handler
DAC_1_Handler
PTC_Handler
TRNG_Handler
TRAM_Handler
                B       .

                ENDP


                ALIGN


; User setup Stack & Heap

                IF      :LNOT::DEF:__MICROLIB
                IMPORT  __use_two_region_memory
                ENDIF

                EXPORT  __initial_sp
                IF      Heap_Size != 0                ; Heap is provided
                EXPORT  __heap_base
                EXPORT  __heap_limit
                ENDIF

                END
