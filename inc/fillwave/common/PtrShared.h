/*
 * PtrShared.h
 *
 *  Created on: Apr 22, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_COMMON_PTRSHARED_H_
#define INC_FILLWAVE_COMMON_PTRSHARED_H_

#include <cwchar>

namespace fillwave {
namespace framework {

template<typename T>
struct PtrShared final {
	PtrShared(T* ptr = nullptr)
		:mRefs(new size_t(1)),  mPtr(ptr) {
	}

	template <class C>
	PtrShared(const PtrShared<C>& other) : mRefs(other.mRefs), mPtr(other.mPtr) {
		++*mRefs;
	}

	~PtrShared() {
		reset();
	}

	PtrShared<T>& operator=(const PtrShared<T>& other) {
		if (this != &other) {
			reset();
			mPtr = other.mPtr;
			mRefs = other.mRefs;
			++*mRefs;
		}
		return *this;
	}

	operator bool() const {
		return nullptr == mPtr;
	}

	PtrShared<T>& operator=(T* p) {
		if (mPtr != p) {
			mPtr = p;
			mRefs = 1;
		}
		return *this;
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

private:
	T* mPtr;
};

template <class T, typename... P>
PtrShared<T> make_shared(P... p) {
	return PtrShared<T>(new T(p...));
}

template <class T, class C, typename... P>
PtrShared<T> make_shared(P... p) {
	return PtrShared<T>(new C(p...));
}

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_COMMON_PTRSHARED_H_ */
