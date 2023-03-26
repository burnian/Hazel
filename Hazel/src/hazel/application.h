#pragma once
#include "events/app_event.h"
#include "hazel/layer_stack.h"
#include "window.h"

namespace hazel {

class HAZEL_API Application {
 public:
  Application();
  virtual ~Application();

  void OnEvent(Event& e);
  void Run();
  void PushLayer(Layer* layer);
  void PushOverlay(Layer* layer);

 private:
  bool OnWindowClose(WindowCloseEvent& e);

  Scope<Window> window_;
  bool running_ = true;
  LayerStack layer_stack_;
};

// to be defined in CLIENT
Application* CreateApplication();

}  // namespace hazel
