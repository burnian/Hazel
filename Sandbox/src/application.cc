#include "hazel.h"

class Sandbox : public hazel::Application {
 public:
  Sandbox();
  ~Sandbox();
};

Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

hazel::Application* hazel::CreateApplication() { return new Sandbox(); }