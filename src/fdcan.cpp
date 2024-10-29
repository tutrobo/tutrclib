#include "main.h"

#ifdef HAL_FDCAN_MODULE_ENABLED

#include "tutrc_harurobo_lib/fdcan.hpp"

#include "FreeRTOS.h"
#include "task.h"

namespace tutrc_harurobo_lib {

std::unordered_map<FDCAN_HandleTypeDef *, FDCAN *> FDCAN::instances_;

bool FDCAN::init(FDCAN_HandleTypeDef *hfdcan, size_t rx_queue_size) {
  hfdcan_ = hfdcan;
  instances_[hfdcan_] = this;
  rx_queue_ = osMessageQueueNew(rx_queue_size, sizeof(CANMessage), nullptr);

  if (hfdcan_->State != HAL_FDCAN_STATE_READY) {
    return false;
  }

  if (HAL_FDCAN_ActivateNotification(hfdcan_, FDCAN_IT_RX_FIFO0_NEW_MESSAGE,
                                     0) != HAL_OK) {
    return false;
  }

  return HAL_FDCAN_Start(hfdcan_) == HAL_OK;
}

bool FDCAN::transmit(const CANMessage *msg) {
  FDCAN_TxHeaderTypeDef tx_header = {};
  tx_header.Identifier = msg->id;
  switch (msg->id_type) {
  case CANIDType::STANDARD:
    tx_header.IdType = FDCAN_STANDARD_ID;
    break;
  case CANIDType::EXTENDED:
    tx_header.IdType = FDCAN_EXTENDED_ID;
    break;
  }
  tx_header.TxFrameType = FDCAN_DATA_FRAME;
  switch (msg->dlc) {
  case 0:
    tx_header.DataLength = FDCAN_DLC_BYTES_0;
    break;
  case 1:
    tx_header.DataLength = FDCAN_DLC_BYTES_1;
    break;
  case 2:
    tx_header.DataLength = FDCAN_DLC_BYTES_2;
    break;
  case 3:
    tx_header.DataLength = FDCAN_DLC_BYTES_3;
    break;
  case 4:
    tx_header.DataLength = FDCAN_DLC_BYTES_4;
    break;
  case 5:
    tx_header.DataLength = FDCAN_DLC_BYTES_5;
    break;
  case 6:
    tx_header.DataLength = FDCAN_DLC_BYTES_6;
    break;
  case 7:
    tx_header.DataLength = FDCAN_DLC_BYTES_7;
    break;
  case 8:
    tx_header.DataLength = FDCAN_DLC_BYTES_8;
    break;
  }
  tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
  tx_header.BitRateSwitch = FDCAN_BRS_OFF;
  tx_header.FDFormat = FDCAN_CLASSIC_CAN;
  tx_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
  tx_header.MessageMarker = 0;

  return HAL_FDCAN_AddMessageToTxFifoQ(hfdcan_, &tx_header, msg->data) ==
         HAL_OK;
}

bool FDCAN::receive(CANMessage *msg, uint32_t timeout) {
  return osMessageQueueGet(rx_queue_, msg, nullptr, timeout) == osOK;
}

size_t FDCAN::available() { return osMessageQueueGetCount(rx_queue_); }

} // namespace tutrc_harurobo_lib

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t) {
  static FDCAN_RxHeaderTypeDef rx_header;
  static tutrc_harurobo_lib::CANMessage msg;

  auto itr = tutrc_harurobo_lib::FDCAN::instances_.find(hfdcan);
  if (itr != tutrc_harurobo_lib::FDCAN::instances_.end()) {
    tutrc_harurobo_lib::FDCAN *fdcan = itr->second;

    for (size_t i = HAL_FDCAN_GetRxFifoFillLevel(hfdcan, FDCAN_RX_FIFO0); i > 0;
         --i) {
      if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_header,
                                 msg.data) != HAL_OK) {
        return;
      }

      msg.id = rx_header.Identifier;
      switch (rx_header.IdType) {
      case FDCAN_STANDARD_ID:
        msg.id_type = tutrc_harurobo_lib::CANIDType::STANDARD;
        break;
      case FDCAN_EXTENDED_ID:
        msg.id_type = tutrc_harurobo_lib::CANIDType::EXTENDED;
        break;
      }
      switch (rx_header.DataLength) {
      case FDCAN_DLC_BYTES_0:
        msg.dlc = 0;
        break;
      case FDCAN_DLC_BYTES_1:
        msg.dlc = 1;
        break;
      case FDCAN_DLC_BYTES_2:
        msg.dlc = 2;
        break;
      case FDCAN_DLC_BYTES_3:
        msg.dlc = 3;
        break;
      case FDCAN_DLC_BYTES_4:
        msg.dlc = 4;
        break;
      case FDCAN_DLC_BYTES_5:
        msg.dlc = 5;
        break;
      case FDCAN_DLC_BYTES_6:
        msg.dlc = 6;
        break;
      case FDCAN_DLC_BYTES_7:
        msg.dlc = 7;
        break;
      case FDCAN_DLC_BYTES_8:
        msg.dlc = 8;
        break;
      }

      osMessageQueuePut(fdcan->rx_queue_, &msg, 0, 0);
    }
  }
}

#endif
