/*
 * Material.h
 *
 *  Created on: 27 sty 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_MODELS_MATERIAL_H_
#define SRC_MODELS_MATERIAL_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/Math.h>
#include <fillwave/Assets.h>

namespace fillwave {
namespace models {

/*! \class Material
 * \brief Per mesh material info.
 */

class Material {
public:
   Material();
   Material(const fMaterial* material);
   virtual ~Material();
   glm::vec4 getAmbient();
   glm::vec4 getDiffuse();
   glm::vec4 getSpecular();

private:
   glm::vec4 mAmbient;
   glm::vec4 mDiffuse;
   glm::vec4 mSpecular;
};

} /* models */
} /* fillwave */

#endif /* SRC_MODELS_MATERIAL_H_ */
