#pragma once
#include "core.hpp"

// This ignores all warnings raised inside External headers
// #pragma warning(push, 0)
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"
// to enable operator<< in event.h, the statament below must be included
// after spdlog.h, or will break down
#include "spdlog/fmt/ostr.h"

// #pragma warning(pop)

namespace hazel {

class HAZEL_API Log {
 public:
  static void Init();

  static Ref<spdlog::logger> &GetCoreLogger() { return sp_core_logger_; }
  static Ref<spdlog::logger> &GetClientLogger() { return sp_client_logger_; }

 private:
  static Ref<spdlog::logger> sp_core_logger_;
  static Ref<spdlog::logger> sp_client_logger_;
};

// template <typename OStream, glm::length_t L, typename T, glm::qualifier Q>
// inline OStream &operator<<(OStream &os, const glm::vec<L, T, Q> &vector) {
//   return os << glm::to_string(vector);
// }
//
// template <typename OStream, glm::length_t C, glm::length_t R, typename T,
//           glm::qualifier Q>
// inline OStream &operator<<(OStream &os, const glm::mat<C, R, T, Q> &matrix) {
//   return os << glm::to_string(matrix);
// }
//
// template <typename OStream, typename T, glm::qualifier Q>
// inline OStream &operator<<(OStream &os, glm::qua<T, Q> quaternion) {
//   return os << glm::to_string(quaternion);
// }

}  // namespace hazel

// core log macros
#define CORE_TRACE(...) \
  SPDLOG_LOGGER_TRACE(::hazel::Log::GetCoreLogger(), __VA_ARGS__)  // white
#define CORE_DEBUG(...) \
  SPDLOG_LOGGER_DEBUG(::hazel::Log::GetCoreLogger(), __VA_ARGS__)  // blue
#define CORE_INFO(...) \
  SPDLOG_LOGGER_INFO(::hazel::Log::GetCoreLogger(), __VA_ARGS__)  // green
#define CORE_WARN(...) \
  SPDLOG_LOGGER_WARN(::hazel::Log::GetCoreLogger(), __VA_ARGS__)  // yellow
#define CORE_ERROR(...) \
  SPDLOG_LOGGER_ERROR(::hazel::Log::GetCoreLogger(), __VA_ARGS__)  // red
#define CORE_FATAL(...)                                 \
  SPDLOG_LOGGER_CRITICAL(::hazel::Log::GetCoreLogger(), \
                         __VA_ARGS__)  // highlighted red

// client log macros
#define APP_TRACE(...) \
  SPDLOG_LOGGER_TRACE(::hazel::Log::GetClientLogger(), __VA_ARGS__)
#define APP_DEBUG(...) \
  SPDLOG_LOGGER_DEBUG(::hazel::Log::GetClientLogger(), __VA_ARGS__)
#define APP_INFO(...) \
  SPDLOG_LOGGER_INFO(::hazel::Log::GetClientLogger(), __VA_ARGS__)
#define APP_WARN(...) \
  SPDLOG_LOGGER_WARN(::hazel::Log::GetClientLogger(), __VA_ARGS__)
#define APP_ERROR(...) \
  SPDLOG_LOGGER_ERROR(::hazel::Log::GetClientLogger(), __VA_ARGS__)
#define APP_FATAL(...) \
  SPDLOG_LOGGER_CRITICAL(::hazel::Log::GetClientLogger(), __VA_ARGS__)
