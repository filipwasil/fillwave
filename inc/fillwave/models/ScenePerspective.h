/*
 * ScenePerspective.h
 *
 *  Created on: 6 May 2015
 *      Author: Filip Wasil
 */

#ifndef ScenePerspective_H_
#define ScenePerspective_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/models/Scene.h>
#include <fillwave/space/CameraPerspective.h>

namespace fillwave {
namespace models {
class ScenePerspective;
}
typedef std::shared_ptr<models::ScenePerspective> pScenePerspective;
namespace models {

/*! \class ScenePerspective
 * \brief Scene with perspective projection.
 *
 */

class ScenePerspective: public Scene {
public:
	ScenePerspective(pCameraPerspective camera = pCameraPerspective());

	virtual ~ScenePerspective();

	void setCamera(pCameraPerspective camera);

	pCamera getCamera();

	void draw();

	void drawDR();

	void draw(space::CameraPerspective& camera);

	void drawDR(space::CameraPerspective& camera);

	void drawPicking();

	void drawSkybox();

	void drawDepthInt();

	void drawAOG();

	void drawAOC();

	void drawOcclusion();

private:
	pCameraPerspective mCamera;
};

} /* models */
static pScenePerspective buildScenePerspective(pCameraPerspective camera =
		pCameraPerspective()) {
	return pScenePerspective(new models::ScenePerspective(camera));
}
} /* fillwave */
#endif /* ScenePerspective_H_ */
