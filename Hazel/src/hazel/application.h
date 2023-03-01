#pragma once
#include "events/event.h"
#include "window.h"

namespace hazel {

class HAZEL_API Application {
 public:
  Application();
  virtual ~Application();

  void Run();

 private:
  Scope<Window> window_;
  bool running_ = true;
};

// to be defined in CLIENT
Application* CreateApplication();

}  // namespace hazel
