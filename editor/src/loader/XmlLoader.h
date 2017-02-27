#ifndef XMLREADER_H
#define XMLREADER_H

#include "IDataLoader.h"
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>
#include <QFile>
#include <QList>
#include <QWidget>

namespace loader
{
    #define MENU_VALID_TYPES_FILE "assets/menutypeassets.txt"

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
