#pragma once
#include "hazel/log.h"

namespace hazel {

// Events in Hazel are currently blocking, meaning when an event occurs it
// immediately gets dispatched and must be dealt with right then an there.
// For the future, a better strategy might e to buffer events in an event bus
// and process them during the "event" part of the update stage.
enum class EventType {
  None = 0,

  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowMoved,

  AppTick,
  AppUpdate,
  AppRender,

  KeyPressed,
  KeyReleased,
  KeyTyped,

  MouseMoved,
  MouseScrolled,

  MouseButtonPressed,
  MouseButtonReleased
};

enum EventCategory {
  None = 0,
  EventCategoryApp = BIT(0),
  EventCategoryInput = BIT(1),
  EventCategoryKeyboard = BIT(2),
  EventCategoryMouse = BIT(3),
  EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type)                                           \
  static EventType GetStaticType() { return EventType::##type; }         \
  virtual EventType GetType() const override { return GetStaticType(); } \
  virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
  virtual int GetCategoryFlags() const override { return category; }

class HAZEL_API Event {
 public:
  virtual EventType GetType() const = 0;
  virtual const char* GetName() const = 0;
  virtual int GetCategoryFlags() const = 0;
  virtual std::string ToString() const { return GetName(); };

  bool IsInCategory(EventCategory category) {
    return GetCategoryFlags() & category;
  }

  bool handled = false;
};

class HAZEL_API EventDispatcher {
 public:
  EventDispatcher(Event& event) : event_(event) {}

  template <typename T, typename F>
  bool Dispatch(const F& func) {
    if (event_.GetType() == T::GetStaticType()) {
      event_.handled |= func(static_cast<T&>(event_));
      return true;
    }
    return false;
  }

 private:
  Event& event_;
};

template <typename OStream>
inline OStream& operator<<(OStream& os, const Event& e) {
  return os << e.ToString();
}

}  // namespace hazel
