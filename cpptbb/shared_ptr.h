/*
 * MIT License
 *
 * Copyright (c) 2021 André Reis
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef INCLUDE_CPPTBB_SHARED_PTR_H
#define INCLUDE_CPPTBB_SHARED_PTR_H

#include <memory.h>
#include "tbb/scalable_allocator.h"

namespace cpptbb {

template <typename TypeT,
          typename ... Args>
std::shared_ptr<TypeT> make_shared(Args ... args) {
  auto scalable_ptr = std::shared_ptr<TypeT>(
      reinterpret_cast<TypeT*>(scalable_malloc(sizeof(TypeT))),
      scalable_free);
  TypeT stack_temp(args...);
  memcpy(scalable_ptr.get(), &stack_temp, sizeof(TypeT));
  return scalable_ptr;
}

template <typename TypeT>
std::shared_ptr<TypeT> make_shared_raw(size_t number_of_elements) {
  return std::shared_ptr<TypeT>(
      reinterpret_cast<TypeT*>(scalable_malloc(number_of_elements * sizeof(TypeT))),
      scalable_free);
}

}  // namespace cpptbb

#endif  // INCLUDE_CPPTBB_SHARED_PTR_H
