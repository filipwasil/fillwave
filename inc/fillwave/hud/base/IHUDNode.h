/*
 * IHUDNode.h
 *
 *  Created on: Jan 10, 2016
 *      Author: filip
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
	   core::Program* program,
	   glm::vec2 position,
	   glm::vec2 scale) :
		mTexture(texture),
		mProgram(program),
		mPosition(position),
		mScale(scale),
		mBlending( {
		GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
	}) {

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
	core::Program* mProgram;
	glm::vec2 mPosition;
	glm::vec2 mScale;
	Blending mBlending;
};

} /* namespace framework */
typedef std::shared_ptr<framework::IHUDNode> pIHUDNode;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_IHUD_NODE_H_ */
