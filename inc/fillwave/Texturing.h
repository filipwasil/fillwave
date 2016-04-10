/*
 * Texturing.h
 *
 *  Created on: Apr 10, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_TEXTURING_H_
#define INC_FILLWAVE_TEXTURING_H_

#include <fillwave/Config.h>

#ifdef FILLWAVE_TEXTURE_LOADER_GLI
#include <gli/gli.hpp>
#else
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif /* FILLWAVE_TEXTURE_LOADER_GLI */

#endif /* INC_FILLWAVE_TEXTURING_H_ */
