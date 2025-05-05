#include "hazel.h"
#include "imgui/imgui.h"

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

  void OnImGuiRender() {
    ImGui::Begin("Test");
    ImGui::Text("Hello World!");
    ImGui::ColorEdit4("", new float[4]);
    ImGui::End();
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
