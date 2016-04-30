//
// Created by filip on 30.04.16.
//

#ifndef LIBFILLWAVE_OBSERVABLE_H
#define LIBFILLWAVE_OBSERVABLE_H

#include <fillwave/common/IObserver.h>
#include <vector>
#include <algorithm>

namespace fillwave {
namespace framework {

class Observable {
 public:
	Observable() = default;
	virtual ~Observable() {
		for (auto& it : mObservers) {
			it->onDeath(this);
		}
	}

	void addObserver(IObserver* observer) {
		for (auto& it : mObservers) {
			if (it == observer) {
				return;
			}
			mObservers.push_back(observer);
		}
	}

	void dropObserver(IObserver* observer) {
		mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer),
		                 mObservers.end());
	}

	void notifyObservers() {
		for (auto& it : mObservers) {
			it->onChanged(this);
		}
	}

 protected:
	std::vector<IObserver*> mObservers;
};

}
}

#endif //LIBFILLWAVE_OBSERVABLE_H
