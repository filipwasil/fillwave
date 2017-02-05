#ifndef CREATESCENERIOMENU_H
#define CREATESCENERIOMENU_H
#include <QVector>

#include <QWidget>
#include "loader/XmlLoader.h"


namespace sceneriocreation
{
class CreateScenerioMenu
{
public:
    CreateScenerioMenu();
    QVector<QWidget*> create(QString path);
private:
    void loadFile(QString path);
};
}
#endif // CREATESCENERIOMENU_H
