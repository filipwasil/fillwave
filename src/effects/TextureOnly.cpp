/*
 * TextureOnly.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/effects/TextureOnly.h>

namespace fillwave {
namespace effects {

TextureOnly::TextureOnly() {

}

TextureOnly::~TextureOnly() {

}

void TextureOnly::preDrawAction(core::Program* program) {
	program->uniformPush("uTextureOnlyEffect", true);
}

void TextureOnly::postDrawAction(core::Program* program) {
	program->uniformPush("uTextureOnlyEffect", false);
}

void TextureOnly::stopAction(core::Program* program) {
	program->uniformPush("uTextureOnlyEffect", false);
}

void TextureOnly::startAction(core::Program* program) {
	program->uniformPush("uTextureOnlyEffect", true);
}

} /* effects*/
} /* fillwave */
