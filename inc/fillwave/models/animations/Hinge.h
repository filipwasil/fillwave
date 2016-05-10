/*
 * Hinge.h
 *
 *  Created on: Jan 9, 2016
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

#ifndef SRC_MODELS_HINGE_H_
#define SRC_MODELS_HINGE_H_

#include <fillwave/models/Entity.h>
#include <fillwave/common/Macros.h>

namespace fillwave {
namespace framework {

/*! \class Hinge
 * \brief Entity capable of populating the draw method towards children.
 */

class Hinge: public Entity {
 public:
	Hinge() = default;
	virtual ~Hinge() = default;

	/* IDrawable */
	void draw(ICamera& camera);
	void drawPBRP(ICamera& camera);
	void drawDR(ICamera& camera);

	/* IRenderable */
	void updateRenderer(IRenderer& renderer) override;
	bool getRenderItem(RenderItem& item) override;
};

} /* namespace framework */
typedef std::unique_ptr<framework::Hinge> puHinge;
static puHinge buildHinge() {
	return std::make_unique<framework::Hinge>();
}
} /* namespace fillwave */

#endif /* SRC_MODELS_HINGE_H_ */
