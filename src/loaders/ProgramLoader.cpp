/*
 * Copyright (c) 2018, Fillwave developers
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/loaders/ShaderLoaderFragment.h>
#include <fillwave/loaders/ShaderLoaderVertex.h>
#include <fillwave/Fillwave.h>
#include <fillwave/common/Strings.h>
#include <fillwave/management/LightSystem.h>
#include <fstream>

namespace flw {
namespace flf {

constexpr GLuint FILLWAVE_RANDOM_VECTOR_SIZE = 64;

/* Headers */
#if defined(FILLWAVE_GLES_3_0)
const std::string gGLVersion = "#version 300 es\n";
#else /* defined(FILLWAVE_GLES_3_0) */
#if defined(FILLWAVE_COMPILATION_OPENGL_4_5)
const std::string gGLVersion = "#version 450 core\n";
#else /* defined(FILLWAVE_COMPILATION_OPENGL_4_5) */
const std::string gGLVersion = "#version 330 core\n";
#endif /* defined(FILLWAVE_COMPILATION_OPENGL_4_5) */
#endif /* defined(FILLWAVE_GLES_3_0) */

const std::string gGLFragmentPrecision = "precision lowp float;\n";
const std::string gGLVertexPrecision = "precision mediump float;\n";

const std::string gGLVaryingIn = "in";
const std::string gGLVaryingOut = "out";
const std::string gGLColorOutDefinition = "out vec4 fColor;\n";
const std::string gGLColorOutAssingment = "fColor";

/* Special values coded in Shaders to enable Deferred rendering */

const std::string gGLCodeZeroDepth = "10000.0";
const std::string gGLAmbient = "10001.0";

/* Attributes */

const std::string gGLBones = "uniform mat4 uBones[" + to_string(FILLWAVE_MAX_BONES) + "];\n";

const std::string gGLVSAttributes = "layout(location = 0) " + gGLVaryingIn +
                                    " vec4 aPosition;                        \n"
                                        "layout(location = 1) " + gGLVaryingIn +
                                    " vec4 aColor;                           \n"
                                        "layout(location = 2) " + gGLVaryingIn +
                                    " vec3 aNormal;                          \n"
                                        "layout(location = 3) " + gGLVaryingIn +
                                    " vec3 aNormalTangent;                   \n"
                                        "layout(location = 4) " + gGLVaryingIn +
                                    " vec2 aTextureCoordinate;               \n"
#if FILLWAVE_MAX_BONES_DEPENDENCIES == 8
"layout(location = 5) " + gGLVaryingIn +
" ivec4 aBoneID;                         \n"
"layout(location = 6) " + gGLVaryingIn +
" ivec4 aBoneID2;                        \n"
"layout(location = 7) " + gGLVaryingIn +
" vec4 aWeight;                          \n"
"layout(location = 8) " + gGLVaryingIn +
" vec4 aWeight2;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 7
"layout(location = 5) " + gGLVaryingIn +
" ivec4 aBoneID;                         \n"
"layout(location = 6) " + gGLVaryingIn +
" ivec3 aBoneID2;                        \n"
"layout(location = 7) " + gGLVaryingIn +
" vec4 aWeight;                          \n"
"layout(location = 8) " + gGLVaryingIn +
" vec3 aWeight2;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 6
"layout(location = 5) " + gGLVaryingIn +
" ivec4 aBoneID;                         \n"
"layout(location = 6) " + gGLVaryingIn +
" ivec2 aBoneID2;                        \n"
"layout(location = 7) " + gGLVaryingIn +
" vec4 aWeight;                          \n"
"layout(location = 8) " + gGLVaryingIn +
" vec2 aWeight2;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 5
"layout(location = 5) " + gGLVaryingIn +
" ivec4 aBoneID;                         \n"
"layout(location = 6) " + gGLVaryingIn +
" int aBoneID2;                          \n"
"layout(location = 7) " + gGLVaryingIn +
" vec4 aWeight;                          \n"
"layout(location = 8) " + gGLVaryingIn +
" float aWeight2;                        \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 4
    "layout(location = 5) " + gGLVaryingIn + " ivec4 aBoneID;                         \n"
                                        "layout(location = 6) " + gGLVaryingIn +
                                    " vec4 aWeight;                          \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 3
"layout(location = 5) " + gGLVaryingIn +
" ivec3 aBoneID;                         \n"
"layout(location = 6) " + gGLVaryingIn +
" vec3 aWeight;                          \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 2
"layout(location = 5) " + gGLVaryingIn +
" ivec2 aBoneID;                         \n"
"layout(location = 6) " + gGLVaryingIn +
" vec2 aWeight;                          \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 1
"layout(location = 5) " + gGLVaryingIn +
" int aBoneID;                           \n"
"layout(location = 6) " + gGLVaryingIn +
" float aWeight;                         \n";
#elif FILLWAVE_MAX_BONES_DEPENDENCIES == 0
#else
#error "Too many bone dependencies"
#endif

const std::string gGLVSBonesTransformation =
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
;
const std::string gGLVSAttributesPosition = "layout(location = 0) " + gGLVaryingIn +
                                            " vec4 aPosition;                        \n";

const std::string gGLVSAttributesQuad = "layout (location = 0) " + gGLVaryingIn + " vec2 aPosition;\n"
    "layout (location = 1) " + gGLVaryingIn + " vec2 aTextureCoordinate;              \n";

const std::string gGLVSAttributesEmiterCPU = "layout (location = 0) " + gGLVaryingIn + " vec3 aVelocity;\n"
    "layout (location = 1) " + gGLVaryingIn + " vec3 aStartPosition;\n"
                                                 "layout (location = 2) " + gGLVaryingIn + " float aStartTime;\n";

const std::string gGLVSAttributesEmiter = "layout(location = 0) " + gGLVaryingIn +
                                          " vec3 aPosition;                             \n"
                                              "layout(location = 1) " + gGLVaryingIn +
                                          " vec3 aVelocity;                             \n"
                                              "layout(location = 2) " + gGLVaryingIn +
                                          " float aSize;                                \n"
                                              "layout(location = 3) " + gGLVaryingIn +
                                          " float aCurtime;                             \n"
                                              "layout(location = 4) " + gGLVaryingIn +
                                          " float aLifetime;                            \n"
                                              "layout(location = 5) " + gGLVaryingIn +
                                          " float aCameraDistance;                      \n";

const std::string gGLVSAttributesAO = "layout(location = 0) " + gGLVaryingIn + " vec4 aPosition;\n"
    "layout(location = 1) " + gGLVaryingIn + " vec4 aColor;\n"
                                          "layout(location = 2) " + gGLVaryingIn + " vec3 aNormal;\n"
                                          "layout(location = 3) " + gGLVaryingIn + " vec3 aNormalTangent;\n";

/* Lights */

const std::string gGLLightDefinitions = "struct Attenuation {\n"
    "   float constant;\n"
    "   float linear;\n"
    "   float exp;\n"
    "};\n"

    "struct Light {\n"
    "   vec3 color;\n"
    "   float ambientIntensity;\n"
    "   float diffuseIntensity;\n"
    "};\n"

    "struct LightPoint {\n"
    "   Light base;\n"
    "   Attenuation attenuation;\n"
    "   vec3 position;\n"
    "   mat4 mvp;\n"
    "};\n"

    "struct LightSpot {\n"
    "   Light base;\n"
    "   Attenuation attenuation;\n"
    "   vec3 position;\n"
    "   float cutOffDistance;\n"
    "   mat4 mvp;\n"
    "};\n"

    "struct LightDirectional {\n"
    "   Light base;\n"
    "   Attenuation attenuation;\n"
    "   vec3 direction;\n"
    "};\n";

const std::string fsEmpty = gGLVersion + gGLFragmentPrecision + "void main() { \n"
    "}             \n";

const std::string vsShadow = gGLVersion + gGLVSAttributesPosition + "uniform mat4 uMVP;                              \n"
    "out vec4 vColor;                                \n"
    "void main() {                                   \n"
    "   gl_Position = uMVP * aPosition;              \n"
    "}                                               \n";

const std::string vsShadowAnimated = gGLVersion + gGLVSAttributes + gGLBones +
                                     "uniform mat4 uMVP;                                             \n"
                                         "out vec4 vColor;                                               \n"
                                         "void main() {                                                  \n"
                                         "   gl_Position = uMVP * (                                      \n" +
                                     gGLVSBonesTransformation +
                                     "      ) * aPosition;                                           \n"
                                         "}                                                              \n";

const std::string vsShadowColorCoded = gGLVersion + gGLVSAttributes + "uniform mat4 uMVP;\n"
    "uniform mat4 uModelMatrix;\n"
    "out vec3 vWorldSpacePosition;\n"
    "void main() {\n"
    "   gl_Position = uMVP * aPosition;\n"
    "   vWorldSpacePosition = (uModelMatrix * aPosition).xyz;\n"
    "}\n";

const std::string vsShadowColorCodedAnimated = gGLVersion + gGLVSAttributes + gGLBones +
                                               "uniform mat4 uMVP;                              \n"
                                                   "uniform mat4 uModelMatrix;                      \n"
                                                   "out vec3 vWorldSpacePosition;                   \n"
                                                   "void main() {\n"
                                                   "   mat4 transformation = " + gGLVSBonesTransformation +
                                               "           ;\n"
                                                   "   gl_Position = uMVP * transformation * aPosition;\n"
                                                   "   vWorldSpacePosition = (uModelMatrix * transformation * aPosition).xyz;\n"
                                                   "}\n";

const std::string fsShadowColorCoded = gGLVersion + gGLFragmentPrecision + "in vec3 vWorldSpacePosition;\n"
    "uniform vec3 uLightPosition;\n" + gGLColorOutDefinition + "void main() {\n"
                                           "   float color = length(vWorldSpacePosition - uLightPosition);\n"
                                           "   " + gGLColorOutAssingment + " = vec4(color, color, color, 1.0);\n"
                                           "}\n";
/* xxx double check this case "out float fColor;\n" */

const std::string fsDebugger = gGLVersion + gGLFragmentPrecision + //xxx low precision
                               "in vec2 vTextureCoordinate;\n"
                                   "uniform sampler2D uTextureUnit;\n"
                                   "uniform float uNearplane;\n"
                                   "uniform float uFarPlane;\n" + gGLColorOutDefinition +
                               "float linearizeDepth(float depth) {\n"
                                   "   return (2.0 * uNearplane) / (uFarPlane + uNearplane - depth * (uFarPlane - uNearplane));\n"
                                   "}\n"
                                   "void main () {\n"
                                   "  vec4 depth = texture (uTextureUnit, vTextureCoordinate);\n"
                                   "  float depthLin = linearizeDepth(depth.z);\n"
                                   "  " + gGLColorOutAssingment + " = vec4(depthLin, depthLin, depthLin,1.0);\n"
                                   "}\n";

const std::string vsDebugger = gGLVersion + gGLVertexPrecision + gGLVSAttributesQuad + "out vec2 vTextureCoordinate;\n"
    "void main () {\n"
    "  vTextureCoordinate = aTextureCoordinate;\n"
    "  gl_Position = vec4 (aPosition, 0.0, 1.0);\n"
    "}\n";

const std::string fsSkybox = gGLVersion + gGLFragmentPrecision + "in vec3 vTextureCoordinate;\n"
    "uniform samplerCube uTextureUnit;\n" + gGLColorOutDefinition + "void main() {\n"
                                 "   " + gGLColorOutAssingment + " = texture(uTextureUnit, vTextureCoordinate);\n"
                                 "}\n";

const std::string fsSkyboxDR = gGLVersion + gGLFragmentPrecision +

                               "layout (location = 0) " + gGLVaryingOut + " vec3 fWorldPosition;\n"
                                   "layout (location = 1) " + gGLVaryingOut + " vec3 fDiffuseTexel;\n"
                                   "layout (location = 2) " + gGLVaryingOut + " vec3 fNormal;\n"
                                   "layout (location = 3) " + gGLVaryingOut + " vec3 fSpecularTexel;\n"

                                   "uniform samplerCube uTextureUnit;\n"

                                   "in vec3 vTextureCoordinate;\n"

                                   "void main() {\n"
                                   "   fWorldPosition = vec3(0.0, 0.0, " + gGLCodeZeroDepth + ");\n"
                                   "   fDiffuseTexel = texture(uTextureUnit, vTextureCoordinate).xyz;\n"
                                   "   fNormal = vec3(0.0);\n"
                                   "   fSpecularTexel = vec3(0.0);\n"
                                   "}\n";

const std::string vsSkybox = gGLVersion + gGLVertexPrecision + gGLVSAttributesPosition + "uniform mat4 uModelMatrix;\n"
    "uniform mat4 uViewProjectionMatrix;\n"
    "uniform vec3 uCameraPosition;\n"
    "out vec3 vTextureCoordinate;\n"
    "void main() {\n"
    "   vec4 position = uViewProjectionMatrix *\n"
    "                   vec4((uModelMatrix * aPosition).xyz + uCameraPosition, aPosition.a);\n"
    "   gl_Position = position;\n"
    "   vTextureCoordinate = aPosition.xyz;\n"
    "}\n";

const std::string fsDRAmbientG = gGLVersion + gGLFragmentPrecision +

                                 "layout (location = 0) " + gGLVaryingOut + " vec3 fWorldPosition;\n"
                                     "layout (location = 1) " + gGLVaryingOut + " vec3 fDiffuseTexel;\n"
                                     "layout (location = 2) " + gGLVaryingOut + " vec3 fNormal;\n"
                                     "layout (location = 3) " + gGLVaryingOut + " vec3 fSpecularTexel;\n"

                                     "uniform sampler2D uTextureUnit;\n"

                                     "in vec2 vTextureCoordinate;\n"

                                     "void main() {\n"
                                     "   fWorldPosition = vec3(0.0, 0.0, " + gGLAmbient + ");\n"
                                     "   fDiffuseTexel = texture(uTextureUnit, vTextureCoordinate).xyz;\n"
                                     "   fNormal = vec3(0.0);\n"
                                     "   fSpecularTexel = vec3(0.0);\n"
                                     "}\n";

const std::string fsHUD = gGLVersion + gGLFragmentPrecision + "in vec2 vTextureCoordinate;\n"
    "in vec2 vScale;\n"
    "uniform sampler2D uDiffuseTextureUnit;\n" + gGLColorOutDefinition + "void main () {\n" + gGLColorOutAssingment +
                          " = texture (uDiffuseTextureUnit, vTextureCoordinate);\n"
                              "}\n"
                              "\n";

const std::string vsHUD = gGLVersion + gGLVertexPrecision + "uniform vec2 uPosition;\n"
    "uniform vec2 uScale;\n"
    "out vec2 vPosition;\n"
    "out vec2 vTextureCoordinate;\n"
    "out vec2 vScale;\n"
    "void main() {\n"
    "   vec4 vertexPosition;\n"
    "   switch(gl_VertexID) {\n"
    "   case 0:\n"
    "      vertexPosition = vec4(0.0, uScale.y, 0.0, 1.0);\n"
    "      break;\n"
    "   case 1:\n"
    "      vertexPosition = vec4(0.0, 0.0, 0.0,1.0);\n"
    "      break;\n"
    "   case 2:\n"
    "      vertexPosition = vec4(uScale.x, uScale.y, 0.0,1.0);\n"
    "      break;\n"
    "   case 3:\n"
    "   default:\n"
    "      vertexPosition = vec4(uScale.x, 0.0, 0.0,1.0);\n"
    "      break;\n"
    "   }\n"
    "   gl_Position = vertexPosition + vec4(uPosition, 0.0, 0.0);\n"
    "   vPosition = vertexPosition.xy + uPosition;\n"
    "   vTextureCoordinate = sign(vertexPosition.xy);\n"
    "   vScale = uScale;\n"
    "}\n";

const std::string fsText = gGLVersion + gGLFragmentPrecision + //xxx low precision
                           "in vec2 vTextureCoordinate;\n"
                               "uniform sampler2D uTextureUnit;\n"
                               "uniform vec4 uColour;\n" + gGLColorOutDefinition + "void main (){\n"
                               "  float pixelSize = 0.001;\n"
                               "  vec4 color = vec4(0.0);\n"
                               "  for (float i=-1.0;i<=1.0;i++)\n"
                               "     for (float j=-1.0;j<=1.0;j++)\n"
                               "        color += texture (uTextureUnit, vTextureCoordinate + pixelSize*vec2(i,j)) * uColour;\n"
                               "  " + gGLColorOutAssingment + " = color * 0.11;\n"
                               "}\n"
                               "\n";

const std::string fsTextBold = gGLVersion + gGLFragmentPrecision + //xxx low precision
                               "in vec2 vTextureCoordinate;\n"
                                   "uniform sampler2D uTextureUnit;\n"
                                   "uniform vec4 uColour;\n" + gGLColorOutDefinition + "void main (){\n"
                                   "  float pixelSize = 0.001;\n"
                                   "  vec4 color = vec4(0.0);\n"
                                   "  for (float i=-1.0;i<=1.0;i++)\n"
                                   "     for (float j=-1.0;j<=1.0;j++)\n"
                                   "        color = max(texture (uTextureUnit, vTextureCoordinate + pixelSize*vec2(i,j)) * uColour, color);\n"
                                   "" + gGLColorOutAssingment + " = color;\n"
                                   "}\n"
                                   "\n";

const std::string vsText = gGLVersion + gGLVertexPrecision + gGLVSAttributesQuad + "out vec2 vTextureCoordinate;\n"
    "void main () {\n"
    "  vTextureCoordinate = aTextureCoordinate;\n"
    "  gl_Position = vec4 (aPosition, 0.0, 1.0);\n"
    "}\n"
    "\n";

const std::string vsGPUEmiter = gGLVersion + gGLVSAttributesEmiter +
                                "uniform float uHowMany, uTime, uLifeTime, uEmissionRate;            \n"
                                    "uniform mediump sampler3D uNoiseSampler;                            \n"
                                    "uniform mat4 uModelMatrix;                                          \n"
                                    "uniform vec3 uCameraPosition, uAcceleration;                        \n"
                                    "uniform vec3 uStartVelocity, uStartPosition;                        \n"
                                    "uniform vec3 uRobustnessVelocity, uRobustnessPosition;              \n"
                                    "out vec3 tfPosition;                                                \n"
                                    "out vec3 tfVelocity;                                                \n"
                                    "out float tfSize;                                                   \n"
                                    "out float tfCurtime;                                                \n"
                                    "out float tfLifetime;                                               \n"
                                    "out float tfCameraDistance;                                         \n"
                                    "float randomValue( inout float seed ) {                             \n"
                                    "   float vertexId = float( gl_VertexID ) / uHowMany;  \n"
                                    "   vec3 texCoord = vec3( uTime, vertexId, seed );                   \n"
                                    "   seed += 0.1;                                                     \n"
                                    "   return texture( uNoiseSampler, texCoord ).r;\n"
                                    "}                                                                   \n"
                                    "void main() {                                                       \n"
                                    "  float seed = uTime;                                               \n"
                                    "  float lifetime = aCurtime - uTime;                                \n"
                                    "  if( lifetime <= 0.0 && randomValue(seed) < uEmissionRate ) {      \n"
                                    "     tfPosition = vec3( (randomValue(seed) - 0.45) * uRobustnessPosition.x + uStartPosition.x,"
                                    "                        (randomValue(seed) - 0.45) * uRobustnessPosition.y + uStartPosition.y,"
                                    "                        (randomValue(seed) - 0.45) * uRobustnessPosition.z + uStartPosition.z) ; \n"
                                    "     tfVelocity = vec3( (randomValue(seed) - 0.45) * uRobustnessVelocity.x + uStartVelocity.x,"
                                    "                        (randomValue(seed) - 0.45) * uRobustnessVelocity.y + uStartVelocity.y,"
                                    "                        (randomValue(seed) - 0.45) * uRobustnessVelocity.z + uStartVelocity.z) ; \n"
                                    "     tfSize = randomValue(seed) * 20.0 + 60.0;                      \n"
                                    "     tfCurtime = uTime;                                             \n"
                                    "     tfLifetime = uLifeTime;                                              \n"
                                    "  } else {                                                          \n"
                                    "     tfPosition = aPosition;                                        \n"
                                    "     tfVelocity = aVelocity;                                        \n"
                                    "     tfSize = aSize;                                                \n"
                                    "     tfCurtime = aCurtime;                                          \n"
                                    "     tfLifetime = aLifetime;                                        \n"
                                    "  }                                                                 \n"
                                    "  vec3 velocity = aVelocity + lifetime * uAcceleration;            \n"
                                    "  vec3 position = aPosition + lifetime * velocity;                 \n"
                                    "  vec4 positionInWorldSpace = uModelMatrix * vec4 (position, 1.0);  \n"
                                    "  tfCameraDistance = length(uCameraPosition - positionInWorldSpace.xyz);\n"
                                    "  gl_Position = vec4( tfPosition, 1.0 );                            \n"
                                    "}                                                                   \n";

const std::string vsParticlesGPU = gGLVersion + gGLVSAttributesEmiter +

                                   "uniform mat4 uModelMatrix, uViewProjectionMatrix;                    \n"
                                       "uniform vec3 uCameraPosition;                                        \n"
                                       "uniform float uTime, uStartSize;                                     \n"
                                       "uniform vec3 uAcceleration;                                          \n"
                                       "                                                                     \n"
                                       "void main() {                                                        \n"
                                       "  float deltaTime = uTime - aCurtime;                                \n"
                                       "  if ( deltaTime <= aLifetime ) {                                    \n"
                                       "    vec3 velocity = aVelocity + deltaTime * uAcceleration;           \n"
                                       "    vec3 position = aPosition + deltaTime * velocity;                \n"
                                       "    vec4 positionInWorldSpace = uModelMatrix * vec4 (position, 1.0); \n"
                                       "    gl_Position = uViewProjectionMatrix * positionInWorldSpace;//gl_Position.z=1.0-vertexId;\n"
                                       "    gl_PointSize = uStartSize * aSize * ( 1.0 - deltaTime / aLifetime ) * inversesqrt(length(positionInWorldSpace.xyz - uCameraPosition ));        \n"
                                       "  }                                                                  \n"
                                       "  else {                                                             \n"
                                       "     gl_Position = vec4( -1000, -1000, 0, 0 );                       \n"
                                       "     gl_PointSize = 0.0;                                             \n"
                                       "  }                                                                  \n"
                                       "}";

const std::string fsParticlesGPU = gGLVersion + gGLFragmentPrecision + //xxx low precision
                                   "uniform vec4 uColor;                                  \n"
                                       "uniform sampler2D uTextureUnit;                       \n"
                                       "uniform float uAlphaCutOff;                           \n" +
                                   gGLColorOutDefinition + "void main() {                                         \n"
                                       "   vec4 texel = texture( uTextureUnit, gl_PointCoord ); \n"
                                       "   " + gGLColorOutAssingment + " = texel * uColor;                        \n"
                                       "   if(length(texel * uColor) < uAlphaCutOff) {                \n"
                                       "      discard;                                        \n"
                                       "   }                                                  \n"
                                       "}                                                     \n";

const std::string fsParticlesCPU = gGLVersion + gGLFragmentPrecision + //xxx low precision
                                   "in float vOpacity;                                           \n"
                                       "" + gGLColorOutDefinition + ""
                                       "uniform sampler2D uTextureUnit;                              \n"
                                       "uniform float uAlphaCutOff;                                  \n"
                                       "uniform vec4 uColor;                                         \n"
                                       "void main () {                                               \n"
                                       "   vec4 texel = texture (uTextureUnit, gl_PointCoord);       \n"
                                       "   vec4 color = texel * uColor;\n"
                                       "   " + gGLColorOutAssingment +
                                   " = vec4 (color.xyz, color.a * vOpacity);            \n"
                                       "   if(color.a < uAlphaCutOff ) { \n"
                                       "      discard;\n"
                                       "   }\n"
                                       "}\n";

const std::string vsParticlesCPU = gGLVersion + gGLVertexPrecision + gGLVSAttributesEmiterCPU +
                                   "uniform mat4 uModelMatrix, uViewProjectionMatrix;\n"
                                       "uniform vec3 uPosition; //  position in world space\n"
                                       "uniform float uTimeElapsed;   // time in seconds\n"
                                       "uniform float uPointSize;   // time in seconds\n"
                                       "uniform float uLifeTime;   // time in seconds\n"
                                       "uniform vec3 uAcceleration;   // 2nd time integral\n"
                                       "uniform vec3 uCameraPosition; // 2nd time integral\n"
                                       "out float vOpacity;\n"
                                       "void main() {\n"
                                       "   float time = mod ( uTimeElapsed - aStartTime, uLifeTime );\n"
                                       "   vOpacity = 0.0;\n"
                                       "   vec3 p = uPosition;\n"
                                       "   // acceleration\n"
                                       "   //position\n"
                                       "   p += aStartPosition + aVelocity * time + 0.5 * uAcceleration * time * time;\n"
                                       "   // Fade to invisible after uLifeTime seconds\n"
                                       "   vOpacity = 1.0 - (time / uLifeTime);\n"
                                       "   vec4 positionInWorldSpace = uModelMatrix * vec4 (p, 1.0);\n"
                                       "   gl_Position = uViewProjectionMatrix * positionInWorldSpace;\n"
                                       "   gl_PointSize = uPointSize * inversesqrt(length(positionInWorldSpace.xyz - uCameraPosition )); // size in pixels\n"
                                       "}\n";

const std::string vsQuad = gGLVersion + gGLVertexPrecision + "out vec2 vPosition;\n"
    "void main() {\n"
    "   vec4 vertexPosition;\n"
    "   switch(gl_VertexID) {\n"
    "   case 0:\n"
    "      vertexPosition = vec4(-1.0, 1.0, 0.0,1.0);\n"
    "      break;\n"
    "   case 1:\n"
    "      vertexPosition = vec4(-1.0, -1.0, 0.0,1.0);\n"
    "      break;\n"
    "   case 2:\n"
    "      vertexPosition = vec4(1.0, 1.0, 0.0,1.0);\n"
    "      break;\n"
    "   case 3:\n"
    "   default:\n"
    "      vertexPosition = vec4(1.0, -1.0, 0.0,1.0);\n"
    "      break;\n"
    "   }\n"
    "   gl_Position = vertexPosition;\n"
    "   vPosition = vertexPosition.xy;\n"
    "}\n";

const std::string fsQuad = gGLVersion + gGLFragmentPrecision + "in vec2 vPosition;\n"
    "out vec4 fColour;\n"
    "uniform sampler2D uPostProcessingSampler;\n"
    "void main () {\n"
    "   //vec4 fColour = texture (uPostProcessingSampler, vec2((vPosition.x+1.0)/2.0, (vPosition.y+1.0)/2.0) );\n"
    "   fColour = texture (uPostProcessingSampler, vec2((vPosition.x+1.0)/2.0, (vPosition.y+1.0)/2.0) );\n"
    "}";

const std::string fsCursor = gGLVersion + gGLFragmentPrecision + "in vec2 vVertexOffset;\n"
    "out vec4 fColour;\n"
    "uniform sampler2D uTextureUnit;\n"
    "void main () {\n"
    "   fColour = texture (uTextureUnit, vec2((vVertexOffset.x+1.0)/2.0, (vVertexOffset.y+1.0)/2.0));\n"
    "}\n";

const std::string vsCursor = gGLVersion + gGLVertexPrecision + "uniform float uSize = 0.1;\n"
    "uniform float uScreenFactor = 1.0;\n"
    "uniform vec2 uPosition = vec2(0.0,0.0);\n"
    "out vec2 vVertexOffset;\n"
    "void main() {\n"
    "   switch(gl_VertexID) {\n"
    "      case 0:\n"
    "         vVertexOffset = vec2(-1.0, 1.0);\n"
    "         break;\n"
    "      case 1:\n"
    "         vVertexOffset = vec2(-1.0, -1.0);\n"
    "         break;\n"
    "      case 2:\n"
    "         vVertexOffset = vec2(1.0, 1.0);\n"
    "         break;\n"
    "      case 3:\n"
    "         vVertexOffset = vec2(1.0, -1.0);\n"
    "      break;\n"
    "   }\n"
    "   gl_Position = vec4(uPosition.x + uSize * vVertexOffset.x, uPosition.y + uSize * vVertexOffset.y * uScreenFactor, 0.0, 1.0);\n"
    "}\n";

const std::string vsCube = gGLVersion + "uniform mat4 uMVP;\n"
    "void main() {\n"
    "   vec4 vertexPosition;\n"
    "   switch(gl_VertexID) {\n"
    "      case 0:\n"
    "         vertexPosition = vec4(-1.0, -1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 1:\n"
    "         vertexPosition = vec4(1.0, -1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 2:\n"
    "         vertexPosition = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 3:\n"
    "         vertexPosition = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 4:\n"
    "         vertexPosition = vec4(-1.0, 1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 5:\n"
    "         vertexPosition = vec4(-1.0, -1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 6:\n"
    "         vertexPosition = vec4(-1.0, -1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 7:\n"
    "         vertexPosition = vec4(1.0, -1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 8:\n"
    "         vertexPosition = vec4(1.0, -1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 9:\n"
    "         vertexPosition = vec4(1.0, -1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 10:\n"
    "         vertexPosition = vec4(-1.0, -1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 11:\n"
    "         vertexPosition = vec4(-1.0, -1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 12:\n"
    "         vertexPosition = vec4(-1.0, 1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 13:\n"
    "         vertexPosition = vec4(1.0, 1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 14:\n"
    "         vertexPosition = vec4(1.0, -1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 15:\n"
    "         vertexPosition = vec4(1.0, -1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 16:\n"
    "         vertexPosition = vec4(-1.0, -1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 17:\n"
    "         vertexPosition = vec4(-1.0, 1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 18:\n"
    "         vertexPosition = vec4(-1.0, 1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 19:\n"
    "         vertexPosition = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 20:\n"
    "         vertexPosition = vec4(1.0, 1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 21:\n"
    "         vertexPosition = vec4(1.0, 1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 22:\n"
    "         vertexPosition = vec4(-1.0, 1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 23:\n"
    "         vertexPosition = vec4(-1.0, 1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 24:\n"
    "         vertexPosition = vec4(1.0, -1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 25:\n"
    "         vertexPosition = vec4(1.0, 1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 26:\n"
    "         vertexPosition = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 27:\n"
    "         vertexPosition = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 28:\n"
    "         vertexPosition = vec4(1.0, -1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 29:\n"
    "         vertexPosition = vec4(1.0, -1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 30:\n"
    "         vertexPosition = vec4(-1.0, 1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 31:\n"
    "         vertexPosition = vec4(-1.0, -1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   case 32:\n"
    "         vertexPosition = vec4(-1.0, -1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 33:\n"
    "         vertexPosition = vec4(-1.0, -1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 34:\n"
    "         vertexPosition = vec4(-1.0, 1.0, 1.0, 1.0);\n"
    "         break;\n"
    "   case 35:\n"
    "   default:\n"
    "         vertexPosition = vec4(-1.0, 1.0, -1.0, 1.0);\n"
    "         break;\n"
    "   };\n"
    "   gl_Position = uMVP * vertexPosition;\n"
    "}\n";

const std::string vsSimpleVertexPass = "uniform mat4 uMVP;\n"
    "void main() {\n"
    "   gl_Position = uMVP * aPosition;\n"
    "}\n";

const std::string vsOcclusionOptimized = gGLVersion + gGLVSAttributesPosition + vsSimpleVertexPass; //xxx rename ?

const std::string vsOcclusion = gGLVersion + gGLVSAttributes + vsSimpleVertexPass;

const std::string fsAOGeometry = gGLVersion + gGLFragmentPrecision + "in vec3 vMVPosition;\n"
    "layout (location = 0) " + gGLVaryingOut + " vec3 fMVPosition;\n"
                                     "void main() {\n"
                                     "   fMVPosition = vMVPosition;\n"
                                     "}\n";

const std::string vsAOGeometry = gGLVersion + gGLVSAttributesAO + "uniform mat4 uMVP;\n"
    "uniform mat4 uMVPosition;\n"
    "out vec3 vMVPosition;\n"
    "void main() {\n"
    "   vMVPosition = (uMVPosition * aPosition).xyz;"
    "   gl_Position = uMVP * aPosition;\n"
    "}\n";

const std::string fsDR = gGLVersion + "in vec4 vVertexWorldSpace;\n"
    "in vec4 vColor;\n"
    "in vec3 vVertexNormal;\n"
    "in vec3 vVertexNormalTangent;\n"
    "in vec2 vTextureCoordinate;\n"

    "layout (location = 0) " + gGLVaryingOut + " vec3 fWorldPosition;\n"
                             "layout (location = 1) " + gGLVaryingOut + " vec3 fDiffuseTexel;\n"
                             "layout (location = 2) " + gGLVaryingOut + " vec3 fNormal;\n"
                             "layout (location = 3) " + gGLVaryingOut + " vec3 fSpecularTexel;\n"

                             "uniform sampler2D uDiffuseTextureUnit;\n"
                             "uniform sampler2D uNormalTextureUnit;\n"
                             "uniform sampler2D uSpecularTextureUnit;\n"

                             "void main() {\n"
                             "   vec3 texelNormal = texture(uNormalTextureUnit, vTextureCoordinate).xyz;\n"
                             "   vec3 Normal = normalize(vVertexNormal);\n"
                             "   vec3 Tangent = normalize(vVertexNormalTangent);\n"

                             "   Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);\n"
                             "   vec3 Bitangent = cross(Tangent, Normal);\n"

                             "   vec3 vertexNormal;\n"

                             "   /* Check if we use normal matrix or not */\n"
                             "   if (length(texelNormal.xyz) == 0.0) {\n"
                             "      vertexNormal = normalize (Normal);\n"
                             "   } else {\n"
                             "      texelNormal = 2.0 * texelNormal - vec3(1.0, 1.0, 1.0);\n"
                             "      mat3 TBN = ( mat3(Tangent, Bitangent, Normal) );\n"
                             "      vertexNormal = TBN * texelNormal;\n"
                             "      vertexNormal = normalize(vertexNormal);\n"
                             "   }\n"

                             "   fWorldPosition = vVertexWorldSpace.xyz;\n"
                             "   fDiffuseTexel = texture(uDiffuseTextureUnit, vTextureCoordinate).xyz + vColor.xyz;\n"
                             "   fSpecularTexel = texture(uSpecularTextureUnit, vTextureCoordinate).rrr * 255.0;\n"
                             "   fNormal = vertexNormal;\n"
                             "}\n\n";

const std::string vsDRShaderQuad = gGLVersion + "void main() {\n"
    "   vec4 vertexPosition;\n"
    "   switch(gl_VertexID) {\n"
    "      case 0:\n"
    "         vertexPosition = vec4(-1.0, 1.0, 0.0,1.0);\n"
    "         break;\n"
    "   case 1:\n"
    "        vertexPosition = vec4(-1.0, -1.0, 0.0,1.0);\n"
    "        break;\n"
    "     case 2:\n"
    "        vertexPosition = vec4(1.0, 1.0, 0.0,1.0);\n"
    "        break;\n"
    "     case 3:\n"
    "     default:\n"
    "        vertexPosition = vec4(1.0, -1.0, 0.0,1.0);\n"
    "        break;\n"
    "   }\n"
    "   gl_Position = vertexPosition;\n"
    "}\n";

const std::string vsDRLightDirectional = gGLVersion + gGLVSAttributesPosition +

                                   "uniform mat4 uMVP;\n"

                                       "void main() {\n"
                                       "   gl_Position = uMVP * aPosition;\n"
                                       "}\n";

const std::string fsDRLightDirectional = gGLVersion + gGLFragmentPrecision + gGLLightDefinitions +

                                   "uniform int uIsAO;\n"
                                       "uniform sampler2D uAOMap;\n"

                                       "uniform sampler2D uShadowMap;\n"
                                       "uniform sampler2D uWorldPositionAttachment;\n"
                                       "uniform sampler2D uDiffuseTexelAttachment;\n"
                                       "uniform sampler2D uNormalAttachment;\n"
                                       "uniform sampler2D uSpecularTexelAttachment;\n"

                                       "uniform LightDirectional uLight;\n"
                                       "uniform vec3 uCameraPosition;\n"
                                       "uniform float uSpecularPower;\n"
                                       "uniform vec2 uScreenSize;\n"

                                       "vec2 CalcTexCoord() {\n"
                                       "   return gl_FragCoord.xy / uScreenSize;\n"
                                       "}\n"

                                       "vec4 CalcLightInternal(Light light,\n"
                                       "   vec3 lightDirection,\n"
                                       "   vec3 WorldPos,\n"
                                       "   vec3 Normal,\n"
                                       "   float specularTexel) {\n"

                                       "   vec4 AmbientColor = vec4(light.color, 1.0) * light.ambientIntensity;\n"

                                       "   if (uIsAO != 0) {\n"
                                       "      AmbientColor *= texture(uAOMap, CalcTexCoord()).r;\n"
                                       "   }\n"

                                       "   float DiffuseFactor = dot(Normal, -lightDirection);\n"

                                       "   vec4 DiffuseColor  = vec4(0, 0, 0, 0);\n"
                                       "   vec4 SpecularColor = vec4(0, 0, 0, 0);\n"

                                       "   if (DiffuseFactor > 0.0) {\n"
                                       "      DiffuseColor = vec4(light.color, 1.0) * light.diffuseIntensity * DiffuseFactor;\n"

                                       "      vec3 VertexToEye = normalize(uCameraPosition - WorldPos);\n"
                                       "      vec3 LightReflect = normalize(reflect(lightDirection, Normal));\n"
                                       "      float SpecularFactor = dot(VertexToEye, LightReflect);\n"
                                       "      SpecularFactor = pow(SpecularFactor, uSpecularPower);\n"
                                       "      if (SpecularFactor > 0.0) {\n"
                                       "          SpecularColor = vec4(light.color, 1.0) * specularTexel * SpecularFactor;\n"
                                       "      }\n"
                                       "   }\n"

                                       "   return (AmbientColor + DiffuseColor + SpecularColor);\n"
                                       "}\n"

                                       "   vec4 CalcDirectionalLight(vec3 WorldPos, vec3 Normal, float speculatTexel) {\n"

                                       "   return CalcLightInternal(uLight.base,\n"
                                       "                             uLight.direction,\n"
                                       "                             WorldPos,\n"
                                       "                             Normal,\n"
                                       "                             speculatTexel);\n"
                                       "}\n"

                                   + gGLColorOutDefinition +

                                   "void main() {\n"
                                       "    vec2 TexCoord = CalcTexCoord();\n"
    "   vec3 WorldPos = texture(uWorldPositionAttachment, TexCoord).xyz;\n"
    "   vec3 Color = texture(uDiffuseTexelAttachment, TexCoord).xyz;\n"
    "   vec3 Normal = texture(uNormalAttachment, TexCoord).xyz;\n"
    "   float specularTexel = texture(uSpecularTexelAttachment, TexCoord).x;\n"

    "   Normal = normalize(Normal);\n"

    "   fColor = vec4(Color, 1.0) * CalcDirectionalLight(WorldPos, Normal, specularTexel);\n"
    "}\n";

const std::string vsDRLightPoint = gGLVersion + gGLVSAttributes + vsSimpleVertexPass;

const std::string fsDRLightPoint = gGLVersion + gGLFragmentPrecision + gGLLightDefinitions +

                             "uniform int uIsAO;\n"
                                 "uniform sampler2D uAOMap;\n"

                                 "uniform sampler2D uShadowMap;\n"
                                 "uniform sampler2D uWorldPositionAttachment;\n"
                                 "uniform sampler2D uDiffuseTexelAttachment;\n"
                                 "uniform sampler2D uNormalAttachment;\n"
                                 "uniform sampler2D uSpecularTexelAttachment;\n"

                                 "uniform LightPoint uLight;\n"
                                 "uniform vec3 uCameraPosition;\n"
                                 "uniform float uSpecularPower;\n"
                                 "uniform vec2 uScreenSize;\n"

                                 "vec2 CalcTexCoord() {\n"
                                 "   return gl_FragCoord.xy / uScreenSize;\n"
                                 "}\n"

                                 "vec4 CalcLightInternal(Light light,\n"
                                 "                       vec3 lightDirection,\n"
                                 "                       vec3 WorldPos,\n"
                                 "                       vec3 Normal,\n"
                                 "                       float specularTexel) {\n"

                                 "   vec4 AmbientColor = vec4(light.color, 1.0) * light.ambientIntensity;\n"

                                 "   if (uIsAO != 0) {\n"
                                 "      AmbientColor *= texture(uAOMap, CalcTexCoord()).r;\n"
                                 "   }\n"

                                 "   float DiffuseFactor = dot(Normal, -lightDirection);\n"

                                 "   vec4 DiffuseColor  = vec4(0, 0, 0, 0);\n"
                                 "   vec4 SpecularColor = vec4(0, 0, 0, 0);\n"

                                 "   if (DiffuseFactor > 0.0) {\n"
                                 "       DiffuseColor = vec4(light.color, 1.0) * light.diffuseIntensity * DiffuseFactor;\n"

                                 "        vec3 VertexToEye = normalize(uCameraPosition - WorldPos);\n"
                                 "        vec3 LightReflect = normalize(reflect(lightDirection, Normal));\n"
                                 "        float SpecularFactor = dot(VertexToEye, LightReflect);\n"
                                 "        SpecularFactor = pow(SpecularFactor, uSpecularPower);\n"
                                 "        if (SpecularFactor > 0.0) {\n"
                                 "            SpecularColor = vec4(light.color, 1.0) * specularTexel * SpecularFactor;\n"
                                 "        }\n"
                                 "    }\n"

                                 "    return (AmbientColor + DiffuseColor + SpecularColor);\n"
                                 "}\n"

                                 "vec4 CalcPointLight(vec3 WorldPos, vec3 Normal, float specularTexel) {\n"
                                 "   vec3 LightDirection = uLight.position-WorldPos;\n"
                                 "   float Distance = length(LightDirection);\n"
                                 "   LightDirection = normalize(LightDirection);\n"

                                 "   vec4 Color = CalcLightInternal(uLight.base, LightDirection, WorldPos, Normal, specularTexel);\n"

                                 "   float attenuation =  uLight.attenuation.constant +\n"
                                 "                        uLight.attenuation.linear * Distance +\n"
                                 "                        uLight.attenuation.exp * Distance * Distance;\n"

                                 "   attenuation = max(1.0, attenuation);\n"

                                 "   return Color / attenuation;\n"
                                 "}\n"

                             + gGLColorOutDefinition +

                             "void main() {\n"
                                 "    vec2 TexCoord = CalcTexCoord();\n"

    "   vec3 WorldPos = texture(uWorldPositionAttachment, TexCoord).xyz;\n"
    "   vec3 Color = texture(uDiffuseTexelAttachment, TexCoord).xyz;\n"
    "   vec3 Normal = texture(uNormalAttachment, TexCoord).xyz;\n"
    "   float specularTexel = texture(uSpecularTexelAttachment, TexCoord).x;\n"
    "   Normal = normalize(Normal);\n"

    "   fColor = vec4(Color, 1.0) * CalcPointLight(WorldPos, Normal, specularTexel);\n"
    "}\n";

const std::string fsDRLightSpot = gGLVersion + gGLFragmentPrecision + gGLLightDefinitions +

                            "uniform sampler2D uShadowMap;\n"

                                "uniform int uIsAO;\n"
                                "uniform sampler2D uAOMap;\n"

                                "uniform sampler2D uWorldPositionAttachment;\n"
                                "uniform sampler2D uDiffuseTexelAttachment;\n"
                                "uniform sampler2D uNormalAttachment;\n"
                                "uniform sampler2D uSpecularTexelAttachment;\n"

                                "uniform LightSpot uLight;\n"
                                "uniform vec3 uCameraPosition;\n"
                                "uniform float uSpecularPower;\n"
                                "uniform vec2 uScreenSize;\n"

                                "vec2 CalcTexCoord() {\n"
                                "   return gl_FragCoord.xy / uScreenSize;\n"
                                "}\n"

                                "float calculateSpotShadowPCF(vec4 spotlightPosition, sampler2D spotShadowMap) {\n"
                                "   vec3 shadowMapUV = spotlightPosition.xyz / spotlightPosition.w;\n"
                                "   float nearestPixel = 0.005;\n"
                                "   float x,y,shadowMapDepth,sum=0.0;\n"
                                "   for (x=-1.0;x<=1.0;x+=1.0) {\n"
                                "     for (y=-1.0;y<=1.0;y+=1.0) {\n"
                                "        shadowMapDepth=texture(spotShadowMap, vec2(shadowMapUV.x + x*nearestPixel, shadowMapUV.y + y*nearestPixel)).x;\n"
                                "        if ( ( shadowMapDepth < shadowMapUV.z - 0.001 )  || shadowMapUV.z <= 0.001 )\n"
                                "           sum += 0.1;\n"
                                "        else\n"
                                "           sum += 1.0;\n"
                                "     }\n"
                                "   }\n"
                                "   return sum*0.11;\n"
                                "}\n"

                                "vec4 CalcLightInternal(Light light,\n"
                                "                      vec3 lightDirection,\n"
                                "                      vec3 WorldPos,\n"
                                "                      vec3 Normal,\n"
                                "                      float specularTexel) {\n"

                                "   vec4 AmbientColor = vec4(light.color, 1.0) * light.ambientIntensity;\n"

                                "   if (uIsAO != 0) {\n"
                                "      AmbientColor *= texture(uAOMap, CalcTexCoord()).r;\n"
                                "   }\n"

                                "   float DiffuseFactor = dot(Normal, lightDirection);\n"

                                "   vec4 DiffuseColor  = vec4(0, 0, 0, 0);\n"
                                "   vec4 SpecularColor = vec4(0, 0, 0, 0);\n"

                                "   if (DiffuseFactor > 0.0) {\n"
                                "     DiffuseColor = vec4(light.color, 1.0) * light.diffuseIntensity * DiffuseFactor;\n"

                                "     vec3 VertexToEye = normalize(uCameraPosition - WorldPos);\n"
                                "     vec3 LightReflect = normalize(reflect(lightDirection, Normal));\n"
                                "     float SpecularFactor = dot(VertexToEye, LightReflect);\n"
                                "     SpecularFactor = pow(SpecularFactor, uSpecularPower);\n"
                                "     if (SpecularFactor > 0.0) {\n"
                                "        SpecularColor = vec4(light.color * specularTexel * SpecularFactor, 1.0);\n"
                                "     }\n"

                                "   }\n"

                                "   return (AmbientColor + DiffuseColor + SpecularColor);\n"
                                "}\n"

                                "vec4 CalcSpotLight(vec3 WorldPos, vec3 Normal, float speculatTexel) {\n"

                                "   float Distance = length(uLight.position-WorldPos);\n"
                                "   float attenuation =  uLight.attenuation.constant +\n"
                                "                        uLight.attenuation.linear * Distance +\n"
                                "                        uLight.attenuation.exp * Distance * Distance;\n"

                                "   attenuation = max(1.0, attenuation) / (calculateSpotShadowPCF(uLight.mvp * vec4(WorldPos, 1.0), uShadowMap));\n"

                                "   return CalcLightInternal(uLight.base,\n"
                                "                            uLight.position-WorldPos,\n"
                                "                            WorldPos,\n"
                                "                            Normal,\n"
                                "                            speculatTexel) / attenuation;\n"
                                "}\n"

                            + gGLColorOutDefinition +

                            "void main() {\n"
                                "    vec2 TexCoord = CalcTexCoord();\n"

    "   vec3 WorldPos = texture(uWorldPositionAttachment, TexCoord).xyz;\n"
    "   vec3 Color = texture(uDiffuseTexelAttachment, TexCoord).xyz;\n"
    "   vec3 Normal = texture(uNormalAttachment, TexCoord).xyz;\n"
    "   float specularTexel = texture(uSpecularTexelAttachment, TexCoord).x;\n"
    "   Normal = normalize(Normal);\n"

    "   fColor = vec4(Color, 1.0) * CalcSpotLight(WorldPos, Normal, specularTexel);\n"
    "}\n";

const std::string fsDRDepthless = gGLVersion + gGLFragmentPrecision + +"uniform sampler2D uDiffuseTexelAttachment;\n"
    "uniform sampler2D uWorldPositionAttachment;\n"
    "uniform vec2 uScreenSize;\n"
    "vec2 CalcTexCoord() {\n"
    "    return gl_FragCoord.xy / uScreenSize;\n"
    "}\n" + gGLColorOutDefinition + "void main() {\n"
                                "   vec2 TexCoord = CalcTexCoord();\n"
                                "   vec3 Color = texture(uDiffuseTexelAttachment, TexCoord).xyz;\n"
                                "   float code = texture(uWorldPositionAttachment, TexCoord).z;\n"
                                //fsSkyboxDR
                                "   if(code == vec3(1.0,1.0," + gGLCodeZeroDepth + ")) {\n"
                                "      fColor = vec4(Color, 1.0);\n"
                                "   } else {\n"
                                "      fColor = vec4(0.0, 0.0, 0.0, 0.0);\n"
                                "   }\n"
                                "}\n";

const std::string fsDRAmbient = gGLVersion + gGLFragmentPrecision + +"uniform sampler2D uDiffuseTexelAttachment;\n"
    "uniform vec2 uScreenSize;\n"
    "vec2 CalcTexCoord() {\n"
    "    return gl_FragCoord.xy / uScreenSize;\n"
    "}\n" + gGLColorOutDefinition + "uniform vec3 uAmbient;"
                              "void main() {\n"
                              "   vec2 TexCoord = CalcTexCoord();\n"
                              "   vec3 Color = texture(uDiffuseTexelAttachment, TexCoord).xyz;\n"
                              "   fColor = vec4(Color * uAmbient, 1.0);\n"
                              "}\n";

const std::string vsAOColor = gGLVersion + gGLVSAttributesPosition + "out vec2 vTextureCoordinate;\n"
    "void main() {\n"
    "   gl_Position = aPosition;\n"
    "   vTextureCoordinate = (aPosition.xy + vec2(1.0)) / 2.0;\n"
    "}\n";

const std::string fsAOColor = gGLVersion + gGLFragmentPrecision + "in vec2 vTextureCoordinate;\n"
    "uniform sampler2D uPositionMap;\n"
    "uniform float uSampleRadius;\n"
    "uniform mat4 uP;\n" + gGLColorOutDefinition + "const int FILLWAVE_RANDOM_VECTORS_SIZE = 64;\n"

                                  "uniform vec3 uRandomVectors[FILLWAVE_RANDOM_VECTORS_SIZE];\n"

                                  "void main() {\n"

                                  "   vec3 texelPosition = texture(uPositionMap, vTextureCoordinate).xyz;\n"

                                  "   float AO = 0.0;\n"

                                  "   for (int i = 0 ; i < FILLWAVE_RANDOM_VECTORS_SIZE ; i++) {\n"
                                  "      vec3 samplePos = texelPosition + uRandomVectors[i];\n"
                                  "      vec4 offset = vec4(samplePos, 1.0);\n"
                                  "      offset = uP * offset;\n"
                                  "      offset.xy /= offset.w;\n"
                                  "      offset.xy = offset.xy * 0.5 + vec2(0.5);\n"
                                  "      float sampleDepth = texture(uPositionMap, offset.xy).b;\n"
                                  "      if (abs(texelPosition.z - sampleDepth) < uSampleRadius) {\n"
                                  "         AO += step(sampleDepth,samplePos.z);\n"
                                  "      }\n"
                                  "   }\n"

                                  "   AO = 1.0 - AO/64.0;\n"

                                  "   fColor = vec4(pow(AO, 2.0));\n"
                                  "}";

const std::string fsStartup = gGLVersion + gGLFragmentPrecision + "#define MAX_ITER 3\n"

    "in vec2 vPosition;\n"
    "out vec4 fColour;\n"

    "uniform float uTime;\n"

    "uniform float uScreenFactor;\n"

    "uniform sampler2D uPostProcessingSampler;\n"

    "void main( void ) {\n"

    "   vec2 coordinates = vec2((vPosition.x*(uScreenFactor) + 1.0) /2.0, (vPosition.y*(uScreenFactor)+1.0)/2.0);\n"

    "   vec4 texel = texture(uPostProcessingSampler, coordinates);\n"

    /* Blur */

    "   float blurFactor = clamp ( 0.01f * (8.0 - 2.0 * uTime)*0.2, 0.0 , 100.0);\n"

    "   for(float i = -1.0; i<=1.0 ; i++) {\n"
    "      for(float j = -1.0; j<=1.0 ; j++) {\n"
    "         vec2 newCoords = vec2(coordinates.x + blurFactor * i, coordinates.y + blurFactor * j);\n"
    "         texel += texture (uPostProcessingSampler, newCoords)*0.11;\n"
    "      }\n"
    "   }\n"

    "vec2 p =  gl_FragCoord.xy * 8.0 / vec2(1900.0,1900.0) - vec2(20.0);\n"
    "vec2 i = p;\n"
    "float c = 1.0;\n"
    "float inten = .05;\n"

    "for (int n = 0; n < MAX_ITER; n++) {\n"
    "      float t = uTime * (1.0 - (3.0 / float(n+1)));\n"

    "      i = p + vec2(cos(t - i.x) + sin(t + i.y),\n"
    "             sin(t - i.y) + cos(t + i.x));\n"

    "      c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),\n"
    "                   p.y / (cos(i.y+t)/inten)));\n"
    "}\n"

    "c /= float(MAX_ITER);\n"
    "c = 1.5 - sqrt(c);\n"

    "vec4 texColor = vec4(0.0, 0.0117647, 0.01568627, 1.0);\n"

    "texColor.rgb *= pow((1.0 / (1.0 - (c + 0.0))), 3.0);\n"

    "   vec3 colorBase = vec3(texColor.xyz*(clamp((8.0 - 0.5 * uTime) * 0.25, 0.0, 2.0) )) + texel.xyz;\n"

    "   fColour = vec4( (1.0-length(vPosition*0.5)) * colorBase * clamp(uTime * 0.25, 0.0, 2.0), 1.0);\n"
    "   if (uTime > 6.0 ) {\n"
    "      fColour = vec4( fColour.xyz * (8.0 - 2.0*(uTime - 4.0)) * 0.25 , 1.0);\n"
    "   }\n"

    /*  Fade with time */
    "   fColour.xyz = fColour.xyz * (1.0 - length(vPosition.xy));\n"

    "}\n";

flc::Program* ProgramLoader::getProgram(EProgram program, const std::string& filenamePrefixForShaders) {
  flc::Program* p = nullptr;
  switch (program)
  {
    case EProgram::basic:
    case EProgram::basicFR:
      p = mEngine->storeProgram("default", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_default.frag", ShaderLoaderFragment().getSource()),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_default.vert", ShaderLoaderVertex().getSource())
      });
      initDefaultUniforms(p);
      break;

    case EProgram::basicAnimated:
    case EProgram::basicAnimatedFR:
      p = mEngine->storeProgram("default_animated", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_default.frag", ShaderLoaderFragment().getSource()),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_default_animated.vert", ShaderLoaderVertex(true).getSource())
      });
      initDefaultUniforms(p);
      break;

    case EProgram::shadow:
      p = mEngine->storeProgram("shadow_mapping", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_empty.frag", fsEmpty),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_internal_shadowing.vert", vsShadow)
      });
      break;

    case EProgram::shadowColorCoded:
      p = mEngine->storeProgram("shadow_mapping_color", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_internal_shadowing_color.frag", fsShadowColorCoded),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_internal_shadowing_color.vert", vsShadowColorCoded)
      });
      break;

    case EProgram::shadowWithAnimation:
      p = mEngine->storeProgram("shadow_mapping_animated", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_empty.frag", fsEmpty),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_internal_shadowing.vert", vsShadowAnimated)
      });
      break;

    case EProgram::shadowColorCodedWithAnimation:
      p = mEngine->storeProgram("shadow_mapping_animated_color", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_internal_shadowing.frag", fsShadowColorCoded),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_internal_shadowing.vert", vsShadowColorCodedAnimated)
      });
      break;

    case EProgram::debugger:
      p = mEngine->storeProgram("debugger", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_ifillwave__debugger.frag", fsDebugger),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_internal_debugger.vert", vsDebugger)
      });
      break;

    case EProgram::skybox:
      p = mEngine->storeProgram("internal_skybox", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_internal_skybox.frag", fsSkybox),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_internal_skybox.vert", vsSkybox)
      });
      break;

    case EProgram::skyboxDR:
      p = mEngine->storeProgram("internal_skybox_dr", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_internal_skybox_dr.frag", fsSkyboxDR),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_internal_skybox.vert", vsSkybox)
      });
      break;

    case EProgram::hud:
      p = mEngine->storeProgram("hud", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_hud.frag", fsHUD),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_hud.vert", vsHUD)
      });
      p->use();
      flc::Uniform::push(glGetUniformLocation(p->getHandle(), "uDiffuseTextureUnit"), FILLWAVE_DIFFUSE_UNIT);
      break;

    case EProgram::text:
      p = mEngine->storeProgram("text", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_internal_text.frag", fsText),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_internal_text.vert", vsText)
      });
      break;

    case EProgram::textBold:
      p = mEngine->storeProgram("text_bold", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_internal_text_bold.frag", fsTextBold),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_internal_text.vert", vsText)
      });
      break;

    case EProgram::particleGPUEmiter:
      p = mEngine->storeProgram("particles_gpu_emiter", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_empty.frag", fsEmpty),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_particles_gpu_emiter.vert", vsGPUEmiter)
      }, GL_TRUE);
      break;

    case EProgram::particleGPU:
      p = mEngine->storeProgram("particles_gpu_program", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_particles_gpu.frag", fsParticlesGPU),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_particles_gpu.vert", vsParticlesGPU)
      });
      break;

    case EProgram::particleCPU:
      p = mEngine->storeProgram("particles_cpu_program", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_particles_cpu.frag", fsParticlesCPU),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_particles_cpu.vert", vsParticlesCPU)
      });
      break;

    case EProgram::particleCPUNoDepthText:
    case EProgram::quad:
      p = mEngine->storeProgram("quad", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_quad.frag", fsQuad),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_quad.vert", vsQuad)
      });
      break;

    case EProgram::quadCustomFragmentShaderStartup:
    case EProgram::cursor:
      p = mEngine->storeProgram("cursor", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_cursor.frag", fsCursor),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_cursor.vert", vsCursor)
      });
      break;

    case EProgram::ambientOcclusionGeometry:
      p = mEngine->storeProgram("ambient_occlusion_geometry", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_ambient_occlusion_geometry.frag", fsAOGeometry),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_ambient_occlusion_geometry.vert", vsAOGeometry)
      });
      break;

    case EProgram::ambientOcclusionColor:
      p = mEngine->storeProgram("ambient_occlusion_color", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_ambient_occlusion_color.frag", fsAOColor),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_ambient_occlusion_color.vert", vsAOColor)
      });
      p->use();
      p->uniformPush("uPositionMap", FILLWAVE_DIFFUSE_ATTACHMENT);

      {
        const float size = static_cast<float>(FILLWAVE_RANDOM_VECTOR_SIZE);
        const float max = static_cast<float>(RAND_MAX) - 1.0f;
        glm::vec3 vectors[FILLWAVE_RANDOM_VECTOR_SIZE];
        for (GLuint i = 0; i < FILLWAVE_RANDOM_VECTOR_SIZE; ++i) {
          const float scale = static_cast<float>(i) / size;
          glm::vec3 v = {
              2.0f * static_cast<float>(rand()) / max,
              2.0f * static_cast<float>(rand()) / max,
              2.0f * static_cast<float>(rand()) / max
          };
          // Use an acceleration function so more points are
          // located closer to the origin
          v *= (0.1f + 0.9f * scale * scale);

          vectors[i] = v;
        }

        p->uniformPush("uRandomVectors[0]", &vectors[0], FILLWAVE_RANDOM_VECTOR_SIZE);
      }
      p->disusePrograms();
      break;

    case EProgram::occlusionPureQuery:
      p = mEngine->storeProgram("occlusion_pure", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_empty.frag", fsEmpty),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_occlusion_pure.vert", vsCube)
      });
      break;

    case EProgram::occlusionQuery:
      p = mEngine->storeProgram("occlusion", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_empty.frag", fsEmpty),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_occlusion.vert", vsOcclusion)
      });
      break;

    case EProgram::occlusionOptimizedQuery:
      p = mEngine->storeProgram("occlusion_optimized", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_empty.frag", fsEmpty),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_occlusion.vert", vsOcclusionOptimized)
      });
      break;

    case EProgram::basicDR:
      p = mEngine->storeProgram("default_dr", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_default_dr.frag", fsDR),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_default_dr.vert", ShaderLoaderVertex().getSource())
      });
      initDefaultUniforms(p);
      break;

    case EProgram::basicAnimatedDR:
      p = mEngine->storeProgram("default_animated_dr", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_default_animated_dr.frag", fsDR),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_default_animated_dr.vert", ShaderLoaderVertex(true)
            .getSource())
      });
      initDefaultUniforms(p);
      break;

    case EProgram::ambientDR:
      p = mEngine->storeProgram("ambient_dr", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_ambient_dr.frag", fsDRAmbient),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_dr_shader_quad.vert", vsDRShaderQuad)
      });
      break;

    case EProgram::depthlessDR:
      p = mEngine->storeProgram("dr_depthless", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_dr_depthless.frag", fsDRDepthless),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_dr_shader_quad.vert", vsDRShaderQuad)
      });
      break;

    case EProgram::directionalLightsDR:
      p = mEngine->storeProgram("dr_directional", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_dr_directional.frag", fsDRLightDirectional),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_dr_shader_quad.vert", vsDRShaderQuad)
      });
      break;

    case EProgram::spotLightsDR:
      p = mEngine->storeProgram("ds_spot", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_ds_spot.frag", fsDRLightSpot),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_dr_shader_quad.vert", vsDRShaderQuad)
      });
      break;

    case EProgram::pointLightsDR:
      p = mEngine->storeProgram("ds_point", {
          mEngine->storeShader<GL_FRAGMENT_SHADER>("fillwave_ds_point.frag", fsDRLightPoint),
          mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_ds_point.vert", vsDRLightPoint)
      });
      break;
  }
  if (!filenamePrefixForShaders.empty()) {
    p->log(filenamePrefixForShaders);
  }
  return p;
}

flc::Program* ProgramLoader::getQuadCustomFragmentShader(const std::string &shaderPath) {
  return mEngine->storeProgram("program_" + shaderPath, {
      mEngine->storeShader<GL_FRAGMENT_SHADER>(shaderPath),
      mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_quad_custom.vert", vsQuad)
  });
}

flc::Program* ProgramLoader::getHUDCustomFragmentShader(const std::string &shaderPath) {
  flc::Program *p = mEngine->storeProgram(shaderPath, {
      mEngine->storeShader<GL_FRAGMENT_SHADER>(shaderPath),
      mEngine->storeShader<GL_VERTEX_SHADER>("fillwave_hud.vert", vsHUD)
  });

  GLint location = glGetUniformLocation(p->getHandle(), "uDiffuseTextureUnit");

  if (location != -1) {
    p->use();
    flc::Uniform::push(location, FILLWAVE_DIFFUSE_UNIT);
  }

  glGetError(); /* Suppress error if happened */
  return p;
}

void ProgramLoader::initDefaultUniforms(flc::Program *program) {
  GLint location[10];

  location[0] = glGetUniformLocation(program->getHandle(), "uLightAmbientIntensity");
  location[1] = glGetUniformLocation(program->getHandle(), "uNumberOfPointLights");
  location[2] = glGetUniformLocation(program->getHandle(), "uNumberOfSpotLights");
  location[3] = glGetUniformLocation(program->getHandle(), "uFogEffect");
  location[4] = glGetUniformLocation(program->getHandle(), "uPainterEffect");
  location[5] = glGetUniformLocation(program->getHandle(), "uTextureOnlyEffect");
  location[6] = glGetUniformLocation(program->getHandle(), "uBoostColorEffect");
  location[7] = glGetUniformLocation(program->getHandle(), "uDiffuseTextureUnit");
  location[8] = glGetUniformLocation(program->getHandle(), "uNormalTextureUnit");
  location[9] = glGetUniformLocation(program->getHandle(), "uSpecularTextureUnit");

  program->use();

  if (location[0] != -1) {
    flc::Uniform::push(location[0], glm::vec4(0.2, 0.2, 0.2, 1.0));
  }
  if (location[1] != -1) {
    flc::Uniform::push(location[1], 0);
  }
  if (location[2] != -1) {
    flc::Uniform::push(location[2], 0);
  }
  if (location[3] != -1) {
    flc::Uniform::push(location[3], false);
  }
  if (location[4] != -1) {
    flc::Uniform::push(location[4], false);
  }
  if (location[5] != -1) {
    flc::Uniform::push(location[5], false);
  }
  if (location[6] != -1) {
    flc::Uniform::push(location[6], false);
  }
  if (location[7] != -1) {
    flc::Uniform::push(location[7], FILLWAVE_DIFFUSE_UNIT);
  }
  if (location[8] != -1) {
    flc::Uniform::push(location[8], FILLWAVE_NORMAL_UNIT);
  }
  if (location[9] != -1) {
    flc::Uniform::push(location[9], FILLWAVE_SPECULAR_UNIT);
  }

  flc::Program::disusePrograms();

  /* Ignore errors*/
  glGetError();
}

ProgramLoader::ProgramLoader(Engine *engine)
    : mEngine(engine) {

}

} /* flf */
} /* flw */
