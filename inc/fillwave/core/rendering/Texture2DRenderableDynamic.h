/*
 * Texture2DRenderableDynamic.h
 *
 *  Created on: Dec 3, 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE2DRENDERABLEDYNAMIC_H_
#define TEXTURE2DRENDERABLEDYNAMIC_H_

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

	virtual ~Texture2DRenderableDynamic() = default;

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
