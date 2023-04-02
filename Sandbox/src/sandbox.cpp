#include "hazel.h"

class TestLayer : public hazel::Layer {
 public:
  TestLayer() : Layer("Test Layer") {}

  void OnUpdate() override {
    // APP_INFO(__func__);
    // APP_INFO(__FUNCTION__);
  }

  void OnEvent(hazel::Event& e) override { APP_TRACE("{}", e); }
};

class Sandbox : public hazel::Application {
 public:
  Sandbox() {
    PushLayer(new TestLayer());
    PushOverlay(new hazel::ImGuiLayer());
  }
  ~Sandbox() {}
};

hazel::Application* hazel::CreateApplication() {
  APP_INFO("Welcome to Sandbox!");
  return new Sandbox();
}