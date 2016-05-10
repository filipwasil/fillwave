/*
 * LightPoint.h
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

#ifndef LIGHTPOINT_H_
#define LIGHTPOINT_H_

#include <fillwave/core/rendering/Texture3DRenderable.h>
#include <fillwave/space/CameraPerspective.h>
#include <fillwave/models/shapes/Sphere.h>
#include <fillwave/space/base/Light.h>

#include <map>

namespace fillwave {
class Engine;
namespace framework {

/*! \class LightPoint
 * \brief Not used.
 */

class LightPoint: public Light {
 public:
	LightPoint(
	   core::Texture3DRenderable* shadowTexture,
	   glm::vec3 position,
	   glm::vec4 intensity,
	   Moveable* followed = nullptr);

	virtual ~LightPoint() = default;

	core::Texture3DRenderable* getShadowTexture();

	CameraPerspective* getShadowCamera(GLenum id);

	void updateShadowCamera();

 protected:
	core::Texture3DRenderable* mShadowTexture;
	std::map<GLenum, puCameraPerspective> mFaceCameras;

 private:
	Sphere mSphere;
};

} /* framework */
typedef std::unique_ptr<framework::LightPoint> puLightPoint;
} /* fillwave */

#endif /* LIGHTPOINT_H_ */
