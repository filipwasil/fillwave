/*
 * Texture3DRenderableDynamic.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: filip
 */

#include <fillwave/core/rendering/Texture3DRenderableDynamic.h>

namespace fillwave {
namespace core {

Texture3DRenderableDynamic::Texture3DRenderableDynamic(
    Texture2DFile* filePosX,
    Texture2DFile* fileNegX,
    Texture2DFile* filePosY,
    Texture2DFile* fileNegY,
    Texture2DFile* filePosZ,
    Texture2DFile* fileNegZ,
    ParameterList& parameters,
    core::Texture2DRenderable* texture2D,
    pProgram program) :
	Texture3DRenderable(filePosX, fileNegX, filePosY, fileNegY, filePosZ,
	                    fileNegZ, texture2D, parameters),
	mProgram(program),
	mTimePassed(0.0f) {
	setAttachment(GL_COLOR_ATTACHMENT0);
}

} /* core */
} /* fillwave */
