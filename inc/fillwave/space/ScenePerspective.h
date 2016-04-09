/*
 * ScenePerspective.h
 *
 *  Created on: 6 May 2015
 *      Author: Filip Wasil
 */

#ifndef ScenePerspective_H_
#define ScenePerspective_H_

#include <fillwave/space/base/IScene.h>
#include <fillwave/space/CameraPerspective.h>

namespace fillwave {
namespace framework {

/*! \class ScenePerspective
 * \brief Scene with perspective projection.
 *
 */

class ScenePerspective: public IScene {
 public:
	ScenePerspective(pCameraPerspective camera = pCameraPerspective());
	virtual ~ScenePerspective() = default;
	void setCamera(pCameraPerspective camera);

	/* Interface IScene */
	pICamera getCamera() override;
	void draw() override;
	void drawPicking() override;
	void drawDepthInt() override;
	void drawOcclusion() override;

 private:
	pCameraPerspective mCamera;
};

} /* framework */

typedef std::shared_ptr<framework::ScenePerspective> pScenePerspective;

pScenePerspective buildScenePerspective(pCameraPerspective camera =
      pCameraPerspective());
} /* fillwave */
#endif /* ScenePerspective_H_ */
