#include "cmsis_os2.h"

#include "tutrc_harurobo_lib.h"
#include "tutrc_harurobo_lib/core.h"

std::map<void *, void *> &tutrc_harurobo_lib::get_handles() {
  static std::map<void *, void *> handles;
  return handles;
}

#ifdef HAL_TIM_MODULE_ENABLED
void tutrc_harurobo_lib_register_TIM_HandleTypeDef(TIM_HandleTypeDef *htim) {
  tutrc_harurobo_lib::get_handles()[htim->Instance] = htim;
}
#endif

#ifdef HAL_UART_MODULE_ENABLED
void tutrc_harurobo_lib_register_UART_HandleTypeDef(UART_HandleTypeDef *huart) {
  tutrc_harurobo_lib::get_handles()[huart->Instance] = huart;
}
#endif

#ifdef HAL_CAN_MODULE_ENABLED
void tutrc_harurobo_lib_register_CAN_HandleTypeDef(CAN_HandleTypeDef *hcan) {
  tutrc_harurobo_lib::get_handles()[hcan->Instance] = hcan;
}
#endif

#ifdef HAL_FDCAN_MODULE_ENABLED
void tutrc_harurobo_lib_register_FDCAN_HandleTypeDef(
    FDCAN_HandleTypeDef *hfdcan) {
  tutrc_harurobo_lib::get_handles()[hfdcan->Instance] = hfdcan;
}
#endif

extern "C" {

void __real___libc_init_array(void);

void __wrap___libc_init_array(void) {}

osStatus_t __real_osKernelInitialize(void);

osStatus_t __wrap_osKernelInitialize(void) {
  osStatus_t res = __real_osKernelInitialize();
  if (res != osOK) {
    return res;
  }
  tutrc_harurobo_lib_init();
  __real___libc_init_array();
  return osOK;
}
}
