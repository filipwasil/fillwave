/*
 * IRenderer.h
 *
 *  Created on: Dec 31, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_CORE_RENDERERS_RENDERER_H_
#define INC_FILLWAVE_CORE_RENDERERS_RENDERER_H_

#include <fillwave/OpenGL.h>
#include <unordered_map>
#include <vector>
#include <memory>

namespace fillwave {
namespace framework {

class ICamera;
class Entity;

class IRenderer {
public:
	IRenderer()
			: mFlagReload(true) {

	}

	virtual ~IRenderer() = default;

	virtual void update(GLuint* id, Entity* entity) = 0;
	virtual void draw(ICamera& camera) = 0;
	virtual void reset() = 0;

	bool mFlagReload;
};

} /* namespace framework */
typedef std::unique_ptr<framework::IRenderer> puIRenderer;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_CORE_RENDERERS_RENDERER_H_ */
