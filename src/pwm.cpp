#include "main.h"

#ifdef HAL_TIM_MODULE_ENABLED

#include "tutrclib/internal/core.h"
#include "tutrclib/pwm.h"

namespace tutrclib {

PWM::PWM(TIM_TypeDef *instance, uint32_t channel) : channel_(channel) {
  htim_ = internal::HALHandleManager::get<TIM_HandleTypeDef>(instance);
  if (!htim_) {
    Error_Handler();
  }

  if (HAL_TIM_PWM_Start(htim_, channel_) != HAL_OK) {
    Error_Handler();
  }
}

uint32_t PWM::get_compare() { return __HAL_TIM_GET_COMPARE(htim_, channel_); }

void PWM::set_compare(uint32_t compare) {
  __HAL_TIM_SET_COMPARE(htim_, channel_, compare);
}

} // namespace tutrclib

#endif
