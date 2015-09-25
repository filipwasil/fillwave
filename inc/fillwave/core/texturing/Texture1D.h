/*
 * Texture1D.h
 *
 *  Created on: Sep 10, 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE1D_H_
#define TEXTURE1D_H_

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

#include <fillwave/core/texturing/Texture.h>

namespace fillwave {
namespace core {

/*! \class Texture1D
 * \brief Not used.
 */

class Texture1D: public Texture {
public:
   Texture1D(ParameterList& parameters);
   virtual ~Texture1D();
   void log();
   };

} /* core */
typedef std::shared_ptr<core::Texture1D> pTexture1D;
} /* fillwave */

#endif /* TEXTURE1D_H_ */
