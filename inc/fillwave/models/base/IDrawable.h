/*
 * IDrawable.h
 *
 *  Created on: Jan 1, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MODELS_BASE_IDRAWABLE_H_
#define INC_FILLWAVE_MODELS_BASE_IDRAWABLE_H_

#include <memory>
#include <unordered_map>
#include <vector>

namespace fillwave {
namespace framework {

class ICamera;
class Entity;

class IDrawable {
public:
	IDrawable() = default;
	virtual ~IDrawable() = default;
	virtual void draw(ICamera& camera) = 0;
	virtual void drawPBRP(ICamera& camera) = 0;
	virtual void drawDR(ICamera& camera) = 0;
	virtual void drawDepth(ICamera& camera) = 0;
	virtual void drawDepthColor(ICamera& camera, glm::vec3& position) = 0;
	virtual void drawAOG(ICamera& camera) = 0;
	virtual void drawAOC(ICamera& camera) = 0;
	virtual void drawOcclusionBox(ICamera& camera) = 0;
	virtual void drawPicking(ICamera& camera) = 0;
	virtual void updateRenderpass(std::unordered_map<GLuint, std::vector<Entity*> >& renderpasses) = 0;
};

} /* namespace framework */
typedef std::shared_ptr<framework::IDrawable> pIDrawable;
typedef std::unique_ptr<framework::IDrawable> pIuDrawable;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MODELS_BASE_IDRAWABLE_H_ */
