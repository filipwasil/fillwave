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

namespace fillwave {
namespace framework {

class Entity;

class IRenderer : public std::unordered_map<GLuint, std::vector<Entity*>> {
public:
	IRenderer():mRefresh(true) {

	}

	virtual ~IRenderer() = default;

	void setRefresh(bool refresh) {
		mRefresh = refresh;
	}

	bool getRefresh() const {
		return mRefresh;
	}

private:
	bool mRefresh;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_CORE_RENDERERS_RENDERER_H_ */
