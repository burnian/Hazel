#include "pch.h"
#include "application.h"

#include "events/app_event.h"
#include "log.h"

namespace hazel {

Application::Application() { window_ = Window::Create(); }

Application::~Application() {}

void Application::Run() {
  // WindowResizeEvent e(1200, 720);

  // if (e.IsInCategory(EventCategoryApp)) {
  //   CORE_INFO("event category app, {}", e);
  // }

  while (running_) {
    window_->OnUpdate();
  }
}

}  // namespace hazel
