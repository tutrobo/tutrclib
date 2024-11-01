#pragma once

#include "main.h"

#include "cmsis_os2.h"

#include "tutrc_harurobo_lib/utility.hpp"

#ifdef HAL_GPIO_MODULE_ENABLED
#include "tutrc_harurobo_lib/gpio.hpp"
#endif

#ifdef HAL_TIM_MODULE_ENABLED
#include "tutrc_harurobo_lib/encoder.hpp"
#include "tutrc_harurobo_lib/pwm.hpp"
#endif

#ifdef HAL_UART_MODULE_ENABLED
#include "tutrc_harurobo_lib/uart.hpp"
#endif

#ifdef HAL_CAN_MODULE_ENABLED
#include "tutrc_harurobo_lib/can.hpp"
#endif

#ifdef HAL_FDCAN_MODULE_ENABLED
#include "tutrc_harurobo_lib/fdcan.hpp"
#endif
