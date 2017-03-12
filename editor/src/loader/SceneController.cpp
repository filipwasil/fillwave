#include "SceneController.h"
#include <QVariant>
#include <QMetaObject>

namespace loader {

    SceneController::SceneController(QGLWidget * scen) :
    mScene(scen)
    {}

    void SceneController::updateScenField(QWidget *menuElement) {
        QVariant elementName = menuElement->property("objectName");
        QVariant elementValue = getValue(menuElement);
        if (!elementName.isValid() || !elementValue.isValid()) {
            return;
        }
        QMap<QString, QVariant> parameter;
        parameter[elementName.toString()] = elementValue;
        mScene->setProperty("sceneParameter", parameter);
    }

    QVariant SceneController::getValue(const QWidget *menuElement) const {
        const QMetaObject *metaobject = menuElement->metaObject();
        if (metaobject->indexOfProperty("value") != -1) {
            return menuElement->property("value");
        }
        else if (metaobject->indexOfProperty("text") != -1) {
            return menuElement->property("text");
        }
        return QVariant();
    }
}