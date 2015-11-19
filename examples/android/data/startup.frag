#version 300 es

#define MAX_ITER 3

in vec2 vPosition;
out vec4 fColour;

uniform float uTime;

uniform sampler2D uPostProcessingSampler;

void main( void ) {

    vec2 coordinates = vec2((vPosition.x+1.0)/2.0, (vPosition.y+1.0)/2.0);
    vec4 texel = texture (uPostProcessingSampler, coordinates);

	vec2 p =  gl_FragCoord.xy * 8.0 / vec2(900.0,900.0) - vec2(20.0);
	vec2 i = p;
	float c = 1.0;
	float inten = .05;

	for (int n = 0; n < MAX_ITER; n++) {
		float t = uTime * (1.0 - (3.0 / float(n+1)));

		i = p + vec2(cos(t - i.x) + sin(t + i.y),
					 sin(t - i.y) + cos(t + i.x));

		c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),
							 p.y / (cos(i.y+t)/inten)));
	}

	c /= float(MAX_ITER);
	c = 1.5 - sqrt(c);

	vec4 texColor = vec4(0.0, 0.0117647, 0.01568627, 1.0);
	
	texColor.rgb *= pow((1.0 / (1.0 - (c + 0.0))), 3.0);
	
   fColour = vec4( (texColor.xyz*(clamp((8.0-uTime) * 0.125, 0.0, 2.0) )
         + texel.xyz * clamp(uTime * 0.125, 0.0, 2.0)), 1.0);
         
   if (uTime > 8.0 ) {
      fColour = vec4(fColour.xyz * (16.0 - uTime) * 0.125 , 1.0);
   }
}