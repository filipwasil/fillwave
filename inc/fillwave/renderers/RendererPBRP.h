/*
 * RendererPBRP.h
 *
 *  Created on: Dec 31, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_CORE_RENDERERS_RENDERERPBRP_H_
#define INC_FILLWAVE_CORE_RENDERERS_RENDERERPBRP_H_

#include <fillwave/renderers/IRenderer.h>
#include <unordered_map>
#include <vector>

namespace fillwave {
namespace framework {

/*! \class RendererPBRP
 * \brief Program based render pases
 */

class RendererPBRP: public IRenderer {
 public:
	RendererPBRP() = default;
	virtual ~RendererPBRP() = default;

	void update(IRenderable* renderable) override;
	void draw(ICamera& camera) override;
	void reset(GLuint width, GLuint height) override;
	void clear() override;

 private:
	std::unordered_map<GLuint, std::vector<IRenderable*> > mRenderPasses;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_CORE_RENDERERS_RENDERERPBRP_H_ */
