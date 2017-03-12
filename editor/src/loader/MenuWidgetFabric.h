#pragma once

#include <QWidget>
#include <QMap>
#include <common/ISceneController.h>
#include "factory/IMenuWidgetFactory.h"
#include "common/ISceneController.h"
#include "loader/IWidgetFabric.h"

namespace loader {
    class MenuWidgetFabric : public IWidgetFabric {
    public:
        MenuWidgetFabric(common::ISceneController *scene);

        ~MenuWidgetFabric();

        QWidget *createWidget(QString typeName, QVector<std::pair<QString, QString>> &parametersVector);

    private:
        QMap<QString, factory::IMenuWidgetFactory *> mFabricMap;
        common::ISceneController *mScene;
    };

}
