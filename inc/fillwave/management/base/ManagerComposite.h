/*
 * ManagerNested.h
 *
 *  Created on: Feb 1, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MANAGEMENT_BASE_MANAGERCOMPOSITE_H_
#define INC_FILLWAVE_MANAGEMENT_BASE_MANAGERCOMPOSITE_H_

#include <unordered_map>
#include <fillwave/management/base/Manager.h>

namespace fillwave {
namespace framework {

/**
 * \brief Basic composition to be managed
 *
 * \param T - Component type
 *
 * \param C - Creation policy
 *
 * \param P - Parameters to T's class constructor
 */
template<class T, class C, typename ... P>
struct Composition {
    Composition(P ... parameters) :
            mComponent(C().Create(parameters...)) {
    }
    T mComponent;
};

/**
 * \brief Basic manager of composites
 *
 * \param T - Item store class to store
 *
 * \param R - Item  to Return
 *
 * \param M - Maximum items
 *
 * \param K - Key class
 */
template <class T, class R, class K, size_t M, class C, typename... P>
class ManagerComposite : public std::unordered_map<K, T> {
public:

    ManagerComposite() = default;
	virtual ~ManagerComposite() = default;

	R add(const K& key, P... parameters) {
		if ((*this).find(key) != (*this).end()) {
			return (*this)[key]->mComponent;
		}

		if ((*this).size() >= M) {
			return R();
		}

		(*this)[key] = FillwaveItemConstruct<T, C, P... >(parameters...);
		return (*this)[key]->mComponent;
	}

	void remove(T& item) {
		auto it = std::find((*this).begin(), (*this).end(),
				item);
		if (it != (*this).end()) {
			(*this).erase(it);
		}
	}
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MANAGEMENT_BASE_MANAGERCOMPOSITE_H_ */
