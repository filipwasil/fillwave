/*
 * TextureManager.cpp
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/management/TextureManager.h>
#include <fillwave/extras/Log.h>

FLOGINIT("TextureManager", FERROR | FFATAL | FINFO)

using namespace fillwave::loader;

namespace fillwave {
namespace manager {

TextureManager::TextureManager(const std::string& rootPath)
		: mRootPath(rootPath) {
	checkExtensions();
}

inline void TextureManager::checkExtensions() {
#if __ANDROID__
#else
	int NumberOfExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);

	for (int i = 0; i < NumberOfExtensions; i++) {
		const GLubyte *ccc = glGetStringi(GL_EXTENSIONS, i);
		auto find_extension = [ccc](const char *name) ->
		bool {
			if ((strcmp((const char *)ccc, name) == 0)) {
				FLOG_INFO("%s supported", name);
				return true;
			} else {
				return false;
			}
		};

#if defined(__APPLE__)
#else
		if (find_extension("GL_EXT_texture_compression_latc")) {
			mSupportedCompresssionTypes.push_back(
					GL_COMPRESSED_LUMINANCE_LATC1_EXT);
			mSupportedCompresssionTypes.push_back(
					GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT);
			mSupportedCompresssionTypes.push_back(
					GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT);
			mSupportedCompresssionTypes.push_back(
					GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT);
		} else if (find_extension("GL_EXT_texture_compression_rgtc")) {
			mSupportedCompresssionTypes.push_back(GL_COMPRESSED_RED_RGTC1_EXT);
			mSupportedCompresssionTypes.push_back(
					GL_COMPRESSED_SIGNED_RED_RGTC1_EXT);
			mSupportedCompresssionTypes.push_back(
					GL_COMPRESSED_RED_GREEN_RGTC2_EXT);
			mSupportedCompresssionTypes.push_back(
					GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT);
		} else if (find_extension("GL_EXT_texture_compression_s3tc")) {
			mSupportedCompresssionTypes.push_back(GL_COMPRESSED_RGB_S3TC_DXT1_EXT);
			mSupportedCompresssionTypes.push_back(
					GL_COMPRESSED_RGBA_S3TC_DXT1_EXT);
			mSupportedCompresssionTypes.push_back(
					GL_COMPRESSED_RGBA_S3TC_DXT3_EXT);
			mSupportedCompresssionTypes.push_back(
					GL_COMPRESSED_RGBA_S3TC_DXT5_EXT);
		}
	}
#endif

#endif
}

void TextureManager::add(
		std::string filePath,
		GLuint mapType,
		eCompression compression,
		eFlip flip) {
	FLOG_DEBUG("Texture to be added: %s", filePath.c_str());
	for (auto& it : mTextureObjects2D) {
		if (it->mFilePath == filePath && it->mTexture->getMapType() == mapType) {
			FLOG_DEBUG("Texture %s already in manager", filePath.c_str());
			return;
		}
	}
	TextureObject2DStatic* texture = new TextureObject2DStatic();
	texture->mFilePath = filePath;
	core::Texture2DFile* file = mLoader->load(filePath, flip,
	GL_RGBA, mRootPath, compression);

	if (file) {
		core::ParameterList parameters;
		FLOG_DEBUG("Texture %s added to manager", filePath.c_str());
		texture->mTexture = pTexture2D(
				new core::Texture2D(puTexture2DFile(file), parameters));
		texture->mTexture->setMapType(mapType);
		mTextureObjects2D.push_back(puTextureObject2D(texture));
	} else {
		FLOG_DEBUG("Texture %s not found", filePath.c_str());
	}
}

void TextureManager::addDynamic(
		const std::string& fragmentShaderPath,
		pProgram program,
		glm::ivec2 screenSize) {
	FLOG_DEBUG("Dynamic texture to be added: %s", fragmentShaderPath.c_str());
	for (auto& it : mTextureObjects2DDynamic) {
		if (it->mFilePath == fragmentShaderPath) {
			FLOG_DEBUG("Dynamic texture %s already in manager",
					fragmentShaderPath.c_str());
			return;
		}
	}

	TextureObject2DDynamic* textureDynamic = new TextureObject2DDynamic();
	textureDynamic->mFilePath = fragmentShaderPath;
	FLOG_DEBUG("Texture %s will be added to manager", fragmentShaderPath.c_str());

	core::Texture2DFile* file = mLoader->loadEmpty(screenSize);

	core::ParameterList parameters;
	parameters.push_back(core::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	parameters.push_back(core::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	textureDynamic->mTexture = pTexture2DRenderableDynamic(
			new core::Texture2DRenderableDynamic(puTexture2DFile(file), parameters,
					program));

	mTextureObjects2DDynamic.push_back(puTextureObject2DDynamic(textureDynamic));
}

void TextureManager::add(
		const std::string& posX,
		const std::string& negX,
		const std::string& posY,
		const std::string& negY,
		const std::string& posZ,
		const std::string& negZ) {

	std::string name = posX + negX + posY + negY + posZ + negZ;

	FLOG_DEBUG("Texture to be added: %s", name.c_str());

	for (auto& it : mTextureObjects3D) {
		if (it->mFilePathPosX == posX && it->mFilePathNegX == negX
				&& it->mFilePathPosY == posY && it->mFilePathNegY == negY
				&& it->mFilePathPosZ == posZ && it->mFilePathNegZ == negZ) {
			FLOG_DEBUG("Texture %s already in manager", name.c_str());
			return;
		}
	}

	TextureObject3DStatic* cubeObject = new TextureObject3DStatic();

	core::ParameterList parameters;
	parameters.push_back(core::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	parameters.push_back(core::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	cubeObject->mFilePathPosX = posX;
	cubeObject->mFilePathNegX = negX;
	cubeObject->mFilePathPosY = posY;
	cubeObject->mFilePathNegY = negY;
	cubeObject->mFilePathPosZ = posZ;
	cubeObject->mFilePathNegZ = negZ;

	FLOG_DEBUG("Texture %s will be added to manager", name.c_str());

	core::Texture2DFile* filePosX = mLoader->load(posX, eFlip::none,
	GL_RGBA, mRootPath);
	core::Texture2DFile* fileNegX = mLoader->load(negX, eFlip::none,
	GL_RGBA, mRootPath);
	core::Texture2DFile* filePosY = mLoader->load(posY, eFlip::none,
	GL_RGBA, mRootPath);
	core::Texture2DFile* fileNegY = mLoader->load(negY, eFlip::none,
	GL_RGBA, mRootPath);
	core::Texture2DFile* filePosZ = mLoader->load(posZ, eFlip::none,
	GL_RGBA, mRootPath);
	core::Texture2DFile* fileNegZ = mLoader->load(negZ, eFlip::none,
	GL_RGBA, mRootPath);

	if (filePosX && fileNegX && filePosY && fileNegY && filePosZ && fileNegZ) {
		FLOG_DEBUG("Texture %s added to manager", name.c_str());
		cubeObject->mTexture = pTexture3D(
				new core::Texture3D((*filePosX), (*fileNegX), (*filePosY),
						(*fileNegY), (*filePosZ), (*fileNegZ), parameters));

		puTextureObject3D ptr = puTextureObject3D(cubeObject);

		mTextureObjects3D.push_back(std::move(ptr));

		delete filePosX;
		delete fileNegX;
		delete filePosY;
		delete fileNegY;
		delete filePosZ;
		delete fileNegZ;

	} else {
		if (!filePosX) {
			FLOG_DEBUG("3D Texture positive x %s not found", posX.c_str());
		} else {
			delete filePosX;
		}
		if (!fileNegX) {
			FLOG_DEBUG("3D Texture negative x %s not found", negX.c_str());
		} else {
			delete fileNegX;
		}
		if (!filePosY) {
			FLOG_DEBUG("3D Texture positive y %s not found", posY.c_str());
		} else {
			delete filePosY;
		}
		if (!fileNegY) {
			FLOG_DEBUG("3D Texture negative y %s not found", negY.c_str());
		} else {
			delete fileNegY;
		}
		if (!filePosZ) {
			FLOG_DEBUG("3D Texture positive z %s not found", posZ.c_str());
		} else {
			delete filePosZ;
		}
		if (!fileNegZ) {
			FLOG_DEBUG("3D Texture negative z %s not found", negZ.c_str());
		} else {
			delete fileNegZ;
		}
	}
}

pTexture TextureManager::get(
		std::string texturePath,
		GLuint mapType,
		eCompression compression,
		eFlip flip) {
	std::string filePath = mRootPath + texturePath;
	add(filePath, mapType, compression, flip);
	for (auto& it : mTextureObjects2D) {
		if (it->mFilePath == filePath && it->mTexture->getMapType() == mapType) {
			return it->mTexture;
		}
	}
	FLOG_ERROR("Texture2D %s not found in manager. Returning empty pointer",
			filePath.c_str());
	return pTexture();
}

GLboolean TextureManager::check(std::string texturePath, GLuint mapType) {
	std::string filePath = mRootPath + texturePath;
	for (auto& it : mTextureObjects2D) {
		if (it->mFilePath == filePath && it->mTexture->getMapType() == mapType) {
			return GL_TRUE;
		}
	}
	return GL_FALSE;
}

pTexture2DRenderableDynamic TextureManager::getDynamic(
		const std::string& fragmentShaderPath,
		pProgram program,
		glm::ivec2 screenSize) {
	std::string filePath = mRootPath + fragmentShaderPath;
	addDynamic(filePath, program, screenSize);
	for (auto& it : mTextureObjects2DDynamic) {
		if (it->mFilePath == filePath) {
			return it->mTexture;
		}
	}
	FLOG_ERROR(
			"pTexture2DRenderableDynamic %s not found in manager. Returning empty pointer",
			filePath.c_str());
	return pTexture2DRenderableDynamic();
}

pTexture3D TextureManager::get(
		const std::string& posX,
		const std::string& negX,
		const std::string& posY,
		const std::string& negY,
		const std::string& posZ,
		const std::string& negZ) {

	std::string filePathPosX = mRootPath + posX;
	std::string filePathNegX = mRootPath + negX;
	std::string filePathPosY = mRootPath + posY;
	std::string filePathNegY = mRootPath + negY;
	std::string filePathPosZ = mRootPath + posZ;
	std::string filePathNegZ = mRootPath + negZ;

	add(filePathPosX, filePathNegX, filePathPosY, filePathNegY, filePathPosZ,
			filePathNegZ);

	std::string name = posX + negX + posY + negY + posZ + negZ;

	for (auto& it : mTextureObjects3D) {
		if (it->mFilePathPosX == filePathPosX && it->mFilePathNegX == filePathNegX
				&& it->mFilePathPosY == filePathPosY
				&& it->mFilePathNegY == filePathNegY
				&& it->mFilePathPosZ == filePathPosZ
				&& it->mFilePathNegZ == filePathNegZ) {
			FLOG_DEBUG("Texture %s already in manager", name.c_str());
			return it->mTexture;
		}
	}
	FLOG_ERROR("Texture3D %s not found in manager. Returning empty pointer",
			(filePathPosX + filePathNegX + filePathPosY + filePathNegY
					+ filePathPosZ + filePathNegZ).c_str());
	return pTexture3D();
}

pTexture2DRenderable TextureManager::getShadow2D(GLuint width, GLuint height) {

	TextureObject2DRenderable* object = new TextureObject2DRenderable();

	core::Texture2DFile* file = new core::Texture2DFile();
	core::ParameterList parameters;

	file->mHeader.mFormat = GL_DEPTH_COMPONENT;
	file->mHeader.mInternalFormat = GL_DEPTH_COMPONENT;
	file->mConfig.mMipmapsLevel = 0;
	file->mConfig.mBorder = 0;
	file->mHeader.mWidth = width;
	file->mHeader.mHeight = height;
	file->mData = nullptr;
	file->mConfig.mMipmaps = GL_FALSE;
	file->mConfig.mCompression = GL_FALSE;

#ifdef __ANDROID__
	file->mHeader.mType = GL_UNSIGNED_INT;
	parameters.push_back(core::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	parameters.push_back(core::Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	parameters.push_back(core::Parameter(GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
	parameters.push_back(core::Parameter(GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
#else
	file->mHeader.mType = GL_FLOAT;
	parameters.push_back(core::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	parameters.push_back(core::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
#endif

	object->mTexture = pTexture2DRenderable(
			new core::Texture2DRenderable(GL_DEPTH_ATTACHMENT,
					puTexture2DFile(file), parameters));

	mTextureObjects2DRenderable.push_back(puTextureObject2DRenderable(object));

	return object->mTexture;
}

pTexture3DRenderable TextureManager::getShadow3D(GLuint width, GLuint height) {
	core::Texture2DFile* file[6];

	TextureObject3DRenderable* object = new TextureObject3DRenderable();

	for (GLint i = 0; i < 6; i++) {
		file[i] = new core::Texture2DFile();
		file[i]->mHeader.mFormat = GL_RED;
		file[i]->mHeader.mInternalFormat = GL_R32F;

		file[i]->mConfig.mMipmapsLevel = 0;
		file[i]->mConfig.mBorder = 0;
		file[i]->mHeader.mWidth = 512;
		file[i]->mHeader.mHeight = 512;
		file[i]->mHeader.mType = GL_FLOAT;
		file[i]->mData = nullptr;
		file[i]->mConfig.mMipmaps = GL_FALSE;
		file[i]->mConfig.mCompression = GL_FALSE;
	}

	core::Texture2DFile* file2D = new core::Texture2DFile();
	file2D->mHeader.mFormat = GL_DEPTH_COMPONENT;
	file2D->mHeader.mInternalFormat = GL_DEPTH_COMPONENT32;

	file2D->mConfig.mMipmapsLevel = 0;
	file2D->mConfig.mBorder = 0;
	file2D->mHeader.mWidth = 512;
	file2D->mHeader.mHeight = 512;
	file2D->mHeader.mType = GL_FLOAT;
	file2D->mData = nullptr;
	file2D->mConfig.mMipmaps = GL_FALSE;
	file2D->mConfig.mCompression = GL_FALSE;

	core::ParameterList parameters2D;
	parameters2D.push_back(core::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	parameters2D.push_back(core::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	parameters2D.push_back(core::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	parameters2D.push_back(core::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	core::ParameterList parameters3D;
	parameters3D.push_back(core::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	parameters3D.push_back(core::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	parameters3D.push_back(core::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	parameters3D.push_back(core::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	parameters3D.push_back(core::Parameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	pTexture2DRenderable t = pTexture2DRenderable(
			new core::Texture2DRenderable(GL_DEPTH_ATTACHMENT,
					puTexture2DFile(file2D), parameters2D));

	object->mTexture = pTexture3DRenderable(
			new core::Texture3DRenderable(*(file[0]), *(file[1]), *(file[2]),
					*(file[3]), *(file[4]), *(file[5]), t, parameters3D));

	mTextureObjects3DRenderable.push_back(puTextureObject3DRenderable(object));

	return object->mTexture;
}

pTexture2DRenderable TextureManager::getColor2D(GLuint width, GLuint height) {

	TextureObject2DRenderable* object = new TextureObject2DRenderable();

	core::Texture2DFile* file = new core::Texture2DFile();

	file->mHeader.mFormat = GL_RGBA;
	file->mHeader.mInternalFormat = GL_RGBA;
	file->mConfig.mMipmapsLevel = 0;
	file->mConfig.mBorder = 0;
	file->mHeader.mWidth = width;
	file->mHeader.mHeight = height;
#ifdef __ANDROID__
	file->mHeader.mType = GL_UNSIGNED_BYTE;
#else
	file->mHeader.mType = GL_FLOAT;
#endif
	file->mData = nullptr;
	file->mConfig.mMipmaps = GL_FALSE;
	file->mConfig.mCompression = GL_FALSE;

	core::ParameterList parameters;
	parameters.push_back(core::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	parameters.push_back(core::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	parameters.push_back(core::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	object->mTexture = pTexture2DRenderable(new core::Texture2DRenderable(
	GL_COLOR_ATTACHMENT0, puTexture2DFile(file), parameters));

	mTextureObjects2DRenderable.push_back(puTextureObject2DRenderable(object));

	return object->mTexture;
}

pTexture2D TextureManager::getDeferredColor(
		GLuint width,
		GLuint height,
		GLuint size) {

	TextureObject2DDeferred* object = new TextureObject2DDeferred();

	core::Texture2DFile* file = new core::Texture2DFile();

	core::Texture2DFileHeader colorTextureHeader;

	core::ParameterList parameters;
	parameters.push_back(core::Parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	parameters.push_back(core::Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST));

#ifdef __ANDROID__
	colorTextureHeader.mFormat = GL_RGBA;
	colorTextureHeader.mInternalFormat = GL_RGBA;
	colorTextureHeader.mType = GL_UNSIGNED_BYTE;
#else
	colorTextureHeader.mFormat = GL_RGB;
	colorTextureHeader.mInternalFormat = GL_RGB32F;
	colorTextureHeader.mType = GL_FLOAT;
#endif
	colorTextureHeader.mWidth = width;
	colorTextureHeader.mHeight = height;

	file->mConfig = core::Texture2DFileConfig();
	file->mHeader = colorTextureHeader;
	file->mData = nullptr;

	object->mTexture = pTexture2D(
			new core::Texture2D(puTexture2DFile(file), parameters, size));

	mTextureObjects2DDeferred.push_back(puTextureObject2DDeferred(object));

	return object->mTexture;
}

pTexture2D TextureManager::getDeferredColorScreen(
		GLuint width,
		GLuint height,
		GLuint size) {

	TextureObject2DDeferred* object = new TextureObject2DDeferred();

	core::Texture2DFile* file = new core::Texture2DFile();

	core::Texture2DFileHeader colorTextureHeader;

	core::ParameterList parameters;
	parameters.push_back(core::Parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	parameters.push_back(core::Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST));

#ifdef __ANDROID__
	colorTextureHeader.mFormat = GL_RGB;
	colorTextureHeader.mInternalFormat = GL_RGBA;
	colorTextureHeader.mType = GL_UNSIGNED_BYTE;
#else
	colorTextureHeader.mFormat = GL_RGB;
	colorTextureHeader.mInternalFormat = GL_RGBA;
	colorTextureHeader.mType = GL_FLOAT;
#endif
	colorTextureHeader.mWidth = width;
	colorTextureHeader.mHeight = height;

	file->mConfig = core::Texture2DFileConfig();
	file->mHeader = colorTextureHeader;
	file->mData = nullptr;

	object->mTexture = pTexture2D(
			new core::Texture2D(puTexture2DFile(file), parameters, size));

	mTextureObjects2DDeferred.push_back(puTextureObject2DDeferred(object));

	return object->mTexture;
}

pTexture2D TextureManager::getDeferredDepth(GLuint width, GLuint height) {

	TextureObject2DDeferred* object = new TextureObject2DDeferred();

	core::Texture2DFileHeader depthTextureHeader;

	core::Texture2DFile* file = new core::Texture2DFile();

	core::ParameterList parameters;

	depthTextureHeader.mFormat = GL_DEPTH_COMPONENT;
	depthTextureHeader.mInternalFormat = GL_DEPTH_COMPONENT;

	depthTextureHeader.mWidth = width;
	depthTextureHeader.mHeight = height;

#ifdef __ANDROID__
	depthTextureHeader.mType = GL_UNSIGNED_INT;
#else
	depthTextureHeader.mType = GL_FLOAT;
#endif

	file->mConfig = core::Texture2DFileConfig();
	file->mHeader = depthTextureHeader;
	file->mData = nullptr;

	object->mTexture = pTexture2D(
			new core::Texture2D(puTexture2DFile(file), parameters));

	mTextureObjects2DDeferred.push_back(puTextureObject2DDeferred(object));

	return object->mTexture;
}

pTexture2D TextureManager::getDeferredStencilDepth(
		GLuint width,
		GLuint height) {

	TextureObject2DDeferred* object = new TextureObject2DDeferred();

	core::Texture2DFileHeader stencilTextureHeader;

	core::Texture2DFile* file = new core::Texture2DFile();

	core::ParameterList parameters;

	stencilTextureHeader.mFormat = GL_DEPTH_STENCIL;
	stencilTextureHeader.mInternalFormat = GL_DEPTH32F_STENCIL8;

	stencilTextureHeader.mWidth = width;
	stencilTextureHeader.mHeight = height;

	stencilTextureHeader.mType = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;

	file->mConfig = core::Texture2DFileConfig();
	file->mHeader = stencilTextureHeader;
	file->mData = nullptr;

	object->mTexture = pTexture2D(
			new core::Texture2D(puTexture2DFile(file), parameters));

	mTextureObjects2DDeferred.push_back(puTextureObject2DDeferred(object));

	return object->mTexture;
}

void TextureManager::resize(GLuint width, GLuint height) {
	resize(mTextureObjects2DDynamic, width, height);
	resize(mTextureObjects2DRenderable, width, height);
}

void TextureManager::reload() {
	reload(mTextureObjects1D);
	reload(mTextureObjects2D);
	reload(mTextureObjects2DDynamic);
	reload(mTextureObjects2DRenderable);
	reload(mTextureObjects3D);
	reload(mTextureObjects3DRenderable);
	reload(mTextureObjects3DDynamic);
	reload(mTextureObjects2DDeferred);
}

} /* manager */
} /* fillwave */
