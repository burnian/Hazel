#pragma once
#include "event.h"
#include "hazel/key_codes.h"

namespace hazel {

class HAZEL_API KeyEvent : public Event {
 public:
  int GetKeyCode() const { return key_code_; }

  EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

 protected:
  KeyEvent(const KeyCode key_code) : key_code_(key_code) {}

  KeyCode key_code_;
};

class HAZEL_API KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(const KeyCode key_code, bool is_repeat = false)
      : KeyEvent(key_code), is_repeat_(is_repeat) {}

  bool IsRepeat() const { return is_repeat_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << key_code_ << " (repeat = " << is_repeat_
       << ")";
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPressed)

 private:
  bool is_repeat_;
};

class HAZEL_API KeyReleasedEvent : public KeyEvent {
 public:
  KeyReleasedEvent(const KeyCode key_code) : KeyEvent(key_code) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << key_code_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPressed)
};

class HAZEL_API KeyTypedEvent : public KeyEvent {
 public:
  KeyTypedEvent(const KeyCode key_code) : KeyEvent(key_code) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << key_code_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyTyped)
};

}  // namespace hazel
