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
	pICamera getCamera();

	void draw();
	void drawDR();
	void draw(ICamera& camera);
	void drawDR(ICamera& camera);
	void drawPicking();
	void drawSkybox();
	void drawDepthInt();
	void drawAOG();
	void drawAOC();
	void drawOcclusion();

private:
	pCameraPerspective mCamera;
};

} /* framework */

typedef std::shared_ptr<framework::ScenePerspective> pScenePerspective;

static pScenePerspective buildScenePerspective(pCameraPerspective camera =
		pCameraPerspective()) {
	return pScenePerspective(new framework::ScenePerspective(camera));
}
} /* fillwave */
#endif /* ScenePerspective_H_ */
