/*
 * macros.h
 *
 *  Created on: 22 May 2015
 *      Author: Filip Wasil
 */

#ifndef MACROS_H_
#define MACROS_H_

#include <algorithm>

namespace fillwave {
namespace framework {

template <typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
	return std::unique_ptr < T > (new T(std::forward<Args>(args)...));
}

template <class T>
void remove(std::vector<T>& vector, T& item) {
	auto it = std::find(vector.begin(), vector.end(), item);
	if (it != vector.end()) {
		vector.erase(it);
	}
}

#if (!defined UINT_MAX)
#   define UINT_MAX (~((unsigned int)0))
#endif

/*
 template<typename T>
 using shared_ptr_unsynchronized = std::__shared_ptr<T, __gnu_cxx::_S_single>;
 */

} /* namespace framework */
} /* namespace fillwave */

#endif /* MACROS_H_ */
