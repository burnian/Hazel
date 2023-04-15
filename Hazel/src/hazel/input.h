#pragma once

#include "hazel/core.hpp"

namespace hazel {

class HAZEL_API Input {
 public:
  static bool IsKeyPressed(int keycode) {
    return instance->IsKeyPressedImpl(keycode);
  }
  static bool IsMouseButtonPressed(int keycode) {
    return instance->IsMouseButtonPressedImpl(keycode);
  }
  static std::pair<float, float> GetMousePos() {
    return instance->GetMousePosImpl();
  }
  static float GetMouseX() { return instance->GetMouseXImpl(); }
  static float GetMouseY() { return instance->GetMouseYImpl(); }

 protected:
  virtual bool IsKeyPressedImpl(int keycode) = 0;
  virtual bool IsMouseButtonPressedImpl(int keycode) = 0;
  virtual std::pair<float, float> GetMousePosImpl() = 0;
  virtual float GetMouseXImpl() = 0;
  virtual float GetMouseYImpl() = 0;

 private:
  static Input* instance;
};

}  // namespace hazel