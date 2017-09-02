#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 resolution;
uniform sampler2D renderbuffer;

float noise(vec3 p) //Thx to Las^Mercury
{
	vec3 i = floor(p);
	vec4 a = dot(i, vec3(1., 57., 21.)) + vec4(0., 57., 21., 78.);
	vec3 f = cos((p-i)*acos(-1.))*(-.5)+.5;
	a = mix(sin(cos(a)*a),sin(cos(1.+a)*(1.+a)), f.x);
	a.xy = mix(a.xz, a.yw, f.y);
	return mix(a.x, a.y, f.z);
}

float sphere(vec3 p, vec4 spr)
{
	return length(spr.xyz-p) - spr.w;
}

float flame(vec3 p)
{
	float d = sphere(p*vec3(1.,.5,1.), vec4(0,-1.,.0,1.));
	return d + (noise(p+vec3(.0,time*10.,.0)) + noise(p*3.)*.5)*.25*(p.y) ;
}

float scene(vec3 p)
{
	return min(100.-length(p) , abs(flame(p)) );
}

vec4 raymarch(vec3 org, vec3 dir)
{
	float d = 0.0, glow = 0.0, eps = 0.02;
	vec3  p = org;
	bool glowed = false;
	
	for(int i=0; i<64; i++)
	{
		d = scene(p) + eps;
		p += d * dir;
		if( d>eps )
		{
			if(flame(p) < .0)
				glowed=true;
			if(glowed)
       			glow = float(i)/64.;
		}
	}
	return vec4(p,glow);
}

float sinish(float t) {
	return sin(t)*0.5+0.5;
}

void main()
{
	vec2 v = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
	v.x *= resolution.x/resolution.y;
	
	vec3 org = vec3(0., -2., 4.);
	vec3 dir = normalize(vec3(v.x*2.5, -v.y-.4, -1.));
	
	vec4 p = raymarch(org, dir);

	float topFade = 1.-v.y;

	float glow = p.w*topFade;
	
	
	vec4 col =vec4(.04);
	

	col = 0.4*vec4(1.0,0.5,0.2,0.4);
	
	gl_FragColor = mix(vec4(0.), col, pow(glow*2.5,4.));

}


