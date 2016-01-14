/*
 * IHUDNode.h
 *
 *  Created on: Jan 10, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_HUD_IHUD_NODE_H_
#define INC_FILLWAVE_HUD_IHUD_NODE_H_

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
namespace framework {

class IHUDNode {
public:
	IHUDNode(
			pTexture2D texture,
			pProgram program,
			glm::vec2 position,
			glm::vec2 scale)
			: mTexture(texture), mProgram(program), mPosition(position), mScale(scale) {

	}

	virtual ~IHUDNode() = default;

	virtual void draw() {
		mProgram->use();
		mProgram->uniformPush("uTextureUnit",
		FILLWAVE_DIFFUSE_UNIT);
	   mProgram->uniformPush("uPosition", mPosition);
	   mProgram->uniformPush("uScale", mScale);
		mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		mTexture->unbind();
	}

protected:
	pTexture2D mTexture;
	pProgram mProgram;
	glm::vec2 mPosition;
	glm::vec2 mScale;
};

} /* namespace framework */
typedef std::shared_ptr<framework::IHUDNode> pIHUDNode;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_IHUD_NODE_H_ */
