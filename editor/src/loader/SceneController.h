#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include <QGLWidget>
#include "common/ISceneController.h"

namespace loader {
    class SceneController : public common::ISceneController {
    public :
        SceneController(QGLWidget* scen);

        void updateScenField(QWidget *menuElement);

    private:
        QGLWidget * mScene;

        QVariant getValue(const QWidget *menuElement) const;
    };

}
#endif //SCENECONTROLLER_H
