/*
 * ShaderLoaderVertex.cpp
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2015] Filip Wasil
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

#include <fillwave/loaders/ShaderLoaderVertex.h>
#include <fillwave/Profiler.h>
#include <fillwave/Assets.h>
#include <fillwave/extras/string.h>

namespace fillwave {
namespace loader {

ShaderLoaderVertex::ShaderLoaderVertex(
		eShaderLoaderOpenGLVersion version,
		eShaderLoaderPrecision precisionInt,
		eShaderLoaderPrecision precisionFloat,
		bool animated)
		: ShaderLoader(version, precisionInt, precisionFloat), mAnimated(animated) {

}

ShaderLoaderVertex::~ShaderLoaderVertex() {

}

const std::string ShaderLoaderVertex::getSource() {

	std::string version =

	(mVersion == eShaderLoaderOpenGLVersion::OpenGL ?
			"#version 330 core\n" : "#version 300 es\n\n");

	std::string attributes =
			"layout(location = 0) in vec4 aPosition;                        \n"
					"layout(location = 1) in vec4 aColor;                           \n"
					"layout(location = 2) in vec3 aNormal;                          \n"
					"layout(location = 3) in vec3 aNormalTangent;                   \n"
					"layout(location = 4) in vec2 aTextureCoordinate;               \n"
#if FILLWAVE_MAX_BONES_DEPENDENCIES == 8
			"layout(location = 5) in ivec4 aBoneID;                         \n"
			"layout(location = 6) in ivec4 aBoneID2;                        \n"
			"layout(location = 7) in vec4 aWeight;                          \n"
			"layout(location = 8) in vec4 aWeight2;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 7
			"layout(location = 5) in ivec4 aBoneID;                         \n"
			"layout(location = 6) in ivec3 aBoneID2;                        \n"
			"layout(location = 7) in vec4 aWeight;                          \n"
			"layout(location = 8) in vec3 aWeight2;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 6
			"layout(location = 5) in ivec4 aBoneID;                         \n"
			"layout(location = 6) in ivec2 aBoneID2;                        \n"
			"layout(location = 7) in vec4 aWeight;                          \n"
			"layout(location = 8) in vec2 aWeight2;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 5
			"layout(location = 5) in ivec4 aBoneID;                         \n"
			"layout(location = 6) in int aBoneID2;                          \n"
			"layout(location = 7) in vec4 aWeight;                          \n"
			"layout(location = 8) in float aWeight2;                        \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 4
			"layout(location = 5) in ivec4 aBoneID;                         \n"
			"layout(location = 6) in vec4 aWeight;                          \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 3
	"layout(location = 5) in ivec3 aBoneID;                         \n"
	"layout(location = 6) in vec3 aWeight;                          \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 2
	"layout(location = 5) in ivec2 aBoneID;                         \n"
	"layout(location = 6) in vec2 aWeight;                          \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 1
	"layout(location = 5) in int aBoneID;                           \n"
	"layout(location = 6) in float aWeight;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 0
#else
#error "Too many bone dependencies"
#endif

	std::string outputs =

	"out vec4 vColor;\n"
			"out vec2 vTextureCoordinate;\n"
			"out vec3 vVertexNormal; // N\n"
			"out vec3 vVertexNormalTangent;\n"
			"out vec4 vVertexWorldSpace;\n"
			"out vec3 vCameraPosition;\n\n";

	std::string uniforms =

	"uniform mat4 uModelMatrix;\n"
			"uniform mat4 uViewProjectionMatrix;\n"
			"uniform mat3 uNormalViewMatrix;\n"
			"uniform mat4 uColorMatrix;\n"
			"uniform mat4 uShadowBiasMatrix;\n"
			"uniform vec3 uCameraPosition;\n\n";

	std::string uniformsBones =

	"uniform float uTime;\n"

			"uniform mat4 uBones[" + strings::to_string(FILLWAVE_MAX_BONES)
			+ "];\n";

	std::string mainStart =

	"void main() {\n";

	std::string mainBones =

			"   mat4 BoneTransform = "
#if FILLWAVE_MAX_BONES_DEPENDENCIES == 8
			"      uBones[aBoneID.x] * aWeight.x +                          \n"
			"      uBones[aBoneID.y] * aWeight.y +                          \n"
			"      uBones[aBoneID.z] * aWeight.z +                          \n"
			"      uBones[aBoneID.w] * aWeight.w +                          \n"
			"      uBones[aBoneID2.x] * aWeight2.x +                        \n"
			"      uBones[aBoneID2.y] * aWeight2.y +                        \n"
			"      uBones[aBoneID2.z] * aWeight2.z +                        \n"
			"      uBones[aBoneID2.w] * aWeight2.w                          \n"
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 7
			"      uBones[aBoneID.x] * aWeight.x +                          \n"
			"      uBones[aBoneID.y] * aWeight.y +                          \n"
			"      uBones[aBoneID.z] * aWeight.z +                          \n"
			"      uBones[aBoneID.w] * aWeight.w +                          \n"
			"      uBones[aBoneID2.x] * aWeight2.x +                        \n"
			"      uBones[aBoneID2.y] * aWeight2.y +                        \n"
			"      uBones[aBoneID2.z] * aWeight2.z                          \n"
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 6
			"      uBones[aBoneID.x] * aWeight.x +                          \n"
			"      uBones[aBoneID.y] * aWeight.y +                          \n"
			"      uBones[aBoneID.z] * aWeight.z +                          \n"
			"      uBones[aBoneID.w] * aWeight.w +                          \n"
			"      uBones[aBoneID2.x] * aWeight2.x +                        \n"
			"      uBones[aBoneID2.y] * aWeight2.y                          \n"
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 5
			"      uBones[aBoneID.x] * aWeight.x +                          \n"
			"      uBones[aBoneID.y] * aWeight.y +                          \n"
			"      uBones[aBoneID.z] * aWeight.z +                          \n"
			"      uBones[aBoneID.w] * aWeight.w +                          \n"
			"      uBones[aBoneID2.x] * aWeight2.x                          \n"
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 4
					"      uBones[aBoneID.x] * aWeight.x +                          \n"
					"      uBones[aBoneID.y] * aWeight.y +                          \n"
					"      uBones[aBoneID.z] * aWeight.z +                          \n"
					"      uBones[aBoneID.w] * aWeight.w                            \n"
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 3
			"      uBones[aBoneID.x] * aWeight.x +                          \n"
			"      uBones[aBoneID.y] * aWeight.y +                          \n"
			"      uBones[aBoneID.z] * aWeight.z                            \n"
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 2
			"      uBones[aBoneID.x] * aWeight.x +                          \n"
			"      uBones[aBoneID.y] * aWeight.y                            \n"
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 1
			"      uBones[aBoneID.x] * aWeight.x                            \n"
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 0
#else
#error "Too many bone dependencies"
#endif
			";\n";

	std::string mainComputations =

			"   vVertexWorldSpace = uModelMatrix * aPosition;\n"
					"   vVertexNormal = (uModelMatrix * vec4(aNormal, 0.0)).xyz;\n"
					"   vVertexNormalTangent = (uModelMatrix * vec4(aNormalTangent, 0.0)).xyz;\n"
					"   vTextureCoordinate = aTextureCoordinate;\n"
					"   vCameraPosition = uCameraPosition;\n"
					"   vColor = aColor;\n"
					"   gl_Position = uViewProjectionMatrix * vVertexWorldSpace;\n";

	std::string mainComputationsWithBones =

			"   vVertexNormal = (uModelMatrix * BoneTransform * vec4(aNormal, 0.0)).xyz;\n"
					"   vVertexNormalTangent = (uModelMatrix * BoneTransform * vec4(aNormalTangent, 0.0)).xyz;\n"
					"   vVertexWorldSpace = uModelMatrix * BoneTransform * aPosition;\n"
					"   vCameraPosition = uCameraPosition;\n"
					"   vTextureCoordinate = aTextureCoordinate;\n"
					"   vColor = aColor;\n"
					"   gl_Position = uViewProjectionMatrix * vVertexWorldSpace;\n";

	std::string mainEnd = "}\n";

	std::string main;

	if (mAnimated) {
		main = uniformsBones + mainStart + mainBones + mainComputationsWithBones
				+ mainEnd;
	} else {
		main = mainStart + mainComputations + mainEnd;
	}

	return version + attributes + outputs + uniforms + main;
}

} /* loader */
} /* fillwave */
