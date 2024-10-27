#include "main.h"

#ifdef HAL_UART_MODULE_ENABLED

#include "tutrc_harurobo_lib/uart.hpp"

#include "task.h"

#include "tutrc_harurobo_lib/utility.hpp"

namespace tutrc_harurobo_lib {

std::unordered_map<UART_HandleTypeDef *, UART *> UART::instances_;
UART *UART::uart_printf_ = nullptr;

UART::UART(UART_HandleTypeDef *huart, size_t rx_buf_size)
    : huart_(huart), rx_buf_(rx_buf_size) {
  instances_[huart_] = this;
  tx_mutex_ = osMutexNew(nullptr);
  rx_mutex_ = osMutexNew(nullptr);
  tx_queue_ = xQueueCreate(1, sizeof(uint8_t));
  rx_queue_ = xQueueCreate(1, sizeof(uint16_t));

  if (HAL_UARTEx_ReceiveToIdle_DMA(huart_, rx_buf_.data(), rx_buf_.size()) !=
      HAL_OK) {
    Error_Handler();
  }
}

bool UART::transmit(const uint8_t *data, size_t size) {
  ScopedLock lock(tx_mutex_);
  if (!lock.acquire(osWaitForever)) {
    return false;
  }
  if (HAL_UART_Transmit_DMA(huart_, data, size) != HAL_OK) {
    return false;
  }
  uint8_t status;
  if (xQueueReceive(tx_queue_, &status, portMAX_DELAY) != pdTRUE) {
    return false;
  }
  if (status == 1) {
    return false;
  }
  return true;
}

bool UART::receive(uint8_t *data, size_t size, uint32_t timeout) {
  ScopedLock lock(rx_mutex_);
  if (timeout == 0) {
    if (!lock.acquire(0)) {
      return false;
    }
    uint16_t rx_write_idx;
    if (xQueueReceive(rx_queue_, &rx_write_idx, 0) == pdTRUE) {
      rx_buf_tail_ = rx_write_idx;
    }
  } else {
    TimeOut_t timeout_state;
    vTaskSetTimeOutState(&timeout_state);
    if (!lock.acquire(timeout)) {
      return false;
    }
    while (available() < size) {
      if (xTaskCheckForTimeOut(&timeout_state, &timeout) != pdFALSE) {
        break;
      }
      uint16_t rx_write_idx;
      if (xQueueReceive(rx_queue_, &rx_write_idx, timeout) == pdTRUE) {
        rx_buf_tail_ = rx_write_idx;
      }
    }
  }

  if (available() < size) {
    return false;
  }
  for (size_t i = 0; i < size; ++i) {
    if (rx_buf_head_ == rx_buf_.size()) {
      rx_buf_head_ = 0;
    }
    data[i] = rx_buf_[rx_buf_head_++];
  }
  return true;
}

size_t UART::available() {
  return (rx_buf_.size() + rx_buf_tail_ - rx_buf_head_) % rx_buf_.size();
}

void UART::flush() { rx_buf_head_ = rx_buf_tail_; }

void UART::enable_printf() { uart_printf_ = this; }

} // namespace tutrc_harurobo_lib

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
  auto itr = tutrc_harurobo_lib::UART::instances_.find(huart);
  if (itr != tutrc_harurobo_lib::UART::instances_.end()) {
    tutrc_harurobo_lib::UART *uart = itr->second;
    uint8_t status = 0;
    BaseType_t yield = pdFALSE;
    xQueueOverwriteFromISR(uart->tx_queue_, &status, &yield);
    portYIELD_FROM_ISR(yield);
  }
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
  auto itr = tutrc_harurobo_lib::UART::instances_.find(huart);
  if (itr != tutrc_harurobo_lib::UART::instances_.end()) {
    tutrc_harurobo_lib::UART *uart = itr->second;
    BaseType_t yield = pdFALSE;
    xQueueOverwriteFromISR(uart->rx_queue_, &Size, &yield);
    portYIELD_FROM_ISR(yield);
  }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
  auto itr = tutrc_harurobo_lib::UART::instances_.find(huart);
  if (itr != tutrc_harurobo_lib::UART::instances_.end()) {
    tutrc_harurobo_lib::UART *uart = itr->second;
    HAL_UART_Abort(huart);
    uint8_t status = 1;
    BaseType_t yield = pdFALSE;
    xQueueOverwriteFromISR(uart->tx_queue_, &status, &yield);
    uart->rx_buf_head_ = 0;
    uart->rx_buf_tail_ = 0;
    HAL_UARTEx_ReceiveToIdle_DMA(huart, uart->rx_buf_.data(),
                                 uart->rx_buf_.size());
    portYIELD_FROM_ISR(yield);
  }
}

int _write(int, char *ptr, int len) {
  if (tutrc_harurobo_lib::UART::uart_printf_) {
    tutrc_harurobo_lib::UART::uart_printf_->transmit(
        reinterpret_cast<uint8_t *>(ptr), len);
  }
  return len;
}

#endif
