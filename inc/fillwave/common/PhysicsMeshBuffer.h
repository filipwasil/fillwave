/*
 * PhysicsMeshBuffer.h
 *
 *  Created on: 4 mar 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_COMMON_PHYSICSMESHBUFFER_H_
#define INC_FILLWAVE_COMMON_PHYSICSMESHBUFFER_H_

#include <memory>

namespace fillwave {
namespace framework {
/*! \struct PhysicsMeshBuffer
 * \brief Physical mesh data.
 */

struct PhysicsMeshBuffer {
	GLint mNumFaces;
	std::vector<glm::vec3> mVertices;
	std::vector<GLint> mIndices;
};
} /* framework */
typedef std::unique_ptr<framework::PhysicsMeshBuffer> puPhysicsMeshBuffer;
} /* fillwave */

#endif /* INC_FILLWAVE_COMMON_PHYSICSMESHBUFFER_H_ */
