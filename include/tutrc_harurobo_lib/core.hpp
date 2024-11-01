#pragma once

#include <unordered_map>

extern "C" void *tutrc_harurobo_lib_get_handle(void *instance);

namespace tutrc_harurobo_lib {

std::unordered_map<void *, void *> &get_instances();

template <class T, class U> void set_instance(T handle, U instance) {
  get_instances()[reinterpret_cast<void *>(handle)] =
      reinterpret_cast<void *>(instance);
}

template <class T, class U> T get_instance(U handle) {
  auto itr = get_instances().find(reinterpret_cast<void *>(handle));
  if (itr != get_instances().end()) {
    return reinterpret_cast<T>(itr->second);
  }
  return nullptr;
}

} // namespace tutrc_harurobo_lib
