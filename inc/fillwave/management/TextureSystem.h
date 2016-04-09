/*
 * TextureSystem.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURESYSTEM_H_
#define TEXTURESYSTEM_H_

#include <fillwave/core/texturing/Texture1D.h>
#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>
#include <fillwave/core/rendering/Texture3DRenderableDynamic.h>
#include <fillwave/loaders/TextureLoader.h>
#include <fillwave/Assets.h>
#include <fillwave/management/base/TManagerComposite.h>
#include <fillwave/management/base/TManagerSmart.h>

namespace fillwave {
namespace framework {

static constexpr size_t FILLWAVE_MAXIMUM_TEXTURES_IN_MANAGER = 50;

/*! \class TextureSystem
 * \brief Manager to handle TextureObject1D, TextureObject2D and TextureObject3D objects.
 */

class TextureSystem {
 public:
	TextureSystem(const std::string& rootPath);
	virtual ~TextureSystem() = default;

	void checkExtensions();

	core::Texture2D* get(std::string texturePath,
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

	TManagerSmart<FILLWAVE_MAXIMUM_TEXTURES_IN_MANAGER, core::Texture1D,
	              size_t, core::ParameterList&> mTextures1D;

	TManagerSmart<FILLWAVE_MAXIMUM_TEXTURES_IN_MANAGER, core::Texture2D,
	              std::string, core::Texture2DFile*, core::ParameterList&, GLuint> mTextures2D;

	TManagerSmart<FILLWAVE_MAXIMUM_TEXTURES_IN_MANAGER, core::Texture2D,
	              size_t, core::Texture2DFile*, core::ParameterList&, GLuint> mTextures2DDeferred;

	TManagerSmart<FILLWAVE_MAXIMUM_TEXTURES_IN_MANAGER, core::Texture2DRenderableDynamic,
	              std::string, core::Texture2DFile*, core::ParameterList&, core::Program*>
	              mTextures2DDynamic;

	TManagerSmart<FILLWAVE_MAXIMUM_TEXTURES_IN_MANAGER, core::Texture2DRenderable,
	              size_t, GLenum, core::Texture2DFile*, core::ParameterList&>
	              mTextures2DRenderable;

	TManagerSmart<FILLWAVE_MAXIMUM_TEXTURES_IN_MANAGER, core::Texture3D,
	              std::string, core::Texture2DFile*, core::Texture2DFile*,
	              core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
	              core::Texture2DFile*, core::ParameterList&> mTextures3D;

	TManagerSmart<FILLWAVE_MAXIMUM_TEXTURES_IN_MANAGER, core::Texture3DRenderableDynamic,
	              std::string, core::Texture2DFile*, core::Texture2DFile*,
	              core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
	              core::Texture2DFile*, core::ParameterList&, core::Texture2DRenderable*,
	              core::Program*> mTextures3DDynamic;

	TManagerSmart<FILLWAVE_MAXIMUM_TEXTURES_IN_MANAGER, core::Texture3DRenderable, size_t,
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
