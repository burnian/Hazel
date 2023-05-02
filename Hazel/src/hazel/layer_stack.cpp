#include "hazel_pch.h"
#include "layer_stack.h"


namespace hazel {

LayerStack::LayerStack() { layer_insert_idx_ = 0; }

LayerStack::~LayerStack() {
  for (Layer* layer : layers_) delete layer;
}

void LayerStack::PushLayer(Layer* layer) {
  layers_.emplace(layers_.begin() + layer_insert_idx_, layer);
  ++layer_insert_idx_;
}

void LayerStack::PushOverlay(Layer* overlay) { layers_.emplace_back(overlay); }

void LayerStack::PopLayer(Layer* layer) {
  auto it = std::find(layers_.begin(), layers_.end(), layer);
  if (it != layers_.end()) {
    layers_.erase(it);
    --layer_insert_idx_;
  }
}

void LayerStack::PopOverlay(Layer* overlay) {
  auto it = std::find(layers_.begin(), layers_.end(), overlay);
  if (it != layers_.end()) layers_.erase(it);
}

}  // namespace hazel