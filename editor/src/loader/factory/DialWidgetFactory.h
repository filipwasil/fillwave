#ifndef DIALWIDGETFACTORY_H
#define DIALWIDGETFACTORY_H
#include "IMenuWidgetFactory.h"

namespace loader
{
    namespace factory
    {

        class DialWidgetFactory : public IMenuWidgetFactory
        {
        public:
            QWidget *create(QVector<std::pair<QString, QString>> &parametersVector);
        };
    }
}

#endif //EXAMPLE_DIALWIDGETFACTORY_H
