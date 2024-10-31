#pragma once

#include "main.h"

#include <cstdint>
#include <functional>
#include <unordered_map>

namespace tutrc_harurobo_lib {

class GPIO {
public:
  GPIO(GPIO_TypeDef *port, uint16_t pin);
  void write(bool state);
  bool read();
  void toggle();
  void set_exti_callback(std::function<void()> &&callback);

private:
  GPIO_TypeDef *port_;
  uint16_t pin_;
  std::function<void()> exti_callback_;

  friend void ::HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
};

} // namespace tutrc_harurobo_lib
