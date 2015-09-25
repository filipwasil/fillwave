/*
 * EmiterPointStep.h
 *
 *  Created on: Sep 10, 2014
 *      Author: Filip Wasil
 */

#ifndef EmiterPointStep_H_
#define EmiterPointStep_H_

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

#include <fillwave/particles/EmiterPoint.h>
#include <fillwave/animation/Key.h>

namespace fillwave {
class Engine;
namespace particles {

/*! \class EmiterPointStep
 * \brief Not used.
 */

class EmiterPointStep: public EmiterPoint {
public:
	EmiterPointStep(
			Engine* engine,
			GLint howMany,
			GLenum blendingSource,
			GLenum blendingDestination,
			pTexture texture);

	virtual ~EmiterPointStep();
};

} /* particles */
} /* fillwave */

#endif /* EmiterPointStep_H_ */
