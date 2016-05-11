/*
 * Bone.h
 *
 *  Created on: Jun 23, 2014
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

#ifndef BONE_H_
#define BONE_H_

#include <fillwave/models/animations/Hinge.h>
#include <fillwave/Assets.h>

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

namespace fillwave {
namespace framework {
class Bone;
}

typedef std::unique_ptr<framework::Bone> puBone;

namespace framework {

/*! \class Bone
 * \brief Hinge used by Animator to populate bone transformations.
 */

class Bone final: public Hinge {
 public:
	Bone(aiBone* assimpBone);
	~Bone() = default;

	std::string getName() const;
	glm::mat4 getOffsetMatrix() const;
	glm::mat4 getGlobalOffsetMatrix() const;

	void setName(std::string name);
	void setOffsetMatrix(glm::mat4 m);
	void setGlobalOffsetMatrix(glm::mat4 m);

	void log();

 private:
	std::string mName;
	glm::mat4 mOffsetMatrix;
	glm::mat4 mGlobalOffsetMatrix;
};

} /* framework */
} /* fillwave */

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

#endif /* BONE_H_ */
