/*
 * TManagerSmart.h
 *
 *  Created on: Mar 30, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSMART_H_
#define INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSMART_H_

#include <unordered_map>

namespace fillwave {
namespace framework {

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
		if ((*this).find(key) != (*this).end()) {
			return (*this)[key].get();
		}

		if ((*this).size() >= M) {
			/* There is no smarter solution needed */
			const char error[] = "\033[35m [FATAL ERROR. MANAGER OVERFLOW] \033[0m";
#ifdef __ANDROID__
			(void)__android_log_print(ANDROID_LOG_ERROR, error);
#else
			printf(error);
#endif
			return nullptr;
		}

		return ((*this)[key] = make_unique<T>(parameters...)).get();
	}
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSMART_H_ */
