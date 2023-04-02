#include "hazel_pch.h"
#include "windows_window.h"

#include <glad/glad.h> // glad should put here before GLFW since glfw defined GLFW_INCLUDE_NONE

#include "hazel/events/app_event.h"
#include "hazel/events/key_event.h"
#include "hazel/events/mouse_event.h"
// #include "Platform/OpenGL/OpenGLContext.h"
// #include "hazel/Renderer/Renderer.h"
// #include "hazel/Core/Input.h"

namespace hazel {

static uint8_t kGLFWWindowCount = 0;

WindowsWindow::WindowsWindow(const WindowProps& props) {
  // HZ_PROFILE_FUNCTION();
  Init(props);
}

WindowsWindow::~WindowsWindow() {
  // HZ_PROFILE_FUNCTION();
  Shutdown();
}

void WindowsWindow::Init(const WindowProps& props) {
  // HZ_PROFILE_FUNCTION();
  data_.title = props.title;
  data_.width = props.width;
  data_.height = props.height;

  CORE_INFO("Creating window {} ({}, {})", props.title, props.width,
            props.height);

  if (kGLFWWindowCount == 0) {
    // HZ_PROFILE_SCOPE("glfwInit");
    int success = glfwInit();
    CORE_ASSERT(success, "Failed to initialize GLFW!");

    glfwSetErrorCallback([](int error, const char* desc) {
      CORE_ERROR("GLFW Error ({}): {}", error, desc);
    });
  }

  {
    // HZ_PROFILE_SCOPE("glfwCreateWindow");
    // #if defined(HAZEL_DEBUG)
    //    if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
    //      glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    // #endif
    window_ = glfwCreateWindow(int(data_.width), int(data_.height),
                               data_.title.c_str(), nullptr, nullptr);
    ++kGLFWWindowCount;
  }

  // context_ = GraphicsContext::Create(window_);
  // context_->Init();
  glfwMakeContextCurrent(window_);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  CORE_ASSERT(status, "Failed to initialize Glad!");
  glfwSetWindowUserPointer(window_, &data_);
  SetVSync(true);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width,
                                        int height) {
    auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    data.width = width;
    data.height = height;
    WindowResizeEvent event(width, height);
    data.event_callback(event);
  });

  glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
    auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    WindowCloseEvent event;
    data.event_callback(event);
  });

  glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode,
                                 int action, int mods) {
    auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    switch (action) {
      case GLFW_PRESS: {
        KeyPressedEvent event(key);
        data.event_callback(event);
        break;
      }
      case GLFW_RELEASE: {
        KeyReleasedEvent event(key);
        data.event_callback(event);
        break;
      }
      case GLFW_REPEAT: {
        KeyPressedEvent event(key, true);
        data.event_callback(event);
        break;
      }
    }
  });

  glfwSetCharCallback(window_, [](GLFWwindow* window, uint32_t keycode) {
    auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    KeyTypedEvent event(keycode);
    data.event_callback(event);
  });

  glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button,
                                         int action, int mods) {
    auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    switch (action) {
      case GLFW_PRESS: {
        MouseButtonPressedEvent event(button);
        data.event_callback(event);
        break;
      }
      case GLFW_RELEASE: {
        MouseButtonReleasedEvent event(button);
        data.event_callback(event);
        break;
      }
    }
  });

  glfwSetScrollCallback(window_, [](GLFWwindow* window, double x_offset,
                                    double y_offset) {
    auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    MouseScrolledEvent event(static_cast<float>(x_offset),
                             static_cast<float>(y_offset));
    data.event_callback(event);
  });

  glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x_pos,
                                       double y_pos) {
    auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    MouseMovedEvent event(static_cast<float>(x_pos), static_cast<float>(y_pos));
    data.event_callback(event);
  });
}

void WindowsWindow::Shutdown() {
  // HZ_PROFILE_FUNCTION();

  glfwDestroyWindow(window_);
  --kGLFWWindowCount;

  if (kGLFWWindowCount == 0) {
    glfwTerminate();
  }
}

void WindowsWindow::OnUpdate() {
  // HZ_PROFILE_FUNCTION();

  glfwPollEvents();
  // context_->SwapBuffers();
  glfwSwapBuffers(window_);
}

void WindowsWindow::SetVSync(bool enabled) {
  // HZ_PROFILE_FUNCTION();

  if (enabled)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);

  data_.vsync = enabled;
}

bool WindowsWindow::IsVSync() const { return data_.vsync; }

}  // namespace hazel
