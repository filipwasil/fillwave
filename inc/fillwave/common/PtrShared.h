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
class PtrShared {
 public:
	PtrShared(T* p = nullptr)
		: m(new MetaData(p, 1)) {
	}

	template <class C>
	PtrShared(const PtrShared<C>& other) {
		m->mPtr = other.m->mPtr;
		m->mRefs = other.m->mRefs;
		++m->mRefs;
	}

	PtrShared(const PtrShared<T>& other)
		: m(other.m) {
		++m->mRefs;
	}
	~PtrShared() {
		reset();
	}

	PtrShared<T>& operator=(const PtrShared<T>& other) {
		if (this != &other) {
			reset();

			m->mPtr = other.m->mPtr;
			m->mRefs = other.m->mRefs;
		}
		return *this;
	}

	operator bool() const {
		return nullptr == m->mPtr;
	}

	PtrShared<T>& operator=(T* p) {
		if (m->mPtr != p) {
			m = {p, 1};
		}
		return *this;
	}

	T& operator*() {
		return m->mPtr;
	}

	const T& operator*() const {
		return m->mPtr;
	}

	T* operator->() {
		return m->mPtr;
	}

	const T* operator->() const {
		return m->mPtr;
	}

	void reset() {
		if (0 == --(m->mRefs)) {
			delete m;
		}
	}
	T* get() const {
		return m->mPtr;
	}

 private:
	struct MetaData {
		MetaData(T* p, size_t c) : mPtr(p), mRefs(c) {

		}
		template <class C>
		MetaData(C& other) {
			mRefs = ++other.mRefs;
			mPtr = other.mPtr;
		}
		template <class C>
		MetaData& operator=(C* p) {
			if (mPtr != p) {
				mPtr = p;
				mRefs = 1;
			}
			return *this;
		}
		T* mPtr;
		size_t mRefs;
	};

 public:
	MetaData* m;
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
