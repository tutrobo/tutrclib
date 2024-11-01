#pragma once

#include "main.h"

#include <cstddef>
#include <cstdint>
#include <map>

#include "cmsis_os2.h"

#include "can_base.h"

namespace tutrclib {

class FDCAN : public CANBase {
public:
  FDCAN(FDCAN_GlobalTypeDef *instance, size_t rx_queue_size = 64);
  bool transmit(const CANMessage *msg) override;
  bool receive(CANMessage *msg, uint32_t timeout) override;
  size_t available() override;

private:
  FDCAN_HandleTypeDef *hfdcan_;
  osMessageQueueId_t rx_queue_;

  static std::map<FDCAN_HandleTypeDef *, FDCAN *> &get_instances();

  friend void ::HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan,
                                          uint32_t RxFifo0ITs);
};

} // namespace tutrclib
