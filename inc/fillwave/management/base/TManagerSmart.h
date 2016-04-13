/*
 * TManagerSmart.h
 *
 *  Created on: Mar 30, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSMART_H_
#define INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSMART_H_

#include <unordered_map>
#include <fillwave/common/Macros.h>

#define FILLWAVE_FORGET_ABOUT_ME()           \
do {                                         \
	if ((*this).find(key) != (*this).end()) { \
		return (*this)[key].get();             \
	}                                         \
	if ((*this).size() >= M) {                \
		printError();                          \
		return nullptr;                        \
	}                                         \
} while(0)

namespace fillwave {
namespace framework {

static constexpr size_t FILLWAVE_MANAGEMENT_MAX_ITEMS = 5000;

/**
 * \brief Basic manager of composites
 *
 * \param T - Item type
 *
 * \param K - Key class
 *
 * \param M - Maximum items
 *
 * \param P - T constructor parameters
 */

template <size_t M, class T, class K, typename ... P>
class TManagerSmart: public std::unordered_map<K, std::unique_ptr<T>> {
 public:
	TManagerSmart() = default;
	virtual ~TManagerSmart() = default;

	T* store(const K& key, P ... parameters) {
		FILLWAVE_FORGET_ABOUT_ME();
		return ((*this)[key] = make_unique<T>(parameters...)).get();
	}

	T* store(T* item, const K& key) {
		FILLWAVE_FORGET_ABOUT_ME();
		return ((*this)[key] = std::unique_ptr < T > (item)).get();
	}

 private:
	inline void printError() {
		const char error[] = "\033[35m[FATAL MANAGER OVERFLOW. "
				"FILLWAVE_MANAGEMENT_MAX_ITEMS too low.] \033[0m\n";
#ifdef __ANDROID__
		(void)__android_log_print(ANDROID_LOG_ERROR, error, "");
#else
		printf(error);
#endif
    }
};

} /* namespace framework */
} /* namespace fillwave */

#undef FILLWAVE_FORGET_ABOUT_ME

#endif /* INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSMART_H_ */
