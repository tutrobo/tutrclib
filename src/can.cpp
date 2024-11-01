#include "main.h"

#ifdef HAL_CAN_MODULE_ENABLED

#include "FreeRTOS.h"
#include "task.h"

#include "tutrclib/can.h"
#include "tutrclib/internal/core.h"

namespace tutrclib {

CAN::CAN(CAN_TypeDef *instance, size_t rx_queue_size) {
  hcan_ = internal::HALHandleManager::get<CAN_HandleTypeDef>(instance);
  if (!hcan_) {
    Error_Handler();
  }

  get_instances()[hcan_] = this;
  rx_queue_ = osMessageQueueNew(rx_queue_size, sizeof(CANMessage), nullptr);

  CAN_FilterTypeDef filter = {};
  filter.FilterIdHigh = 0;
  filter.FilterIdLow = 0;
  filter.FilterMaskIdHigh = 0;
  filter.FilterMaskIdLow = 0;
  filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  filter.FilterBank = 0;
#ifdef CAN2
  if (hcan_->Instance == CAN2) {
    filter.FilterBank = 14;
  }
#endif
  filter.FilterMode = CAN_FILTERMODE_IDMASK;
  filter.FilterScale = CAN_FILTERSCALE_32BIT;
  filter.FilterActivation = ENABLE;
  filter.SlaveStartFilterBank = 14;

  if (HAL_CAN_ConfigFilter(hcan_, &filter) != HAL_OK) {
    Error_Handler();
  }

  if (HAL_CAN_ActivateNotification(hcan_, CAN_IT_RX_FIFO0_MSG_PENDING) !=
      HAL_OK) {
    Error_Handler();
  }

  if (HAL_CAN_Start(hcan_) != HAL_OK) {
    Error_Handler();
  }
}

bool CAN::transmit(const CANMessage *msg) {
  CAN_TxHeaderTypeDef tx_header = {};
  switch (msg->id_type) {
  case CANIDType::STANDARD:
    tx_header.StdId = msg->id;
    tx_header.IDE = CAN_ID_STD;
    break;
  case CANIDType::EXTENDED:
    tx_header.ExtId = msg->id;
    tx_header.IDE = CAN_ID_EXT;
    break;
  }
  tx_header.RTR = CAN_RTR_DATA;
  tx_header.DLC = msg->dlc;
  tx_header.TransmitGlobalTime = DISABLE;

  uint32_t tx_mailbox;

  return HAL_CAN_AddTxMessage(hcan_, &tx_header, msg->data, &tx_mailbox) ==
         HAL_OK;
}

bool CAN::receive(CANMessage *msg, uint32_t timeout) {
  return osMessageQueueGet(rx_queue_, msg, nullptr, timeout) == osOK;
}

size_t CAN::available() { return osMessageQueueGetCount(rx_queue_); }

std::map<CAN_HandleTypeDef *, CAN *> &CAN::get_instances() {
  static std::map<CAN_HandleTypeDef *, CAN *> instances;
  return instances;
}

} // namespace tutrclib

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  static CAN_RxHeaderTypeDef rx_header;
  static tutrclib::CANMessage msg;

  auto itr = tutrclib::CAN::get_instances().find(hcan);
  if (itr != tutrclib::CAN::get_instances().end()) {
    tutrclib::CAN *can = itr->second;
    for (size_t i = HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO0); i > 0;
         --i) {
      if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, msg.data) !=
          HAL_OK) {
        return;
      }

      switch (rx_header.IDE) {
      case CAN_ID_STD:
        msg.id_type = tutrclib::CANIDType::STANDARD;
        msg.id = rx_header.StdId;
        break;
      case CAN_ID_EXT:
        msg.id_type = tutrclib::CANIDType::EXTENDED;
        msg.id = rx_header.ExtId;
        break;
      }
      msg.dlc = rx_header.DLC;

      osMessageQueuePut(can->rx_queue_, &msg, 0, 0);
    }
  }
}

#endif
