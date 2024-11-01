#pragma once

#include <map>

extern "C" void *tutrc_harurobo_lib_get_handle(void *instance);

namespace tutrc_harurobo_lib {

std::map<void *, void *> &get_handles();

} // namespace tutrc_harurobo_lib

// extern "C" void *tutrc_harurobo_lib_set_uart_handle() {}
