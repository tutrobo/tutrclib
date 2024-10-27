#pragma once

#include <algorithm>
#include <cmath>
#include <type_traits>

#include "cmsis_os2.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace tutrc_harurobo_lib {

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

class ScopedLock {
public:
  ScopedLock(osMutexId_t mutex) : mutex_(mutex) {}

  ~ScopedLock() { osMutexRelease(mutex_); }

  bool acquire(uint32_t timeout) {
    return osMutexAcquire(mutex_, timeout) == osOK;
  }

private:
  osMutexId_t mutex_;
};

} // namespace tutrc_harurobo_lib
