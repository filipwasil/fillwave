
#version 330 core

precision lowp float;

out vec4 fColor;

uniform float uTime;
uniform vec2 uResolution;
uniform vec2 uPosition;
uniform float uProgress;
uniform sampler2D uDiffuseTextureUnit;

in vec2 vPosition;
in vec2 vTextureCoordinate;
in vec2 vScale;

void main(){
	if ( vPosition.x > (uProgress * 2.0 - 1.0) || vPosition.y < 0.63)
	{
		discard;
	}
	float fade = vPosition.x + 0.8;
	float fadeY = clamp(0.0, 1.0,abs(vPosition.y - 0.815));
	vec4 color = vec4(
		vec3(0.5,0.5,0.1)*(0.2/abs(0.1-(length(vec2(vPosition.y - 1.0 + uResolution/1000000.0))*2.0-0.4)))
		,1.);
	color = vec4(clamp(color, 0.0, 1.0).rgb * fade * fadeY, 1.0);

	fColor = color;
	//fColor = vec4(vTextureCoordinate,.0,1.0);
}
