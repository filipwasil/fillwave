/*
 * TextureLoader.cpp
 *
 *  Created on: 4 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/loaders/TextureLoader.h>
#include <fillwave/loaders/FileLoader.h>

#include <fillwave/common/string.h>

#include <fillwave/Log.h>

#include <fillwave/Profiler.h>

#include <fillwave/Assets.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>

FLOGINIT("TextureLoader", FERROR | FFATAL | FDEBUG)

using namespace std;

namespace fillwave {
namespace framework {

core::Texture2DFile* TextureLoader::load(
    const std::string& filePath,
    eFlip flip,
    GLenum format,
    std::string rootPath,
    eCompression compression) {

	FLOG_DEBUG("Texture %s loading ...", filePath.c_str());
	size_t posCheckboard = filePath.find(".checkboard");
	size_t posColor = filePath.find(".color");
	size_t posDDS = filePath.find(".dds");
	uint8_t r = 0, g = 0, b = 0;
	if (filePath == rootPath) {
		FLOG_DEBUG("Empty texture %s generation and loading ...",
		           filePath.c_str());
		core::Texture2DFile* file = loadVirtualFileColor(512, 512, 0, 0, 0);
		return file;
	} else if (posColor != std::string::npos) {
		FLOG_DEBUG("Color texture %s generation and loading ...",
		           filePath.c_str());
		std::string sub = filePath.substr(rootPath.size(), posColor);
		std::vector<std::string> tokens = split(sub, '_');
		if (tokens.size() >= 3) {
			r = atoi(tokens[0].c_str());
			g = atoi(tokens[1].c_str());
			b = atoi(tokens[2].c_str());
		} else {
			FLOG_ERROR("Could not found color parameters in %s", filePath.c_str());
			return nullptr;
		}
		core::Texture2DFile* file = loadVirtualFileColor(512, 512, r, g, b);
		return file;
	} else if (posCheckboard != std::string::npos) {
		FLOG_DEBUG("Checkboard texture %s generation and loading ...",
		           filePath.c_str());
		std::string sub = filePath.substr(rootPath.size(), posCheckboard);
		std::vector<std::string> tokens = split(sub, '_');
		if (tokens.size() >= 3) {
			r = atoi(tokens[0].c_str());
			g = atoi(tokens[1].c_str());
			b = atoi(tokens[2].c_str());
		} else {
			FLOG_ERROR("Could not found color parameters in %s", filePath.c_str());
			return nullptr;
		}
		core::Texture2DFile* file = loadVirtualFileCheckboard(512, 512, r, g, b);
		return file;
	} else if (posDDS != std::string::npos) {
		FLOG_ERROR("Compressed Texture %s not supported yet", filePath.c_str());
		return nullptr;
	} else {
		GLint w, h, n;
		GLubyte *content = stbi_load(filePath.c_str(), &w, &h, &n,
		                             getBytesPerPixel(format));
		if (content == NULL) { //xxx NULL, not nullptr because the stb library uses NULL
			FILE *f = fopen(filePath.c_str(), "rb");
			if (!f) {
				FLOG_ERROR("Texture %s not found", filePath.c_str());
			} else {
				FLOG_ERROR("Texture %s found but not supported ", filePath.c_str());
				fclose(f);
			}
			return nullptr;
		} else {
			FLOG_DEBUG("Image %s size %dx%d pixel %d bytes per pixel",
			           filePath.c_str(), w, h, n);
			core::Texture2DFile* file = new core::Texture2DFile();

			file->mHeader.mFormat = format;
			file->mHeader.mWidth = w;
			file->mHeader.mHeight = h;
			file->mHeader.mType = GL_UNSIGNED_BYTE;

			file->mConfig.mMipmaps = GL_TRUE;
			file->mConfig.mMipmapsLevel = 0;

			if (compression == eCompression::eNone) {
				file->mConfig.mCompression = GL_FALSE;
				file->mHeader.mInternalFormat = format;
			} else {
				file->mConfig.mCompression = GL_TRUE;
				file->mHeader.mInternalFormat = getComporession(compression);
				file->mConfig.mCompressionSize = 0;
				FLOG_FATAL("Texture compression feature not ready");
			}

			file->mConfig.mBorder = 0;

			file->mData = content;

			file->mAllocation = core::eMemoryAllocation::eMallock;

			FLOG_DEBUG("Flipping Texture %s ...", filePath.c_str());
			switch (flip) {
			case eFlip::eVertical:
				#pragma omp parallel for schedule(guided) num_threads(2)
				for (int row = 0; row < h / 2; row++) {
					for (int column = 0; column < w; column++) {
						int pixelOffset1 = row * w * n + column * n;
						int pixelOffset2 = (h - row - 1) * w * n + column * n;
						for (int byteInPixel = 0; byteInPixel < n; byteInPixel++) {
							int exchangeIndex1 = pixelOffset1 + byteInPixel;
							int exchangeIndex2 = pixelOffset2 + byteInPixel;
							file->mData[exchangeIndex1] ^=
							    file->mData[exchangeIndex2];
							file->mData[exchangeIndex2] ^=
							    file->mData[exchangeIndex1];
							file->mData[exchangeIndex1] ^=
							    file->mData[exchangeIndex2];
						}
					}
				}
				break;

			case eFlip::eHorizontal_vertical:
				#pragma omp parallel for schedule(guided) num_threads(2)
				for (int row = 0; row < h; row++) {
					for (int column = 0; column < w / 2; column++) {
						int pixelOffset1 = row * w * n + column * n;
						int pixelOffset2 = row * w * n + (w - column - 1) * n;
						for (int byteInPixel = 0; byteInPixel < n; byteInPixel++) {
							int exchangeIndex1 = pixelOffset1 + byteInPixel;
							int exchangeIndex2 = pixelOffset2 + byteInPixel;
							file->mData[exchangeIndex1] ^=
							    file->mData[exchangeIndex2];
							file->mData[exchangeIndex2] ^=
							    file->mData[exchangeIndex1];
							file->mData[exchangeIndex1] ^=
							    file->mData[exchangeIndex2];
						}
					}
				}
				break;

			case eFlip::eHorizontal:
				#pragma omp parallel for schedule(guided) num_threads(2)
				for (int row = 0; row < h; row++) {
					for (int column = 0; column < w / 2; column++) {
						int pixelOffset1 = row * w * n + column * n;
						int pixelOffset2 = row * w * n + (w - column - 1) * n;
						for (int byteInPixel = 0; byteInPixel < n; byteInPixel++) {
							int exchangeIndex1 = pixelOffset1 + byteInPixel;
							int exchangeIndex2 = pixelOffset2 + byteInPixel;
							file->mData[exchangeIndex1] ^=
							    file->mData[exchangeIndex2];
							file->mData[exchangeIndex2] ^=
							    file->mData[exchangeIndex1];
							file->mData[exchangeIndex1] ^=
							    file->mData[exchangeIndex2];
						}
					}
				}
				#pragma omp parallel for schedule(guided) num_threads(2)
				for (int row = 0; row < h / 2; row++) {
					for (int column = 0; column < w; column++) {
						int pixelOffset1 = row * w * n + column * n;
						int pixelOffset2 = (h - row - 1) * w * n + column * n;
						for (int byteInPixel = 0; byteInPixel < n; byteInPixel++) {
							int exchangeIndex1 = pixelOffset1 + byteInPixel;
							int exchangeIndex2 = pixelOffset2 + byteInPixel;
							file->mData[exchangeIndex1] ^=
							    file->mData[exchangeIndex2];
							file->mData[exchangeIndex2] ^=
							    file->mData[exchangeIndex1];
							file->mData[exchangeIndex1] ^=
							    file->mData[exchangeIndex2];
						}
					}
				}
				break;

			case eFlip::eNone:
			default:
				break;
			}
			return file;
		}
	}
}

core::Texture2DFile* TextureLoader::loadEmpty(
    glm::ivec2 screenSize,
    GLenum format) {
	core::Texture2DFile* file = new core::Texture2DFile();

	file->mHeader.mFormat = format;
	file->mHeader.mInternalFormat = format;
	file->mHeader.mWidth = screenSize.x;
	file->mHeader.mHeight = screenSize.y;
	file->mHeader.mType = GL_UNSIGNED_BYTE;

	file->mConfig.mMipmaps = GL_TRUE;
	file->mConfig.mMipmapsLevel = 0;
	file->mConfig.mCompression = GL_FALSE;
	file->mConfig.mBorder = 0;

	file->mData = nullptr;

	file->mAllocation = core::eMemoryAllocation::eNone;

	return file;
}

core::Texture2DFile* TextureLoader::loadVirtualFileCheckboard(
    GLuint width,
    GLuint height,
    GLubyte red,
    GLubyte green,
    GLubyte blue,
    GLenum format) {

	GLint bytesPerPixel = getBytesPerPixel(format);
	GLint size = bytesPerPixel * width * height * sizeof(GLubyte);
	GLubyte* content = new GLubyte[size];

	GLint i, r = 0, g = 0, b = 0;
	for (i = 0; i < size; i += bytesPerPixel) {
		if (i % ((width * bytesPerPixel) * 8) == 0) {
			r ^= red;
			g ^= green;
			b ^= blue;
		}
		if (i % (bytesPerPixel * 8) == 0) {
			r ^= red;
			g ^= green;
			b ^= blue;
		}
		content[i] = r;
		content[i + 1] = g;
		content[i + 2] = b;
		content[i + 3] = 1.0;
	}

	core::Texture2DFile* file = new core::Texture2DFile();
	file->mHeader.mFormat = format;
	file->mHeader.mInternalFormat = format;
	file->mHeader.mWidth = width;
	file->mHeader.mHeight = height;
	file->mHeader.mType = GL_UNSIGNED_BYTE;

	file->mConfig.mMipmaps = GL_TRUE;
	file->mConfig.mMipmapsLevel = 0;
	file->mConfig.mCompression = GL_FALSE;
	file->mConfig.mBorder = 0;

	file->mData = content;

	file->mAllocation = core::eMemoryAllocation::eNew;

	return file;
}

core::Texture2DFile* TextureLoader::loadVirtualFileColor(
    GLuint width,
    GLuint height,
    GLubyte red,
    GLubyte green,
    GLubyte blue,
    GLenum format) {
	GLint bytesPerPixel = getBytesPerPixel(format);

	int size = bytesPerPixel * width * height * sizeof(GLubyte);
	GLubyte* content = new GLubyte[size];

	for (int i = 0; i < size; i += bytesPerPixel) {
		content[i] = red;
		content[i + 1] = green;
		content[i + 2] = blue;
		content[i + 3] = 1.0;
	}

	core::Texture2DFile* file = new core::Texture2DFile();
	file->mHeader.mFormat = format;
	file->mHeader.mInternalFormat = format;
	file->mHeader.mWidth = width;
	file->mHeader.mHeight = height;
	file->mHeader.mType = GL_UNSIGNED_BYTE;

	file->mConfig.mMipmaps = GL_FALSE;
	file->mConfig.mMipmapsLevel = 0;
	file->mConfig.mCompression = GL_FALSE;
	file->mConfig.mBorder = 0;

	file->mData = content;

	file->mAllocation = core::eMemoryAllocation::eNew;

	return file;
}

inline GLint TextureLoader::getBytesPerPixel(GLenum format) {
	GLint bytes;
	switch (format) {
	case GL_RGBA:
		bytes = 4;
		break;
	case GL_RGB:
		bytes = 3;
		break;
	case GL_ALPHA:
	case GL_RED:
	case GL_GREEN:
	case GL_BLUE:
		bytes = 1;
		break;
	default:
		FLOG_ERROR("Not recognized texture format loading");
		bytes = 0;
		break;
	}
	return bytes;
}

inline GLenum TextureLoader::getComporession(eCompression compression) {
#ifdef FILLWAVE_GLES_3_0
	(void)compression;
#else
	switch (compression) {
	case eCompression::eNone:
		return GL_NONE;
		break;
	case eCompression::eGeneric_r:
		return GL_COMPRESSED_RED;
		break;
	case eCompression::eGeneric_rg:
		return GL_COMPRESSED_RG;
		break;
	case eCompression::eGeneric_rgb:
		return GL_COMPRESSED_RGB;
		break;
	case eCompression::eGeneric_rgba:
		return GL_COMPRESSED_RGBA;
		break;
	case eCompression::eGeneric_srgb:
		return GL_COMPRESSED_SRGB;
		break;
	case eCompression::eGeneric_srgba:
		return GL_COMPRESSED_SRGB_ALPHA;
		break;
#if defined(__APPLE__)
#else
	case eCompression::eLatc_luminance:
		return GL_COMPRESSED_LUMINANCE_LATC1_EXT;
		break;
	case eCompression::eLatc_luminance_signed:
		return GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT;
		break;
	case eCompression::eLatc_luminance_alpha:
		return GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT;
		break;
	case eCompression::eLatc_luminance_alpha_signed:
		return GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT;
		break;
	case eCompression::eRgtc1_r:
		return GL_COMPRESSED_RED_RGTC1_EXT;
		break;
	case eCompression::eRgtc1_r_signed:
		return GL_COMPRESSED_SIGNED_RED_RGTC1_EXT;
		break;
	case eCompression::eRgtc1_rg:
		return GL_COMPRESSED_RED_GREEN_RGTC2_EXT;
		break;
	case eCompression::eRgtc1_rg_signed:
		return GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT;
		break;
	case eCompression::eS3tc_dxt1_rgb:
		return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
		break;
	case eCompression::eS3tc_dxt1_rgba:
		return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case eCompression::eS3tc_dxt3_rgba:
		return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case eCompression::eS3tc_dxt5_rgba:
		return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
#endif /* __APPLE__ */
	default:
		break;
	}
#endif /* FILLWAVE_GLES_3_0 */
	return GL_NONE;
}

} /* framework */
} /* fillwave */
