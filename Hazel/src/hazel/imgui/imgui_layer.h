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

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnEvent(Event& event) override;
  virtual void OnImGuiRender() override;

  void Begin();
  void End();

  // void BlockEvents(bool block) { m_BlockEvents = block; }

  // void SetDarkThemeColors();

  // uint32_t GetActiveWidgetID() const;

 private:
  bool block_events_ = true;
};

}  // namespace hazel