/*
 * BufferSystem.h
 *
 *  Created on: Apr 15, 2016
 *      Author: fiwasi
 */

#ifndef INC_FILLWAVE_MANAGEMENT_BASE_BUFFERSYSTEM_H_
#define INC_FILLWAVE_MANAGEMENT_BASE_BUFFERSYSTEM_H_

#include <fillwave/core/buffers/Buffer.h>
#include <fillwave/models/base/IReloadable.h>

namespace fillwave {
namespace framework {

/*! \class ManagerBuffers
 * \brief Connects VAO pointer and VAO's user pointer in single class.
 */

struct BufferSystem {
	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexArray,
			  IReloadable*> mVertexArrays;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferBasic,
			  core::VertexArray*, framework::TerrainConstructor*, GLint, GLfloat,
			  std::vector<GLuint>&> mVertices;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::IndexBufferBasic,
			  core::VertexArray*, std::vector<GLuint>&> mIndices;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferText,
			  core::VertexArray*, const std::vector<GLfloat>&, const std::vector<GLfloat>&> mVerticesText;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::IndexBufferParticles,
			  core::VertexArray*, GLuint> mIndicesParticles;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferParticlesGPU,
			  core::VertexArray*, std::vector<core::VertexParticleGPU>&> mVerticesParticlesGPU;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferParticles,
			  core::VertexArray*, std::vector<GLfloat>&, std::vector<GLfloat>&, std::vector<GLfloat>&> mVerticesParticles;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferDebug,
			  core::VertexArray*, GLfloat> mVerticesDebugger;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferFloat,
			  core::VertexArray*, std::vector<core::VertexFloat>&> mVerticesFloat;

	TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexBufferPosition,
			  core::VertexArray*, std::vector<core::VertexPosition>&> mVerticesPosition;

};

} /* framework */
} /* fillwave */

#endif /* INC_FILLWAVE_MANAGEMENT_BASE_BUFFERSYSTEM_H_ */
