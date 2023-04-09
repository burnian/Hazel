#pragma once
#include "hazel/events/app_event.h"
#include "hazel/events/key_event.h"
#include "hazel/events/mouse_event.h"
#include "hazel/layer.h"

namespace hazel {

class HAZEL_API ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach();
  void OnDetach();
  void OnUpdate();
  void OnEvent(Event& event);

 private:
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
  bool OnMouseMovedEvent(MouseMovedEvent& e);
  bool OnMouseScrolledEvent(MouseScrolledEvent& e);

  bool OnKeyPressedEvent(KeyPressedEvent& e);
  bool OnKeyReleasedEvent(KeyReleasedEvent& e);
  bool OnKeyTypedEvent(KeyTypedEvent& e);

  bool OnWindowResizeEvent(WindowResizeEvent& e);

  float time_ = 0.0f;
};

}  // namespace hazel