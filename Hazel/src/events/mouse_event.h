#ifndef _MOUSE_EVENT_H_
#define _MOUSE_EVENT_H_

#include <sstream>

#include "events/event.h"
#include "hazel/mouse_codes.h"

namespace hazel {

class HAZEL_API MouseMovedEvent : public Event {
 public:
  MouseMovedEvent(const float x, const float y) : mouse_x_(x), mouse_y_(y) {}

  float GetX() const { return mouse_x_; }
  float GetY() const { return mouse_y_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << mouse_x_ << ", " << mouse_y_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseMoved)
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

 private:
  float mouse_x_, mouse_y_;
};

class HAZEL_API MouseScrolledEvent : public Event {
 public:
  MouseScrolledEvent(const float x_offset, const float y_offset)
      : x_offset_(x_offset), y_offset_(y_offset) {}

  float GetXOffset() const { return x_offset_; }
  float GetYOffset() const { return y_offset_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseScrolled)
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
 private:
  float x_offset_, y_offset_;
};

class HAZEL_API MouseButtonEvent : public Event {
 public:
  MouseCode GetMouseCode() const { return mouse_code_; }

  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput |
                       EventCategoryMouseButton)
 protected:
  MouseButtonEvent(const MouseCode mouse_code) : mouse_code_(mouse_code) {}

  MouseCode mouse_code_;
};

class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  MouseButtonPressedEvent(const MouseCode mouse_code)
      : MouseButtonEvent(mouse_code) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << mouse_code_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonPressed)
};

class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  MouseButtonReleasedEvent(const MouseCode mouse_code)
      : MouseButtonEvent(mouse_code) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << mouse_code_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonReleased)
};

}  // namespace hazel
#endif
