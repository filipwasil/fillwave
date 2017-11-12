/*
 * Engine.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: filip
 */

#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

FLOGINIT("Engine", FERROR | FFATAL | FINFO | FDEBUG)

namespace flw {

struct Engine::EngineImpl {
  EngineImpl() = default;

  ~EngineImpl() = default;
};

Engine::Engine(GLint /*argc*/, GLchar *const /*argv*/[]) {
  // nothing
}

Engine::~Engine() {
  // nothing
}

flc::Texture2D *Engine::storeTexture(const std::string & /*texturePath*/, flf::ECompression /*compression*/) {
  return nullptr;
}

} /* flw */
