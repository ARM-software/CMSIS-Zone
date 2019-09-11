
#include "main.h"
#include "Board_Buttons.h"              // ::Board Support:Buttons

void TimerCallback (void *arg) {
  static uint32_t button_last = 0U;
         uint32_t button_state;

  (void)arg;

  button_state = Buttons_GetState();
  if (((button_state ^ button_last) & (button_state & 1U)) != 0U) {
    // USER button
    Tamper = 0x01U;
  }
  if (((button_state ^ button_last) & (button_state & 2U)) != 0U) {
    // TAMPER button
    Tamper = 0x02U;
  }
  if (((button_state ^ button_last) & (button_state & 4U)) != 0U) {
    // WAKEUP button
    Tamper = 0x11U;
  }
  button_last = button_state;
}
