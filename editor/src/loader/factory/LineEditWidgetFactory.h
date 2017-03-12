#pragma once

#include "IMenuWidgetFactory.h"

namespace loader {
    namespace factory {
        class LineEditWidgetFactory : public IMenuWidgetFactory {
        //Q_OBJECT
        public:
            QWidget *create(QVector<std::pair<QString, QString>> &parametersVector, common::ISceneController *scene);
        };
    }
}

