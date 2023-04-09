#include "hazel_pch.h"
#include "application.h"

#include "hazel/core.hpp"

namespace hazel {

Application* Application::instance_ = nullptr;

Application::Application() {
  CORE_ASSERT(!instance_, "Application already exists!");
  instance_ = this;

  window_ = Window::Create();
  window_->SetEventCallback(HAZEL_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() {}

void Application::OnEvent(Event& e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      HAZEL_BIND_EVENT_FN(Application::OnWindowClose));

  for (auto it = layer_stack_.end(); it != layer_stack_.begin();) {
    Layer* p_layer = *--it;
    p_layer->OnEvent(e);
    if (e.handled) break;
  }

  CORE_INFO("{}", e);
}

void Application::Run() {
  // WindowResizeEvent e(1200, 720);
  // if (e.IsInCategory(EventCategoryApp)) {
  //   CORE_INFO("event category app, {}", e);
  // }
  while (running_) {
    for (Layer* layer : layer_stack_) layer->OnUpdate();

    window_->OnUpdate();
  }
}

void Application::PushLayer(Layer* layer) {
  layer_stack_.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer* layer) {
  layer_stack_.PushOverlay(layer);
  layer->OnAttach();
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
  running_ = false;
  return true;
}

}  // namespace hazel
