/*
 * Key.h
 *
 *  Created on: Jun 23, 2014
 *      Author: Filip Wasil
 */

#ifndef KEY_H_
#define KEY_H_

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
namespace animation {

/*! \class Key
 * \brief Base for all animation keys.
 */

template<class T>
class Key {
public:
	float mTime;
	T mValue;
	Key(float timeStamp, T value)
			: mTime(timeStamp), mValue(value) {
	}
	virtual ~Key() {
	}
};

} /* animation */
} /* fillwave */

#endif /* KEY_H_ */
