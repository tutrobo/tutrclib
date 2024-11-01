#include "main.h"

#ifdef HAL_TIM_MODULE_ENABLED

#include "tutrc_harurobo_lib/core.hpp"
#include "tutrc_harurobo_lib/encoder.hpp"

namespace tutrc_harurobo_lib {

Encoder::Encoder(TIM_TypeDef *instance, uint16_t ppr, float period)
    : ppr_(ppr), period_(period) {
  htim_ = reinterpret_cast<TIM_HandleTypeDef *>(get_handles()[instance]);

  if (HAL_TIM_Encoder_Start(htim_, TIM_CHANNEL_ALL) != HAL_OK) {
    Error_Handler();
  }
}

void Encoder::update() {
  int16_t delta = __HAL_TIM_GET_COUNTER(htim_);
  __HAL_TIM_SET_COUNTER(htim_, 0);

  float cpr = ppr_ * 4;
  count_ += delta;
  rps_ = delta / period_ / cpr;
  position_ = count_ / cpr;
}

float Encoder::get_rps() { return rps_; }

float Encoder::get_rpm() { return get_rps() * 60; }

float Encoder::get_position() { return position_; }

} // namespace tutrc_harurobo_lib

#endif
