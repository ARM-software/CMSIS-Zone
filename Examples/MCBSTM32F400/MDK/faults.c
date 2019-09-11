
#include "RTE_Components.h"
#include CMSIS_device_header
#include "cmsis_compiler.h"
#include "rtx_os.h"                     // ARM::CMSIS:RTOS2:Keil RTX5
#include "mputable.h"

uint32_t MemManage_HandlerC (void) {
  uint32_t fault;
  uint32_t pid;
  uint32_t ret = 0U;

  fault = SCB->CFSR;
  SCB->CFSR = SCB_CFSR_IACCVIOL_Msk  |
              SCB_CFSR_DACCVIOL_Msk  |
              SCB_CFSR_MUNSTKERR_Msk |
              SCB_CFSR_MSTKERR_Msk   |
              SCB_CFSR_MLSPERR_Msk   |
              SCB_CFSR_MMARVALID_Msk;

  /* Check if fault occured on exception entry */
  if ((fault & SCB_CFSR_MSTKERR_Msk) != 0U) {
    /* Clear pending SVC */
    SCB->SHCSR &= ~SCB_SHCSR_SVCALLPENDED_Msk;
  }

  /* Check if a thread caused the fault */
  if ((SCB->ICSR & SCB_ICSR_RETTOBASE_Msk) != 0U) {
    /* Check process of the running thread */
    pid = osRtxProcessGetId();
    if (pid == MPUTABLE_NET) {
      osRtxProcessBlock(pid);
      ret = 1U;
    }
  }
  return ret;
}

__attribute__((naked)) void MemManage_Handler (void) {
  __ASM volatile (
    ".syntax unified\n\t"
    "push {r12,lr}\n\t"
    "ldr  r0,=MemManage_HandlerC\n\t"
    "blx  r0\n\t"
    "pop  {r12,lr}\n\t"
    "cbz  r0,dead\n\t"
    "ldr  r0,= osRtxFaultExit\n\t"
    "bx   r0\n\t"
    "dead:\n\t"
    "b    .\n"
  );
}
