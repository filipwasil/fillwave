#version 330

precision mediump float;

out vec4 fColor;

uniform float uTime;
uniform vec2 uResolution;
uniform float uProgress;
uniform float uSpeedAngle;
uniform float uRPMAngle;
uniform sampler2D uDiffuseTextureUnit;

in vec2 vPosition;
in vec2 vTextureCoordinate;
in vec2 vScale;

void main() {
      fColor = texture(uDiffuseTextureUnit, vTextureCoordinate);
}