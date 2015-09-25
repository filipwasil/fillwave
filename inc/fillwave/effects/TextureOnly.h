/*
 * TextureOnly.h
 *
 *  Created on: Dec 5, 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTUREONLY_H_
#define TEXTUREONLY_H_

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

/*! \class TextureOnly
 * \brief Effect to color the model with texture only (exclude light effects and shadows).
 */

class TextureOnly: public Effect {
public:
   TextureOnly();
   virtual ~TextureOnly();
   void preDrawAction(core::Program* program);
   void postDrawAction(core::Program* program);
   void stopAction(core::Program* program);
   void startAction(core::Program* program);
   };

} /* effects*/
} /* fillwave */

#endif /* TEXTUREONLY_H_ */
