#pragma once

#include <QWidget>
#include <common/MenuWidgetTranslator.h>

namespace common {
    class ISceneController : public QObject {
    public:
        virtual ~ISceneController() {}

        virtual void addTranslator(MenuWidgetTranslator *translator) = 0;

        virtual void deleteTranslators() = 0;

    public slots:

        virtual void updateScenField(QWidget *menuElement) = 0;
    };
}

