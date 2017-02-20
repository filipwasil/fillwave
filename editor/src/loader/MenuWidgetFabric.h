#ifndef MENUWIDGETFABRIC_H
#define MENUWIDGETFABRIC_H

#include <QWidget>
#include <QMap>

#include "factory/IMenuWidgetFactory.h"

namespace loader
{
    class MenuWidgetFabric
    {
        //Q_OBJECT
    public:
        MenuWidgetFabric();
        ~MenuWidgetFabric();
        QWidget * createWidget(QString typeName, QVector<std::pair<QString, QString>> &parametersVector);
    private:
        QMap<QString, factory::IMenuWidgetFactory*> mFabricMap;
    };

}

#endif //FILLWAVE_QT_EXAMPLE_MENUWIDGETFABRIC_H
