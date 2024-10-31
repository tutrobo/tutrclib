#pragma once

#include "main.h"

#include <cstddef>
#include <cstdint>
#include <unordered_map>

#include "cmsis_os2.h"

extern "C" int _write(int file, char *ptr, int len);

namespace tutrc_harurobo_lib {

/**
 * UARTクラスを使う際は、`USARTx global interrupt` を有効化する必要があります。
 *
 * @code{.cpp}
 * #include "main.h"
 * #include <cstdio>
 * #include "cmsis_os2.h"
 * #include "tutrc_harurobo_lib/uart.hpp"
 *
 * extern UART_HandleTypeDef huart1;
 * extern UART_HandleTypeDef huart2;
 *
 * using namespace tutrc_harurobo_lib;
 *
 * UART uart1;
 * UART uart2;
 *
 * void example_thread(void *) {
 *   uart1.init(&huart1);
 *   uart2.init(&huart2);
 *
 *   uart2.enable_printf(); // UART2に対してprintf有効化
 *
 *   while (true) {
 *     uint8_t data[] = {'h', 'e', 'l', 'l', 'o'};
 *
 *     // 5バイト送信
 *     if (uart1.transmit(data, sizeof(data))) {
 *       printf("送信成功\r\n");
 *     }
 *
 *     // 5バイト溜まるまで受信待機、10msでタイムアウト
 *     if (uart1.receive(data, sizeof(data), 10)) {
 *       printf("受信成功\r\n");
 *     }
 *
 *     osDelay(1000);
 *   }
 * }
 * @endcode
 */
class UART {
public:
  /**
   * UART初期化
   *
   * @param huart UART_HandleTypeDefへのポインタ
   * @param rx_queue_size 受信キューサイズ
   * @return true: 成功, false: 失敗
   */
  UART(USART_TypeDef *instance, size_t rx_queue_size = 64);

  /**
   * UART送信
   *
   * @param data 送信するバイト列の先頭ポインタ
   * @param size 送信するバイト数
   * @return true: 成功, false: 失敗
   */
  bool transmit(const uint8_t *data, size_t size);

  /**
   * UART受信
   *
   * @param data 受信したバイト列を格納するポインタ
   * @param size 受信するバイト数
   * @param timeout タイムアウトまでの時間(ms)
   * @return true: 成功, false: 失敗
   */
  bool receive(uint8_t *data, size_t size, uint32_t timeout);

  /**
   * 受信キューにあるバイト数を取得する
   */
  size_t available();

  /**
   * 受信キューを空にする
   */
  void flush();

  /**
   * printf() を呼び出した際にこのペリフェラルを介して出力する
   */
  void enable_printf();

private:
  UART_HandleTypeDef *huart_;
  osSemaphoreId_t tx_sem_;
  osSemaphoreId_t rx_sem_;
  osMutexId_t rx_queue_;
  uint8_t rx_buf_;

  inline static UART *&get_printf_uart() {
    static UART *uart = nullptr;
    return uart;
  }

  inline static osMutexId_t get_printf_mutex() {
    static osMutexId_t mutex = osMutexNew(nullptr);
    return mutex;
  }

  friend void ::HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
  friend void ::HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
  friend void ::HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
  friend int ::_write(int file, char *ptr, int len);
};

} // namespace tutrc_harurobo_lib
