#version 330 core
precision mediump float;
layout(location = 0) in vec4 aPosition;                        
layout(location = 1) in vec4 aColor;                           
layout(location = 2) in vec3 aNormal;                          
layout(location = 3) in vec3 aNormalTangent;                   
layout(location = 4) in vec2 aTextureCoordinate;               
layout(location = 5) in ivec4 aBoneID;                         
layout(location = 6) in vec4 aWeight;

out vec4 vColor;
out vec2 vTextureCoordinate;
out vec3 vVertexNormal; // N
out vec3 vVertexNormalTangent;
out vec4 vVertexWorldSpace;
out vec3 vCameraPosition;

uniform mat4 uModelMatrix;
uniform mat4 uViewProjectionMatrix;
uniform mat3 uNormalViewMatrix;
uniform mat4 uColorMatrix;
uniform mat4 uShadowBiasMatrix;
uniform vec3 uCameraPosition;

void main() {
   vVertexWorldSpace = uModelMatrix * aPosition;
   vVertexNormal = (uModelMatrix * vec4(aNormal, 0.0)).xyz;
   vVertexNormalTangent = (uModelMatrix * vec4(aNormalTangent, 0.0)).xyz;
   vTextureCoordinate = aTextureCoordinate;
   vCameraPosition = uCameraPosition;
   vColor = aColor;
   gl_Position = uViewProjectionMatrix * vVertexWorldSpace;
}

