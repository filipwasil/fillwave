/*
 * GradientBall.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: filip
 */

#include "GradientBall.h"

namespace flw {
namespace flf {

GradientBall::GradientBall(Engine *engine,
    flc::Program *program,
    GLfloat lifetime,
    GLfloat size,
    flc::Texture *texture)
    : Impostor(engine, lifetime, size, texture), mProgram(program) {
}

GradientBall::~GradientBall() {

}

void GradientBall::draw(ICamera &camera) {
  mProgram->use();
  mProgram->uniformPush("uModelMatrix", mParentMMC * mMMC);
  mProgram->uniformPush("uSize", mSize);
  mProgram->uniformPush("uTextureUnit", FILLWAVE_DIFFUSE_UNIT);
  mProgram->uniformPush("uViewProjectionMatrix", camera.getViewProjection());
  coreDraw();
}

} /* flf */
} /* flw */
