#pragma once

#include <fillwave/OpenGL.h>
#include <memory>

#include <fillwave/models/Impostor.h>

namespace flw {
namespace flf {

/*! \class GradientBall
 * \brief Impostor to define a gradient ball.
 */

class GradientBall: public Impostor {
 private:
	flc::Program* mProgram;
 public:
	GradientBall(Engine* engine,
	             flc::Program* program,
	             GLfloat lifetime = 1.0,
	             glm::vec4 position = glm::vec4(),
	             glm::vec4 color = glm::vec4(),
	             GLfloat size = 1.0,
	             flc::Texture* texture = nullptr);
	virtual ~GradientBall();
	void draw(ICamera& camera);
};

} /* flf */
typedef std::shared_ptr<flf::GradientBall> pGradientBall;
} /* flw */
