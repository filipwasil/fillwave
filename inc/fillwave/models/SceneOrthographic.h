/*
 * SceneOrthographic.h
 *
 *  Created on: 6 May 2015
 *      Author: Filip Wasil
 */

#ifndef SCENEOrthographic_H_
#define SCENEOrthographic_H_

#include <fillwave/models/Scene.h>
#include <fillwave/space/CameraOrthographic.h>

namespace fillwave {
namespace models {
class SceneOrthographic;
}
typedef std::shared_ptr<models::SceneOrthographic> pSceneOrthographic;
namespace models {

/*! \class SceneOrthographic
 * \brief Scene with orthographic projection.
 *
 */

class SceneOrthographic: public Scene {
public:
	SceneOrthographic(pCameraOrthographic camera = pCameraOrthographic());

	virtual ~SceneOrthographic() = default;

	void setCamera(pCameraOrthographic camera);

	pCamera getCamera();

	void draw();
	void drawDR();
	void draw(space::CameraOrthographic& camera);
	void drawDR(space::CameraOrthographic& camera);
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
	return pSceneOrthographic(new models::SceneOrthographic(camera));
}
} /* fillwave */
#endif /* SCENEOrthographic_H_ */
