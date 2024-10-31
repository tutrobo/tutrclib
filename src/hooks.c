#include "cmsis_os2.h"

void __real___libc_init_array(void);

void __wrap___libc_init_array(void) {}

osStatus_t __real_osKernelStart(void);

osStatus_t __wrap_osKernelStart(void) {
  __real___libc_init_array();
  return __real_osKernelStart();
}
