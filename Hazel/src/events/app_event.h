#ifndef _APP_EVENT_H_
#define _APP_EVENT_H_

#include <sstream>

#include "event.h"

namespace hazel {

class HAZEL_API WindowResizeEvent : public Event {
 public:
  WindowResizeEvent(size_t width, size_t height)
      : width_(width), height_(height) {}

  inline size_t GetWidth() const { return width_; }
  inline size_t GetHeight() const { return height_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << width_ << ", " << height_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(WindowResize)
  EVENT_CLASS_CATEGORY(EventCategoryApp)

 private:
  size_t width_, height_;
};

class HAZEL_API WindowCloseEvent : public Event {
 public:
  WindowResizeEvent(size_t width, size_t height)
      : width_(width), height_(height) {}

  inline size_t GetWidth() const { return width_; }
  inline size_t GetHeight() const { return height_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << width_ << ", " << height_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(WindowResize)
  EVENT_CLASS_CATEGORY(EventCategoryApp)

 private:
  size_t width_, height_;
};

}  // namespace hazel

#endif
