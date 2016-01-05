/*
 * RendererFR.h
 *
 *  Created on: Jan 4, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_RENDERERS_RENDERERFR_H_
#define INC_FILLWAVE_RENDERERS_RENDERERFR_H_

#include <fillwave/renderers/IRenderer.h>

namespace fillwave {
namespace framework {

class RendererFR: public IRenderer {
public:
	RendererFR() = default;
	virtual ~RendererFR() = default;

	void update(GLuint* programId, Entity* entity);
	void draw(ICamera& camera);
	void reset();
private:
	std::vector<Entity*> mRenderPasses;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_RENDERERS_RENDERERFR_H_ */
