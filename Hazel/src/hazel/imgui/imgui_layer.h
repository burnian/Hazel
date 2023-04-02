#pragma once
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
  float time_ = 0.0f;
};

}  // namespace hazel