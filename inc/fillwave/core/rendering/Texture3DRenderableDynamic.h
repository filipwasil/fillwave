/*
 * Texture3DRenderableDynamic.h
 *
 *  Created on: Dec 6, 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE3DRENDERABLEDYNAMIC_H_
#define TEXTURE3DRENDERABLEDYNAMIC_H_

#include <fillwave/core/rendering/Texture3DRenderable.h>
#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
namespace core {

/*! \class Texture3DRenderableDynamic
 * \brief Not used.
 */

class Texture3DRenderableDynamic: public Texture3DRenderable {
 public:
	Texture3DRenderableDynamic(
	   Texture2DFile* filePosX,
	   Texture2DFile* fileNegX,
	   Texture2DFile* filePosY,
	   Texture2DFile* fileNegY,
	   Texture2DFile* filePosZ,
	   Texture2DFile* fileNegZ,
	   ParameterList& parameters,
	   core::Texture2DRenderable* texture2D,
	   core::Program* program);

	virtual ~Texture3DRenderableDynamic() = default;

 private:
	core::Program* mProgram;
	GLfloat mTimePassed;
};

} /* core */
typedef framework::PtrShared<core::Texture3DRenderableDynamic>
pTexture3DRenderableDynamic;
} /* fillwave */

#endif /* TEXTURE3DRENDERABLEDYNAMIC_H_ */
