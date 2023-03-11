#include "hazel_pch.h"
#include "window.h"


#ifdef HAZEL_PLATFORM_WINDOWS
#include "platform/windows/windows_window.h"
#endif

namespace hazel {

Scope<Window> Window::Create(const WindowProps& props) {
#ifdef HAZEL_PLATFORM_WINDOWS
  return CreateScope<WindowsWindow>(props);
#else
  CORE_ASSERT(false, "Unknown platform!");
  return nullptr;
#endif
}

}  // namespace hazel