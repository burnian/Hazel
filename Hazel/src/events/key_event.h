#ifndef _KEY_EVENT_H_
#define _KEY_EVENT_H_

#include <sstream>

#include "event.h"

namespace hazel {
class HAZEL_API KeyEvent : public Event {
 public:
  inline int GetKeyCode() const { return key_code_; }

  EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

 protected:
  KeyEvent(int key_code) : key_code_(key_code) {}

  int key_code_;
};

class HAZEL_API KeyPressedEvent :public KeyEvent {
  public:
    KeyPressedEvent(int key_code,int repeat_count):KeyEvent(key_code),repeat_count_(repeat_count){}

    inline int GetRepeatCount()const{return repeat_count_;}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << key_code_ << " (" << repeat_count_<<" repeats)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPressed)

  private:
    int repeat_count_;
};

class HAZEL_API KeyReleasedEvent :public KeyEvent {
  public:
    KeyPressedEvent(int key_code,int repeat_count):KeyEvent(key_code),repeat_count_(repeat_count){}

    inline int GetRepeatCount()const{return repeat_count_;}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << key_code_ << " (" << repeat_count_<<" repeats)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPressed)

  private:
    int repeat_count_;
};

}  // namespace hazel

#endif
