#pragma once

#include <algorithm>
#include <cmath>
#include <type_traits>
#include <unordered_map>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

template <class T>
constexpr std::underlying_type_t<T> to_underlying(T value) noexcept {
  return static_cast<std::underlying_type_t<T>>(value);
}

template <class T> constexpr T clamp(T x, T a, T b) {
  return std::min(std::max(x, a), b);
}

template <class T> constexpr T normalize_angle(T x) {
  x = std::fmod(x, 2 * M_PI);
  if (x < 0) {
    x += 2 * M_PI;
  }
  return x;
}

} // namespace tutrc_harurobo_lib
