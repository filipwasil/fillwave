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

vec2 getCorrectedClipSpacePosition() {
      vec2 pos = gl_FragCoord.xy / uResolution;
      pos.x *= uResolution.x / uResolution.y;
      return pos;
}

void main() {
  fColor = texture(uDiffuseTextureUnit, vTextureCoordinate);
  vec2 pos = getCorrectedClipSpacePosition();
  if (0.3*log(2.8 *pos.x + 0.8) > pos.y - 0.55 && 0.3*log(3.2*pos.x + 0.8) < 1.25 *pos.y - 0.55) {
    fColor += vec4(1.0, 1.0, 0.0, 0.0);
  }
}