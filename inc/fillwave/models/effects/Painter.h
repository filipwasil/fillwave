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

class Painter: public IEffect {
 public:
	Painter(glm::vec4 color);
	virtual ~Painter() = default;
	void setColor(glm::vec4 color);
	void preDrawAction(core::Program* program) override;
	void postDrawAction(core::Program* program) override;
	void stopAction(core::Program* program) override;
	void startAction(core::Program* program) override;

 private:
	glm::vec4 mColor;
};

} /* framework */
typedef std::shared_ptr<framework::Painter> pPainter;
} /* fillwave */

#endif /* PAINTER_H_ */
