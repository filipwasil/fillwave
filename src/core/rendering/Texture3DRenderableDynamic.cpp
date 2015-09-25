/*
 * Texture3DRenderableDynamic.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: filip
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
 * fillwave@gmail.com
 *
 */

#include <fillwave/core/rendering/Texture3DRenderableDynamic.h>

namespace fillwave {
namespace core {

Texture3DRenderableDynamic::Texture3DRenderableDynamic(Texture2DFile& filePosX,
                                                       Texture2DFile& fileNegX,
                                                       Texture2DFile& filePosY,
                                                       Texture2DFile& fileNegY,
                                                       Texture2DFile& filePosZ,
                                                       Texture2DFile& fileNegZ,
                                                       ParameterList& parameters,
                                                       pTexture2DRenderable texture2D,
                                                       pProgram program)
:Texture3DRenderable(filePosX,
 fileNegX,
 filePosY,
 fileNegY,
 filePosZ,
 fileNegZ,
 texture2D,
 parameters),
 mProgram(program),
 mTimePassed(0.0f) {
   setAttachment(GL_COLOR_ATTACHMENT0);
}

Texture3DRenderableDynamic::~Texture3DRenderableDynamic() {

}

} /* core */
} /* fillwave */
