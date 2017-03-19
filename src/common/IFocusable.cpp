//
// Created by filip on 27.04.16.
//

#include <fillwave/common/IFocusable.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
namespace framework {

IFocusable::IFocusable(Engine *engine)
    : mEngine (engine) {

}

IFocusable::~IFocusable() {
  mEngine->dropFocus (this);
}

void IFocusable::attachCallback(Callback *callback) {
  mCallbacks.push_back (callback);
}

}
}