/*
 * GradientBall.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: filip
 */

#include "GradientBall.h"

namespace fillwave {
namespace particles {

GradientBall::GradientBall(Engine* engine,
                           pProgram program,
                           GLfloat lifetime,
                           glm::vec4 position,
                           glm::vec4 color,
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
   mProgram->uniformPush("uModelMatrix", mParentMatrix* mModelMatrixCache);
   mProgram->uniformPush("uSize", mSize);
   mProgram->uniformPush("uTextureUnit", FILLWAVE_DIFFUSE_UNIT);
   mProgram->uniformPush("uViewProjectionMatrix", camera.getViewProjection());
   coreDraw();
}

} /* particles */
} /* fillwave */
