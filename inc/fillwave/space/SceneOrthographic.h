/*
 * SceneOrthographic.h
 *
 *  Created on: 6 May 2015
 *      Author: Filip Wasil
 */

#ifndef SCENEOrthographic_H_
#define SCENEOrthographic_H_

#include <fillwave/space/base/IScene.h>
#include <fillwave/space/CameraOrthographic.h>

namespace fillwave {
namespace framework {
class SceneOrthographic;
}
typedef std::shared_ptr<framework::SceneOrthographic> pSceneOrthographic;
namespace framework {

/*! \class SceneOrthographic
 * \brief Scene with orthographic projection.
 *
 */

class SceneOrthographic: public IScene {
public:
	SceneOrthographic(pCameraOrthographic camera = pCameraOrthographic());

	virtual ~SceneOrthographic() = default;

	void setCamera(pCameraOrthographic camera);
	pICamera getCamera();

	void draw();
	void drawPBRP();
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
	pCameraOrthographic mCamera;
};

} /* models */
static pSceneOrthographic buildSceneOrthographic(pCameraOrthographic camera =
		pCameraOrthographic()) {
	return pSceneOrthographic(new framework::SceneOrthographic(camera));
}
} /* fillwave */
#endif /* SCENEOrthographic_H_ */
