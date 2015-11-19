#version 330 core

uniform mat4 uViewProjectionMatrix, uModelMatrix;
uniform float uTimeElapsed;
uniform float uPointSize;

uniform float uSize = 0.8;
uniform vec3 uPosition = vec3(0.0,0.0,0.0);
uniform vec4 uColor = vec4(1.0,1.0,1.0,1.0);

// the fragment shader can use this for it's output colour's alpha component 
out float vOpacity;
out vec4 vColor;
out vec2 vVertexOffset;

void main() {
   vec2 radiusOffset;
   switch(gl_VertexID) {
      case 0:
      // 2D
      vVertexOffset = vec2(-1.0, 1.0);
      radiusOffset = vec2(-uSize, uSize);
      break;
   case 1:
      // 2D
      vVertexOffset = vec2(-1.0, -1.0);
      radiusOffset = vec2(-uSize, -uSize);
      break;
   case 2:
      // 2D
      vVertexOffset = vec2(1.0, 1.0);
      radiusOffset = vec2(uSize, uSize);
      break;
   case 3:
      // 2D
      vVertexOffset = vec2(1.0, -1.0);
      radiusOffset = vec2(uSize, -uSize);
      break;
   }

   vec4 vertexPosition = vec4(uPosition, 1.0);
   vertexPosition.xy += radiusOffset;

   gl_Position = uViewProjectionMatrix * uModelMatrix * vertexPosition;

   float time = mod (uTimeElapsed, 6.0);

   vOpacity = 1.0 - (time / 6.0);
   vColor = uColor;
}
