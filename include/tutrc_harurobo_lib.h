#pragma once

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void tutrc_harurobo_lib_init();

#ifdef HAL_TIM_MODULE_ENABLED
void tutrc_harurobo_lib_register_TIM_HandleTypeDef(TIM_HandleTypeDef *htim);
#endif

#ifdef HAL_UART_MODULE_ENABLED
void tutrc_harurobo_lib_register_UART_HandleTypeDef(UART_HandleTypeDef *huart);
#endif

#ifdef HAL_CAN_MODULE_ENABLED
void tutrc_harurobo_lib_register_CAN_HandleTypeDef(CAN_HandleTypeDef *hcan);
#endif

#ifdef HAL_FDCAN_MODULE_ENABLED
void tutrc_harurobo_lib_register_FDCAN_HandleTypeDef(
    FDCAN_HandleTypeDef *hfdcan);
#endif

#ifdef __cplusplus
}
#endif
