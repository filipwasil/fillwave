precision mediump float;

// Yuldashev Mahmud Effect took from shaderToy mahmud9935@gmail.com
out vec4 fColor;

uniform float uTime;
uniform vec2 uResolution;
uniform float uProgress;
uniform float uSpeed;
uniform float uRPM;

in vec2 vPosition;
in vec2 vTextureCoordinate;
in vec2 vScale;

float snoise(vec3 uv, float res) {
	const vec3 s = vec3(1e0, 1e2, 1e3);

	uv *= res;

	vec3 uv0 = floor(mod(uv, res)) * s;
	vec3 uv1 = floor(mod(uv + vec3(1.0), res)) * s;

	vec3 f = smoothstep(0.0, 1.0, fract(uv));

	vec4 v = vec4(uv0.x + uv0.y + uv0.z,
		      uv1.x + uv0.y + uv0.z,
		      uv0.x + uv1.y + uv0.z,
		      uv1.x + uv1.y + uv0.z);

	vec4 r = fract(sin(v * 1e-1) * 1e3);
	float r0 = mix(mix(r.x, r.y, f.x), mix(r.z, r.w, f.x), f.y);

	r = fract(sin((v + uv1.z - uv0.z) * 1e-1) * 1e3);
	float r1 = mix(mix(r.x, r.y, f.x), mix(r.z, r.w, f.x), f.y);

	return mix(r0, r1, f.z) * 2.0 - 1.0;
}

vec4 gauge(float offset) {
	vec2 p = -0.5 + gl_FragCoord.xy / uResolution.xy;
	p.x += offset;
	p.x *= uResolution.x / uResolution.y;
	float lp = length(0.4*p);
	float color = 3.0 - (6.0 * lp);
	vec3 coord = vec3(atan(p.x, p.y) / 6.2832 + 0.5, 0.4 * lp, 0.5);
	float power = 1.0;
	for (int i = 0; i < 7; i++) {
		power *= 2.0;
		color += (1.5 / power) * snoise(coord + vec3(0.0, -0.05 * uTime, 0.01 * uTime), 16.0 * power);
	}
	color = max(color, 0.0);
	float c2 = color * color;
	float c3 = color * c2;

 if ( vPosition.y > 0.55) {
   return vec4( 0.0 );
 } else {
	return vec4(vec3(1.0) - vec3(color, 0.4 * c2, 0.15 * c3) , 1.0);
 }
}

vec4 marker(float centerX)
{
 vec2 U = gl_FragCoord.xy;
 U = U/uResolution.xy*2.-1.;
 U*=3.0;
 U.y -= 0.5;
 float len = 0.3;
 float col = smoothstep(
        	1.,
        	0.,
        	.3+length(U.y+0.5+vec2(0.,pow(abs(U.x - centerX),2.1)*1e2+.2*fract(sin(uTime*0e4))))*len
    	);
 return vec4(col, col * 3.0, 0.0, 0.0);
}

mat2 rot(float a){
	return mat2(cos(a), -sin(a), sin(a),+ cos(a));
}

vec4 rpm(float centerY)
{
 vec2 p = -.5 + (gl_FragCoord.xy - vec2(-uResolution.x * 1.0, uResolution.y * 0.4)) / uResolution.xy;
 //stretch to fit
 p.x *= (uResolution.x/uResolution.y)*0.03;

 //mod swirl 1.0
 float d = length(p)*0.0;

 //mod size 1.0
 p *= 3.0*rot(2.*cos(d*2. + .2*snoise(vec3(p*.9, d*.2 + sin(uTime*.2)), 5. )));

 float color = 3.0 - (3.*length(2.*p));

 vec3 coord = vec3(atan(p.x,p.y)/6.2832+.5, length(p)*.4, .5);

 for(int i = 2; i <= 7; i++)
 {
    float power = pow(2.0, float(i));
    color += (1.5 / power) * snoise(coord + vec3(0.,-uTime*.05, uTime*.01), power*16.);
 }

 vec4 col = 2.0* vec4( pow(max(color,0.),2.)*0.1, pow(max(color,0.),2.)*0.1, pow(max(color,0.),2.)*0.4 , 0.0);
 float posX = (gl_FragCoord.x / uResolution.x + 1.0)*0.5;
 if (posX > uProgress) {
   return vec4( 0.0 );
 }
 else {
   return vec4( (uProgress + posX) * col.r, (1.0 - uProgress - posX) * col.g, (1.0 - uProgress) * col.b, 1.0);
 }
}

void main() {
	vec4 leftGauge = gauge(0.27);
	vec4 rightGauge = gauge(-0.30);
	vec4 leftMarker = marker(0.5);
	vec4 rightMarker = marker(-0.5);
	vec4 upRpm = rpm (2.4);

	fColor = max(min(leftGauge,rightGauge) + leftMarker + rightMarker, upRpm);
	fColor.a = 1.0;
}