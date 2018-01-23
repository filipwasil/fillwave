/*
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Crater C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are not permitted.
 */

#pragma once

#include <memory>
#include <functional>

namespace flw {

template <class T>
using pu = std::unique_ptr<T>;

template <class T>
using ps = std::shared_ptr<T>;

template <typename T, typename... Args>
pu<T> make_pu(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <class T>
using Callback = std::function<T>;

} /* flw */
