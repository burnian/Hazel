#include "pch.h"
#include "application.h"

#include "events/app_event.h"
#include "log.h"

namespace hazel {

Application::Application() {}

Application::~Application() {}

void Application::Run() {
  WindowResizeEvent e(1200, 720);

  if (e.IsInCategory(EventCategoryApp)) {
    CORE_INFO("event category app, {}", e);
  }
  if (e.IsInCategory(EventCategoryInput)) {
    CORE_INFO("event category input, {}", e);
  }

  while (true) {
  }
}

}  // namespace hazel
