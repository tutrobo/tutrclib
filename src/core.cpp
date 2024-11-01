#include "cmsis_os2.h"

#include "tutrc_harurobo_lib/core.hpp"

extern "C" {

void tutrc_harurobo_lib_init();

void __real___libc_init_array(void);

void __wrap___libc_init_array(void) {}

osStatus_t __real_osKernelInitialize(void);

osStatus_t __wrap_osKernelInitialize(void) {
  osStatus_t res = __real_osKernelInitialize();
  if (res != osOK) {
    return res;
  }
  tutrc_harurobo_lib_init();
  __real___libc_init_array();
  return osOK;
}
}

std::unordered_map<void *, void *> &tutrc_harurobo_lib::pointer_to_pointer() {
  static std::unordered_map<void *, void *> handles;
  return handles;
}

/* std::unordered_map<void *, void *> &tutrc_harurobo_lib::get_instances() {
  static std::unordered_map<void *, void *> instances;
  return instances;
}
 */
