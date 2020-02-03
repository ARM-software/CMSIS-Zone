/*
 * MPU Table Source File generated by CMSIS-Zone 
 */
 
#include "mputable.h"

const ARM_MPU_Region_t mpuTable[5u][8u] = {
{ /* Execution Zone 'Net' */ 
  // CODE (0x8000000..0x80FFFFF)
  { .RBAR = ARM_MPU_RBAR(0u, 0x8000000), .RASR = ARM_MPU_RASR_EX(0u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_1MB) },
  // RAM_SHARED, RAM_EVR (0x20008000..0x2000BFFF)
  { .RBAR = ARM_MPU_RBAR(1u, 0x20008000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_16KB) },
  // RAM_BSD (0x2000C000..0x2000DFFF)
  { .RBAR = ARM_MPU_RBAR(2u, 0x2000C000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 0u), 0x0u, ARM_MPU_REGION_SIZE_8KB) },
  // RAM_NET (0x2000E000..0x20015FFF)
  { .RBAR = ARM_MPU_RBAR(3u, 0x20008000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_32KB) },
  // SYSCFG, EXTI (0x40013800..0x40013FFF)
  { .RBAR = ARM_MPU_RBAR(4u, 0x40013800), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(0u), 0x0u, ARM_MPU_REGION_SIZE_2KB) },
  // GPIOA, GPIOG (0x40020000..0x40021BFF)
  { .RBAR = ARM_MPU_RBAR(5u, 0x40020000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(1u), 0x80u, ARM_MPU_REGION_SIZE_8KB) },
  // RCC (0x40023800..0x40023BFF)
  { .RBAR = ARM_MPU_RBAR(6u, 0x40023800), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(0u), 0x0u, ARM_MPU_REGION_SIZE_1KB) },
  // Ethernet_MAC, Ethernet_DMA (0x40028000..0x40029FFF)
  { .RBAR = ARM_MPU_RBAR(7u, 0x40028000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(0u), 0x0u, ARM_MPU_REGION_SIZE_8KB) }
},{ /* Execution Zone 'Main' */ 
  // CODE (0x8000000..0x80FFFFF)
  { .RBAR = ARM_MPU_RBAR(0u, 0x8000000), .RASR = ARM_MPU_RASR_EX(0u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_1MB) },
  // RAM_SHARED, RAM_EVR (0x20008000..0x2000BFFF)
  { .RBAR = ARM_MPU_RBAR(1u, 0x20008000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_16KB) },
  // RAM_MAIN (0x20019000..0x20019FFF)
  { .RBAR = ARM_MPU_RBAR(2u, 0x20019000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 0u), 0x0u, ARM_MPU_REGION_SIZE_4KB) },
  // IWDG (0x40003000..0x400033FF)
  { .RBAR = ARM_MPU_RBAR(3u, 0x40003000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(0u), 0x0u, ARM_MPU_REGION_SIZE_1KB) },
  { .RBAR = ARM_MPU_RBAR(4u, 0u), .RASR = 0u },
  { .RBAR = ARM_MPU_RBAR(5u, 0u), .RASR = 0u },
  { .RBAR = ARM_MPU_RBAR(6u, 0u), .RASR = 0u },
  { .RBAR = ARM_MPU_RBAR(7u, 0u), .RASR = 0u }
},{ /* Execution Zone 'Blinky' */ 
  // CODE (0x8000000..0x80FFFFF)
  { .RBAR = ARM_MPU_RBAR(0u, 0x8000000), .RASR = ARM_MPU_RASR_EX(0u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_1MB) },
  // RAM_SHARED, RAM_EVR (0x20008000..0x2000BFFF)
  { .RBAR = ARM_MPU_RBAR(1u, 0x20008000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_16KB) },
  // RAM_ADC, RAM_LED (0x20017000..0x20018FFF)
  { .RBAR = ARM_MPU_RBAR(2u, 0x20016000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 0u), 0x0u, ARM_MPU_REGION_SIZE_8KB) },
  // ADC1, C_ADC (0x40012000..0x400123FF)
  { .RBAR = ARM_MPU_RBAR(3u, 0x40012000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(0u), 0x0u, ARM_MPU_REGION_SIZE_1KB) },
  // GPIOG (0x40021800..0x40021BFF)
  { .RBAR = ARM_MPU_RBAR(4u, 0x40021800), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(1u), 0x0u, ARM_MPU_REGION_SIZE_1KB) },
  // GPIOH, GPIOI (0x40021C00..0x400223FF)
  { .RBAR = ARM_MPU_RBAR(5u, 0x40021800), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(0u), 0x0u, ARM_MPU_REGION_SIZE_2KB) },
  { .RBAR = ARM_MPU_RBAR(6u, 0u), .RASR = 0u },
  { .RBAR = ARM_MPU_RBAR(7u, 0u), .RASR = 0u }
},{ /* Execution Zone 'Timer' */ 
  // CODE (0x8000000..0x80FFFFF)
  { .RBAR = ARM_MPU_RBAR(0u, 0x8000000), .RASR = ARM_MPU_RASR_EX(0u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_1MB) },
  // RAM_SHARED, RAM_EVR (0x20008000..0x2000BFFF)
  { .RBAR = ARM_MPU_RBAR(1u, 0x20008000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_16KB) },
  // RAM_NET (0x2000E000..0x20015FFF)
  { .RBAR = ARM_MPU_RBAR(2u, 0x20008000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_32KB) },
  // RAM_TIMER (0x20016000..0x20016FFF)
  { .RBAR = ARM_MPU_RBAR(3u, 0x20016000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 0u), 0x0u, ARM_MPU_REGION_SIZE_4KB) },
  // GPIOA, GPIOG (0x40020000..0x40021BFF)
  { .RBAR = ARM_MPU_RBAR(4u, 0x40020000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_DEVICE(1u), 0x80u, ARM_MPU_REGION_SIZE_8KB) },
  { .RBAR = ARM_MPU_RBAR(5u, 0u), .RASR = 0u },
  { .RBAR = ARM_MPU_RBAR(6u, 0u), .RASR = 0u },
  { .RBAR = ARM_MPU_RBAR(7u, 0u), .RASR = 0u }
},{ /* Execution Zone 'Idle' */ 
  // CODE (0x8000000..0x80FFFFF)
  { .RBAR = ARM_MPU_RBAR(0u, 0x8000000), .RASR = ARM_MPU_RASR_EX(0u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_1MB) },
  // RAM_SHARED, RAM_EVR (0x20008000..0x2000BFFF)
  { .RBAR = ARM_MPU_RBAR(1u, 0x20008000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 1u), 0x0u, ARM_MPU_REGION_SIZE_16KB) },
  // RAM_IDLE (0x2001A000..0x2001AFFF)
  { .RBAR = ARM_MPU_RBAR(2u, 0x2001A000), .RASR = ARM_MPU_RASR_EX(1u, ARM_MPU_AP_FULL, ARM_MPU_ACCESS_NORMAL(ARM_MPU_CACHEP_NOCACHE, ARM_MPU_CACHEP_NOCACHE, 0u), 0x0u, ARM_MPU_REGION_SIZE_4KB) },
  { .RBAR = ARM_MPU_RBAR(3u, 0u), .RASR = 0u },
  { .RBAR = ARM_MPU_RBAR(4u, 0u), .RASR = 0u },
  { .RBAR = ARM_MPU_RBAR(5u, 0u), .RASR = 0u },
  { .RBAR = ARM_MPU_RBAR(6u, 0u), .RASR = 0u },
  { .RBAR = ARM_MPU_RBAR(7u, 0u), .RASR = 0u }
}};