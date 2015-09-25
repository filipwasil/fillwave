/*
 * Computer.h
 *
 *  Created on: May 30, 2014
 *      Author: filip
 */


#ifndef COMPUTER_H_
#define COMPUTER_H_

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

#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
namespace core {

/*! \class Computer
 * \brief Not used.
 *
 */

class Computer {
public:
   Computer();
   virtual ~Computer();
};

} /* core */
} /* fillwave */

#endif /* COMPUTER_H_ */


/*
void glDispatchCompute(GLuint num_groups_x​, GLuint num_groups_y​, GLuint num_groups_z​);
num_groups_x
The number of work groups to be launched in the X dimension.
num_groups_y
The number of work groups to be launched in the Y dimension.
num_groups_z
The number of work groups to be launched in the Z dimension.

void glDispatchComputeIndirect(GLintptr indirect​);
indirect
The offset into the buffer object currently bound
to the GL_DISPATCH_INDIRECT_BUFFER​ buffer
target at which the dispatch parameters are stored.
*/
