/* shader to render simple particle system points */
#version 300 es

in vec2 vPosition;
out vec4 fColour;

uniform float uTime;

uniform sampler2D uPostProcessingSampler;

void main () {
   vec2 coordinates = vec2((vPosition.x+1.0)/2.0, (vPosition.y+1.0)/2.0);
   vec4 texel = texture (uPostProcessingSampler, coordinates);
   fColour = vec4(texel.xyz * clamp(0.2*uTime, 0.0, 2.0), 1.0);
}