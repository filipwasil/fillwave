/*
 * PostProcessingPass.h
 *
 *  Created on: 4 mar 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_OPERATIONS_POSTPROCESSINGPASS_H_
#define SRC_OPERATIONS_POSTPROCESSINGPASS_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

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

	virtual ~PostProcessingPass();

	pTexture2DRenderableDynamic getFrame();

	pProgram getProgram();

private:
	pTexture2DRenderableDynamic mFrame;

	pProgram mProgram;
};

} /* common */
typedef std::unique_ptr<common::PostProcessingPass> puPostProcessingPass;
} /* fillwave */

#endif /* SRC_OPERATIONS_POSTPROCESSINGPASS_H_ */
