/*
 * RenderData.h
 *
 *  Created on: Jan 24, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MODELS_BASE_RENDERITEM_H_
#define INC_FILLWAVE_MODELS_BASE_RENDERITEM_H_

#include <fillwave/OpenGL.h>
#include <fillwave/core/pipeline/Blending.h>

namespace fillwave {
namespace framework {
/*! \struct RenderItem
 * \brief Single draw item structure
 */

struct RenderItem {
	enum eRenderHandles {
		eRenderHandleProgram,
		eRenderHandleVAO,
		eRenderHandleDiffuse,
		eRenderHandleNormal,
		eRenderHandleSpecular,
		eRenderHandleSampler,
		eRenderHandlesSize
	};

	union  {
		GLubyte mRenderStatus;
		struct {
			GLubyte bVAO :1;
			GLubyte bIndexDraw :1;
			GLubyte bDiffuse :1;
			GLubyte bNormal :1;
			GLubyte bSpecular :1;
			GLubyte bBlending :1;
			GLubyte bIsContainer :1;
			GLubyte bEmpty :1;
		} mStatus;
	};

	GLenum mMode;
	GLsizei mFirst;
	GLsizei mCount;
	GLenum mDataType;
	GLvoid* mIndicesPointer;
	Blending mBlend;
	GLuint mHandles[eRenderHandlesSize];
};

} /* namespace framework */
} /* namespace fillwave */


#endif /* INC_FILLWAVE_MODELS_BASE_RENDERITEM_H_ */
