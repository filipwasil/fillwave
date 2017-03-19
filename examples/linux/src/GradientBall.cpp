/*
 * GradientBall.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: filip
 */

#include "../../linux/src/GradientBall.h"

namespace fillwave {
namespace framework {

GradientBall::GradientBall(Engine *engine,
    core::Program *program,
    GLfloat lifetime,
    GLfloat size,
    core::Texture *texture)
    : Impostor (engine, lifetime, size, texture), mProgram (program) {
}

GradientBall::~GradientBall() {

}

void GradientBall::draw(ICamera &camera) {
  mProgram->use ();
  mProgram->uniformPush ("uModelMatrix", mParentMMC * mMMC);
  mProgram->uniformPush ("uSize", mSize);
  mProgram->uniformPush ("uTextureUnit", FILLWAVE_DIFFUSE_UNIT);
  mProgram->uniformPush ("uViewProjectionMatrix", camera.getViewProjection ());
  coreDraw ();
}

} /* framework */
} /* fillwave */
