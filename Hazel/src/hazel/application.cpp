#include "hazel_pch.h"
#include "application.h"

#include "hazel/core.hpp"
#include "input.h"

// TEMPORARY
#include "glad/glad.h"

namespace hazel {

Application* Application::instance_ = nullptr;

Application::Application() {
  CORE_ASSERT(!instance_, "Application already exists!");
  instance_ = this;

  window_ = Window::Create();
  window_->SetEventCallback(HAZEL_BIND_EVENT_FN(Application::OnEvent));

  // Renderer::Init();

  imgui_layer_ = new ImGuiLayer();
  PushOverlay(imgui_layer_);
}

Application::~Application() {
  // ScriptEngine::Shutdown();
  // Renderer::Shutdown();
}

///@brief event poll once per frame
void Application::OnEvent(Event& e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      HAZEL_BIND_EVENT_FN(Application::OnWindowClose));
  dispatcher.Dispatch<WindowResizeEvent>(
      HAZEL_BIND_EVENT_FN(Application::OnWindowResize));

  for (auto it = layer_stack_.end(); it != layer_stack_.begin();) {
    Layer* p_layer = *--it;
    p_layer->OnEvent(e);
    if (e.handled) break;
  }

  // CORE_INFO("{}", e);
}

///@brief run when cpu idle
void Application::Run() {
  while (running_) {
    //glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!minimized_) {
      {
        // HZ_PROFILE_SCOPE("LayerStack OnUpdate");
        for (Layer* layer : layer_stack_) layer->OnUpdate();
      }

      imgui_layer_->Begin();
      {
        // HZ_PROFILE_SCOPE("LayerStack OnImGuiRender");
        for (Layer* layer : layer_stack_) layer->OnImGuiRender();
      }
      imgui_layer_->End();
    }

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

bool Application::OnWindowResize(WindowResizeEvent& e) {
  if (e.GetWidth() == 0 || e.GetHeight() == 0) {
    minimized_ = true;
    return false;
  }

  minimized_ = false;
  // Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

  return false;
}

}  // namespace hazel
