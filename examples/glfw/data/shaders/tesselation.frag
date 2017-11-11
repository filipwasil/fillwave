#version 330 core
precision lowp float;
in vec4 vColor;
in vec2 vTextureCoordinate;
in vec3 vVertexNormal;
in vec3 vVertexNormalTangent;
in vec4 vVertexWorldSpace;
in vec3 vCameraPosition;

out vec4 fColor0;

#define MAX_SPOT_LIGHTS 4
#define MAX_POINT_LIGHTS 4
#define MAX_DIRECTIONAL_LIGHTS 4

struct LightPoint {
vec4 position;
vec4 intensity;
mat4 mvp;
};

uniform vec4 uLightAmbientIntensity;
uniform vec4 uLightDiffuseIntensity;
uniform vec4 uLightSpecularIntensity;
uniform LightPoint uPointLights[MAX_POINT_LIGHTS];
uniform int uNumberOfPointLights;
uniform int uNumberOfSpotLights;
layout(std140) uniform uSpotLightsUBO {
LightPoint uSpotLights[MAX_SPOT_LIGHTS + MAX_DIRECTIONAL_LIGHTS];
};

uniform samplerCube uPointShadowMap0;
uniform samplerCube uPointShadowMap1;
uniform samplerCube uPointShadowMap2;
uniform samplerCube uPointShadowMap3;
uniform sampler2D uShadowMap0;
uniform sampler2D uShadowMap1;
uniform sampler2D uShadowMap2;
uniform sampler2D uShadowMap3;
uniform sampler2D uShadowMap4;
uniform sampler2D uShadowMap5;
uniform sampler2D uShadowMap6;
uniform sampler2D uShadowMap7;

uniform bool uColorPicking;
uniform bool uFogEffect;
uniform vec3 uFogColor;
uniform float uFogNearDistance;
uniform float uFogFarDistance;
uniform bool uPainterEffect;
uniform vec4 uPainterColor;
uniform bool uTextureOnlyEffect;
uniform bool uBoostColorEffect;
uniform float uBoostColorFactor;
uniform sampler2D uDiffuseTextureUnit;
uniform sampler2D uNormalTextureUnit;
uniform sampler2D uSpecularTextureUnit;
float calculateSpotShadow(vec4 spotlightPosition, sampler2D spotShadowMap) {
   vec3 shadowMapUV = spotlightPosition.xyz / spotlightPosition.w;
   float shadowMapDepth = texture(spotShadowMap, shadowMapUV.xy).x;
   if ( ( shadowMapDepth < shadowMapUV.z - 0.001 ) )
      return 0.1;
   else
      return 1.0;
}

float calculateSpotShadowPCF(vec4 spotlightPosition, sampler2D spotShadowMap) {
   vec3 shadowMapUV = spotlightPosition.xyz / spotlightPosition.w;
   float nearestPixel = 0.005;
   float x,y,shadowMapDepth,sum=0.0;
   for (x=-1.0;x<=1.0;x+=1.0) {
      for (y=-1.0;y<=1.0;y+=1.0) {
         shadowMapDepth=texture(spotShadowMap, vec2(shadowMapUV.x + x*nearestPixel, shadowMapUV.y + y*nearestPixel)).x;
         if ( ( shadowMapDepth < shadowMapUV.z - 0.001 )  || shadowMapUV.z <= 0.001 )
            sum += 0.1;
         else
            sum += 1.0;
      }
   }
   return sum*0.11;
}
float calculatePointShadow(vec3 toLightdirection, samplerCube pointShadowMap) {
    float SampledDistance = texture(pointShadowMap, toLightdirection).r;
    float Distance = length(toLightdirection);
    if (Distance <= SampledDistance + 0.001)
        return 1.0;
    else
        return 0.1;
}
float calcDiffuse(vec3 normal, vec3 direction) {
   return clamp( dot(normal, normalize ( direction) ), 0.0, 1.0);
}
void main() {
   /*shadow*/
   float shadowFactor;
   vec4  lightDepth;
   /*common for light models*/
   vec4 intensity;
   float attenuation;
   vec4 color;
   /*ambient*/
   vec3 ambientFactor = vec3(1.0, 1.0, 1.0) - uLightAmbientIntensity.xyz;
   /*diffuse*/
   float diffuse;
   vec4 diffuseSum;
   vec4 colorDiffuse;
   vec3 toLightDirection;
   vec4 texelDiffuse = uLightDiffuseIntensity * texture(uDiffuseTextureUnit, vTextureCoordinate);
   vec3 texelNormal = texture(uNormalTextureUnit, vTextureCoordinate).xyz;
   vec4 texelSpecular = uLightSpecularIntensity * texture(uSpecularTextureUnit, vTextureCoordinate) * 255.0;
   vec3 vertexNormal;
   /* Create TBN normals */
   vec3 Normal = normalize(vVertexNormal);
   vec3 Tangent = normalize(vVertexNormalTangent);
   Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
   vec3 Bitangent = cross(Tangent, Normal);
   /* Check if we use normal matrix or not */
   if (length(texelNormal.xyz) == 0.0) {
      vertexNormal = normalize (Normal);
   } else {
      texelNormal = 2.0 * texelNormal - vec3(1.0, 1.0, 1.0);
      mat3 TBN = ( mat3(Tangent, Bitangent, Normal) );
      vertexNormal = TBN * texelNormal;
      vertexNormal = normalize(vertexNormal);
   }
   /*specular*/
   float specular;
   vec4 specularSum;
   vec4 colorSpecular;
   float toLightDirectionSqr;
   float lightAttenuation = 0.2;
   vec3 viewDirection = normalize(vVertexWorldSpace.xyz - vCameraPosition);
   int realNumberOfSpotLights = MAX_SPOT_LIGHTS + MAX_DIRECTIONAL_LIGHTS;
   int realNumberOfPointLights = MAX_POINT_LIGHTS;
   if ( uPainterEffect || uColorPicking ) {
      color = uPainterColor;
   } else {
      if (uNumberOfSpotLights < MAX_SPOT_LIGHTS + MAX_DIRECTIONAL_LIGHTS) {
         realNumberOfSpotLights = uNumberOfSpotLights;
      }
      if (uNumberOfPointLights < MAX_POINT_LIGHTS) {
         realNumberOfPointLights = uNumberOfPointLights;
      }
      diffuseSum = vec4(0.0);
      specularSum = vec4(0.0);
      shadowFactor = 0.0;

      /* ---------- SPOT LIGHTS ----------*/
      for (int i = 0; i < realNumberOfSpotLights; i++) {
         /* Direction to light in world space */
         toLightDirection = uSpotLights[i].position.xyz - vVertexWorldSpace.xyz;
         toLightDirectionSqr = dot(toLightDirection, toLightDirection);
         attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));
         intensity = uSpotLights[i].intensity * attenuation;

         lightDepth = uSpotLights[i].mvp * vVertexWorldSpace;
         switch (i) {
            case 0:
               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap0);break;
            case 1:
               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap1);break;
            case 2:
               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap2);break;
            case 3:
               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap3);break;
            case 4:
               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap4);break;
            case 5:
               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap5);break;
            case 6:
               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap6);break;
            case 7:
               shadowFactor = calculateSpotShadowPCF(lightDepth, uShadowMap7);break;
         }

         /* Diffuse factor */
         diffuse = calcDiffuse(vertexNormal, toLightDirection);
         /* Specular factor */
         if (texelSpecular.r == 0.0 || length(texelSpecular.xyz) == 0.0) { /*xxx workaround*/
            texelSpecular.r = 255.0;
         }
         /* Specular Blinn-Phong BRDF calculations */
         /* (Bidirectional Reflectance Distribution Function)*/
         vec3 halfAngle = normalize(normalize(toLightDirection) - normalize(viewDirection));
         specular = dot(vertexNormal, halfAngle);
         specular = clamp(specular, 0.0, 1.0);
         specular = dot(vertexNormal, toLightDirection) != 0.0 ? specular : 0.0;
         specular = pow(specular, texelSpecular.r);
         diffuseSum += (shadowFactor * intensity * diffuse);
         specularSum += (shadowFactor * shadowFactor * shadowFactor * intensity * specular);
      }
      /* POINT LIGHTS */
      for (int i=0; i<realNumberOfPointLights; i++) {
         toLightDirection = uPointLights[i].position.xyz - vVertexWorldSpace.xyz;
         toLightDirectionSqr = dot(toLightDirection, toLightDirection);
         attenuation = (1.0 / ( 1.0 + lightAttenuation * sqrt(toLightDirectionSqr)));
         intensity = uPointLights[i].intensity * attenuation;
         if ( i < realNumberOfPointLights) {
            //lightDepth = uPointLights[i].mvp * vVertexWorldSpace;
            if ( i == 0 ) {
               shadowFactor = calculatePointShadow(-toLightDirection, uPointShadowMap0);
            } else if ( i == 1 ) {
               shadowFactor = calculatePointShadow(-toLightDirection, uPointShadowMap1);
            } else if ( i == 2 ) {
               shadowFactor = calculatePointShadow(-toLightDirection, uPointShadowMap2);
            } else if ( i == 3 ) {
               shadowFactor = calculatePointShadow(-toLightDirection, uPointShadowMap3);
            }
         }
         diffuse = calcDiffuse(vertexNormal, toLightDirection);
         vec3 halfAngle = normalize(normalize(toLightDirection) - normalize(viewDirection));
         specular = dot(vertexNormal, halfAngle);
         specular = clamp(specular, 0.0, 1.0);
         specular = dot(vertexNormal, toLightDirection) != 0.0 ? specular : 0.0;
         specular = pow(specular, texelSpecular.r);
         diffuseSum += diffuse * shadowFactor * intensity;
         specularSum += specular * shadowFactor * intensity;
      }
      diffuseSum.w = 0.0;
      specularSum.w = 0.0;
      colorDiffuse = vec4 (ambientFactor, 1.0) * (diffuseSum + vColor);
      color = ( vec4(colorDiffuse.xyz, 1.0) + uLightAmbientIntensity ) * texelDiffuse + specularSum;
      color.a = colorDiffuse.a;
      /* Effects */
      if ( uPainterEffect ){
         color = uPainterColor;
      } else if ( uTextureOnlyEffect ) {
         color = texelDiffuse;
      } else if ( uBoostColorEffect ) {
         color = vec4(uBoostColorFactor * color.x,
                      uBoostColorFactor * color.y,
                      uBoostColorFactor * color.z, 1.0);
      }
      if ( uFogEffect ) {
         float fogFactor = ( length(-vCameraPosition + vVertexWorldSpace.xyz) - uFogNearDistance) / (uFogFarDistance - uFogNearDistance);
         fogFactor = clamp (fogFactor, 0.0, 1.0);
         color = vec4(mix (color.rgb , uFogColor, fogFactor), 1.0);
      }
   }
fColor0 = color;

}

