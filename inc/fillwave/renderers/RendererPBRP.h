/*
 * RendererPBRP.h
 *
 *  Created on: Dec 31, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_CORE_RENDERERS_RENDERERPBRP_H_
#define INC_FILLWAVE_CORE_RENDERERS_RENDERERPBRP_H_

#include <fillwave/renderers/IRenderer.h>

namespace fillwave {
namespace framework {

class RendererPBRP: public IRenderer {
public:
	RendererPBRP() = default;
	virtual ~RendererPBRP() = default;

	void update(GLuint programId, Entity* entity);
	void draw(ICamera& camera);
	void reset();

private:
	std::unordered_map<GLuint, std::vector<Entity*>> mRenderPasses;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_CORE_RENDERERS_RENDERERPBRP_H_ */
