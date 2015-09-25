/*
 * Texture2DRenderableDynamic.h
 *
 *  Created on: Dec 3, 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE2DRENDERABLEDYNAMIC_H_
#define TEXTURE2DRENDERABLEDYNAMIC_H_

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

#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
namespace core {

/*! \class Texture2DRenderableDynamic
 * \brief Dynamic texture will update its content during runtime according to specified fragment shader.
 */

class Texture2DRenderableDynamic: public Texture2DRenderable {
public:
	Texture2DRenderableDynamic(
			puTexture2DFile file,
			ParameterList& parameters,
			pProgram program);

	virtual ~Texture2DRenderableDynamic();

	void draw(GLfloat timePassed);

	void reload();

private:
	pProgram mProgram;

	GLfloat mTimePassed;

	GLint mUniformLocationCacheTime;
	GLint mUniformLocationCachePostprocessingSampler;

	void initUniformsCache();
};

} /* core */
typedef std::shared_ptr<core::Texture2DRenderableDynamic> pTexture2DRenderableDynamic;
} /* fillwave */

#endif /* TEXTURE2DRENDERABLEDYNAMIC_H_ */
