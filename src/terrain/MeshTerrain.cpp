/*
 * MeshTerrain.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2012 - 2015 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/terrain/MeshTerrain.h>

#include <fillwave/extras/Log.h>

#include <fillwave/Fillwave.h>

FLOGINIT("MeshTerrain", FERROR | FFATAL)

namespace fillwave {
namespace terrain {

MeshTerrain::MeshTerrain(Engine* engine,
   pProgram program,
   terrain::TerrainConstructor* constructor,
   const models::Material& material,
   const std::string& diffuseMapPath,
   const std::string& normalMapPath,
   const std::string& specularMapPath,
   GLuint radius,
   GLuint density)
:models::Programmable(program),
 mChunkWidth(radius * 0.2 * 16/density),
 mJumpStep(density * 0.2 * 16/density) {

   models::Material _material;

   pTexture diffuseMap = engine->storeTexture(
               diffuseMapPath.c_str(), aiTextureType_DIFFUSE);

   pTexture normalMap = engine->storeTexture(
              normalMapPath.c_str(), aiTextureType_NORMALS);

   pTexture specularMap = engine->storeTexture(
               specularMapPath.c_str(), aiTextureType_SPECULAR);


   int index, pointsWidth, pointsWidthNext, offset, quadID = 0;

   std::vector<GLuint> indices;

   indices.reserve(density*density);

   for (int z=0; z<density; z++) {
      for (int x=0; x<density; x++) {
         pointsWidth = density + 1;
         pointsWidthNext = density + 2;
         offset = x + z * pointsWidth;
         indices.push_back(0 + offset);
         indices.push_back(pointsWidth + offset);
         indices.push_back(pointsWidthNext + offset);
         indices.push_back(1 + offset);
         indices.push_back(0 + offset);
         indices.push_back(pointsWidthNext + offset);
      }
   }

   GLfloat gapSize = 0.2 * 16/density;
   GLint indexTerrainChunk = radius;

   loader::ProgramLoader loader;

   for (GLint x=-indexTerrainChunk; x<=indexTerrainChunk; x++) {
      for (GLint z=-indexTerrainChunk; z<=indexTerrainChunk; z++) {
         pMesh ptr = pMesh(new models::Mesh(engine,
                           _material,
                           buildTextureRegion(diffuseMap),
                           buildTextureRegion(normalMap),
                           buildTextureRegion(specularMap),
                           program,
                           loader.getShadow(engine),
                           loader.getShadowColorCoded(engine),
                           loader.getOcclusionOptimizedQuery(engine),
                           loader.getAmbientOcclusionGeometry(engine),
                           loader.getAmbientOcclusionColor(engine),
                           engine->getLightManager(),
                           pVertexBufferBasic(new core::VertexBufferBasic(constructor, density, gapSize, indices)),
                           pIndexBufferBasic(new core::IndexBufferBasic(indices))));

         ptr->moveTo(glm::vec3(density * gapSize * (GLfloat(x)),
                               0.0,
                               density * gapSize * (GLfloat(z))));
         attach(ptr);
      }
   }
}

MeshTerrain::~MeshTerrain() {

}

void MeshTerrain::draw(space::Camera& camera) {
   updateMatrixTree();
   distanceCheck(camera);
   drawWithEffects(camera);
}

inline void MeshTerrain::distanceCheck(space::Camera& camera) {
   /* check if there are any children too far away from the camera */
   glm::vec3 distanceToCamera;
   GLfloat direction = 0.0f;

   distanceToCamera = camera.getTranslation() - getTranslation();

   GLfloat maximumDistance = mJumpStep*2;
   GLfloat jumpStep = mJumpStep*2 ;
   if (glm::abs(distanceToCamera.x) > maximumDistance) { //OK
      if (distanceToCamera.x > 0.0f) {
         direction = 1.0;
      } else {
         direction = -1.0;
      }
      moveBy(glm::vec3(direction * jumpStep, 0.0, 0.0));
   }

   if (glm::abs(distanceToCamera.z) > maximumDistance) { //OK
      if (distanceToCamera.z > 0.0f) {
         direction = 1.0;
      } else {
         direction = -1.0;
      }
      moveBy(glm::vec3(0.0, 0.0, direction * jumpStep));
   }
}

} /* models */
} /* fillwave */
