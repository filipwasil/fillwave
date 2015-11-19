/* shader to render simple particle system points */
#version 330 core

in float vOpacity;
in vec4 vColor ;
in vec2 vVertexOffset;

out vec4 fColour;

uniform sampler2D uTextureUnit;

void main () {
   float lensqr = dot(vVertexOffset, vVertexOffset);
   if(lensqr > 1.0)
      discard;
   vec4 texel = texture (uTextureUnit, vec2((vVertexOffset.x+1.0)/2.0, (vVertexOffset.y+1.0)/2.0));
   fColour.a = 1.0 - lensqr;
   fColour.rgb = vColor.rgb * texel.rgb;
}