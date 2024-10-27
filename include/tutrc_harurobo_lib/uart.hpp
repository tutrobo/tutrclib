#pragma once

#include "main.h"

#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "queue.h"

extern "C" int _write(int file, char *ptr, int len);

namespace tutrc_harurobo_lib {

/**
 * UARTクラスを使う際は、
 *
 * - USARTx global interrupt
 * - USARTx_TX DMA (Mode: Normal)
 * - USARTx_RX DMA (Mode: Circular)
 *
 * を有効化する必要があります。
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
 * void example_thread(void *) {
 *   tutrc_harurobo_lib::UART uart1(&huart1);
 *   tutrc_harurobo_lib::UART uart2(&huart2);
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
   * コンストラクタ
   *
   * @param huart UART_HandleTypeDefへのポインタ
   * @param rx_buf_size 受信バッファサイズ
   */
  UART(UART_HandleTypeDef *huart, size_t rx_buf_size = 64);

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
   * 受信バッファにあるバイト数を取得する
   */
  size_t available();

  /**
   * 受信バッファをflush(空に)する
   */
  void flush();

  /**
   * printf() を呼び出した際にこのペリフェラルを介して出力する
   */
  void enable_printf();

private:
  UART_HandleTypeDef *huart_;
  osMutexId_t tx_mutex_;
  osMutexId_t rx_mutex_;
  QueueHandle_t tx_queue_;
  QueueHandle_t rx_queue_;
  std::vector<uint8_t> rx_buf_;
  uint16_t rx_buf_head_ = 0;
  uint16_t rx_buf_tail_ = 0;

  static std::unordered_map<UART_HandleTypeDef *, UART *> instances_;
  static UART *uart_printf_;
  friend void ::HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
  friend void ::HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,
                                           uint16_t Size);
  friend void ::HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
  friend int ::_write(int file, char *ptr, int len);
};

} // namespace tutrc_harurobo_lib
