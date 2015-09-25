/*
 * Blending.h
 *
 *  Created on: 24 lut 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_COMMON_BLENDING_H_
#define INC_FILLWAVE_COMMON_BLENDING_H_

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
namespace common {

/*! \struct Blending
 * \brief Structure defining the blending parameters.
 *
 */

struct Blending {
	GLenum mSource;
	GLenum mDestination;
};

} /* common */
} /* fillwave */

#endif /* INC_FILLWAVE_COMMON_BLENDING_H_ */
