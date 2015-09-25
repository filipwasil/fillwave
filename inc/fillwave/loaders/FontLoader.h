/*
 * FontLoader.h
 *
 *  Created on: Aug 9, 2014
 *      Author: Filip Wasil
 */

#ifndef FONTLOADER_H_
#define FONTLOADER_H_

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

#include <fontGenerator.h>

namespace fillwave {
namespace loader {

/*! \class FontLoader
 * \brief Loads fonts fromttf files.
 */

class FontLoader {
public:
	FontLoader();
	virtual ~FontLoader();
	void load(std::string name);
};

} /* loader */
} /* fillwave */

#endif /* FONTLOADER_H_ */
