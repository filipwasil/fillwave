/*
 * ShaderLoaderFragment.cpp
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

#include <fillwave/common/string.h>
#include <fillwave/loaders/ShaderLoaderFragment.h>

namespace fillwave {
namespace framework {

ShaderLoaderFragment::ShaderLoaderFragment(GLuint renderTargets)
		:
				mFog(GL_FALSE),
				mColor(GL_FALSE),
				mColorBoost(GL_FALSE),
				mTextureOnly(GL_FALSE),
				mPointLights(GL_TRUE),
				mRendertargets(renderTargets) {

}

const std::string ShaderLoaderFragment::getSource() const {

	std::string inputs =

	"" + mGLVaryingIn + " vec4 vColor;\n"
			"" + mGLVaryingIn + " vec2 vTextureCoordinate;\n"
			"" + mGLVaryingIn + " vec3 vVertexNormal;\n"
			"" + mGLVaryingIn + " vec3 vVertexNormalTangent;\n"
			"" + mGLVaryingIn + " vec4 vVertexWorldSpace;\n"
			"" + mGLVaryingIn + " vec3 vCameraPosition;\n\n";

	std::string outputs;
	for (GLuint i = 0; i < mRendertargets; i++) {

		outputs += "" + mGLVaryingOut + " vec4 fColor" + to_string(i) + ";\n";

	}
	outputs += "\n";

	std::string lightsMaximum =

	"#define MAX_SPOT_LIGHTS 4\n"
			"#define MAX_POINT_LIGHTS 4\n"
			"#define MAX_DIRECTIONAL_LIGHTS 4\n\n";

	std::string lightStructDefinition =

	"struct LightPoint {\n"
			"vec4 position;\n"
			"vec4 intensity;\n"
			"mat4 mvp;\n"
			"};\n\n";

	std::string lightUniforms =

	"uniform vec4 uLightAmbientIntensity;\n"
			"uniform vec4 uLightDiffuseIntensity;\n"
			"uniform vec4 uLightSpecularIntensity;\n"
			"uniform LightPoint uPointLights[MAX_POINT_LIGHTS];\n"
			"uniform int uNumberOfPointLights;\n"
			"uniform int uNumberOfSpotLights;\n"
			"layout(std140) uniform uSpotLightsUBO {\n"
			"LightPoint uSpotLights[MAX_SPOT_LIGHTS + MAX_DIRECTIONAL_LIGHTS];\n"
			"};\n\n";

#ifdef FILLWAVE_GLES_3_0
	std::string lightSamplerUniforms =

	"uniform lowp sampler2DShadow uShadowMap0;\n"
	"uniform lowp sampler2DShadow uShadowMap1;\n"
	"uniform lowp sampler2DShadow uShadowMap2;\n"
	"uniform lowp sampler2DShadow uShadowMap3;\n"
	"uniform lowp sampler2DShadow uShadowMap4;\n"
	"uniform lowp sampler2DShadow uShadowMap5;\n"
	"uniform lowp sampler2DShadow uShadowMap6;\n"
	"uniform lowp sampler2DShadow uShadowMap7;\n\n";
#else
	std::string lightSamplerUniforms =

	"uniform samplerCube uPointShadowMap0;\n"
			"uniform samplerCube uPointShadowMap1;\n"
			"uniform samplerCube uPointShadowMap2;\n"
			"uniform samplerCube uPointShadowMap3;\n"

			"uniform sampler2D uShadowMap0;\n"
			"uniform sampler2D uShadowMap1;\n"
			"uniform sampler2D uShadowMap2;\n"
			"uniform sampler2D uShadowMap3;\n"
			"uniform sampler2D uShadowMap4;\n"
			"uniform sampler2D uShadowMap5;\n"
			"uniform sampler2D uShadowMap6;\n"
			"uniform sampler2D uShadowMap7;\n\n";
#endif

	std::string effectsUniforms =

	"uniform bool uColorPicking;\n"

			"uniform bool uFogEffect;\n"
			"uniform vec3 uFogColor;\n"
			"uniform float uFogNearDistance;\n"
			"uniform float uFogFarDistance;\n"

			"uniform bool uPainterEffect;\n"
			"uniform vec4 uPainterColor;\n"

			"uniform bool uTextureOnlyEffect;\n"

			"uniform bool uBoostColorEffect;\n"
			"uniform float uBoostColorFactor;\n";

	std::string textures =

	"uniform sampler2D uDiffuseTextureUnit;\n"
			"uniform sampler2D uNormalTextureUnit;\n"
			"uniform sampler2D uSpecularTextureUnit;\n";

	std::string functions =

#ifdef FILLWAVE_GLES_3_0

			"float clamp_to_border_factor (vec2 coords, bool clamp_to_border) {\n"
			"   bvec2 out1 = greaterThan (coords, vec2 (1,1));\n"
			"   bvec2 out2 = lessThan (coords, vec2 (0,0));\n"
			"   bool do_clamp = (any (out1) || any (out2)) && clamp_to_border;\n"
			"   return float (!do_clamp);\n"
			"}\n"

			"float calculateSpotShadow(vec4 spotlightPosition, sampler2DShadow spotShadowMap) {\n"
			"   return textureProj(spotShadowMap, spotlightPosition) * \n"
			"      clamp_to_border_factor(spotlightPosition.xy/spotlightPosition.w, true);\n"
			"}\n"

			"float calculateSpotShadowPCF(vec4 spotlightPosition, sampler2DShadow spotShadowMap) {\n"
			"   float nearestPixel = 0.005;\n"
			"   float x,y,sum=0.0;\n"
			"   for (x=-1.0;x<=1.0;x+=1.0) {\n"
			"      for (y=-1.0;y<=1.0;y+=1.0) {\n"
			"         sum+=textureProj(spotShadowMap, spotlightPosition + vec4(x*nearestPixel, y*nearestPixel,0.0,0.0));\n"
			"      }\n"
			"   }\n"
			"   return sum*0.11*clamp_to_border_factor(spotlightPosition.xy/spotlightPosition.w, true);\n"
			"}\n"

			"float calcDiffuse(vec3 normal, vec3 direction) {\n"
			"   return clamp( dot(normal, normalize ( direction) ), 0.0, 1.0);\n"
			"}\n";

#else
			"float calculateSpotShadow(vec4 spotlightPosition, sampler2D spotShadowMap) {\n"
					"   vec3 shadowMapUV = spotlightPosition.xyz / spotlightPosition.w;\n"
					"   float shadowMapDepth = texture(spotShadowMap, shadowMapUV.xy).x;\n"

					"   if ( ( shadowMapDepth < shadowMapUV.z - 0.001 ) )\n"
					"      return 0.1;\n"
					"   else\n"
					"      return 1.0;\n"
					"}\n\n"

					"float calculateSpotShadowPCF(vec4 spotlightPosition, sampler2D spotShadowMap) {\n"
					"   vec3 shadowMapUV = spotlightPosition.xyz / spotlightPosition.w;\n"
					"   float nearestPixel = 0.005;\n"
					"   float x,y,shadowMapDepth,sum=0.0;\n"
					"   for (x=-1.0;x<=1.0;x+=1.0) {\n"
					"      for (y=-1.0;y<=1.0;y+=1.0) {\n"
					"         shadowMapDepth=texture(spotShadowMap, vec2(shadowMapUV.x + x*nearestPixel, shadowMapUV.y + y*nearestPixel)).x;\n"
					"         if ( ( shadowMapDepth < shadowMapUV.z - 0.001 )  || shadowMapUV.z <= 0.001 )\n"
					"            sum += 0.1;\n"
					"         else\n"
					"            sum += 1.0;\n"
					"      }\n"
					"   }\n"
					"   return sum*0.11;\n"
					"}\n"

					"float calculatePointShadow(vec3 toLightdirection, samplerCube pointShadowMap) {\n"

					"    float SampledDistance = texture(pointShadowMap, toLightdirection).r;\n"
					"    float Distance = length(toLightdirection);\n"

					"    if (Distance <= SampledDistance + 0.001)\n"
					"        return 1.0;\n"
					"    else\n"
					"        return 0.1;\n"
					"}\n"

					"float calcDiffuse(vec3 normal, vec3 direction) {\n"
					"   return clamp( dot(normal, normalize ( direction) ), 0.0, 1.0);\n"
					"}\n";

#endif

	std::string main =
			"void main() {\n"
					"   /*shadow*/\n"
					"   float shadowFactor;\n"
					"   vec4  lightDepth;\n"

					"   /*common for light models*/\n"
					"   vec4 intensity;\n"
					"   float attenuation;\n"
					"   vec4 color;\n"

					"   /*ambient*/\n"
					"   vec3 ambientFactor = vec3(1.0, 1.0, 1.0) - uLightAmbientIntensity.xyz;\n"

					"   /*diffuse*/\n"
					"   float diffuse;\n"
					"   vec4 diffuseSum;\n"
					"   vec4 colorDiffuse;\n"
					"   vec3 toLightDirection;\n"
#ifdef FILLWAVE_GLES_3_0
			"   vec4 texelDiffuse = uLightDiffuseIntensity * texture(uDiffuseTextureUnit, vTextureCoordinate);\n"
			"   vec3 texelNormal = texture(uNormalTextureUnit, vTextureCoordinate).xyz;\n"
			"   vec4 texelSpecular = uLightSpecularIntensity * texture(uSpecularTextureUnit, vTextureCoordinate) * 255.0;\n"
#else
			"   vec4 texelDiffuse = uLightDiffuseIntensity * texture2D(uDiffuseTextureUnit, vTextureCoordinate);\n"
			"   vec3 texelNormal = texture2D(uNormalTextureUnit, vTextureCoordinate).xyz;\n"
			"   vec4 texelSpecular = uLightSpecularIntensity * texture2D(uSpecularTextureUnit, vTextureCoordinate) * 255.0;\n"
#endif

			"   vec3 vertexNormal;\n"

			"   /* Create TBN normals */\n"
			"   vec3 Normal = normalize(vVertexNormal);\n"
			"   vec3 Tangent = normalize(vVertexNormalTangent);\n"

			"   Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);\n"
			"   vec3 Bitangent = cross(Tangent, Normal);\n"

			"   /* Check if we use normal matrix or not */\n"
			"   if (length(texelNormal.xyz) == 0.0) {\n"
			"      vertexNormal = normalize (Normal);\n"
			"   } else {\n"
			"      texelNormal = 2.0 * texelNormal - vec3(1.0, 1.0, 1.0);\n"
			"      mat3 TBN = ( mat3(Tangent, Bitangent, Normal) );\n"
			"      vertexNormal = TBN * texelNormal;\n"
			"      vertexNormal = normalize(vertexNormal);\n"
			"   }\n"

			"   /*specular*/\n"
			"   float specular;\n"
			"   vec4 specularSum;\n"
			"   vec4 colorSpecular;\n"
			"   float toLightDirectionSqr;\n"
			"   float lightAttenuation = 0.2;\n"
			"   vec3 viewDirection = normalize(vVertexWorldSpace.xyz - vCameraPosition);\n"
			"   int realNumberOfSpotLights = MAX_SPOT_LIGHTS + MAX_DIRECTIONAL_LIGHTS;\n"
			"   int realNumberOfPointLights = MAX_POINT_LIGHTS;\n"

			"   if ( uPainterEffect || uColorPicking ) {\n"
			"      color = uPainterColor;\n"
			"   } else {\n"
			"      if (uNumberOfSpotLights < MAX_SPOT_LIGHTS + MAX_DIRECTIONAL_LIGHTS) {\n"
			"         realNumberOfSpotLights = uNumberOfSpotLights;\n"
			"      }\n"
			"      if (uNumberOfPointLights < MAX_POINT_LIGHTS) {\n"
			"         realNumberOfPointLights = uNumberOfPointLights;\n"
			"      }\n"
			"      diffuseSum = vec4(0.0);\n"
			"      specularSum = vec4(0.0);\n"
			"      shadowFactor = 0.0;\n\n"
			"      /* ---------- SPOT LIGHTS ----------*/\n"
			"      for (int i = 0; i < realNumberOfSpotLights; i++) {\n"
#ifdef FILLWAVE_GLES_3_0
			"         switch (i) {\n"
			"            case 0:\n"
			"               toLightDirection = uSpotLights[0].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uSpotLights[0].intensity * attenuation;\n"
			"               lightDepth = uSpotLights[0].mvp * vVertexWorldSpace;\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap0);\n"
			"               break;\n"
			"            case 1:\n"
			"               toLightDirection = uSpotLights[1].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uSpotLights[1].intensity * attenuation;\n"
			"               lightDepth = uSpotLights[1].mvp * vVertexWorldSpace;\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap1);\n"
			"               break;\n"
			"            case 2:\n"
			"               toLightDirection = uSpotLights[2].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uSpotLights[2].intensity * attenuation;\n"
			"               lightDepth = uSpotLights[2].mvp * vVertexWorldSpace;\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap2);\n"
			"               break;\n"
			"            case 3:\n"
			"               toLightDirection = uSpotLights[3].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uSpotLights[3].intensity * attenuation;\n"
			"               lightDepth = uSpotLights[3].mvp * vVertexWorldSpace;\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap3);\n"
			"               break;\n"
			"            case 4:\n"
			"               toLightDirection = uSpotLights[4].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uSpotLights[4].intensity * attenuation;\n"
			"               lightDepth = uSpotLights[4].mvp * vVertexWorldSpace;\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap4);\n"
			"               break;\n"
			"            case 5:\n"
			"               toLightDirection = uSpotLights[5].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uSpotLights[5].intensity * attenuation;\n"
			"               lightDepth = uSpotLights[5].mvp * vVertexWorldSpace;\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap5);\n"
			"               break;\n"
			"            case 6:\n"
			"               toLightDirection = uSpotLights[6].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uSpotLights[6].intensity * attenuation;\n"
			"               lightDepth = uSpotLights[6].mvp * vVertexWorldSpace;\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap6);\n"
			"               break;\n"
			"            case 7:\n"
			"               toLightDirection = uSpotLights[7].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uSpotLights[7].intensity * attenuation;\n"
			"               lightDepth = uSpotLights[7].mvp * vVertexWorldSpace;\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap7);\n"
			"               break;"
			"         }\n"
#else
			"         /* Direction to light in world space */\n"
			"         toLightDirection = uSpotLights[i].position.xyz - vVertexWorldSpace.xyz;\n"
			"         toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"         attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"         intensity = uSpotLights[i].intensity * attenuation;\n\n"

			"         lightDepth = uSpotLights[i].mvp * vVertexWorldSpace;\n"
			"         switch (i) {\n"
			"            case 0:\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap0);break;\n"
			"            case 1:\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap1);break;\n"
			"            case 2:\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap2);break;\n"
			"            case 3:\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap3);break;\n"
			"            case 4:\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap4);break;\n"
			"            case 5:\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap5);break;\n"
			"            case 6:\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap6);break;\n"
			"            case 7:\n"
			"               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap7);break;\n"
			"         }\n\n"
#endif
			"         /* Diffuse factor */\n"
			"         diffuse = calcDiffuse(vertexNormal, toLightDirection);\n"

			"         /* Specular factor */\n"
			"         if (texelSpecular.r == 0.0 || length(texelSpecular.xyz) == 0.0) { /*xxx workaround*/\n"
			"            texelSpecular.r = 255.0;\n"
			"         }\n"
			"         /* Specular Blinn-Phong BRDF calculations */\n"
			"         /* (Bidirectional Reflectance Distribution Function)*/\n"
			"         vec3 halfAngle = normalize(normalize(toLightDirection) - normalize(viewDirection));\n"
			"         specular = dot(vertexNormal, halfAngle);\n"
			"         specular = clamp(specular, 0.0, 1.0);\n"
			"         specular = dot(vertexNormal, toLightDirection) != 0.0 ? specular : 0.0;\n"
			"         specular = pow(specular, texelSpecular.r);\n"

			"         diffuseSum += (shadowFactor * intensity * diffuse);\n"
			"         specularSum += (shadowFactor * shadowFactor * shadowFactor * intensity * specular);\n"
			"      }\n"

#ifdef FILLWAVE_GLES_3_0
			"      /* POINT LIGHTS - concept\n"
			"      1) Right vector to read a cubemap is vWorldVertexPosition.xyz - uLightPosition\n"
			"      2) Shader factory is necessary here.\n"
			"      \n"
			"      float SampledDistance;\n"
			"      float Distance;\n"
			"      for (int j = 0; j < realNumberOfPointLights; j++) {\n"
			"         if ( j < realNumberOfPointLights) {\n"
			"            if ( j == 0 ) {\n"
			"               toLightDirection = uPointLights[0].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uPointLights[0].intensity * attenuation;\n"
			"               SampledDistance = 0.0;//texture(uPointShadowMap0, toLightDirection).r;\n"
			"               Distance = length(toLightDirection);\n"
			"               if (Distance <= SampledDistance + 0.001)\n"
			"                  shadowFactor =  1.0;\n"
			"               else\n"
			"                  shadowFactor =  0.1;\n"
			"            } else if ( j == 1 ) {\n"
			"               toLightDirection = uPointLights[1].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uPointLights[1].intensity * attenuation;\n"
			"               SampledDistance = 0.0;//texture(uPointShadowMap1, toLightDirection).r;\n"
			"               Distance = length(toLightDirection);\n"
			"               if (Distance <= SampledDistance + 0.001)\n"
			"                  shadowFactor =  1.0;\n"
			"               else\n"
			"                  shadowFactor =  0.1;\n"
			"            } else if ( j == 2 ) {\n"
			"               toLightDirection = uPointLights[2].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uPointLights[2].intensity * attenuation;\n"
			"               SampledDistance = 0.0;//texture(uPointShadowMap2, toLightDirection).r;\n"
			"               Distance = length(toLightDirection);\n"
			"               if (Distance <= SampledDistance + 0.001)\n"
			"                  shadowFactor =  1.0;\n"
			"               else\n"
			"                  shadowFactor =  0.1;\n"
			"            } else if ( j == 3 ) {\n"
			"               toLightDirection = uPointLights[3].position.xyz - vVertexWorldSpace.xyz;\n"
			"               toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"               attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"               intensity = uPointLights[3].intensity * attenuation;\n"
			"               SampledDistance = 0.0;//texture(uPointShadowMap3, toLightDirection).r;\n"
			"               Distance = length(toLightDirection);\n"
			"               if (Distance <= SampledDistance + 0.001)\n"
			"                  shadowFactor =  1.0;\n"
			"               else\n"
			"                  shadowFactor =  0.1;\n"
			"            }\n"
			"         }\n"
			"         diffuse = calcDiffuse(vertexNormal, toLightDirection);\n"

			"         vec3 halfAngle = normalize(normalize(toLightDirection) - normalize(viewDirection));\n"
			"         specular = dot(vertexNormal, halfAngle);\n"
			"         specular = clamp(specular, 0.0, 1.0);\n"
			"         specular = dot(vertexNormal, toLightDirection) != 0.0 ? specular : 0.0;\n"
			"         specular = pow(specular, texelSpecular.r);\n"

			"         diffuseSum += diffuse * shadowFactor * intensity;\n"
			"         specularSum += specular * shadowFactor * intensity;\n"
			"      }*/\n"

#else
			"      /* POINT LIGHTS */\n"
			"      for (int i=0; i<realNumberOfPointLights; i++) {\n"
			"         toLightDirection = uPointLights[i].position.xyz - vVertexWorldSpace.xyz;\n"
			"         toLightDirectionSqr = dot(toLightDirection, toLightDirection);\n"
			"         attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));\n"
			"         intensity = uPointLights[i].intensity * attenuation;\n"
			"         if ( i < realNumberOfPointLights) {\n"
			"            //lightDepth = uPointLights[i].mvp * vVertexWorldSpace;\n"
			"            if ( i == 0 ) {\n"
			"               shadowFactor = calculatePointShadow(-toLightDirection, uPointShadowMap0);\n"
			"            } else if ( i == 1 ) {\n"
			"               shadowFactor = calculatePointShadow(-toLightDirection, uPointShadowMap1);\n"
			"            } else if ( i == 2 ) {\n"
			"               shadowFactor = calculatePointShadow(-toLightDirection, uPointShadowMap2);\n"
			"            } else if ( i == 3 ) {\n"
			"               shadowFactor = calculatePointShadow(-toLightDirection, uPointShadowMap3);\n"
			"            }\n"
			"         }\n"
			"         diffuse = calcDiffuse(vertexNormal, toLightDirection);\n"

			"         vec3 halfAngle = normalize(normalize(toLightDirection) - normalize(viewDirection));\n"
			"         specular = dot(vertexNormal, halfAngle);\n"
			"         specular = clamp(specular, 0.0, 1.0);\n"
			"         specular = dot(vertexNormal, toLightDirection) != 0.0 ? specular : 0.0;\n"
			"         specular = pow(specular, texelSpecular.r);\n"

			"         diffuseSum += diffuse * shadowFactor * intensity;\n"
			"         specularSum += specular * shadowFactor * intensity;\n"
			"      }\n"
#endif
			"      diffuseSum.w = 0.0;\n"
			"      specularSum.w = 0.0;\n"

			"      colorDiffuse = vec4 (ambientFactor, 1.0) * (diffuseSum + vColor);\n"
			"      color = ( vec4(colorDiffuse.xyz, 1.0) + uLightAmbientIntensity ) * texelDiffuse + specularSum;\n"
			"      color.a = colorDiffuse.a;\n"

			"      /* Effects */\n"
			"      if ( uPainterEffect ){\n"
			"         color = uPainterColor;\n"
			"      } else if ( uTextureOnlyEffect ) {\n"
			"         color = texelDiffuse;\n"
			"      } else if ( uBoostColorEffect ) {\n"
			"         color = vec4(uBoostColorFactor * color.x,\n"
			"                      uBoostColorFactor * color.y,\n"
			"                      uBoostColorFactor * color.z, 1.0);\n"
			"      }\n"

			"      if ( uFogEffect ) {\n"
			"         float fogFactor = ( length(-vCameraPosition + vVertexWorldSpace.xyz) - uFogNearDistance) / (uFogFarDistance - uFogNearDistance);\n"
			"         fogFactor = clamp (fogFactor, 0.0, 1.0);\n"
			"         color = vec4(mix (color.rgb , uFogColor, fogFactor), 1.0);\n"
			"      }\n"
			"   }\n";

	std::string end = "";

	/* Many render targets for DR */
	for (GLuint i = 0; i < mRendertargets; i++) {
		end += "fColor" + to_string(i) + " = color;\n";
	}

	end += "\n}\n";

	return mGLVersion + mGLFragmentPrecision + inputs + outputs + lightsMaximum + lightStructDefinition
			+ lightUniforms + lightSamplerUniforms + effectsUniforms + textures
			+ functions + main + end;
}

} /* framework */
} /* fillwave */
