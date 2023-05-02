#pragma once
#include "hazel/events/app_event.h"
#include "hazel/imgui/imgui_layer.h"
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

  static Application& Get() { return *instance_; }
  Window& GetWindow() { return *window_; }

 private:
  bool OnWindowClose(WindowCloseEvent& e);
  bool OnWindowResize(WindowResizeEvent& e);
  
  static Application* instance_;

  Scope<Window> window_;
  ImGuiLayer* imgui_layer_;
  LayerStack layer_stack_;

  bool running_ = true;
  bool minimized_ = false;
};

// to be defined in CLIENT
Application* CreateApplication();

}  // namespace hazel
