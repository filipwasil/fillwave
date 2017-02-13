#ifndef IDATAREADER_H
#define IDATAREADER_H

#include <QWidget>
#include <QVector>
#include <utility>

namespace loader
{
    class IDataLoader
    {
    public:
        virtual QList<QWidget *> load(QString pathToFile) = 0;
    };
}
#endif // IXMLREADER_H
