/*
 * MeshTerrain.h
 *
 *  Created on: Apr 20, 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_TERRAIN_MESHTERRAIN_H_
#define INC_FILLWAVE_TERRAIN_MESHTERRAIN_H_

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
   MeshTerrain(Engine* engine,
         pProgram program,
         terrain::TerrainConstructor* constructor,
         const models::Material& material,
         const std::string& diffuseMapPath,
         const std::string& normalMapPath,
         const std::string& specularMapPath,
         GLuint radius,
         GLuint density = 8);

   virtual ~MeshTerrain();

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
