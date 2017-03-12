#ifndef ISCENECONTROLLER_H
#define ISCENECONTROLLER_H

#include <QWidget>

namespace common {
    class ISceneController {
    public slots:
        virtual void updateScenField(QWidget *menuElement) = 0;
    };
}

#endif //ISCENECONTROLLER_H
