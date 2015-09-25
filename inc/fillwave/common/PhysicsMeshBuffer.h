/*
 * PhysicsMeshBuffer.h
 *
 *  Created on: 4 mar 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_COMMON_PHYSICSMESHBUFFER_H_
#define INC_FILLWAVE_COMMON_PHYSICSMESHBUFFER_H_

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
#include <memory>

namespace fillwave {

/*! \struct PhysicsMeshBuffer
 * \brief Physical mesh data.
 */

struct PhysicsMeshBuffer {
   GLint mNumFaces;
   std::vector<glm::vec3> mVertices;
   std::vector<GLint> mIndices;
};

} /* fillwave */

typedef std::unique_ptr<fillwave::PhysicsMeshBuffer> puPhysicsMeshBuffer;

#endif /* INC_FILLWAVE_COMMON_PHYSICSMESHBUFFER_H_ */
