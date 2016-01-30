/*
 * Container.h
 *
 *  Created on: Jan 30, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MANAGEMENT_BASE_CONTAINER_H_
#define INC_FILLWAVE_MANAGEMENT_BASE_CONTAINER_H_

#include <memory>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <fillwave/common/Macros.h>

namespace fillwave {
namespace framework {

/*! \class PolicyDefault
 * \brief Creation policy which creates an object as regular pointer
 */
template<class T>
class PolicyDefault {
public:
	PolicyDefault() = default;
	~PolicyDefault() = default;

	template <typename... P>
	inline T* Create(P... parameters) {
		return new T(parameters...);
	}
};

/*! \class PolicyShared
 * \brief Creation policy which creates an object as shared pointer
 */
template<class T>
class PolicyShared {
public:
	PolicyShared() = default;
	~PolicyShared() = default;

	template <typename... P>
	inline std::shared_ptr<T> Create(P... parameters) {
		return std::make_shared<T>(parameters...);
	}
};

/*! \class PolicyUnique
 * \brief Creation policy which creates an object as unique pointer
 */
template<class T, typename... P>
class PolicyUnique {
public:
	PolicyUnique() = default;
	~PolicyUnique() = default;

	inline std::unique_ptr<T> Create(P... parameters) {
		return make_unique<T>(parameters...);
	}
};

/*! \fn FillwaveItemConstruct
 * \brief Helper function to enable creation by policies
 */
template <class T, class C, typename... P>
T FillwaveItemConstruct (P... parameters) {
	return C().Create(parameters...);
}

/*! \class Main Fillwave
 * \brief Basic manager
 */
template <class T, int M, class C, typename... P>
class Container {
public:

	Container() = default;
	virtual ~Container() = default;

	T add(P... parameters) {
		T item;
		if (mItems.size() < M) {
			item = FillwaveItemConstruct<T, C, P... >(parameters...);
			mItems.push_back(item);
		} else {
			item = T();
		}
		return item;
	}

	T get(int i) {
		if (mItems.size() < M) {
			return mItems[i];
		}
		return T();
	}

	void clear() {
		mItems.clear();
	}

	void remove(T item ) {
		auto it = std::find(mItems.begin(), mItems.end(),
				item);
		if (it != mItems.end()) {
			mItems.erase(it);
		}
	}

	int howMany() {
		return mItems.size();
	}

private:
	std::vector<T> mItems;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MANAGEMENT_BASE_CONTAINER_H_ */
