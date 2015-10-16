/*
 * PostProcessingPass.h
 *
 *  Created on: 4 mar 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_OPERATIONS_POSTPROCESSINGPASS_H_
#define SRC_OPERATIONS_POSTPROCESSINGPASS_H_

#include <fillwave/core/pipeline/Program.h>
#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>
#include <fillwave/common/Finishable.h>

namespace fillwave {
namespace common {

/*! \class PostProcessingPass
 * \brief Defines one post processing pass.
 */

class PostProcessingPass: public Finishable {
public:
	PostProcessingPass(
			pProgram p,
			GLuint width,
			GLuint height,
			pTexture2DRenderableDynamic t,
			GLfloat lifetime);

	virtual ~PostProcessingPass() = default;

	pTexture2DRenderableDynamic getFrame() const;

	pProgram getProgram() const;

private:
	pTexture2DRenderableDynamic mFrame;

	pProgram mProgram;
};

} /* common */
typedef std::unique_ptr<common::PostProcessingPass> puPostProcessingPass;
} /* fillwave */

#endif /* SRC_OPERATIONS_POSTPROCESSINGPASS_H_ */
