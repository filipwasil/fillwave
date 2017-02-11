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
    class XmlLoader : public IDataLoader
    {
    public:
        QList<QWidget *> load(QString pathToFile) override;

    private:
        bool init();

        void readXml(QFile *file);

        void processXml();

        void processChild();

        std::pair<QString, QString> extractParameter();

        QVector<QString> mPossibleWidgets;
        QList<QWidget *> mWidgetsList;
        QXmlStreamReader mXml;
    };
}
#endif // XMLREADER_H
