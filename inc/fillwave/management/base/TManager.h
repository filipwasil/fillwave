/*
 * Container.h
 *
 *  Created on: Jan 30, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MANAGEMENT_BASE_TMANAGER_H_
#define INC_FILLWAVE_MANAGEMENT_BASE_TMANAGER_H_

#include <memory>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <fillwave/common/Macros.h>

namespace fillwave {
namespace framework {

/*! \class PolicyShared
 * \brief Creation policy which creates an object as shared pointer
 */
template<class T>
class TPolicyShared {
public:
	TPolicyShared() = default;
	~TPolicyShared() = default;

	template <typename... P>
	inline std::shared_ptr<T> Create(P... parameters) {
		return std::make_shared<T>(parameters...);
	}
};

/*! \class PolicyUnique
 * \brief Creation policy which creates an object as unique pointer
 */
template<class T>
class TPolicyUnique {
public:
	TPolicyUnique() = default;
	~TPolicyUnique() = default;

	template <typename... P>
	inline std::unique_ptr<T> Create(P... parameters) {
		return make_unique<T>(parameters...);
	}
};

/*! \fn FillwaveItemConstruct
 * \brief Helper function to enable creation by policies
 */
template <class T, class C, typename... P>
inline T FillwaveItemConstruct (P... parameters) {
	return C().Create(parameters...);
}

/*! \class Main Fillwave
 * \brief Basic manager
 */
template <class T, size_t M, class C, typename... P>
class TManager : public std::vector<T> {
public:

	TManager() = default;
	virtual ~TManager() = default;

	T add(P... parameters) {
		if ((*this).size() >= M) {
			return T();
		}
		(*this).push_back(FillwaveItemConstruct<T, C, P... >(parameters...));
		return (*this).back();
	}

	void remove(T& item) {
		auto it = std::find((*this).begin(), (*this).end(),
				item);
		if (it != (*this).end()) {
			(*this).erase(it);
		}
	}

	bool isNew(T& item) {
		for(auto& it : (*this)) {
			if (it == item) {
				return false;
			}
		}
		return true;
	}

	void log() {
		for(auto& it : (*this)) {
			it->log();
		}
	}
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MANAGEMENT_BASE_TMANAGER_H_ */
