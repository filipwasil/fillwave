/*
 * GradientBall.h
 *
 *  Created on: Nov 7, 2014
 *      Author: filip
 */

#ifndef GRADIENTBALL_H_
#define GRADIENTBALL_H_

#include <fillwave/OpenGL.h>
#include <memory>

#include <fillwave/particles/Impostor.h>

namespace fillwave {
namespace particles {

/*! \class GradientBall
 * \brief Impostor to define a gradient ball.
 */

class GradientBall: public Impostor {
private:
   pProgram mProgram;
public:
   GradientBall(Engine* engine,
                pProgram program,
                GLfloat lifetime = 1.0,
                GLfloat size = 1.0,
                pTexture texture = pTexture());
   virtual ~GradientBall();
   void draw(space::Camera& camera);
   };

} /* particles */
typedef std::shared_ptr<particles::GradientBall> pGradientBall;
} /* fillwave */

#endif /* GRADIENTBALL_H_ */
