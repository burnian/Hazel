#ifndef _LOG_H_
#define _LOG_H_

#include <memory>

#include "core.h"
#include "spdlog/spdlog.h"

namespace hazel {

class HAZEL_API Log {
 public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
    return sp_core_logger_;
  }
  inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
    return sp_client_logger_;
  }

 private:
  static std::shared_ptr<spdlog::logger> sp_core_logger_;
  static std::shared_ptr<spdlog::logger> sp_client_logger_;
};

}  // namespace hazel

// core log macros
#define CORE_TRACE(...) ::hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_DEBUG(...) ::hazel::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define CORE_INFO(...) ::hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) ::hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) ::hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_FATAL(...) ::hazel::Log::GetCoreLogger()->critical(__VA_ARGS__)

// client log macros
#define APP_TRACE(...) ::hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define APP_DEBUG(...) ::hazel::Log::GetClientLogger()->debug(__VA_ARGS__)
#define APP_INFO(...) ::hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define APP_WARN(...) ::hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...) ::hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define APP_FATAL(...) ::hazel::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif