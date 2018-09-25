#pragma once

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <flw/OpenGL.h>

#include <type_traits>
#include <iostream>

#include <stddef.h>

namespace flw {
namespace flc {

//template <class... Ts>
//struct Vertex {
//
//};
//
//template <class T, class... Ts>
//struct Vertex<T, Ts...> : Vertex<Ts...> {
//  Vertex(T t, Ts... ts) : Vertex<Ts...>(ts...), mAttribute(t) {}
//
//  T mAttribute;
//};
//
//template <size_t k,  class T,class... Ts>
//struct AttributeTypeHolder {};
//
//template <class T, class... Ts>
//struct AttributeTypeHolder<0, Vertex<T, Ts...> > {
//  typedef T type;
//};
//
//template <size_t k, class T, class... Ts>
//struct AttributeTypeHolder<k, Vertex<T, Ts...> > {
//  typedef typename AttributeTypeHolder<k - 1, Vertex<Ts...>>::type type;
//};
//
//template <size_t k = 0, class... Ts>
//typename std::enable_if<
//    k == 0, typename AttributeTypeHolder<0, Vertex<Ts...>>::type&>::type
//getVertex(Vertex<Ts...>& t) {
//  return t.mAttribute;
//}
//
//template <size_t k = 0, class T, class... Ts>
//typename std::enable_if<
//    k != 0, typename AttributeTypeHolder<k, Vertex<T, Ts...>>::type&>::type
//getVertex(Vertex<T, Ts...>& t) {
//   Vertex<Ts...>& base = t;
//   return getVertex<k - 1>(base);
//}
//
//template <int k = 0, class... Ts>
//typename std::enable_if<
//   k == 0, int>::type
//getAttributeOffset(Vertex<Ts...>& t, int size = 0) {
//   return size;
//}
//
//template <int k = 0, class T, class... Ts>
//typename std::enable_if<
//   k != 0, int>::type
//getAttributeOffset(Vertex<T, Ts...>& t, int size = 0) {
//   Vertex<Ts...>& base = t;
//   if (sizeof(base) == 1) {
//      return size + sizeof(t);
//   } else {
//      return getAttributeOffset<k - 1>(base, size + sizeof(t) - sizeof(base));
//   }
//}

/*
 * How to:
 *
 * Vertex<int, float, char, glmL::mat4> vertexTuple;
 *
 * ------------- VALUES ---------------
 *
 * int integer = get<0>(vertexTuple);
 *
 * float floatingPoint = get<1>(vertexTuple);
 *
 * get<2>(vertexTuple) = 'a';
 *
 * get<3>(vertexTuple) = glm::mat4(1.0);
 *
 * ------------- OFFSETS --------------
 *
 * int offsetInt = getOffset<0>(vertexTuple);
 *
 * int offsetFloat = getOffset<1>(vertexTuple);
 *
 * int offsetChar = getOffset<2>(vertexTuple);
 *
 * int offsetMatrix = getOffset<3>(vertexTuple);
 *
 */

} /* flc */
} /* flw */
