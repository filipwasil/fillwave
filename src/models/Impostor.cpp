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

bool Cursor::getRenderItem(RenderItem& item) {
	item.mBlend = mBlending;
	item.mCount = 4;
	item.mDataType = GL_NONE;
	item.mFirst = 0;
	item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle();
	item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle();
	item.mHandles[RenderItem::eRenderHandleVAO] = 0;
	item.mHandles[RenderItem::eRenderHandleDiffuse] = mTexture->getHandle();
	item.mHandles[RenderItem::eRenderHandleNormal] = 0;
	item.mHandles[RenderItem::eRenderHandleSpecular] = 0;
	item.mIndicesPointer = 0;
	item.mMode = GL_TRIANGLE_STRIP;
   item.mStatus.bBlending = 1;
   item.mRenderStatus = 0x24; // blending, diffuse
	return true;
}

} /* framework */
} /* fillwave */
