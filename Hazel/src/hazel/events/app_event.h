#pragma once
#include "event.h"

namespace hazel {

class HAZEL_API WindowResizeEvent : public Event {
 public:
  WindowResizeEvent(unsigned int width, unsigned int height)
      : width_(width), height_(height) {}

  unsigned int GetWidth() const { return width_; }
  unsigned int GetHeight() const { return height_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << width_ << ", " << height_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(WindowResize)
  EVENT_CLASS_CATEGORY(EventCategoryApp)

 private:
  unsigned int width_, height_;
};

class HAZEL_API WindowCloseEvent : public Event {
 public:
  WindowCloseEvent() = default;

  EVENT_CLASS_TYPE(WindowClose)
  EVENT_CLASS_CATEGORY(EventCategoryApp)
};

class HAZEL_API AppTickEvent : public Event {
 public:
  AppTickEvent() = default;

  EVENT_CLASS_TYPE(AppTick)
  EVENT_CLASS_CATEGORY(EventCategoryApp)
};

class HAZEL_API AppUpdateEvent : public Event {
 public:
  AppUpdateEvent() = default;

  EVENT_CLASS_TYPE(AppUpdate)
  EVENT_CLASS_CATEGORY(EventCategoryApp)
};

class HAZEL_API AppRenderEvent : public Event {
 public:
  AppRenderEvent() = default;

  EVENT_CLASS_TYPE(AppRender)
  EVENT_CLASS_CATEGORY(EventCategoryApp)
};

}  // namespace hazel
