//
// Created by filip on 27.04.16.
//

#ifndef LIBFILLWAVE_FOCUSABLE_H
#define LIBFILLWAVE_FOCUSABLE_H

namespace fillwave {
    class Engine;
    namespace framework {

        class Focusable {
        public:
            Focusable(Engine* engine);
            virtual ~Focusable();
        protected:
            Engine* mEngine;
        };
    }
}

#endif //LIBFILLWAVE_FOCUSABLE_H
