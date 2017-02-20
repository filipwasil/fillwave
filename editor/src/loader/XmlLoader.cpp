#include "XmlLoader.h"
#include "MenuWidgetFabric.h"
#include "common/Tools.h"

#include <QMessageBox>

namespace loader
{
    bool XmlLoader::init()
    {
        bool initStatus;
        initStatus = false;
        mPossibleWidgets = tools::readFileToStrings("assets/menutypeassets.txt");
        if (!mPossibleWidgets.isEmpty()) {
            initStatus = true;
        }
        return initStatus;
    }

    QList<QWidget *> XmlLoader::load(QString pathToFile)
    {
        QList<QWidget *> emptyList;
        if (!init()) {
            return emptyList;
        }
        QFile file(pathToFile);
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox msgBox;
            msgBox.setText("Can't load file");
            msgBox.exec();
            return emptyList;
        }
        readXml(&file);
        return mWidgetsList;
    }

    void XmlLoader::readXml(QFile *file) {
        mXml.setDevice(file);

        while (!mXml.atEnd() && !mXml.hasError())
        {
            QXmlStreamReader::TokenType token = mXml.readNext();
            if (token == QXmlStreamReader::StartDocument) {
                continue;
            }
            if (token == QXmlStreamReader::StartElement) {
                processXml();
            }
        }
    }

    void XmlLoader::processXml()
    {
        if (mXml.name() == "menu") {
            return;
        }
        if (mPossibleWidgets.contains(mXml.name().toString()))
            processChild();
    }

    void XmlLoader::processChild()
    {
        QString widgetType = mXml.name().toString();
        mXml.readNext();
        QVector<std::pair<QString, QString>> parametersVector;
        MenuWidgetFabric widgetsFabric;

        while (!(mXml.tokenType() == QXmlStreamReader::EndElement &&
                 mXml.name() == widgetType)) {
            if (mXml.tokenType() == QXmlStreamReader::StartElement) {
                parametersVector.push_back(extractParameter());
            }
            mXml.readNext();
        }
        auto widget = widgetsFabric.createWidget(widgetType, parametersVector);
        mWidgetsList.append(widget);
    }

    std::pair<QString, QString> XmlLoader::extractParameter()
    {
        auto name = mXml.name().toString();
        auto text = mXml.text().toString();
        return std::make_pair(name, text);
    }

}
