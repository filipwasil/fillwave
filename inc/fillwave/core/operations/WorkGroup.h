/*
 * WorkGroup.h
 *
 *  Created on: 16 Jun 2014
 *      Author: Filip Wasil
 */

#ifndef WORKGROUP_H_
#define WORKGROUP_H_

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

namespace fillwave {
namespace core {

/*! \class WorkGroup
 *
 * \brief Group of compute shader jobs.
 *
 * Not used.
 *
 */

class WorkGroup {
public:
    WorkGroup();
    virtual ~WorkGroup();
};

} /* core */
} /* fillwave */

#endif /* WORKGROUP_H_ */
