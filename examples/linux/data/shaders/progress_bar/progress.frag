#version 330 core

out vec4 fColor;

uniform float uTime;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec2 position;
uniform vec2 size;
uniform float progress;

in vec2 vPosition;

#define MAX_ITER 3

void main( void ) {
	vec2 sp = vPosition;//vec2(.4, .7);
	vec2 p = sp*6.0 - vec2(125.0);
	vec2 i = p;
	float c = 1.0;
	
	float inten = 0.01;

	for (int n = 0; n < MAX_ITER; n++) 
	{
		float t = uTime/10.0* (1.0 - (3.0 / float(n+1)));
		i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
		c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
	}
	c /= float(MAX_ITER);
	c = 1.5-sqrt(c);
	
	float progressRealPosition = progress
	vec2 border1 = position - size * 0.5;
	vec2 border2 = position + size * 0.5;
	
	if (border2.x > vPosition.x
	    || border2.y > vPosition.x
		|| border1.x < vPosition.x
		|| border1.y < vPosition.y) {
		discard;
	}
	fColor = vec4(vec3(c*c*c*c), 999.0) + vec4(0.0, 0.3, 0.5, 4.0);
}