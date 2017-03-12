#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "common/ISceneController.h"

namespace loader {

    class LoadMenu {
    public:
        LoadMenu();

        QVBoxLayout *createDefaultMainMenu(common::ISceneController *sceneController);

        QVBoxLayout *createMainMenu(QString pathToFile);

    protected:
        QList<QWidget *> getMenuWidgetList(common::ISceneController *sceneControlle) const;

        QVBoxLayout *getMainMenuVBoxLayout(const QList<QWidget *> &menuWidgets);

        const QString mDefaultScenerioMenu;
    };
}

