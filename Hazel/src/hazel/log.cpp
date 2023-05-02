#include "hazel_pch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace hazel {

std::shared_ptr<spdlog::logger> Log::sp_core_logger_;
std::shared_ptr<spdlog::logger> Log::sp_client_logger_;

void Log::Init() {
  spdlog::set_pattern("%^[%C-%m-%d %T %n][%s:%#] %v%$");

  sp_core_logger_ = spdlog::stdout_color_mt("CORE");
  sp_core_logger_->set_level(spdlog::level::trace);

  sp_client_logger_ = spdlog::stdout_color_mt("APP");
  sp_client_logger_->set_level(spdlog::level::trace);
}

}  // namespace hazel
