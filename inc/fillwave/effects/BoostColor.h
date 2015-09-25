/*
 * BoostColor.h
 *
 *  Created on: Dec 5, 2014
 *      Author: Filip Wasil
 */

#ifndef BOOSTCOLOR_H_
#define BOOSTCOLOR_H_

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

#include <fillwave/effects/Effect.h>

namespace fillwave {
namespace effects {

/*! \class BoostColor
 * \brief Effect to boost the models color.
 */

class BoostColor: public Effect {
public:
   BoostColor(GLfloat boost = 1.0f);
   virtual ~BoostColor();
   void preDrawAction(core::Program* program);
   void postDrawAction(core::Program* program);
   void stopAction(core::Program* program);
   void startAction(core::Program* program);

private:
   GLfloat mBoost;
};

} /* effects*/
} /* fillwave */

#endif /* BOOSTCOLOR_H_ */
