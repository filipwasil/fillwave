#ifndef XMLREADER_H
#define XMLREADER_H
#include "idatareader.h"
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>
#include <QFile>

namespace databaseperation
{
class XmlReader : public IDataReader
{
public:
    XmlReader();
    elementsData load(QString pathToFile) override;

private:
    void readXml(QFile* file);
    void processXml();
    void procesChild();
    std::pair<QString, QString> extractChilds();

    elementsData mRetrivedData;
    QVector<QString> mWidgetList;
    QXmlStreamReader xml;
};
}
#endif // XMLREADER_H
