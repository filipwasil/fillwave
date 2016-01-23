/*
 * IRenderable.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: filip
 */

#include <fillwave/models/base/IRenderable.h>

namespace fillwave {
namespace framework {

IRenderable::IRenderable(GLenum renderMode) {
	mRenderData.mMode = renderMode;
	mRenderData.mFirst = 0;
	mRenderData.mCount = 0;
	mRenderData.mDataType = GL_UNSIGNED_INT;
	mRenderData.mIndicesPointer = reinterpret_cast<GLvoid*>(0);
}

RenderData IRenderable::getRenderData() {
	return mRenderData;
}

} /* namespace framework */
} /* namespace fillwave */
