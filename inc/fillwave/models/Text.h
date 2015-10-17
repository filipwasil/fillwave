/*
 * Text.h
 *
 *  Created on: Jul 26, 2014
 *      Author: Filip Wasil
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <fillwave/core/texturing/TextureRegion.h>
#include <fillwave/core/buffers/VertexBufferText.h>
#include <fillwave/core/pipeline/Program.h>

#include <fillwave/common/Blending.h>

#include <fillwave/loaders/FontLoader.h>
#include <fillwave/models/Reloadable.h>

#include <map>

namespace fillwave {
class Engine;

enum class eTextEffect {
	none, bold
};

namespace models {

/*! \class Text
 * \brief 2D Text on the screen.
 */

class Text: public Reloadable {
public:
	Text(
			std::string& text,
			pTexture texture,
			GLfloat startingPositionX,
			GLfloat startingPositionY,
			Engine* engine,
			GLfloat scale,
			Font* font,
			glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0),
			eTextEffect effect = eTextEffect::none);

	virtual ~Text() = default;

	void draw();

	void editAspectRatio(Engine* engine);
	void editString(std::string text);
	void editColor(glm::vec4 color);
	void editSize(GLfloat size);
	void editPosition(GLfloat startingX, GLfloat startingY);

private:
	Engine* mEngine;

	std::string mText;

	glm::vec4 mColor;

	common::Blending mBlending;

	eTextEffect mEffect;

	std::map<std::string, pTextureRegion> mCharacters;

	GLint mViewportWidth, mViewportHeight;

	GLfloat mStartingX, mStartingY, mScale;

	pProgram mProgram;
	pTexture mTexture;
	pVertexBufferText mVBO;
	Font* mFont;

	GLint mUniformLocationCacheColor, mUniformLocationCacheTextureUnit;

	void createProgram();

	void initBuffers();

	void initPipeline();

	void initUniformsCache();

	void createVBO();

	void clearVBO();

	void initVBO();

	void initVAO();
};

} /* models */
typedef std::shared_ptr<models::Text> pText;
typedef std::unique_ptr<models::Text> puText;
} /* fillwave */

#endif /* TEXT_H_ */
