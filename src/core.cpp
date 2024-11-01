#include "cmsis_os2.h"

#include "tutrc_harurobo_lib/core.hpp"

extern "C" {

void __real___libc_init_array(void);

void __wrap___libc_init_array(void) {}

osStatus_t __real_osKernelInitialize(void);

osStatus_t __wrap_osKernelInitialize(void) {
  osStatus_t res = __real_osKernelInitialize();
  __real___libc_init_array();
  // tutrc_harurobo_lib_init();
  return res;
}
}

std::unordered_map<void *, void *> &tutrc_harurobo_lib::get_instances() {
  static std::unordered_map<void *, void *> instances;
  return instances;
}
