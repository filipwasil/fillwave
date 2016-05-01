/*
 * ProgressBar.h
 *
 *  Created on: Jan 11, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_HUD_PROGRESSBAR_H_
#define INC_FILLWAVE_HUD_PROGRESSBAR_H_

#include <fillwave/hud/base/IHUDNode.h>
#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class ProgressBar
 * \brief HUD node to indicate progress.
 */

class ProgressBar: public IHUDNode {
 public:
	ProgressBar(
	   Engine* engine,
	   core::Texture2D* texture,
	   const std::string& shaderPath,
	   glm::vec2 position,
	   glm::vec2 scale);
	virtual ~ProgressBar() = default;

	void setProgress(GLfloat progress);

	void draw() override;

 private:
	GLfloat mProgress;
};

} /* namespace framework */
typedef std::unique_ptr<framework::ProgressBar> puProgressBar;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_PROGRESSBAR_H_ */
