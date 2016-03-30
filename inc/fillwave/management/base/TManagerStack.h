/*
 * TManagerStack.h
 *
 *  Created on: Mar 30, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSTACK_H_
#define INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSTACK_H_

#include <unordered_map>

namespace fillwave {
namespace framework {

/**
 * \brief Basic manager of composites
 *
 * \param T - Item store class to store
 *
 * \param M - Maximum items
 *
 * \param K - Key class
 */
template <class T, class K, size_t M, typename ... P>
class TManagerStack: public std::unordered_map<K, T> {
public:

	TManagerStack() = default;
	virtual ~TManagerStack() = default;

	T& add(const K& key, P ... parameters) {
		if ((*this).find(key) != (*this).end()) {
			return (*this)[key];
		}

		if ((*this).size() >= M) {
			abort();
		}

		return (*this)[key] = T(parameters...);
	}

	void remove(K& key) {
		(*this).erase(key);
	}
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSTACK_H_ */
