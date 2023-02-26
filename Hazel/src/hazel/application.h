#pragma once
#include "core.hpp"
#include "events/event.h"

namespace hazel {

class HAZEL_API Application {
 public:
  Application();
  virtual ~Application();

  void Run();
};

// to be defined in CLIENT
Application* CreateApplication();

}  // namespace hazel
