/*
 * TextureSystem.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TEXTURESYSTEM_H_
#define TEXTURESYSTEM_H_

#include <fillwave/core/texturing/Texture1D.h>
#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>
#include <fillwave/core/rendering/Texture3DRenderableDynamic.h>
#include <fillwave/loaders/TextureLoader.h>
#include <fillwave/Assets.h>
#include <fillwave/management/base/TManagerSmart.h>

namespace fillwave {
namespace framework {

/*! \class TextureSystem
 * \brief Manager to handle TextureObject1D, TextureObject2D and TextureObject3D objects.
 */

class TextureSystem {
 public:
	TextureSystem(const std::string& rootPath);
	virtual ~TextureSystem() = default;

	void checkExtensions();

	core::Texture2D* get(const std::string& texturePath,
	                     eCompression = eCompression::eNone, eFlip flip =
	                        eFlip::eVertical);

	core::Texture3D* get(
	   const std::string& posX,
	   const std::string& negX,
	   const std::string& posY,
	   const std::string& negY,
	   const std::string& posZ,
	   const std::string& negZ);

	core::Texture2DRenderable* getShadow2D(GLuint width, GLuint height);
	core::Texture3DRenderable* getShadow3D(GLuint width, GLuint height);
	core::Texture2DRenderable* getColor2D(GLuint width, GLuint height);
	core::Texture2D* getDeferredColor(GLuint width, GLuint height, GLuint size = 1);
	core::Texture2D* getDeferredColorScreen(GLuint width, GLuint height,
	                                        GLuint size =
	                                              1);
	core::Texture2D* getDeferredDepth(GLuint width, GLuint height);
	core::Texture2D* getDeferredStencilDepth(GLuint width, GLuint height);
	core::Texture2DRenderableDynamic* getDynamic(
	   const std::string& fragmentShaderPath,
	   core::Program* program,
	   glm::ivec2 screenSize);

	void reload();

	void evaluateDynamicTextures(GLfloat timeExpiredInSeconds);
	void resizeTextures(GLuint width, GLuint height);
	void resize(GLuint width, GLuint height);

 private:

#ifdef FILLWAVE_GLES_3_0
#else /* FILLWAVE_GLES_3_0 */
	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Texture1D,
	              size_t, core::ParameterList&> mTextures1D;
#endif /* FILLWAVE_GLES_3_0 */
	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Texture2D,
	              std::string, core::Texture2DFile*, core::ParameterList&, GLuint> mTextures2D;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Texture2D,
	              size_t, core::Texture2DFile*, core::ParameterList&, GLuint> mTextures2DDeferred;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Texture2DRenderableDynamic,
	              std::string, core::Texture2DFile*, core::ParameterList&, core::Program*>
	              mTextures2DDynamic;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Texture2DRenderable,
	              size_t, GLenum, core::Texture2DFile*, core::ParameterList&>
	              mTextures2DRenderable;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Texture3D,
	              std::string, core::Texture2DFile*, core::Texture2DFile*,
	              core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
	              core::Texture2DFile*, core::ParameterList&> mTextures3D;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Texture3DRenderableDynamic,
	              std::string, core::Texture2DFile*, core::Texture2DFile*,
	              core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
	              core::Texture2DFile*, core::ParameterList&, core::Texture2DRenderable*,
	              core::Program*> mTextures3DDynamic;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Texture3DRenderable, size_t,
	              core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
	              core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
	              core::Texture2DRenderable*, core::ParameterList&> mTextures3DRenderable;

	std::vector<GLenum> mSupportedCompresssionTypes;
	std::string mRootPath;
	TextureLoader mLoader;

	template <class T>
	inline void reload(T& textures) {
		for (auto& it : textures) {
			it.second->reload();
		}
	}

	template <class T>
	inline void resize(T& textures, GLuint width, GLuint height) {
		for (auto& it : textures) {
			it.second->resize(width, height);
		}
	}
};

} /* framework */
typedef std::unique_ptr<framework::TextureSystem> puTextureSystem;
} /* fillwave */

#endif /* TEXTUREMANAGER_H_ */
