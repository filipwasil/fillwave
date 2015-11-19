/* shader to render simple particle system points */
#version 330 core

in vec2 vPosition;
out vec4 fColour;

uniform float uTime = 1.0;

uniform sampler2D uPostProcessingSampler;

float Hash( vec2 p) {
   vec3 p2 = vec3(p.xy,1.0);
   return fract(sin(dot(p2,vec3(37.1,61.7, 12.4)))*3758.5453123);
}

float noise(in vec2 p) {
   vec2 i = floor(p);
   vec2 f = fract(p);
   f *= f * (3.0-2.0*f);

   return mix(mix(Hash(i + vec2(0.,0.)), Hash(i + vec2(1.,0.)),f.x),
          mix(Hash(i + vec2(0.,1.)), Hash(i + vec2(1.,1.)),f.x),
          f.y);
}

float fbm(vec2 p) {
   float v = 0.0;
   v += noise(p*1.)*.5;
   v += noise(p*2.)*.25;
   v += noise(p*4.)*.125;
   return v;
}

void main(void) {
   vec2 pos = vPosition;
   vec2 opos=pos;
   float time = 8.1 - uTime;
   float flag=1.0;
   vec3 color = texture (uPostProcessingSampler, vec2((vPosition.x+1.0)/2.0, (vPosition.y+1.0)/2.0) ).xyz;
   pos.x = fract(time*.1)*1.3;
   float d = pos.x+pos.y*0.5-0.3;
   d+=0.5*fbm(opos*15.1);

   if (d >0.35) {
      color = clamp((color-(d-0.35)*10.),0.0,1.0);
   }

   if (d >0.47 && d < 0.99) {
      float b = 1.-abs(d-.48)*33.3;
      color += flag * b*1.5*(0.0+noise(100.*pos+vec2(-time*3.,0.)))*vec3(1.5,0.5,0.0);
      color += b*0.5*(0.0+noise(100.*pos+vec2(-time*3.,0.)))*vec3(1.5,0.5,0.0);
   }
   fColour = vec4(color, 1.0);
}
