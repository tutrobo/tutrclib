#pragma once

#include <map>

namespace tutrclib {
namespace internal {

class HALHandleManager {
public:
  template <class T> static T *get(void *instance) {
    auto itr = get_handles().find(instance);
    if (itr != get_handles().end()) {
      return reinterpret_cast<T *>(itr->second);
    }
    return nullptr;
  }

  template <class T> static void set(T *handle) {
    get_handles()[handle->Instance] = handle;
  }

private:
  static std::map<void *, void *> &get_handles();
};

} // namespace internal
} // namespace tutrclib
