#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "core.h"

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

#endif