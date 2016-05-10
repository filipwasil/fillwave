/*
 * Camera.h
 *
 *  Created on: May 7, 2014
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

#ifndef CAMERA_H_
#define CAMERA_H_

#include <fillwave/models/base/Moveable.h>
#include <memory>

namespace fillwave {
namespace framework {

/*! \class ICamera
 * \brief Stores camera view parameters.
 */

class ICamera: public Moveable {
 public:
	ICamera();

	ICamera(glm::vec3, glm::quat rotation);

	virtual ~ICamera() = default;

	void update();
	void updateView();

	glm::mat4 getEye();
	glm::mat4 getProjection();
	glm::mat4 getViewProjection();

	virtual void updateProjection() = 0;
	virtual GLfloat getProjectionNearPlane() = 0;
	virtual GLfloat getProjectionFarPlane() = 0;
	virtual void log() const;

 protected:
	glm::mat4 mCameraMatrix;
	glm::mat4 mProjectionMatrix;

	GLboolean mRefreshView;
	GLboolean mRefreshProjection;
};
} /* framework */
typedef std::unique_ptr<framework::ICamera> puICamera;
} /* fillwave */

#endif /* CAMERA_H_ */
