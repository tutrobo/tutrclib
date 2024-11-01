#pragma once

#include "main.h"

#include <cstddef>
#include <cstdint>
#include <map>

#include "cmsis_os2.h"

#include "can_base.h"

namespace tutrclib {

class CAN : public CANBase {
public:
  CAN(CAN_TypeDef *instance, size_t rx_queue_size = 64);
  bool transmit(const CANMessage *msg) override;
  bool receive(CANMessage *msg, uint32_t timeout) override;
  size_t available() override;

private:
  CAN_HandleTypeDef *hcan_;
  osMessageQueueId_t rx_queue_;

  static std::map<CAN_HandleTypeDef *, CAN *> &get_instances();

  friend void ::HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
};

} // namespace tutrclib
