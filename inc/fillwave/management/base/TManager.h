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

/*! \class TManager
 * \brief Basic manager
 */
template <class T, size_t M, typename ... P>
class TManager: public std::vector<std::unique_ptr<T>> {
 public:

	TManager() = default;
	virtual ~TManager() = default;

	T* add(P ... parameters) {
		if ((*this).size() >= M) {
			return nullptr;
		}
		(*this).push_back(make_unique<T>(parameters...));
		return (*this).back().get();
	}

	bool isNew(T& item) {
		for (auto& it : (*this)) {
			if (it == item) {
				return false;
			}
		}
		return true;
	}

	void log() {
		for (auto& it : (*this)) {
			it->log();
		}
	}
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MANAGEMENT_BASE_TMANAGER_H_ */
