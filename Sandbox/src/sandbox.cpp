#include "hazel.h"

class TestLayer : public hazel::Layer {
 public:
  TestLayer() : Layer("Test Layer") {}

  void OnUpdate() override {
    if (hazel::Input::IsKeyPressed(hazel::key::Tab)) {
      APP_TRACE("key Tab is pressed.");
    }
  }

  void OnEvent(hazel::Event& e) override {
    // APP_TRACE("{} {}", __FUNCTION__, e);
    if (e.GetType() == hazel::EventType::KeyPressed) {
      hazel::KeyPressedEvent& ee = (hazel::KeyPressedEvent&)e;
      APP_TRACE("{}", (char)(ee.GetKeyCode()));
    }
  }
};

class Sandbox : public hazel::Application {
 public:
  Sandbox() {
    PushLayer(new TestLayer());
  }
  ~Sandbox() {}
};

hazel::Application* hazel::CreateApplication() {
  APP_INFO("Welcome to Sandbox!");
  return new Sandbox();
}
