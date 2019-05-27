#include "RTE_Components.h"
#include CMSIS_device_header

/* User Config */
const uint32_t USER_CONFIG[4] __USED = {
  0xFFFFFFFFU,
  0xFFFFFFFFU,
  0xFFFFFFFFU,
  0xFFFFFFFFU
};


/* eXecute Online Memory region config */

typedef struct {
  uint32_t base;
  uint32_t size;
  uint32_t ctrl;
  uint32_t reserved0;
} xom_region_t;

const xom_region_t XOM_CONFIG[4] __USED = {
  /* XOMR0 */
  { 0xFFFFFFFFU,
    0xFFFFFFFFU,
    0x5AU,
    0U },
  /* XOMR1 */
  { 0xFFFFFFFFU,
    0xFFFFFFFFU,
    0x5AU,
    0U },
  /* XOMR2 */
  { 0xFFFFFFFFU,
    0xFFFFFFFFU,
    0x5AU,
    0U },
  /* XOMR3 */
  { 0xFFFFFFFFU,
    0xFFFFFFFFU,
    0x5AU,
    0U },
};

/* Non-secure boundary address */
const uint32_t NSCBA_CONFIG __USED = 0x40000U;

/* Secure Region Lock */
const uint32_t SCRLOCK_CONFIG __USED = 0x5AU;

/* All Region Lock */
const uint32_t ARLOCK_CONFIG __USED = 0x5AU;
