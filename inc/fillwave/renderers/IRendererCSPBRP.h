/*
 * IRendererCSPBRP.h
 *
 *  Created on: Jan 23, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_RENDERERS_IRENDERERCSPBRP_H_
#define INC_FILLWAVE_RENDERERS_IRENDERERCSPBRP_H_

#include <fillwave/renderers/IRenderer.h>
#include <fillwave/models/base/IRenderable.h>
#include <vector>
#include <unordered_map>

namespace fillwave {
namespace framework {

class LightManager;

/*! \class IRendererCSPBRP
 * \brief Cache Safe Program Based Render Pass IRenderer. Not ready (Rev.4.2.1).
 */

class IRendererCSPBRP: public IRenderer {
  public:
	IRendererCSPBRP(LightManager* lightManager);
	virtual ~IRendererCSPBRP() = default;

	void update(IRenderable* renderable) override;
	void draw(ICamera& camera) override;
	void reset(GLuint width, GLuint height) override;
	void clear() override;

  private:
	std::unordered_map<GLuint, std::vector<std::vector<RenderItem>>>mRenderPasses;
	LightManager* mLightManager;
};

}
/* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_RENDERERS_IRENDERERCSPBRP_H_ */
