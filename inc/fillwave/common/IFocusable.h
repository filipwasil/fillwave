//
// Created by filip on 27.04.16.
//

#ifndef LIBFILLWAVE_IFOCUSABLE_H
#define LIBFILLWAVE_IFOCUSABLE_H

#include <fillwave/actions/events/EventType.h>
#include <fillwave/actions/callbacks/Callback.h>
#include <vector>

/*! \class IFocusable
 * \brief Capable to notify engine that focus related callbacks can be freed.
 */

namespace fillwave {
class Engine;
namespace framework {

class IFocusable {
 public:
	IFocusable(Engine* engine);
	virtual ~IFocusable();

	virtual void handleFocusEvent(EventType& event) = 0;
	void attachCallback(Callback* callback);

 protected:
	Engine* mEngine;
	std::vector<Callback*> mCallbacks;
};

}
}

#endif //LIBFILLWAVE_IFOCUSABLE_H
