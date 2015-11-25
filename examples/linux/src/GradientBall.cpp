/*
 * GradientBall.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: filip
 */

#include "../../linux/src/GradientBall.h"

namespace fillwave {
namespace particles {

GradientBall::GradientBall(Engine* engine,
                           pProgram program,
                           GLfloat lifetime,
                           GLfloat size,
                           pTexture texture):Impostor(engine,
                                                      lifetime,
                                                      size,
                                                      texture),
                                             mProgram(program) {
}

GradientBall::~GradientBall() {

}

void GradientBall::draw(space::Camera& camera) {
   mProgram->use();
   mProgram->uniformPush("uModelMatrix", mParentMMC* mMMC);
   mProgram->uniformPush("uSize", mSize);
   mProgram->uniformPush("uTextureUnit", FILLWAVE_DIFFUSE_UNIT);
   mProgram->uniformPush("uViewProjectionMatrix", camera.getViewProjection());
   coreDraw();
}

} /* particles */
} /* fillwave */
