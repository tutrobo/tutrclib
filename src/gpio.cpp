#include "main.h"

#ifdef HAL_GPIO_MODULE_ENABLED

#include "tutrc_harurobo_lib/gpio.hpp"

namespace tutrc_harurobo_lib {

std::unordered_map<uint16_t, tutrc_harurobo_lib::GPIO *>
    tutrc_harurobo_lib::GPIO::instances_;

GPIO::GPIO(GPIO_TypeDef *port, uint16_t pin) : port_(port), pin_(pin) {
  instances_[pin_] = this;
}

void GPIO::write(bool state) {
  HAL_GPIO_WritePin(port_, pin_, static_cast<GPIO_PinState>(state));
}

bool GPIO::read() { return HAL_GPIO_ReadPin(port_, pin_); }

void GPIO::toggle() { HAL_GPIO_TogglePin(port_, pin_); }

void GPIO::set_exti_callback(std::function<void()> &&callback) {
  exti_callback_ = std::move(callback);
}

} // namespace tutrc_harurobo_lib

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  auto itr = tutrc_harurobo_lib::GPIO::instances_.find(GPIO_Pin);
  if (itr != tutrc_harurobo_lib::GPIO::instances_.end()) {
    tutrc_harurobo_lib::GPIO *gpio = itr->second;
    if (gpio->exti_callback_) {
      gpio->exti_callback_();
    }
  }
}

#endif
