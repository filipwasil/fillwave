/*
 * RendererFR.h
 *
 *  Created on: Jan 4, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_RENDERERS_RENDERERFR_H_
#define INC_FILLWAVE_RENDERERS_RENDERERFR_H_

#include <fillwave/renderers/IRenderer.h>
#include <vector>

namespace fillwave {
namespace framework {

/*! \class RendererFR
 * \brief Forward IRenderer.
 */

class RendererFR: public IRenderer {
public:
	RendererFR() = default;
	virtual ~RendererFR() = default;

	void update(IRenderable* renderable) override;
	void draw(ICamera& camera) override;
	void reset(GLuint width, GLuint height) override;
	void clear() override;
private:
	std::vector<IRenderable*> mRenderPasses;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_RENDERERS_RENDERERFR_H_ */
