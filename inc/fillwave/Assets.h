/*
 * Assets.h
 *
 *  Created on: Jun 9, 2014
 *      Author: Filip Wasil
 */

#ifndef FILLWAVE_ASSETS_H_
#define FILLWAVE_ASSETS_H_

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

#include <fillwave/Config.h>

#ifdef FILLWAVE_COMPILATION_TINY_ASSET_LOADER

#include <tinyobjloader/tiny_obj_loader.h>

typedef aiAnimation fAnimation;
typedef aiBone fBone;
typedef aiScene fScene;
typedef aiNodeAnim fNodeAnim;
typedef aiString std::string;

#define FILLWAVE_TEXTURE_TYPE_NONE 0
#define FILLWAVE_TEXTURE_TYPE_DIFFUSE 0
#define FILLWAVE_TEXTURE_TYPE_NORMALS 0
#define FILLWAVE_TEXTURE_TYPE_SPECULAR 0

#define FILLWAVE_PROCESS_TRIANGULATE 0
#define FILLWAVE_PROCESS_SORT_BY_P_TYPE 0
#define FILLWAVE_PROCESS_CALC_TANGENT_SPACE 0

#else

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <assimp/material.h>

#define FILLWAVE_DO_NOT_ANIMATE -1
#define FILLWAVE_MAX_BONES 45
#define FILLWAVE_MAX_BONES_DEPENDENCIES 4

/* Types */
typedef aiAnimation fAnimation;
typedef aiBone fBone;
typedef aiScene fScene;
typedef aiNodeAnim fNodeAnim;
typedef aiString fString;
typedef aiMaterial fMaterial;
typedef aiNode fNode;
typedef aiMesh fMesh;

/* Constants */
#define FILLWAVE_TEXTURE_TYPE_NONE aiTextureType_NONE
#define FILLWAVE_TEXTURE_TYPE_DIFFUSE aiTextureType_DIFFUSE
#define FILLWAVE_TEXTURE_TYPE_NORMALS aiTextureType_NORMALS
#define FILLWAVE_TEXTURE_TYPE_SPECULAR aiTextureType_SPECULAR

#define FILLWAVE_PROCESS_TRIANGULATE aiProcess_Triangulate
#define FILLWAVE_PROCESS_SORT_BY_P_TYPE aiProcess_SortByPType
#define FILLWAVE_PROCESS_CALC_TANGENT_SPACE aiProcess_CalcTangentSpace

#endif /* FILLWAVE_COMPILATION_TINY_ASSET_LOADER */

#endif /* FILLWAVE_ASSETS_H_ */
