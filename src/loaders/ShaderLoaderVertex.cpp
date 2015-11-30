/*
 * ShaderLoaderVertex.cpp
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

#include <fillwave/loaders/ShaderLoaderVertex.h>
#include <fillwave/Profiler.h>
#include <fillwave/Assets.h>
#include <fillwave/common/string.h>

namespace fillwave {
namespace loader {

ShaderLoaderVertex::ShaderLoaderVertex(bool animated)
		: mAnimated(animated) {

}

const std::string ShaderLoaderVertex::getSource() const {

	std::string attributes =
			"layout(location = 0) " + mGLVaryingIn + " vec4 aPosition;                        \n"
					"layout(location = 1) " + mGLVaryingIn + " vec4 aColor;                           \n"
					"layout(location = 2) " + mGLVaryingIn + " vec3 aNormal;                          \n"
					"layout(location = 3) " + mGLVaryingIn + " vec3 aNormalTangent;                   \n"
					"layout(location = 4) " + mGLVaryingIn + " vec2 aTextureCoordinate;               \n"
#if FILLWAVE_MAX_BONES_DEPENDENCIES == 8
			"layout(location = 5) " + mGLVaryingIn + " ivec4 aBoneID;                         \n"
			"layout(location = 6) " + mGLVaryingIn + " ivec4 aBoneID2;                        \n"
			"layout(location = 7) " + mGLVaryingIn + " vec4 aWeight;                          \n"
			"layout(location = 8) " + mGLVaryingIn + " vec4 aWeight2;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 7
			"layout(location = 5) " + mGLVaryingIn + " ivec4 aBoneID;                         \n"
			"layout(location = 6) " + mGLVaryingIn + " ivec3 aBoneID2;                        \n"
			"layout(location = 7) " + mGLVaryingIn + " vec4 aWeight;                          \n"
			"layout(location = 8) " + mGLVaryingIn + " vec3 aWeight2;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 6
			"layout(location = 5) " + mGLVaryingIn + " ivec4 aBoneID;                         \n"
			"layout(location = 6) " + mGLVaryingIn + " ivec2 aBoneID2;                        \n"
			"layout(location = 7) " + mGLVaryingIn + " vec4 aWeight;                          \n"
			"layout(location = 8) " + mGLVaryingIn + " vec2 aWeight2;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 5
			"layout(location = 5) " + mGLVaryingIn + " ivec4 aBoneID;                         \n"
			"layout(location = 6) " + mGLVaryingIn + " int aBoneID2;                          \n"
			"layout(location = 7) " + mGLVaryingIn + " vec4 aWeight;                          \n"
			"layout(location = 8) " + mGLVaryingIn + " float aWeight2;                        \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 4
			"layout(location = 5) " + mGLVaryingIn + " ivec4 aBoneID;                         \n"
			"layout(location = 6) " + mGLVaryingIn + " vec4 aWeight;                          \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 3
	"layout(location = 5) " + mGLVaryingIn + " ivec3 aBoneID;                         \n"
	"layout(location = 6) " + mGLVaryingIn + " vec3 aWeight;                          \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 2
	"layout(location = 5) " + mGLVaryingIn + " ivec2 aBoneID;                         \n"
	"layout(location = 6) " + mGLVaryingIn + " vec2 aWeight;                          \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 1
	"layout(location = 5) " + mGLVaryingIn + " int aBoneID;                           \n"
	"layout(location = 6) " + mGLVaryingIn + " float aWeight;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 0
#else
#error "Too many bone dependencies"
#endif

	std::string outputs =

	"" + mGLVaryingOut + " vec4 vColor;\n"
			"" + mGLVaryingOut + " vec2 vTextureCoordinate;\n"
			"" + mGLVaryingOut + " vec3 vVertexNormal; // N\n"
			"" + mGLVaryingOut + " vec3 vVertexNormalTangent;\n"
			"" + mGLVaryingOut + " vec4 vVertexWorldSpace;\n"
			"" + mGLVaryingOut + " vec3 vCameraPosition;\n\n";

	std::string uniforms =

	"uniform mat4 uModelMatrix;\n"
			"uniform mat4 uViewProjectionMatrix;\n"
			"uniform mat3 uNormalViewMatrix;\n"
			"uniform mat4 uColorMatrix;\n"
			"uniform mat4 uShadowBiasMatrix;\n"
			"uniform vec3 uCameraPosition;\n\n";

	std::string uniformsBones =

	"uniform float uTime;\n"

			"uniform mat4 uBones[" + common::to_string(FILLWAVE_MAX_BONES)
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

	return mGLVersion + mGLVertexPrecision +  attributes + outputs + uniforms + main;
}

} /* loader */
} /* fillwave */
