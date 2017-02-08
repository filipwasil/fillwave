#ifndef XMLREADER_H
#define XMLREADER_H
#include "idataloader.h"
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>
#include <QFile>
#include <QList>
#include <QWidget>

namespace loader
{
class XmlReader : public IDataLoader
{
public:
    XmlReader();
    QList<QWidget*> load(QString pathToFile) override;

private:
    void readXml(QFile* file);
    void processXml();
    void processChild();
    std::pair<QString, QString> extractParameters();

    QVector<QString> mPossibleWidgets;
    QList<QWidget*> mWidgestList;
    QXmlStreamReader mXml;
};
}
#endif // XMLREADER_H
