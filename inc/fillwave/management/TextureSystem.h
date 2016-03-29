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

namespace fillwave {
namespace framework {

typedef Composition<pTexture1D, TPolicyShared<core::Texture1D>,
		core::ParameterList&> TextureObject1D;

typedef Composition<pTexture2D, TPolicyShared<core::Texture2D>,
		core::Texture2DFile*, core::ParameterList&, GLuint> TextureObject2DDeferred;

typedef Composition<pTexture2D, TPolicyShared<core::Texture2D>,
		core::Texture2DFile*, core::ParameterList&, GLuint> TextureObject2D;

typedef Composition<pTexture2D, TPolicyShared<core::Texture2D>,
		core::Texture2DFile*, core::ParameterList&, GLuint> TextureObject2DStatic;

typedef Composition<pTexture2DRenderableDynamic,
		TPolicyShared<core::Texture2DRenderableDynamic>, core::Texture2DFile*,
		core::ParameterList&, pProgram> TextureObject2DDynamic;

typedef Composition<pTexture2DRenderable,
		TPolicyShared<core::Texture2DRenderable>, GLenum, core::Texture2DFile*,
		core::ParameterList&> TextureObject2DRenderable;

typedef Composition<pTexture3D, TPolicyShared<core::Texture3D>,
		core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
		core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
		core::ParameterList&> TextureObject3D;

typedef Composition<pTexture3DRenderable,
		TPolicyShared<core::Texture3DRenderable>, core::Texture2DFile*,
		core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
		core::Texture2DFile*, core::Texture2DFile*, pTexture2DRenderable,
		core::ParameterList&> TextureObject3DRenderable;

typedef Composition<pTexture3DRenderableDynamic,
		TPolicyShared<core::Texture3DRenderableDynamic>, core::Texture2DFile*,
		core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
		core::Texture2DFile*, core::Texture2DFile*, core::ParameterList&,
		pTexture2DRenderable, pProgram> TextureObject3DDynamic;

/*! \class TextureSystem
 * \brief Manager to handle TextureObject1D, TextureObject2D and TextureObject3D objects.
 */

class TextureSystem {
public:
	TextureSystem(const std::string& rootPath);
	virtual ~TextureSystem() = default;

	void checkExtensions();

	pTexture2D get(std::string texturePath, eCompression = eCompression::eNone, eFlip flip =
			eFlip::eVertical);

	pTexture3D get(
			const std::string& posX,
			const std::string& negX,
			const std::string& posY,
			const std::string& negY,
			const std::string& posZ,
			const std::string& negZ);

	pTexture2DRenderable getShadow2D(GLuint width, GLuint height);
	pTexture3DRenderable getShadow3D(GLuint width, GLuint height);
	pTexture2DRenderable getColor2D(GLuint width, GLuint height);
	pTexture2D getDeferredColor(GLuint width, GLuint height, GLuint size = 1);
	pTexture2D getDeferredColorScreen(GLuint width, GLuint height, GLuint size =
			1);
	pTexture2D getDeferredDepth(GLuint width, GLuint height);
	pTexture2D getDeferredStencilDepth(GLuint width, GLuint height);
	pTexture2DRenderableDynamic getDynamic(
			const std::string& fragmentShaderPath,
			pProgram program,
			glm::ivec2 screenSize);

	void reload();

	void evaluateDynamicTextures(GLfloat timeExpiredInSeconds);
	void resizeTextures(GLuint width, GLuint height);
	void resize(GLuint width, GLuint height);

private:

	ManagerComposite<std::unique_ptr<TextureObject1D>, pTexture1D, std::string,
			UINT_MAX, TPolicyUnique<TextureObject1D>, core::ParameterList&> mTextures1D;

	ManagerComposite<std::unique_ptr<TextureObject2DStatic>, pTexture2D,
			std::string, UINT_MAX, TPolicyUnique<TextureObject2DStatic>,
			core::Texture2DFile*, core::ParameterList&, GLuint> mTextures2D;

	ManagerComposite<std::unique_ptr<TextureObject2DDeferred>, pTexture2D,
			std::string, UINT_MAX, TPolicyUnique<TextureObject2DDeferred>,
			core::Texture2DFile*, core::ParameterList&, GLuint> mTextures2DDeferred;

	ManagerComposite<std::unique_ptr<TextureObject2DDynamic>,
			pTexture2DRenderableDynamic, std::string, UINT_MAX,
			TPolicyUnique<TextureObject2DDynamic>, core::Texture2DFile*,
			core::ParameterList&, pProgram> mTextures2DDynamic;

	ManagerComposite<std::unique_ptr<TextureObject2DRenderable>,
			pTexture2DRenderable, std::string, UINT_MAX,
			TPolicyUnique<TextureObject2DRenderable>, GLenum, core::Texture2DFile*,
			core::ParameterList&> mTextures2DRenderable;

	ManagerComposite<std::unique_ptr<TextureObject3D>, pTexture3D, std::string,
			UINT_MAX, TPolicyUnique<TextureObject3D>, core::Texture2DFile*,
			core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
			core::Texture2DFile*, core::Texture2DFile*, core::ParameterList&> mTextures3D;

	ManagerComposite<std::unique_ptr<TextureObject3DDynamic>, pTexture3D,
			std::string, UINT_MAX, TPolicyUnique<TextureObject3DDynamic>,
			core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
			core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
			core::ParameterList&, pTexture2DRenderable, pProgram> mTextures3DDynamic;

	ManagerComposite<std::unique_ptr<TextureObject3DRenderable>,
			pTexture3DRenderable, std::string, UINT_MAX,
			TPolicyUnique<TextureObject3DRenderable>, core::Texture2DFile*,
			core::Texture2DFile*, core::Texture2DFile*, core::Texture2DFile*,
			core::Texture2DFile*, core::Texture2DFile*, pTexture2DRenderable,
			core::ParameterList&> mTextures3DRenderable;

	std::vector<GLenum> mSupportedCompresssionTypes;
	std::string mRootPath;
	TextureLoader mLoader;

	void add(
			std::string filePath,
			eCompression compression,
			eFlip flip);

	void add(
			const std::string& posX,
			const std::string& negX,
			const std::string& posY,
			const std::string& negY,
			const std::string& posZ,
			const std::string& negZ);

	void addDynamic(
			const std::string& fragmentShaderPath,
			pProgram program,
			glm::ivec2 screenSize);

	template <class T>
	inline void reload(T& textures) {
		for (auto& it : textures) {
			it.second->mComponent->reload();
		}
	}

	template <class T>
	inline void resize(T& textures, GLuint width, GLuint height) {
		for (auto& it : textures) {
			it.second->mComponent->resize(width, height);
		}
	}
};

} /* framework */
typedef std::unique_ptr<framework::TextureSystem> puTextureSystem;
} /* fillwave */

#endif /* TEXTUREMANAGER_H_ */
