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
#include <fillwave/core/pipeline/Blending.h>

#include <fillwave/models/base/ITreeNode.h>

namespace fillwave {
namespace framework {

/*! \class IHUDNode
 * \brief HUD base element.
 */

class IHUDNode {
public:
	IHUDNode(
			core::Texture2D* texture,
			pProgram program,
			glm::vec2 position,
			glm::vec2 scale) :
				mTexture(texture),
				mProgram(program),
				mPosition(position),
				mScale(scale),
				mBlending( { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA }) {

	}

	virtual ~IHUDNode() = default;

	void onAttached(ITreeNode* /*node*/) {

	}

	void onDetached() {

	}

	virtual void draw() {
		mProgram->use();
		mProgram->uniformPush("uPosition", mPosition);
		mProgram->uniformPush("uScale", mScale);
		coreDraw();
	}

	void coreDraw() {
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(mBlending.mSrc, mBlending.mSrc);
		mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		mTexture->unbind();
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

protected:
	core::Texture2D* mTexture;
	pProgram mProgram;
	glm::vec2 mPosition;
	glm::vec2 mScale;
	Blending mBlending;
};

} /* namespace framework */
typedef std::shared_ptr<framework::IHUDNode> pIHUDNode;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_IHUD_NODE_H_ */
