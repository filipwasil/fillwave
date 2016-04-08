/*
 * ShaderLoaderVertex.h
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

#ifndef SHADERLOADERVERTEX_H_
#define SHADERLOADERVERTEX_H_

#include <fillwave/loaders/ShaderLoader.h>

namespace fillwave {
namespace framework {

/*! \class ShaderLoaderVertex
 * \brief ShaderLoader to load vertex shader sources.
 */

class ShaderLoaderVertex: public ShaderLoader {
  public:
	ShaderLoaderVertex(bool animated = false);

	virtual ~ShaderLoaderVertex() = default;

	const std::string getSource() const;

  private:
	bool mAnimated;
};

} /* framework */
} /* fillwave */

#endif /* SHADERLOADERVERTEX_H_ */
