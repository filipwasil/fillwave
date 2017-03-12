#include "SceneController.h"
#include <QVariant>
#include <QMetaObject>

namespace common {

    SceneController::SceneController(QWidget * scen) :
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

    void SceneController::addTranslator(MenuWidgetTranslator *translator) {
        mTranslators.push_back(translator);
        QObject::connect(translator, &MenuWidgetTranslator::updateScene, this, &SceneController::updateScenField);
    }

    void SceneController::deleteTranslators() {
        qDeleteAll(mTranslators);
        mTranslators.clear();
    }
}