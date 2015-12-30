/*
 * Painter.h
 *
 *  Created on: Oct 6, 2014
 *      Author: Filip Wasil
 */

#ifndef PAINTER_H_
#define PAINTER_H_

#include <fillwave/models/effects/Effect.h>

namespace fillwave {
namespace framework {

/*! \class Painter
 * \brief Effect to draw a mesh with single color.
 */

class Painter: public Effect {
public:
	Painter(glm::vec4 color);
	virtual ~Painter() = default;
	void setColor(glm::vec4 color);
	void preDrawAction(core::Program* program);
	void postDrawAction(core::Program* program);
	void stopAction(core::Program* program);
	void startAction(core::Program* program);

private:
	glm::vec4 mColor;
};

} /* framework */
typedef std::shared_ptr<framework::Painter> pPainter;
} /* fillwave */

#endif /* PAINTER_H_ */
