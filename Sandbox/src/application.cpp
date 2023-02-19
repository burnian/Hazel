#include "hazel.h"

class Sandbox : public hazel::Application {
 public:
  Sandbox();
  ~Sandbox();
};

Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

hazel::Application* hazel::CreateApplication() {
  // APP_INFO("Welcome to spdlog! {},{}", __FILE__, __LINE__);
  return new Sandbox();
}