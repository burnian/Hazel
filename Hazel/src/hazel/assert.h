#pragma once

#include <filesystem>

#include "hazel/log.h"

#ifdef HAZEL_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and
// "NO_MSG" and provide support for custom formatting by concatenating the
// formatting string instead of having the format inside the default message
#define HAZEL_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
  {                                                       \
    if (!(check)) {                                       \
      HZ##type##ERROR(msg, __VA_ARGS__);                  \
      HAZEL_DEBUGBREAK();                                 \
    }                                                     \
  }
#define HAZEL_INTERNAL_ASSERT_WITH_MSG(type, check, ...) \
  HAZEL_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define HAZEL_INTERNAL_ASSERT_NO_MSG(type, check)       \
  HAZEL_INTERNAL_ASSERT_IMPL(                           \
      type, check, "Assertion '{0}' failed at {1}:{2}", \
      HAZEL_STRINGIFY_MACRO(check),                     \
      std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define HAZEL_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define HAZEL_INTERNAL_ASSERT_GET_MACRO(...)               \
  HAZEL_EXPAND_MACRO(HAZEL_INTERNAL_ASSERT_GET_MACRO_NAME( \
      __VA_ARGS__, HAZEL_INTERNAL_ASSERT_WITH_MSG,         \
      HAZEL_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the
// message) being optional
#define HAZEL_ASSERT(...) \
  HAZEL_EXPAND_MACRO(     \
      HAZEL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#define HAZEL_CORE_ASSERT(...) \
  HAZEL_EXPAND_MACRO(          \
      HAZEL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#define HAZEL_ASSERT(...)
#define HAZEL_CORE_ASSERT(...)
#endif
