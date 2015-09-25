/*
 * Terrain.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
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
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/terrain/Terrain.h>
#include <fillwave/Fillwave.h>

FLOGINIT("Terrain", FERROR | FFATAL)

namespace fillwave {
namespace terrain {

Terrain::Terrain(GLint radius, GLfloat gap)
:mRadius(radius),
 mGap(gap){
}

Terrain::~Terrain() {

}

void Terrain::draw(space::Camera& camera) {
   drawVoxels(camera);
}

void Terrain::drawVoxels(space::Camera& camera) {
   /* Parent-children transformations */
   updateMatrixTree();

   /* check if there are any children too far away from the camera */
   glm::vec3 distanceToCamera;
   GLfloat direction = 0.0f;

   GLint cenralChunkIndex = ((mRadius*2+1)*(mRadius*2+1)-1)/2;
   distanceToCamera = camera.getTranslation() - glm::vec3(mVoxelChunks[cenralChunkIndex]->getTranslation());

   GLfloat singleChunkWidth = FILLWAVE_VOXEL_CHUNK_SIZE*mGap*mRadius;
   GLfloat maximumDistance = singleChunkWidth*0.5;

   if ( glm::abs(distanceToCamera.x) > maximumDistance) {//OK
      if ( distanceToCamera.x > 0.0f) {
         direction = 1.0;
      } else {
         direction = -1.0;
      }
      for (auto it : mVoxelChunks) {
         it->moveBy(glm::vec3(direction * singleChunkWidth, 0.0, 0.0));//OK
      }
   }

   if ( glm::abs(distanceToCamera.z) > maximumDistance) {//OK
      if ( distanceToCamera.z > 0.0f) {
         direction = 1.0;
      } else {
         direction = -1.0;
      }
      for (auto it : mVoxelChunks) {
         it->moveBy(glm::vec3(0.0, 0.0, direction * singleChunkWidth));//OK
      }
   }

   for (auto it : mVoxelChunks) {
      it->draw(camera);
   }
}

void Terrain::addChunk(pVoxelChunk chunk) {
   mVoxelChunks.push_back(chunk);
}

} /* models */
} /* fillwave */
