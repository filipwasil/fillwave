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

#include <fillwave/models/Impostor.h>

namespace fillwave {
namespace framework {

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
   void draw(ICamera& camera);
   };

} /* framework */
typedef std::shared_ptr<framework::GradientBall> pGradientBall;
} /* fillwave */

#endif /* GRADIENTBALL_H_ */
