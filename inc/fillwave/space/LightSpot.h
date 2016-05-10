/*
 * LightSpot.h
 *
 *  Created on: Nov 30, 2014
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

#ifndef LIGHTSPOT_H_
#define LIGHTSPOT_H_

#include <fillwave/management/TextureSystem.h>
#include <fillwave/space/base/Light.h>
#include <fillwave/space/CameraPerspective.h>

namespace fillwave {
namespace framework {

/*! \class LightSpot
 * \brief Light implementing directional torch.
 */

class LightSpot: public Light {
 protected:
	core::Texture2DRenderable* mShadowTexture;
	puCameraPerspective mShadowCamera;

 public:
	LightSpot(
	   core::Texture2DRenderable* shadowTexture,
	   glm::vec3 position,
	   glm::quat rotation,
	   glm::vec4 intensity,
	   Moveable* followed = nullptr);

	virtual ~LightSpot() = default;

	core::Texture2DRenderable* getShadowTexture();

	CameraPerspective* getShadowCamera();

	void updateShadowCamera();

	void log();

};

} /* framework */
typedef std::unique_ptr<framework::LightSpot> puLightSpot;
} /* fillwave */

#endif /* LIGHTSPOT_H_ */
