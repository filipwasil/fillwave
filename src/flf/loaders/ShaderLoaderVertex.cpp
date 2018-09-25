/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <flw/flf/loaders/ShaderLoaderVertex.h>
#include <flw/flf/loaders/modelloader/ModelLoaderTraits.h>
#include <flw/cmn/Strings.h>
#include <flw/flf/loaders/ModelLoader.h>
#include <flw/PlatformSW.h>

namespace flw {
namespace flf {

ShaderLoaderVertex::ShaderLoaderVertex(bool animated)
    : mAnimated(animated) {
  // nothing
}

const std::string ShaderLoaderVertex::getSource() const {

  std::string attributes = "layout(location = 0) " + mGLVaryingIn + " vec4 aPosition;                        \n"
      "layout(location = 1) " + mGLVaryingIn + " vec4 aColor;                           \n"
                               "layout(location = 2) " + mGLVaryingIn + " vec3 aNormal;                          \n"
                               "layout(location = 3) " + mGLVaryingIn + " vec3 aNormalTangent;                   \n"
                               "layout(location = 4) " + mGLVaryingIn + " vec2 aTextureCoordinate;               \n"
                               "layout(location = 5) " + mGLVaryingIn + " ivec4 aBoneID;                         \n"
                               "layout(location = 6) " + mGLVaryingIn + " vec4 aWeight;                          \n";

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

          "uniform mat4 uBones[" + to_string(ModelLoader::COUNT_BONES_DEFINED) + "];\n";

  std::string mainStart =

      "void main() {\n";

  std::string mainBones =

      "   mat4 BoneTransform = "
          "      uBones[aBoneID.x] * aWeight.x +                          \n"
          "      uBones[aBoneID.y] * aWeight.y +                          \n"
          "      uBones[aBoneID.z] * aWeight.z +                          \n"
          "      uBones[aBoneID.w] * aWeight.w                            \n"
          ";\n";

  std::string mainComputations =

      "   vVertexWorldSpace = uModelMatrix * aPosition;\n"
          "   vVertexNormal = (uModelMatrix * vec4(aNormal, 0.0)).xyz;\n"
          "   vVertexNormalTangent = (uModelMatrix * vec4(aNormalTangent, 0.0)).xyz;\n"
          "   vTextureCoordinate = " + std::string(FILLWAVE_OS_TEXTURE_SAMPLE_FACTOR) + " * aTextureCoordinate;\n"
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
    main = uniformsBones + mainStart + mainBones + mainComputationsWithBones + mainEnd;
  } else {
    main = mainStart + mainComputations + mainEnd;
  }

  return mGLVersion + mGLVertexPrecision + attributes + outputs + uniforms + main;
}

} /* flf */
} /* flw */
