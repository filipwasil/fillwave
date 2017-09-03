// from Mr Hoskins ST;
#ifdef GL_ES
precision lowp float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

	//HPPH
float offset = time/10.;
float s = 0.0, v = 0.0;
vec3 col = vec3(0);

void main()
{
	vec2 uv = gl_FragCoord.xy / resolution.xy *2.0-1.0;

	vec3 init = vec3(sin(offset/4.)*3.,  cos(offset/3.1)*3., offset);
	for (int r = 0; r < 90; r++)
	{
		vec3 p = init + s * vec3(uv, 0.05);
		p.z = fract(p.z);
		// Thanks to Kali's little chaotic loop...
		for (int i=0; i < 9; i++) p = abs(p * 2.04) / dot(p, p) - .9;
		v += pow(dot(p, p), .7) * .06;
		col +=  vec3(v * .1+.4, 12.-s*2., .1 + v * 1.5) * v * 0.00003;
		s += .025;
	}
	gl_FragColor = vec4(clamp(col, 0.0, 1.0), 1.0);
}