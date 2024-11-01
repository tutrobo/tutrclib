#pragma once

#include "main.h"

#include "cmsis_os2.h"

#ifdef __cplusplus

#include "tutrc/utility.h"

#ifdef HAL_GPIO_MODULE_ENABLED
#include "tutrc/gpio.h"
#endif

#ifdef HAL_TIM_MODULE_ENABLED
#include "tutrc/encoder.h"
#include "tutrc/pwm.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED
#include "tutrc/uart.h"
#endif

#ifdef HAL_CAN_MODULE_ENABLED
#include "tutrc/can.h"
#endif

#ifdef HAL_FDCAN_MODULE_ENABLED
#include "tutrc/fdcan.h"
#endif

extern "C" {
#endif

void tutrc_init();

#ifdef HAL_TIM_MODULE_ENABLED
void tutrc_register_TIM_HandleTypeDef(TIM_HandleTypeDef *htim);
#endif

#ifdef HAL_UART_MODULE_ENABLED
void tutrc_register_UART_HandleTypeDef(UART_HandleTypeDef *huart);
#endif

#ifdef HAL_CAN_MODULE_ENABLED
void tutrc_register_CAN_HandleTypeDef(CAN_HandleTypeDef *hcan);
#endif

#ifdef HAL_FDCAN_MODULE_ENABLED
void tutrc_register_FDCAN_HandleTypeDef(FDCAN_HandleTypeDef *hfdcan);
#endif

#ifdef __cplusplus
}
#endif
