#pragma once

#include <algorithm>
#include <cmath>
#include <type_traits>
#include <unordered_map>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace tutrc_harurobo_lib {

extern "C" void *tutrc_harurobo_lib_get_handle(void *instance);

inline std::unordered_map<void *, void *> &get_instances() {
  static std::unordered_map<void *, void *> instances;
  return instances;
}

template <class T> T get_instance(void *handle) {
  auto itr = tutrc_harurobo_lib::get_instances().find(handle);
  if (itr != tutrc_harurobo_lib::get_instances().end()) {
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
