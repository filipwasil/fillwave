/*
 * Material.h
 *
 *  Created on: 27 sty 2015
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

#ifndef SRC_MODELS_MATERIAL_H_
#define SRC_MODELS_MATERIAL_H_

#include <fillwave/Math.h>
#include <fillwave/Assets.h>

namespace fillwave {
namespace framework {

/*! \class Material
 * \brief Per mesh material info.
 */

class Material {
 public:
	Material();
	virtual ~Material() = default;

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
	Material(const aiMaterial* material);
#else
	Material(const tinyobj::material_t& material);
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

	const glm::vec4& getAmbient() const;
	const glm::vec4& getDiffuse() const;
	const glm::vec4& getSpecular() const;

 private:
	glm::vec4 mAmbient;
	glm::vec4 mDiffuse;
	glm::vec4 mSpecular;
};

} /* framework */
} /* fillwave */

#endif /* SRC_MODELS_MATERIAL_H_ */
