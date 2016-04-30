//
// Created by filip on 30.04.16.
//

#ifndef LIBFILLWAVE_IOBSERVER_H
#define LIBFILLWAVE_IOBSERVER_H

namespace fillwave {
namespace framework {
class Observable;

class IObserver {
 public:
	IObserver() = default;
	virtual ~IObserver() = default;
	virtual void onDeath(Observable* observable) = 0;
	virtual void onChanged(Observable* observable) = 0;
};
}
}

#endif //LIBFILLWAVE_IOBSERVER_H
