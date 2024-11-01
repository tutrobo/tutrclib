#pragma once

#include "main.h"

#include <cstdint>

namespace tutrc {

class Encoder {
public:
  Encoder(TIM_TypeDef *htim, uint16_t ppr, float period);
  void update();
  float get_rps();
  float get_rpm();
  float get_position();

private:
  TIM_HandleTypeDef *htim_;
  uint16_t ppr_;
  float period_;

  int64_t count_ = 0;
  float rps_;
  float position_;
};

} // namespace tutrc
