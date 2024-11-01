#include "main.h"

#ifdef HAL_TIM_MODULE_ENABLED

#include "tutrc_harurobo_lib/pwm.hpp"

namespace tutrc_harurobo_lib {

PWM::PWM(TIM_TypeDef *instance, uint32_t channel) : channel_(channel) {
  htim_ = get_handles()[instance];

  if (HAL_TIM_PWM_Start(htim_, channel_) != HAL_OK) {
    Error_Handler();
  }
}

uint32_t PWM::get_compare() { return __HAL_TIM_GET_COMPARE(htim_, channel_); }

void PWM::set_compare(uint32_t compare) {
  __HAL_TIM_SET_COMPARE(htim_, channel_, compare);
}

} // namespace tutrc_harurobo_lib

void tutrc_harurobo_lib_register_TIM_HandleTypeDef(TIM_HandleTypeDef *htim) {
  tutrc_harurobo_lib::PWM::get_handles()[htim->Instance] = htim;
}

#endif
