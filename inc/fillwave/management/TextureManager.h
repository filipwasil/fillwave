/*
 * TextureManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <fillwave/core/texturing/Texture1D.h>
#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>
#include <fillwave/core/rendering/Texture3DRenderableDynamic.h>

#include <fillwave/loaders/TextureLoader.h>

#include <fillwave/Assets.h>

namespace fillwave {
namespace framework {

/*! \class TextureObject
 * \brief Template class for all texture objects.
 */

template<class T>
class TextureObject {
public:
	T mTexture;
};

/*! \typedef TextureObject1D
 * \brief Data structure containing each Texture1D instance info.
 */

typedef TextureObject<pTexture1D> TextureObject1D;
typedef std::unique_ptr<TextureObject1D> puTextureObject1D;

/*! \typedef TextureObject2DDeferred
 * \brief Data structure containing each Texture2D instance info for deferred rendering.
 */

typedef TextureObject<pTexture2D> TextureObject2DDeferred;
typedef std::unique_ptr<TextureObject2DDeferred> puTextureObject2DDeferred;

/*! \class TextureObject2D
 * \brief Data structure containing each Texture2D instance info.
 */

template<class T>
class TextureObject2D: public TextureObject<T> {
public:
	std::string mFilePath;
};
typedef TextureObject2D<pTexture2D> TextureObject2DStatic;
typedef std::unique_ptr<TextureObject2DStatic> puTextureObject2D;

/*! \typedef TextureObject2DRenderable
 * \brief Data structure containing each Texture2DRenderable instance info.
 */

typedef TextureObject<pTexture2DRenderable> TextureObject2DRenderable;
typedef std::unique_ptr<TextureObject2DRenderable> puTextureObject2DRenderable;

/*! \typedef TextureObject2DDynamic
 * \brief Data structure containing each TextureObject2DDynamic instance info.
 */

typedef TextureObject2D<pTexture2DRenderableDynamic> TextureObject2DDynamic;
typedef std::unique_ptr<TextureObject2DDynamic> puTextureObject2DDynamic;

/*! \typedef TextureObject3D
 * \brief Data structure containing each Texture3D instance info.
 */

template<class T>
class TextureObject3D: public TextureObject<T> {
public:
	std::string mFilePathPosX;
	std::string mFilePathNegX;
	std::string mFilePathPosY;
	std::string mFilePathNegY;
	std::string mFilePathPosZ;
	std::string mFilePathNegZ;
};
typedef TextureObject3D<pTexture3D> TextureObject3DStatic;
typedef std::unique_ptr<TextureObject3DStatic> puTextureObject3D;

/*! \typedef TextureObject3DRenderable
 * \brief Data structure containing each Texture2DRenderable instance info.
 */

typedef TextureObject<pTexture3DRenderable> TextureObject3DRenderable;
typedef std::unique_ptr<TextureObject3DRenderable> puTextureObject3DRenderable;

/*! \typedef TextureObject3DDynamic
 * \brief Data structure containing each Texture3DRenderableDynamic instance info.
 */

typedef TextureObject3D<pTexture3DRenderableDynamic> TextureObject3DDynamic;
typedef std::unique_ptr<TextureObject3DDynamic> puTextureObject3DDynamic;

/*! \class TextureManager
 * \brief Manager to handle TextureObject1D, TextureObject2D and TextureObject3D objects.
 */

class TextureManager {
public:
	TextureManager(const std::string& rootPath);
	virtual ~TextureManager() = default;

	void checkExtensions();

	pTexture get(
			std::string texturePath,
			GLuint mapType =
			FILLWAVE_TEXTURE_TYPE_NONE,
			eCompression = eCompression::eNone,
			eFlip flip = eFlip::eVertical);

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

	GLboolean check(std::string texturePath, GLuint mapType =
	FILLWAVE_TEXTURE_TYPE_NONE);

	void reload();

	void resizeTextures(GLuint width, GLuint height);
	void resize(GLuint width, GLuint height);

private:
	std::vector<puTextureObject1D> mTextureObjects1D;
	std::vector<puTextureObject2D> mTextureObjects2D;
	std::vector<puTextureObject2DDynamic> mTextureObjects2DDynamic;
	std::vector<puTextureObject2DRenderable> mTextureObjects2DRenderable;
	std::vector<puTextureObject3D> mTextureObjects3D;
	std::vector<puTextureObject3DDynamic> mTextureObjects3DDynamic;
	std::vector<puTextureObject3DRenderable> mTextureObjects3DRenderable;
	std::vector<puTextureObject2DDeferred> mTextureObjects2DDeferred;
	std::vector<GLenum> mSupportedCompresssionTypes;
	std::string mRootPath;
	puTextureLoader mLoader;

	void add(
			std::string filePath,
			GLuint mapType,
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

	template<class T>
	inline void reload(std::vector<T>& textures) {
		for (auto& it : textures) {
			it->mTexture->reload();
		}
	}

	template<class T>
	inline void resize(std::vector<T>& textures, GLuint width, GLuint height) {
		for (auto& it : textures) {
			it->mTexture->resize(width, height);
		}
	}

};

} /* framework */
typedef std::unique_ptr<framework::TextureManager> puTextureManager;
} /* fillwave */

#endif /* TEXTUREMANAGER_H_ */
