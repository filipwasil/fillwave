/*
 * PtrShared.h
 *
 *  Created on: Apr 22, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_COMMON_PTRSHARED_H_
#define INC_FILLWAVE_COMMON_PTRSHARED_H_

#include <cwchar>
#include <memory>

namespace fillwave {
namespace framework {

#ifdef FILLWAVE_COMPILATION_OPTIMIZE_SHARED_POINTERS

template<typename T>
struct PtrShared final {
	PtrShared(T* ptr = nullptr)
		:mRefs(new size_t(1)), mPtr(ptr) {
	}

	template <class C>
	PtrShared(const PtrShared<C>& other) : mRefs(other.mRefs), mPtr(other.mPtr) {
		++*mRefs;
	}

	~PtrShared() {
		reset();
	}

	template <class C>
	PtrShared<T>& operator=(const C& other ) {
		if (this != &other) {
			reset();
			mPtr = other.mPtr;
			mRefs = other.mRefs;
		}
		return *this;
	}

	PtrShared<T>& operator=(PtrShared<T>& other) {
		if (this != &other) {
			reset();
			mPtr = other.mPtr;
			mRefs = other.mRefs;
		}
		return *this;
	}

	PtrShared<T>& operator=(const PtrShared<T>& other) {
		if (this != &other) {
			reset();
			mPtr = other.mPtr;
			mRefs = other.mRefs;
		}
		return *this;
	}

	PtrShared<T>& operator=(T* p) {
		if (mPtr != p) {
			mPtr = p;
			mRefs = 1;
		}
		return *this;
	}

	operator bool() const {
		return nullptr == mPtr;
	}

	T& operator*() {
		return mPtr;
	}

	const T& operator*() const {
		return mPtr;
	}

	T* operator->() {
		return mPtr;
	}

	const T* operator->() const {
		return mPtr;
	}

	void reset() {
		if (0 == --*mRefs) {
			delete mRefs;
			delete mPtr;
			mPtr = nullptr;
		}
	}

	T* get() const {
		return mPtr;
	}

	size_t* mRefs;
	T* mPtr;
};

template <class T, typename... P>
PtrShared<T> make_shared(P... p) {
	return PtrShared<T>(new T(p...));
}

#else

template<class T>
using PtrShared = std::shared_ptr<T>;

template <class T, typename... Args>
auto make_shared(Args&&... args) -> decltype(std::make_shared(std::forward<Args>(args)...)) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

#endif

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_COMMON_PTRSHARED_H_ */
