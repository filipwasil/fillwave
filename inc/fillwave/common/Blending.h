/*
 * Blending.h
 *
 *  Created on: 24 lut 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_COMMON_BLENDING_H_
#define INC_FILLWAVE_COMMON_BLENDING_H_

namespace fillwave {
namespace framework {
/*! \struct Blending
 * \brief Structure defining the blending parameters.
 */

struct Blending {
	GLenum mSource;
	GLenum mDestination;
};

} /* framework */
} /* fillwave */

#endif /* INC_FILLWAVE_COMMON_BLENDING_H_ */
