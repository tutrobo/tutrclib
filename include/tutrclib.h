#pragma once

#include "main.h"

#include "cmsis_os2.h"

#ifdef __cplusplus

#include "tutrclib/utility.h"

#ifdef HAL_GPIO_MODULE_ENABLED
#include "tutrclib/gpio.h"
#endif

#ifdef HAL_TIM_MODULE_ENABLED
#include "tutrclib/encoder.h"
#include "tutrclib/pwm.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED
#include "tutrclib/uart.h"
#endif

#ifdef HAL_CAN_MODULE_ENABLED
#include "tutrclib/can.h"
#endif

#ifdef HAL_FDCAN_MODULE_ENABLED
#include "tutrclib/fdcan.h"
#endif

extern "C" {
#endif

void tutrclib_init();

#ifdef HAL_TIM_MODULE_ENABLED
void tutrclib_register_TIM_HandleTypeDef(TIM_HandleTypeDef *htim);
#endif

#ifdef HAL_UART_MODULE_ENABLED
void tutrclib_register_UART_HandleTypeDef(UART_HandleTypeDef *huart);
#endif

#ifdef HAL_CAN_MODULE_ENABLED
void tutrclib_register_CAN_HandleTypeDef(CAN_HandleTypeDef *hcan);
#endif

#ifdef HAL_FDCAN_MODULE_ENABLED
void tutrclib_register_FDCAN_HandleTypeDef(FDCAN_HandleTypeDef *hfdcan);
#endif

#ifdef __cplusplus
}
#endif
