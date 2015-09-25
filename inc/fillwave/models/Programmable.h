/*
 * Programmable.h
 *
 *  Created on: May 15, 2015
 *      Author: filip
 */

#ifndef SRC_MODELS_PROGRAMMABLE_H_
#define SRC_MODELS_PROGRAMMABLE_H_

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

#include <fillwave/models/Entity.h>
#include <fillwave/effects/Effect.h>

namespace fillwave {
namespace models {

/*! \class Programmable
 * \brief Entity for which is it possible to add/remove Effect objects.
 */

class Programmable: public Entity {
public:
   Programmable(pProgram program);

   virtual ~Programmable();

   /* Effects */
   void addEffect(pEffect effect);

   void removeEffect(pEffect effect);

   void drawWithEffects(space::Camera& camera);

   void drawWithEffectsDR(space::Camera& camera);

protected:
   pProgram mProgram;

   std::vector<pEffect> mEffects;
};

} /* models */
} /* fillwave */

#endif /* SRC_MODELS_PROGRAMMABLE_H_ */
