#ifndef MENUWIDGETFABRIC_H
#define MENUWIDGETFABRIC_H
#include <utility>
#include <QVector>
#include <QWidget>

namespace loader
{

class MenuWidgetFabric
{
public:
    MenuWidgetFabric();
    QWidget* createWidget(QString type, QVector<std::pair<QString,QString>>& parametersVector);
};
}
#endif // MENUWIDGETFABRIC_H
