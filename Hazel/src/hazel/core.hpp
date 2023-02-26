#pragma once
#include "pch.h"

#ifdef HAZEL_PLATFORM_WINDOWS

#ifdef HAZEL_BUILD_DLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif

#else
#error Hazel only support Windows!
#endif

#define BIT(x) (1 << x)

namespace hazel {

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace hazel
