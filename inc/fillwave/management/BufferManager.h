/*
 * BufferManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef BUFFERMANAGER_H_
#define BUFFERMANAGER_H_

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

#include <fillwave/core/buffers/Buffer.h>
#include <fillwave/models/Reloadable.h>

namespace fillwave {
namespace manager {

struct VAOObject {
   models::Reloadable* mVAOUser;
   pwVertexArray mVAO;
};

typedef std::shared_ptr<VAOObject> puVAOObject;

/*! \class BufferManager
 * \brief Not used.
 */

class BufferManager {
public:
   BufferManager();

   virtual ~BufferManager();

   void collectGarbage();

   void reload();

   pVertexArray getVAO(models::Reloadable* renderable);

private:
   std::vector<puVAOObject> mVAOObjects;
};

} /* manager */
typedef std::unique_ptr<manager::BufferManager> puBufferManager;
} /* fillwave */

#endif /* BUFFERMANAGER_H_ */
