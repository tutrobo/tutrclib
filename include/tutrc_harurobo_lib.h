#pragma once

#define TUTRC_HARUROBO_LIB_FOR_1(proc, arg) proc(arg)
#define TUTRC_HARUROBO_LIB_FOR_2(proc, arg, ...)                               \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_1(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_3(proc, arg, ...)                               \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_2(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_4(proc, arg, ...)                               \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_3(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_5(proc, arg, ...)                               \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_4(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_6(proc, arg, ...)                               \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_5(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_7(proc, arg, ...)                               \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_6(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_8(proc, arg, ...)                               \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_7(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_9(proc, arg, ...)                               \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_8(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_10(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_9(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_11(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_10(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_12(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_11(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_13(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_12(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_14(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_13(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_15(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_14(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_16(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_15(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_17(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_16(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_18(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_17(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_19(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_18(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_20(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_19(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_21(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_20(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_22(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_21(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_23(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_22(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_24(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_23(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_25(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_24(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_26(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_25(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_27(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_26(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_28(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_27(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_29(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_28(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_30(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_29(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_31(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_30(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR_32(proc, arg, ...)                              \
  proc(arg) __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_31(proc, __VA_ARGS__))
#define TUTRC_HARUROBO_LIB_FOR(proc, ...)                                      \
  __VA_OPT__(TUTRC_HARUROBO_LIB_FOR_32(proc, __VA_ARGS__))

#define TUTRC_HARUROBO_LIB_SET_HANDLE(handle)                                  \
  if (instance == (handle).Instance) {                                         \
    return &(handle);                                                          \
  }

#define TUTRC_HARUROBO_LIB_SET_HANDLES(...)                                    \
  void *tutrc_harurobo_lib_get_handle(void *instance) {                        \
    TUTRC_HARUROBO_LIB_FOR(TUTRC_HARUROBO_LIB_SET_HANDLE, __VA_ARGS__)         \
    return NULL;                                                               \
  }
