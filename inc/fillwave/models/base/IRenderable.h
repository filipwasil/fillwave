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

class IRenderable {
public:
	IRenderable(GLenum renderMode);
	virtual ~IRenderable() = default;

	enum eRenderHandles {
		eProgram = 0,
		eVAO,
		eIBO,
		eVBO,
		eDiffuse,
		eNormal,
		eSpecular,
		eRenderHandlesSize
	};

	virtual void updateRenderer(IRenderer& renderer) = 0;

protected:
	GLenum mRenderMode;
	GLsizei mRenderFirst;
	GLsizei mRenderCount;
	GLenum mRenderDataType;
	GLvoid* mRenderIndicesPointer;
	Blending mBlendSource, mBlendDst;
	GLuint mRenderData[eRenderHandlesSize];

private:
	struct {
		GLbyte bVAO :1;
		GLbyte bIBO :1;
		GLbyte bVBO :1;
		GLbyte bDiffuse :1;
		GLbyte bNormal :1;
		GLbyte bSpecular :1;
		GLbyte bBlending :1;
		GLbyte bIsContainer :1;
	} mDrawStatus;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MODELS_BASE_IRENDERABLE_H_ */
