#ifndef LINEEDITWIDGETFACTORY_H
#define LINEEDITWIDGETFACTORY_H

#include "IMenuWidgetFactory.h"

namespace loader
{
    namespace factory
    {
        class LineEditWidgetFactory : public IMenuWidgetFactory
        {
        public:
            QWidget *create(QVector<std::pair<QString, QString>> &parametersVector);
        };
    }
}


#endif //LINEEDITWIDGETFACTORY_H
