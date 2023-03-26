#pragma once
#include <vector>

#include "hazel/core.hpp"
#include "layer.h"

namespace hazel {

class HAZEL_API LayerStack {
 public:
  LayerStack();
  ~LayerStack();

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);
  void PopLayer(Layer* layer);
  void PopOverlay(Layer* overlay);

  std::vector<Layer*>::iterator begin() { return layers_.begin(); }
  std::vector<Layer*>::iterator end() { return layers_.end(); }
  size_t size() { return layers_.size(); }

 private:
  std::vector<Layer*> layers_;
  std::vector<Layer*>::iterator layer_itr_;  // layer_insert_;
};

}  // namespace hazel