#pragma once

#include <QWidget>
#include <QVector>
#include "common/ISceneController.h"

namespace common {
    class SceneController : public common::ISceneController {
    Q_OBJECT
    public :
        SceneController(QWidget *scen);

        void updateScenField(QWidget *menuElement);

        void addTranslator(MenuWidgetTranslator *translator);

        void deleteTranslators() override;

    private:
        QWidget *mScene;
        QVector<MenuWidgetTranslator *> mTranslators;

        QVariant getValue(const QWidget *menuElement) const;
    };
}

