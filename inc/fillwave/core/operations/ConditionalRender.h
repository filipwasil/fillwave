/*
 * ConditionalRender.h
 *
 *  Created on: May 17, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_OPERATIONS_CONDITIONALRENDER_H_
#define INC_FILLWAVE_OPERATIONS_CONDITIONALRENDER_H_

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

#ifdef __ANDROID__
#else

#include <fillwave/OpenGL.h>

namespace fillwave {
namespace core {

/*! \class ConditionalRender
 * \brief Operation of rendering only meshes passing the occlusion test.
 */

class ConditionalRender {
private:
   GLenum mMode;

public:

	/*!
	 * \brief Specifies the conditional rendering pass mode.
	 *
	 * \param Possible modes:
	 *  GL_QUERY_WAIT,
	 *  GL_QUERY_NO_WAIT,
	 *  GL_QUERY_BY_REGION_WAIT,
	 *  GL_QUERY_BY_REGION_NO_WAIT,
	 */

   ConditionalRender(GLenum mode);

   virtual ~ConditionalRender();

   void begin(GLuint querryID);

   void end();
};

} /* core */
} /* fillwave */

#endif

#endif /* INC_FILLWAVE_OPERATIONS_CONDITIONALRENDER_H_ */
