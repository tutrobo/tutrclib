#include "main.h"

#ifdef HAL_TIM_MODULE_ENABLED

#include "tutrc/internal/core.h"
#include "tutrc/pwm.h"

namespace tutrc {

PWM::PWM(TIM_TypeDef *instance, uint32_t channel) : channel_(channel) {
  htim_ = reinterpret_cast<TIM_HandleTypeDef *>(
      internal::get_stm32hal_handles()[instance]);

  if (HAL_TIM_PWM_Start(htim_, channel_) != HAL_OK) {
    Error_Handler();
  }
}

uint32_t PWM::get_compare() { return __HAL_TIM_GET_COMPARE(htim_, channel_); }

void PWM::set_compare(uint32_t compare) {
  __HAL_TIM_SET_COMPARE(htim_, channel_, compare);
}

} // namespace tutrc

#endif
