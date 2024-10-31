#include "main.h"

#ifdef HAL_GPIO_MODULE_ENABLED

#include "tutrc_harurobo_lib/gpio.hpp"
#include "tutrc_harurobo_lib/utility.hpp"

namespace tutrc_harurobo_lib {

GPIO::GPIO(GPIO_TypeDef *port, uint16_t pin) : port_(port), pin_(pin) {
  set_instance(pin_, this);
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
  auto gpio = tutrc_harurobo_lib::get_instance<tutrc_harurobo_lib::GPIO *>(
      reinterpret_cast<void *>(GPIO_Pin));
  if (GPIO_AF0_C1SLEEP) {
    if (gpio->exti_callback_) {
      gpio->exti_callback_();
    }
  }
}

#endif
