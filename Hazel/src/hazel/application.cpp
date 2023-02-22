#include "application.h"

#include "events/app_event.h"
#include "log.h"

namespace hazel {

Application::Application() {}

Application::~Application() {}

void Application::Run() {
  WindowResizeEvent e(1200, 720);

  if (e.IsInCategory(EventCategoryApp)) {
    CORE_TRACE("event category app, {}", e.ToString());
  }
  if (e.IsInCategory(EventCategoryInput)) {
    CORE_TRACE("event category input, {}", e.ToString());
  }

  while (true) {
  }
}

}  // namespace hazel
