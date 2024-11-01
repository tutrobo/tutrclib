#pragma once

#include <map>

namespace tutrc {
namespace internal {

std::map<void *, void *> &get_stm32hal_handles();

}
} // namespace tutrc
