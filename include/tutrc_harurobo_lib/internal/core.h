#pragma once

#include <map>

namespace tutrc_harurobo_lib {
namespace internal {

std::map<void *, void *> &get_stm32hal_handles();

}
} // namespace tutrc_harurobo_lib
