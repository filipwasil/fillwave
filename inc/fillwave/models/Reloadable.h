/*
 * Renderable.h
 *
 *  Created on: May 24, 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_MODELS_RELOADABLE_H_
#define INC_FILLWAVE_MODELS_RELOADABLE_H_

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

#include <fillwave/core/buffers/VertexArray.h>
#include <fillwave/core/texturing/Sampler.h>

namespace fillwave {
class Engine;
namespace models {

/*! \class Reloadable
 * \brief Encapsulates Renderable objects.
 */

class Reloadable {
public:
   Reloadable(Engine* engine);

   virtual ~Reloadable();

   virtual void initBuffers() = 0;

   virtual void initPipeline() = 0;

   virtual void initUniformsCache() = 0;

   virtual void initVAO() = 0;

   virtual void initVBO() = 0;

   void reload();

protected:
   pVertexArray mVAO;

   pSampler mSampler;
};

} /* models */
} /* fillwave */

#endif /* INC_FILLWAVE_MODELS_RELOADABLE_H_ */
