/*
 * TextureRegion.h
 *
 *  Created on: 5 Jun 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTUREREGION_H_
#define TEXTUREREGION_H_

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

#include <fillwave/core/texturing/Texture2D.h>

namespace fillwave {

namespace core {
class TextureRegion;
}

typedef std::shared_ptr<core::TextureRegion> pTextureRegion;

namespace core {

/*! \class TextureRegion
 * \brief Texture2D part.
 */

class TextureRegion {
public:
    TextureRegion(pTexture texture,
                  GLfloat u1 = 0,
				      GLfloat v1 = 0,
                  GLfloat u2 = 1,
                  GLfloat v2 = 1);

    virtual ~TextureRegion();
    pTexture getTexture();
    GLfloat convertU(GLfloat u);
    GLfloat convertV(GLfloat v);

private:
    GLfloat mU1;
    GLfloat mU2;
    GLfloat mV1;
    GLfloat mV2;
    pTexture mTexture;
};

} /* core */
static pTextureRegion buildTextureRegion(pTexture texture,
                             GLfloat u1 = 0.0,
                             GLfloat v1 = 0.0,
                             GLfloat u2 = 1.0,
                             GLfloat v2 = 1.0) {
    return pTextureRegion (new core::TextureRegion(texture,
                                             u1,
                                             v1,
                                             u2,
                                             v2));
} /* core */
} /* fillwave */

#endif /* TEXTUREREGION_H_ */
