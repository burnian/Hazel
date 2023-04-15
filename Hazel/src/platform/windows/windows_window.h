#pragma once
#include <GLFW/glfw3.h>

#include "hazel/window.h"
// #include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace hazel {

class HAZEL_API WindowsWindow : public Window {
 public:
  WindowsWindow(const WindowProps& props);
  virtual ~WindowsWindow();

  void OnUpdate() override;

  uint32_t GetWidth() const override { return data_.width; }
  uint32_t GetHeight() const override { return data_.height; }

  // Window attributes
  void SetEventCallback(const EventCallback& callback) override {
    data_.event_callback = callback;
  }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

  virtual void* GetNativeWindow() const override { return window_; }

 private:
  virtual void Init(const WindowProps& props);
  virtual void Shutdown();

  struct WindowData {
    std::string title;
    uint32_t width, height;
    bool vsync;
    EventCallback event_callback;
  };

  WindowData data_;
  // Scope<GraphicsContext> m_Context;
  GLFWwindow* window_;
};

}  // namespace hazel