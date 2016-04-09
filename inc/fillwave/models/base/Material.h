/*
 * Material.h
 *
 *  Created on: 27 sty 2015
 *      Author: Filip Wasil
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
	Material(const fMaterial* material);
	virtual ~Material() = default;
	glm::vec4 getAmbient() const;
	glm::vec4 getDiffuse() const;
	glm::vec4 getSpecular() const;

 private:
	glm::vec4 mAmbient;
	glm::vec4 mDiffuse;
	glm::vec4 mSpecular;
};

} /* framework */
} /* fillwave */

#endif /* SRC_MODELS_MATERIAL_H_ */
