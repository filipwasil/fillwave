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
void remove(std::vector<T>& vec, T& item) {
	auto new_end = std::remove_if(vec.begin(), vec.end(),
	[item](const std::unique_ptr<T>& l) {
		return item == l.get();
	});
	vec.erase(new_end, vec.end());
}

/* Forgive me, but i needed this so badly ... */
template<typename CONTAINER>
void vectorForward(CONTAINER &vec) {}

template<typename CONTAINER, typename TCURRENT, typename... TNEXT>
void vectorForward(CONTAINER &container, TCURRENT&& t, TNEXT&&... args) {
	container->push_back(std::move(t));
	vectorForward(container, args...);
}

template<typename CONTAINER, typename TCURRENT, typename... TNEXT>
CONTAINER make_unique_container(TCURRENT&& t, TNEXT&&... args) {
	CONTAINER container;
	container->push_back(std::move(t));
	vectorForward<CONTAINER, TNEXT...>(container, args...);
	return std::move(container);
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
