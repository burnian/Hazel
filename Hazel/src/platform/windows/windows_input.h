#pragma once

#include "hazel/input.h"

namespace hazel {

class WindowsInput : public Input {
 protected:
  virtual bool IsKeyPressedImpl(int keycode) override;
  virtual bool IsMouseButtonPressedImpl(int button) override;
  virtual std::pair<float, float> GetMousePosImpl() override;
  virtual float GetMouseXImpl() override;
  virtual float GetMouseYImpl() override;
};

}  // namespace hazel
