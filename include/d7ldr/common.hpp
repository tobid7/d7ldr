#pragma once

#include <3ds.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>

#ifndef PD_SMART_CTOR
#define PD_SMART_CTOR(type)                                      \
  using Ref = std::shared_ptr<type>;                             \
  template <typename... args>                                    \
  static Ref New(args&&... cargs) {                              \
    return std::make_shared<type>(std::forward<args>(cargs)...); \
  }
#endif