/*
 * Texture.h
 *
 *  Created on: 28 Mar 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE_2D_H_
#define TEXTURE_2D_H_

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

/*! \class Texture2D
 * \brief Single GLSL 2D Texture object.
 */

class Texture2D: public Texture {
public:
   Texture2D(puTexture2DFile file,
             ParameterList& parameters,
             GLuint howMany = 1);

   virtual ~Texture2D();

   void generateMipMaps();

   void sendData(Texture2DFileData data = nullptr);

   virtual void reload();

   void log();

   static void unbind2DTexture(GLint textureUnit);

   static void unbind2DTextures();

   puTexture2DFile mFile;

protected:
   ParameterList mParameters;
};

} /* core */
typedef std::shared_ptr<core::Texture2D> pTexture2D;
} /* fillwave */

#endif /* TEXTURE_2D_H_ */
