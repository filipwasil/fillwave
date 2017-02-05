#ifndef IDATAREADER_H
#define IDATAREADER_H
#include <QWidget>
#include <QVector>
#include <utility>

namespace databaseperation
{
using parametersVector = std::pair<QString, QVector<std::pair<QString, QString>> >;
using elementsData = QVector<parametersVector>;
class IDataReader
{
public:
    virtual elementsData load(QString pathToFile) = 0;
};
}
#endif // IXMLREADER_H
