/*
 * Impostor.cpp
 *
 *  Created on: May 10, 2014
 *      Author: filip
 */

#include <fillwave/models/Impostor.h>
#include <fillwave/Fillwave.h>

#include <fillwave/Log.h>

FLOGINIT("Impostor", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Impostor::Impostor(
		Engine* engine,
		GLfloat lifetime,
		GLfloat size,
		pTexture texture,
		GLenum blendingSource,
		GLenum blendingDestination)
		:
				Finishable(lifetime),
				mTexture(texture),
				mSampler(engine->storeSO(FILLWAVE_DIFFUSE_UNIT)),
				mSize(size) {
	mBlending.mSrc = blendingSource;
	mBlending.mDst = blendingDestination;
}

void Impostor::coreDraw() {
	if (mTexture) {
		mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
	}

	glEnable(GL_BLEND);
	glBlendFunc(mBlending.mSrc, mBlending.mDst);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisable(GL_BLEND);
	core::Texture2D::unbind2DTextures();
}

bool Cursor::getRenderData(RenderData& renderData) {
	RenderData data;
	data.mBlend = mBlending;
	data.mCount = 4;
	data.mDataType = GL_NONE;
	data.mFirst = 0;
	data.mHandles[RenderData::eRenderHandleProgram] = mProgram->getHandle();
	data.mHandles[RenderData::eRenderHandleSampler] = mSampler->getHandle();
	data.mHandles[RenderData::eRenderHandleVAO] = 0;
	data.mHandles[RenderData::eRenderHandleDiffuse] = mTexture->getHandle();
	data.mHandles[RenderData::eRenderHandleNormal] = 0;
	data.mHandles[RenderData::eRenderHandleSpecular] = 0;
	data.mIndicesPointer = 0;
	data.mMode = GL_TRIANGLE_STRIP;
   data.mStatus.bBlending = 1;

   data.mStatus = 00100100b; // blending, diffuse

	return true;
}

} /* framework */
} /* fillwave */
