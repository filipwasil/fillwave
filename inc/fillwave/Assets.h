/*
 * Assets.h
 *
 *  Created on: Jun 9, 2014
 *      Author: Filip Wasil
 */

#ifndef FILLWAVE_ASSETS_H_
#define FILLWAVE_ASSETS_H_

#include <fillwave/Config.h>

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <assimp/material.h>
#else
#include <tinyobjloader/tiny_obj_loader.h>
#endif

//constexpr int FILLWAVE_DO_NOT_ANIMATE = -1;
//constexpr int FILLWAVE_MAX_BONES = 45;
//constexpr int FILLWAVE_MAX_BONES_DEPENDENCIES = 4;
// for #if FILLWAVE_MAX_BONES_DEPENDENCIES == 8 constexpr is not visible

#define FILLWAVE_DO_NOT_ANIMATE -1
#define FILLWAVE_MAX_BONES 45
#define FILLWAVE_MAX_BONES_DEPENDENCIES 4

#endif /* FILLWAVE_ASSETS_H_ */
