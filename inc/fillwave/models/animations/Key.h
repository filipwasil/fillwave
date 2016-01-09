/*
 * Key.h
 *
 *  Created on: Jun 23, 2014
 *      Author: Filip Wasil
 */

#ifndef KEY_H_
#define KEY_H_

namespace fillwave {
namespace framework {

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
	virtual ~Key() = default;
};

} /* framework */
} /* fillwave */

#endif /* KEY_H_ */
