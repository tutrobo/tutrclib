#include "main.h"

#ifdef HAL_GPIO_MODULE_ENABLED

#include "tutrclib/gpio.h"

namespace tutrclib {

GPIO::GPIO(GPIO_TypeDef *port, uint16_t pin) : port_(port), pin_(pin) {
  get_instances()[pin_] = this;
}

void GPIO::write(bool state) {
  HAL_GPIO_WritePin(port_, pin_, static_cast<GPIO_PinState>(state));
}

bool GPIO::read() { return HAL_GPIO_ReadPin(port_, pin_); }

void GPIO::toggle() { HAL_GPIO_TogglePin(port_, pin_); }

void GPIO::set_exti_callback(std::function<void()> &&callback) {
  exti_callback_ = std::move(callback);
}

std::map<uint16_t, GPIO *> &GPIO::get_instances() {
  static std::map<uint16_t, GPIO *> instances;
  return instances;
}

} // namespace tutrclib

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  auto itr = tutrclib::GPIO::get_instances().find(GPIO_Pin);
  if (itr != tutrclib::GPIO::get_instances().end()) {
    tutrclib::GPIO *gpio = itr->second;
    if (gpio->exti_callback_) {
      gpio->exti_callback_();
    }
  }
}

#endif
