/*
 * MeshTerrain.h
 *
 *  Created on: Apr 20, 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_TERRAIN_MESHTERRAIN_H_
#define INC_FILLWAVE_TERRAIN_MESHTERRAIN_H_

#include <fillwave/models/Mesh.h>
#include <fillwave/models/Programmable.h>
#include <fillwave/terrain/TerrainConstructor.h>

namespace fillwave {
class Engine;
}

namespace fillwave {
namespace terrain {

/*! \class MeshTerrain
 * \brief Programmable to provide mesh terrain functionality.
 */

class MeshTerrain: public models::Programmable {
public:
	MeshTerrain(
			Engine* engine,
			pProgram program,
			terrain::TerrainConstructor* constructor,
			const models::Material& material,
			const std::string& diffuseMapPath,
			const std::string& normalMapPath,
			const std::string& specularMapPath,
			GLuint radius,
			GLuint density = 8);

	virtual ~MeshTerrain() = default;

	void draw(space::Camera& camera);

private:
	GLfloat mChunkWidth;
	GLfloat mJumpStep;

	void distanceCheck(space::Camera& camera);
};

} /* model */
typedef std::shared_ptr<terrain::MeshTerrain> pMeshTerrain;
} /* fillwave */

#endif /* INC_FILLWAVE_TERRAIN_MESHTERRAIN_H_ */
