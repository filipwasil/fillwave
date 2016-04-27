//
// Created by filip on 27.04.16.
//

#include <fillwave/common/Focusable.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
    namespace framework {

        Focusable::Focusable(Engine* engine) : mEngine(engine) {

        }

        Focusable::~Focusable() {
            mEngine->unregisterCallback(this);
        }
    }
}