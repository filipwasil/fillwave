/*
 * TestLoader.cpp
 *
 *  Created on: Jun 9, 2014
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

#include <fillwave/loaders/TestLoader.h>
#include <fillwave/extras/Log.h>

FLOGINIT("TestLoader", FERROR | FFATAL)

namespace fillwave {
namespace loader {

TestLoader::TestLoader(const std::string& pFile):mFileName(pFile) {

}

TestLoader::~TestLoader() {

}

void TestLoader::testFile() {
   Assimp::Importer importer;
   const fScene* scene = importer.ReadFile(mFileName.c_str(),
         FILLWAVE_PROCESS_TRIANGULATE |
         FILLWAVE_PROCESS_SORT_BY_P_TYPE |
         FILLWAVE_PROCESS_CALC_TANGENT_SPACE);

   if (!scene) {
      FLOG_ERROR("ASSIMP ERROR: %s", importer.GetErrorString());
      return;
   }
   testScene(scene);
}

void TestLoader::printVertices(const fScene* assimpScene, GLint meshID) {
   if (assimpScene->mMeshes[meshID]->HasPositions()) {
      for (GLuint j = 0; j < assimpScene->mMeshes[meshID]->mNumVertices; j++) {
         FLOG_INFO("Vertex %d : %f %f %f", j,
               assimpScene->mMeshes[meshID]->mVertices[j].x,
               assimpScene->mMeshes[meshID]->mVertices[j].y,
               assimpScene->mMeshes[meshID]->mVertices[j].z);
      }
   }
}

void TestLoader::printNormals(const fScene* assimpScene, GLint meshID) {
   if (assimpScene->mMeshes[meshID]->HasNormals()) {
      for (GLuint j = 0; j < assimpScene->mMeshes[meshID]->mNumVertices; j++) {
         FLOG_INFO("Normal %d : %f %f %f", j,
               assimpScene->mMeshes[meshID]->mNormals[j].x,
               assimpScene->mMeshes[meshID]->mNormals[j].y,
               assimpScene->mMeshes[meshID]->mNormals[j].z);
      }
   }
}

void TestLoader::printUV(const fScene* assimpScene, GLint meshID) {
   // k - texture map index
   // i - mesh id
   // j - UV index
   for (GLuint k = 0; k < assimpScene->mMeshes[meshID]->GetNumUVChannels(); k++) {
      FLOG_INFO("UV Channel %d: ", k);
      if (assimpScene->mMeshes[meshID]->HasTextureCoords(k)) {
         for (GLuint j = 0; j < assimpScene->mMeshes[meshID]->mNumVertices; j++) {
            if (assimpScene->mMeshes[meshID]->mNumUVComponents[k] == 1) {
               FLOG_INFO("UV: %f ",
                     assimpScene->mMeshes[meshID]->mTextureCoords[k][j].x);
            }
            if (assimpScene->mMeshes[meshID]->mNumUVComponents[k] == 2) {
               FLOG_INFO("UV: %f %f",
                     assimpScene->mMeshes[meshID]->mTextureCoords[k][j].x,
                     assimpScene->mMeshes[meshID]->mTextureCoords[k][j].y);
            }
            if (assimpScene->mMeshes[meshID]->mNumUVComponents[k] == 3) {
               FLOG_INFO("UV: %f %f %f",
                     assimpScene->mMeshes[meshID]->mTextureCoords[k][j].x,
                     assimpScene->mMeshes[meshID]->mTextureCoords[k][j].y,
                     assimpScene->mMeshes[meshID]->mTextureCoords[k][j].z);
            }
         }
      }
   }
}

void TestLoader::printTangents(const fScene* assimpScene, GLint meshID) {

}

void TestLoader::printBitangents(const fScene* assimpScene, GLint meshID){

}

void TestLoader::printIndices(const fScene* assimpScene, GLint meshID){
   if (assimpScene->mMeshes[meshID]->HasFaces()) {
      for (GLuint j = 0; j < assimpScene->mMeshes[meshID]->mNumFaces; j++) {
         for (GLuint k = 0; k < assimpScene->mMeshes[meshID]->mFaces[j].mNumIndices;
               k++) {
            FLOG_INFO("Face index %d: %d", k,
            assimpScene->mMeshes[meshID]->mFaces[j].mIndices[k]);
         }
      }
   }
}

void TestLoader::testScene(const fScene* assimpScene) {
   FLOG_INFO("assimpScene mFlags: %x", assimpScene->mFlags); // Any combination of the AI_SCENE_FLAGS_XXX flags.
   FLOG_INFO("assimpScene mNumAnimations: %d", assimpScene->mNumAnimations); // The number of animations in the scene.
   FLOG_INFO("assimpScene mNumCameras: %d", assimpScene->mNumCameras); // The number of cameras in the scene.
   FLOG_INFO("assimpScene mNumLights: %d", assimpScene->mNumLights); // The number of light sources in the scene.
   FLOG_INFO("assimpScene mNumMaterials: %d", assimpScene->mNumMaterials); // The number of materials in the scene.
   FLOG_INFO("assimpScene mNumMeshes: %d", assimpScene->mNumMeshes); // The number of meshes in the scene.
   FLOG_INFO("assimpScene mNumTextures: %d", assimpScene->mNumTextures); //The number of textures embedded into the file.

   for (GLuint i = 0; i < assimpScene->mNumMeshes; i++) {
      printInfoShort(assimpScene, i);
   }
}

void TestLoader::printTree(const fScene* assimpScene) {
   printNameNode(assimpScene->mRootNode, 0);
}

void TestLoader::printNameNode(aiNode* node, GLint recursion) {
   FLOG_INFO("assimpNode mName: %s", node->mName.C_Str()); //The number of textures embedded into the file.
   for (GLuint i = 0; i < node->mNumChildren; i++) {
      printNameNode(node->mChildren[i], i);
   }
}

void TestLoader::printNamesMesh(const fScene* assimpScene) {
   for (GLuint j = 0; j < assimpScene->mNumMeshes; j++) {
      FLOG_INFO("assimpMesh name: %s", assimpScene->mMeshes[j]->mName.C_Str());
   }
}

void TestLoader::printInfoShort(const fScene* assimpScene, GLint meshID) {
   if (assimpScene->mMeshes[meshID]) {
      fMesh* mesh = assimpScene->mMeshes[meshID];
      FLOG_INFO("assimpMesh mNumAnimMeshes: %x", mesh->mNumAnimMeshes); // Any combination of the AI_SCENE_FLAGS_XXX flags.
      FLOG_INFO("assimpMesh mMaterialIndex: %d", mesh->mMaterialIndex); // The number of animations in the scene.
      FLOG_INFO("assimpMesh mNumBones: %d", mesh->mNumBones); // The number of cameras in the scene.
      FLOG_INFO("assimpMesh mNumFaces: %d", mesh->mNumFaces); // The number of light sources in the scene.
      FLOG_INFO("assimpMesh mNumUVComponents[0]: %d", mesh->mNumUVComponents[0]); // The number of materials in the scene.
      FLOG_INFO("assimpMesh mNumUVComponents[1]: %d", mesh->mNumUVComponents[1]); // The number of meshes in the scene.
      FLOG_INFO("assimpMesh mNumUVComponents[2]: %d", mesh->mNumUVComponents[2]); //The number of textures embedded into the file.
      FLOG_INFO("assimpMesh mNumUVComponents[3]: %d", mesh->mNumUVComponents[3]); //The number of textures embedded into the file.
      FLOG_INFO("assimpMesh mNumUVComponents[4]: %d", mesh->mNumUVComponents[4]); //The number of textures embedded into the file.
      FLOG_INFO("assimpMesh mNumUVComponents[5]: %d", mesh->mNumUVComponents[5]); //The number of textures embedded into the file.
      FLOG_INFO("assimpMesh mNumUVComponents[6]: %d", mesh->mNumUVComponents[6]); //The number of textures embedded into the file.
      FLOG_INFO("assimpMesh mNumUVComponents[7]: %d", mesh->mNumUVComponents[7]);
      FLOG_INFO("assimpMesh mNumVertices: %d", mesh->mNumVertices);
      FLOG_INFO("assimpMesh mPrimitiveTypes: %d", mesh->mPrimitiveTypes);
      FLOG_INFO("assimpMesh GetNumColorChannels: %d", mesh->GetNumColorChannels());
      FLOG_INFO("assimpMesh GetNumUVChannels: %d", mesh->GetNumUVChannels());
      FLOG_INFO("assimpMesh name: %s", mesh->mName.C_Str());
   }
}

} /* loader */
} /* fillwave */
