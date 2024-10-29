#pragma once

#include "main.h"

#include <cstddef>
#include <cstdint>
#include <unordered_map>

#include "cmsis_os2.h"

#include "can_base.hpp"

namespace tutrc_harurobo_lib {

class CAN : public CANBase {
public:
  bool init(CAN_HandleTypeDef *hcan, size_t rx_queue_size = 64);
  bool transmit(const CANMessage *msg) override;
  bool receive(CANMessage *msg, uint32_t timeout) override;
  size_t available() override;

private:
  CAN_HandleTypeDef *hcan_;
  osMessageQueueId_t rx_queue_;

  static std::unordered_map<CAN_HandleTypeDef *, CAN *> instances_;
  friend void ::HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
};

} // namespace tutrc_harurobo_lib
