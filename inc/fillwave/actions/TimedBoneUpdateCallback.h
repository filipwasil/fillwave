/*
 * TimedBoneUpdateCallback.h
 *
 *  Created on: 2 Jul 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDBONEUPDATECALLBACK_H_
#define TIMEDBONEUPDATECALLBACK_H_

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

#include <fillwave/actions/TimedCallback.h>

namespace fillwave {
namespace models{
class Model;
}

namespace actions {

/*! \class TimedBoneUpdateCallback
 *
 * \brief TimedCallback to update animation keys.
 * It will be attached to every model containing animations.
 *
 */

class TimedBoneUpdateCallback: public TimedCallback {
public:
   TimedBoneUpdateCallback(models::Model* model);
   virtual ~TimedBoneUpdateCallback();

   /*
    * perform
    *
    * \brief Performs ItemCallback action
    */
   void performTime(TimeEventData& data);

protected:
   models::Model* mModel;
};

} /* actions */
} /* fillwave */

#endif /* TIMEDBONEUPDATECALLBACK_H_ */
