#ifndef ISCENE_H
#define ISCENE_H

#include <utility>
#include <QString>

namespace scene {
    class IScene {
    public:
        virtual void updateValue(const std::pair<QString, QString> &value) = 0;
    };
}

#endif //IScene_H
