#pragma once
#include "hazel/core.hpp"
#include "hazel/events/event.h"

namespace hazel {

class HAZEL_API Layer {
 public:
  Layer(const std::string& name = "Layer");
  virtual ~Layer() = default;

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate() {}
  virtual void OnEvent(Event& event) {}
  virtual void OnImGuiRender() {}

  inline const std::string& GetName() const { return debug_name_; }

 protected:
  std::string debug_name_;
};

}  // namespace hazel
