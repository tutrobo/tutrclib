#include "main.h"

#ifdef HAL_UART_MODULE_ENABLED

#include "FreeRTOS.h"
#include "task.h"

#include "tutrclib/internal/core.h"
#include "tutrclib/uart.h"

namespace tutrclib {

UART::UART(USART_TypeDef *instance, size_t rx_queue_size) {
  huart_ = internal::HALHandleManager::get<UART_HandleTypeDef>(instance);
  if (!huart_) {
    Error_Handler();
  }

  get_instances()[huart_] = this;
  tx_sem_ = osSemaphoreNew(1, 1, nullptr);
  rx_sem_ = osSemaphoreNew(1, 1, nullptr);
  rx_queue_ = osMessageQueueNew(rx_queue_size, sizeof(uint8_t), nullptr);

  if (HAL_UART_Receive_IT(huart_, &rx_buf_, 1) != HAL_OK) {
    Error_Handler();
  }
}

bool UART::transmit(const uint8_t *data, size_t size) {
  osSemaphoreAcquire(tx_sem_, osWaitForever);
  if (HAL_UART_Transmit_IT(huart_, data, size) != HAL_OK) {
    return false;
  }
  return true;
}

bool UART::receive(uint8_t *data, size_t size, uint32_t timeout) {
  TimeOut_t timeout_state;
  vTaskSetTimeOutState(&timeout_state);
  while (available() < size) {
    if (xTaskCheckForTimeOut(&timeout_state, &timeout) != pdFALSE) {
      break;
    }
    osSemaphoreAcquire(rx_sem_, timeout);
  }
  if (available() < size) {
    return false;
  }
  for (size_t i = 0; i < size; ++i) {
    osMessageQueueGet(rx_queue_, &data[i], nullptr, 0);
  }
  return true;
}

size_t UART::available() { return osMessageQueueGetCount(rx_queue_); }

void UART::flush() { osMessageQueueReset(rx_queue_); }

void UART::enable_printf() { get_printf_uart() = this; }

std::map<UART_HandleTypeDef *, UART *> &UART::get_instances() {
  static std::map<UART_HandleTypeDef *, UART *> instances;
  return instances;
}

UART *&UART::get_printf_uart() {
  static UART *uart = nullptr;
  return uart;
}

osMutexId_t UART::get_printf_mutex() {
  static osMutexId_t mutex = osMutexNew(nullptr);
  return mutex;
}

} // namespace tutrclib

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
  auto itr = tutrclib::UART::get_instances().find(huart);
  if (itr != tutrclib::UART::get_instances().end()) {
    tutrclib::UART *uart = itr->second;
    osSemaphoreRelease(uart->tx_sem_);
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  auto itr = tutrclib::UART::get_instances().find(huart);
  if (itr != tutrclib::UART::get_instances().end()) {
    tutrclib::UART *uart = itr->second;
    osMessageQueuePut(uart->rx_queue_, &uart->rx_buf_, 0, 0);
    osSemaphoreRelease(uart->rx_sem_);
    HAL_UART_Receive_IT(huart, &uart->rx_buf_, 1);
  }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
  auto itr = tutrclib::UART::get_instances().find(huart);
  if (itr != tutrclib::UART::get_instances().end()) {
    tutrclib::UART *uart = itr->second;
    HAL_UART_Abort(huart);
    osSemaphoreRelease(uart->tx_sem_);
    osSemaphoreRelease(uart->rx_sem_);
    HAL_UART_Receive_IT(huart, &uart->rx_buf_, 1);
  }
}

int _write(int, char *ptr, int len) {
  auto uart = tutrclib::UART::get_printf_uart();
  if (uart) {
    osMutexAcquire(tutrclib::UART::get_printf_mutex(), osWaitForever);
    uart->transmit(reinterpret_cast<uint8_t *>(ptr), len);
    osMutexRelease(tutrclib::UART::get_printf_mutex());
    return len;
  }
  return -1;
}

#endif
