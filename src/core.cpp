#include "cmsis_os2.h"

#include "tutrclib.h"
#include "tutrclib/internal/core.h"

std::map<void *, void *> &tutrclib::internal::HALHandleManager::get_handles() {
  static std::map<void *, void *> handles;
  return handles;
}

#ifdef HAL_TIM_MODULE_ENABLED
void tutrclib_register_TIM_HandleTypeDef(TIM_HandleTypeDef *htim) {
  tutrclib::internal::HALHandleManager::set(htim);
}
#endif

#ifdef HAL_UART_MODULE_ENABLED
void tutrclib_register_UART_HandleTypeDef(UART_HandleTypeDef *huart) {
  tutrclib::internal::HALHandleManager::set(huart);
}
#endif

#ifdef HAL_CAN_MODULE_ENABLED
void tutrclib_register_CAN_HandleTypeDef(CAN_HandleTypeDef *hcan) {
  tutrclib::internal::HALHandleManager::set(hcan);
}
#endif

#ifdef HAL_FDCAN_MODULE_ENABLED
void tutrclib_register_FDCAN_HandleTypeDef(FDCAN_HandleTypeDef *hfdcan) {
  tutrclib::internal::HALHandleManager::set(hfdcan);
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
  tutrclib_init();
  __real___libc_init_array();
  return osOK;
}
}
