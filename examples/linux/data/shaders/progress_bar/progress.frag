#version 330 core

out vec4 fColor;

uniform float uTime;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec2 uPosition;
uniform float uProgress;
uniform sampler2D uDiffuseTextureUnit;

in vec2 vPosition;
in vec2 vTextureCoordinate;
in vec2 vScale;

#define MAX_ITER 3

void main( void ) {
	vec2 sp = vPosition;//vec2(.4, .7);
	vec2 p = sp*6.0 - vec2(125.0);
	vec2 i = p;
	float c = 1.0;
	
	float inten = 0.01;

	for (int n = 0; n < MAX_ITER; n++) {
		float t = uProgress/10.0* (1.0 - (3.0 / float(n+1)));
		i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
		c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
	}
	c /= float(MAX_ITER);
	c = 1.5-sqrt(c);
	
	if (uPosition.x + uProgress * vScale.x < vPosition.x ) {
		discard;
	}

	fColor = vec4(vec3(c*c*c*c), 999.0);
}