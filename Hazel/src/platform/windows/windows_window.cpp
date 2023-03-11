#include "hazel_pch.h"
#include "platform/windows/windows_window.h"

#include "events/app_event.h"
#include "events/key_event.h"
#include "events/mouse_event.h"
#include "hazel/assert.h"
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

  glfwSetWindowUserPointer(window_, &data_);
  SetVSync(true);

  // Set GLFW callbacks
  // glfwSetWindowSizeCallback(
  //    window_, [](GLFWwindow* window, int width, int height) {
  //      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
  //      data.width = width;
  //      data.height = height;

  //      WindowResizeEvent event(width, height);
  //      data.EventCallback(event);
  //    });

  // glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
  //   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
  //   WindowCloseEvent event;
  //   data.EventCallback(event);
  // });

  // glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode,
  //                                 int action, int mods) {
  //   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

  //  switch (action) {
  //    case GLFW_PRESS: {
  //      KeyPressedEvent event(key, 0);
  //      data.EventCallback(event);
  //      break;
  //    }
  //    case GLFW_RELEASE: {
  //      KeyReleasedEvent event(key);
  //      data.EventCallback(event);
  //      break;
  //    }
  //    case GLFW_REPEAT: {
  //      KeyPressedEvent event(key, true);
  //      data.EventCallback(event);
  //      break;
  //    }
  //  }
  //});

  // glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int keycode)
  // {
  //   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

  //  KeyTypedEvent event(keycode);
  //  data.EventCallback(event);
  //});

  // glfwSetMouseButtonCallback(
  //     window_, [](GLFWwindow* window, int button, int action, int mods) {
  //       WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

  //      switch (action) {
  //        case GLFW_PRESS: {
  //          MouseButtonPressedEvent event(button);
  //          data.EventCallback(event);
  //          break;
  //        }
  //        case GLFW_RELEASE: {
  //          MouseButtonReleasedEvent event(button);
  //          data.EventCallback(event);
  //          break;
  //        }
  //      }
  //    });

  // glfwSetScrollCallback(
  //     window_, [](GLFWwindow* window, double xOffset, double yOffset) {
  //       WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

  //      MouseScrolledEvent event((float)xOffset, (float)yOffset);
  //      data.EventCallback(event);
  //    });

  // glfwSetCursorPosCallback(
  //     window_, [](GLFWwindow* window, double xPos, double yPos) {
  //       WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

  //      MouseMovedEvent event((float)xPos, (float)yPos);
  //      data.EventCallback(event);
  //    });
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
