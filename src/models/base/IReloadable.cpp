/*
 * IReloadable.cpp
 *
 *  Created on: May 24, 2015
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


#include <fillwave/Fillwave.h>


namespace fillwave {
namespace framework {

IReloadable::IReloadable(Engine *engine, core::VertexArray *vao)
    : mVAO (vao ? vao : engine->storeVAO (this)), mSampler (engine->storeSO (FILLWAVE_DIFFUSE_UNIT)) {
  mSampler->bind ();
  mSampler->setParameter (GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  mSampler->setParameter (GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  mSampler->setParameter (GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
}

void IReloadable::reload() {
  initBuffers ();
  initPipeline ();
  initVBO ();
  initVAO ();
  initUniformsCache ();
}

} /* framework */
} /* fillwave */
