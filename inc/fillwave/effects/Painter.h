/*
 * Painter.h
 *
 *  Created on: Oct 6, 2014
 *      Author: Filip Wasil
 */

#ifndef PAINTER_H_
#define PAINTER_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/effects/Effect.h>

namespace fillwave {
namespace effects {

/*! \class Painter
 *
 * \brief Effect to draw a mesh with single color.
 *
 */

class Painter: public Effect {
public:
	Painter(glm::vec4 color);
	virtual ~Painter();
	void setColor(glm::vec4 color);
	void preDrawAction(core::Program* program);
	void postDrawAction(core::Program* program);
	void stopAction(core::Program* program);
	void startAction(core::Program* program);

private:
	glm::vec4 mColor;
};

} /* effects */
typedef std::shared_ptr<effects::Painter> pPainter;
} /* fillwave */

#endif /* PAINTER_H_ */
