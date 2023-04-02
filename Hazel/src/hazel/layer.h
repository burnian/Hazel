#pragma once
#include "hazel/events/event.h"
#include "hazel/core.hpp"

namespace hazel {

class HAZEL_API Layer {
 public:
  Layer(const std::string& name = "Layer");
  virtual ~Layer();

  virtual void OnAttach(){};
  virtual void OnDetach(){};
  virtual void OnUpdate(){};
  virtual void OnEvent(Event& event){};

  inline const std::string& GetName() const { return debug_name_; }

 protected:
  std::string debug_name_;
};

}  // namespace hazel
