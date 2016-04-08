/*
 * Texture1D.h
 *
 *  Created on: Sep 10, 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE1D_H_
#define TEXTURE1D_H_

#include <fillwave/core/texturing/Texture.h>

namespace fillwave {
namespace core {

/*! \class Texture1D
 * \brief Not used.
 */

class Texture1D: public Texture {
  public:
	Texture1D(ParameterList& parameters);
	virtual ~Texture1D() = default;
	void log();
};

} /* core */
typedef std::shared_ptr<core::Texture1D> pTexture1D;
} /* fillwave */

#endif /* TEXTURE1D_H_ */
