//
// Created by filip on 27.04.16.
//

#ifndef LIBFILLWAVE_IFOCUSABLE_H
#define LIBFILLWAVE_IFOCUSABLE_H

#include <fillwave/actions/events/EventType.h>
#include <fillwave/actions/callbacks/Callback.h>
#include <vector>
#include <algorithm>

namespace fillwave {
class Engine;
namespace framework {

class IFocusable {
 public:
	IFocusable(Engine* engine);
	virtual ~IFocusable();

	virtual void handleFocusEvent(EventType& event) = 0;
	void attachCallback(Callback* callback);

	template <class T>
	static void handleEvent(
	   std::vector<T>& callbacks, EventType& event) {
		/* Run callbacks */
		for (auto& it : callbacks) {
			if (it->isEnabled()) {
				if (it->getEventType() == event.getType()) {
					it->perform(event);
				}
			}
		}

		/* Erase finished callbacks */
		auto _find_finished_function =
		   [](T & m) -> bool {return m->isFinished();};
		auto _begin = callbacks.begin();
		auto _end = callbacks.end();
		auto it = std::remove_if(_begin, _end, _find_finished_function);
		callbacks.erase(it, _end);
	}

 protected:
	Engine* mEngine;
	std::vector<Callback*> mCallbacks;
};

}
}

#endif //LIBFILLWAVE_IFOCUSABLE_H
