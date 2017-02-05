#ifndef CREATEMENUWIDGETS_H
#define CREATEMENUWIDGETS_H
#include <QVector>
#include <QMap>
#include <QWidget>
#include <utility>

namespace sceneriocreation {
using parametersVector = QVector<std::pair<QString, QString> >;
using elementsData = QMap<QString, parametersVector >;

class CreateMenuWidgets
{
public:
    CreateMenuWidgets();
    QVector<QWidget*> creatWidgets(elementsData elements);
};
}
#endif // CREATEMENUWIDGETS_H
