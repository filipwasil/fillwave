/*
 * TextureRegion.cpp
 *
 *  Created on: 5 Jun 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwavel@gmail.com
 *
 */

#include <fillwave/core/texturing/TextureRegion.h>

namespace fillwave {
namespace core {

TextureRegion::TextureRegion(pTexture texture,
                             GLfloat u1,
                             GLfloat v1,
                             GLfloat u2,
                             GLfloat v2):mU1(u1),
                                         mV1(v1),
                                         mU2(u2),
                                         mV2(v2),
                                         mTexture(texture){

}

TextureRegion::~TextureRegion() {

}

pTexture TextureRegion::getTexture() {
   return mTexture;
}

GLfloat TextureRegion::convertU(GLfloat u) {
   return mU1 + u*( mU2 - mU1 );
}

GLfloat TextureRegion::convertV(GLfloat v) {
   return mV1 + v*( mV2 - mV1 );
}

} /* core */
} /* fillwave */
