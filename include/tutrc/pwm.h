#pragma once

#include "main.h"

#include <cstdint>

namespace tutrc {

class PWM {
public:
  /**
   * PWM初期化
   *
   * @param htim TIM_HandleTypeDefへのポインタ
   * @param channel 使用するPWMチャネル
   * @return true: 成功, false: 失敗
   */
  PWM(TIM_TypeDef *instance, uint32_t channel);

  /**
   * タイマのカウンタを取得
   */
  uint32_t get_compare();

  /**
   * タイマのカウンタを設定
   */
  void set_compare(uint32_t compare);

private:
  TIM_HandleTypeDef *htim_;
  uint32_t channel_;
};

} // namespace tutrc
