/*
 * macros.h
 *
 *  Created on: 22 May 2015
 *      Author: Filip Wasil
 */

#ifndef MACROS_H_
#define MACROS_H_

namespace fillwave {
namespace framework {

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

} /* namespace framework */
} /* namespace fillwave */

#endif /* MACROS_H_ */
