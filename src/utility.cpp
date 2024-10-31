#include "cmsis_os2.h"

#include "tutrc_harurobo_lib/utility.hpp"

extern "C" {

void __real___libc_init_array(void);

void __wrap___libc_init_array(void) {}

osStatus_t __real_osKernelStart(void);

osStatus_t __wrap_osKernelStart(void) {
  __real___libc_init_array();
  return __real_osKernelStart();
}
}

std::unordered_map<void *, void *> &tutrc_harurobo_lib::get_instances() {
  static std::unordered_map<void *, void *> instances;
  return instances;
}
