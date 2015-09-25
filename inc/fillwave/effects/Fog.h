/*
 * Fog.h
 *
 *  Created on: Jul 18, 2014
 *      Author: Filip Wasil
 */

#ifndef FOG_H_
#define FOG_H_

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

#include <fillwave/effects/Effect.h>

namespace fillwave {
namespace effects {

/*! \class Fog
 *
 * \brief Effect to create a fog.
 *
 */

class Fog : public Effect{
private:
   glm::vec3 mColour;
   GLfloat mNearDistance;
   GLfloat mFarDistance;

public:
   glm::vec3 getColour() {return mColour;}
   GLfloat getNearDistance() {return mNearDistance;}
   GLfloat getFarDistance() {return mFarDistance;}

   void setColour(glm::vec3 colour) {mColour = colour;}
   void setNearDistance(GLfloat near) {mNearDistance = near;}
   void setFarDistance(GLfloat far) {mFarDistance = far;}

   Fog(glm::vec3 colour = glm::vec3(0.1,0.1,0.1),
       GLfloat near = 0.1,
       GLfloat far = 20.0f);

   virtual ~Fog();

   void preDrawAction(core::Program* program);
   void postDrawAction(core::Program* program);
   void stopAction(core::Program* program);
   void startAction(core::Program* program);
};

} /* effects */
typedef std::shared_ptr<effects::Fog> pFog;
} /* fillwave*/
#endif /* FOG_H_ */
