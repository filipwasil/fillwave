/*
 * Vertex.h
 *
 *  Created on: 29 May 2015
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <fillwave/OpenGL.h>

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
#endif /* VERTEX_H_ */
