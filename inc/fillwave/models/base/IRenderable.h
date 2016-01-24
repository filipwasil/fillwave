/*
 * IRenderable.h
 *
 *  Created on: Jan 23, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MODELS_BASE_IRENDERABLE_H_
#define INC_FILLWAVE_MODELS_BASE_IRENDERABLE_H_

#include <fillwave/OpenGL.h>
#include <fillwave/core/pipeline/Blending.h>

namespace fillwave {
namespace framework {

class IRenderer;

enum eRenderHandles {
	eRenderHandleVAO,
	eRenderHandleDiffuse,
	eRenderHandleNormal,
	eRenderHandleSpecular,
	eRenderHandlesSize
};

struct RenderData {
	GLenum mMode;
	GLsizei mFirst;
	GLsizei mCount;
	GLenum mDataType;
	GLvoid* mIndicesPointer;
	Blending mBlend;
	GLuint mHandles[eRenderHandlesSize];

	struct {
		GLbyte bVAO :1;
		GLbyte bIndexDraw :1;
		GLbyte bDiffuse :1;
		GLbyte bNormal :1;
		GLbyte bSpecular :1;
		GLbyte bBlending :1;
		GLbyte bIsContainer :1;
	} mStatus;
};

class IRenderable {
public:
	IRenderable(GLenum renderMode);
	virtual ~IRenderable() = default;

	RenderData getRenderData();

	virtual void updateRenderer(IRenderer& renderer) = 0;

protected:
//	virtual void updateRendererData() = 0;
	RenderData mRenderData;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MODELS_BASE_IRENDERABLE_H_ */
