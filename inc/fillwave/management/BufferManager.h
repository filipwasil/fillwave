/*
 * BufferManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef BUFFERMANAGER_H_
#define BUFFERMANAGER_H_

#include <fillwave/core/buffers/Buffer.h>
#include <fillwave/models/base/IReloadable.h>

namespace fillwave {
namespace framework {

/*! \class ManagerBuffers
 * \brief Connects VAO pointer and VAO's user pointer in single class.
 */
typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexArray,
        IReloadable*> ManagerBuffers;

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferBasic,
        core::VertexArray*, framework::TerrainConstructor*, GLint, GLfloat,
        std::vector<GLuint>&> ManagerVertices;

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::IndexBufferBasic,
        core::VertexArray*, std::vector<GLuint>&> ManagerIndices;

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferText,
		core::VertexArray*, const std::vector<GLfloat>&, const std::vector<GLfloat>&> ManagerVerticesText;

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::IndexBufferParticles,
        core::VertexArray*, GLuint> ManagerIndicesParticles;

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferParticlesGPU,
        core::VertexArray*, std::vector<core::VertexParticleGPU>&> ManagerVerticesParticlesGPU;

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferParticles,
        core::VertexArray*, std::vector<GLfloat>&, std::vector<GLfloat>&, std::vector<GLfloat>&> ManagerVerticesParticles;

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferDebug,
        core::VertexArray*, GLfloat> ManagerVerticesDebugger;

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferDebug,
        core::VertexArray*, GLfloat> ManagerVerticesDebugger;

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferFloat,
        core::VertexArray*, std::vector<core::VertexFloat>&> ManagerVerticesFloat;

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferPosition,
        core::VertexArray*, std::vector<core::VertexPosition>&> ManagerVerticesPosition;

} /* framework */
} /* fillwave */

#endif /* BUFFERMANAGER_H_ */
