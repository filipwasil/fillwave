/*
 * IRenderable.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: filip
 */

#include <fillwave/models/base/IRenderable.h>

namespace fillwave {
namespace framework {

IRenderable::IRenderable(GLenum renderMode)
:
		mRenderMode(renderMode),
		mRenderFirst(0),
		mRenderCount(0),
		mRenderDataType(GL_UNSIGNED_INT),
		mRenderIndicesPointer(reinterpret_cast<GLvoid*>(0)) {

}

} /* namespace framework */
} /* namespace fillwave */
