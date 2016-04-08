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

	/* Interface IScene */
	pICamera getCamera() override;
	void draw() override;
	void drawPicking() override;
	void drawDepthInt() override;
	void drawOcclusion() override;

  private:
	pCameraOrthographic mCamera;
};

} /* models */
pSceneOrthographic buildSceneOrthographic(pCameraOrthographic camera =
            pCameraOrthographic());
} /* fillwave */
#endif /* SCENEOrthographic_H_ */
