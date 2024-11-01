#pragma once

#include <map>

namespace tutrclib {
namespace internal {

std::map<void *, void *> &get_stm32hal_handles();

}
} // namespace tutrclib
