/*
 * Copyright 2019 Arm Limited
 *
 * SPDX-License-Identifier: Apache 2.0
 */

#ifndef TZ_CONFIG_H
#define TZ_CONFIG_H

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

/*----------------------------------------------------------------------------
  Configuration Values
 *----------------------------------------------------------------------------*/
 
// <e>Setup behaviour of Sleep and Exception Handling
#define SCB_CSR_AIRCR_INIT  1U

//   <o> Deep Sleep can be enabled by
//     <0=>Secure and Non-Secure state
//     <1=>Secure state only
//   <i> Value for SCB->CSR register bit DEEPSLEEPS
#define SCB_CSR_DEEPSLEEPS_VAL       1U

//   <o>System reset request accessible from
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for SCB->AIRCR register bit SYSRESETREQS
#define SCB_AIRCR_SYSRESETREQS_VAL   1U

//   <o>Priority of Non-Secure exceptions is
//     <0=> Not altered
//     <1=> Lowered to 0x80-0xFF
//   <i> Value for SCB->AIRCR register bit PRIS
#define SCB_AIRCR_PRIS_VAL           1U

// </e>



// <e>Setup behaviour of Floating Point Unit
#define TZ_FPU_NS_USAGE 1U

// <o>Floating Point Unit usage
//     <0=> Secure state only
//     <3=> Secure and Non-Secure state
//   <i> Value for SCB->NSACR register bits CP10, CP11
#define SCB_NSACR_CP10_11_VAL        3U

// <o>Treat floating-point registers as Secure
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit TS
#define FPU_FPCCR_TS_VAL             0U

// <o>Clear on return (CLRONRET) accessibility
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for FPU->FPCCR register bit CLRONRETS
#define FPU_FPCCR_CLRONRETS_VAL      0U

// <o>Clear floating-point caller saved registers on exception return
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit CLRONRET
#define FPU_FPCCR_CLRONRET_VAL       1U

// </e>


/*----------------------------------------------------------------------------
  Function Prototypes
 *----------------------------------------------------------------------------*/
void TZ_Config_SAU(void)
void TZ_Config_NVIC(void)
void TZ_Config_MPC(void)
void TZ_Config_PPC(void)



#endif  /* TZ_CONFIG_H */
