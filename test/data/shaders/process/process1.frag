/* shader to render simple particle system points */
#version 330 core

in vec2 vPosition;
out vec4 fColour;

uniform float uTime = 1.0;

uniform sampler2D uPostProcessingSampler;

void main () {
   vec4 texel = texture (uPostProcessingSampler, vec2((vPosition.x+1.0)/2.0, (vPosition.y+1.0)/2.0) );
   fColour = texel*clamp(0.2*uTime, 0.0, 2.0);
}