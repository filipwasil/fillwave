#include "xmlreader.h"
#include "menuwidgetfabric.h"
#include <QMessageBox>

namespace loader
{

XmlReader::XmlReader()
{
    //Should be loading from some asset file
    mPossibleWidgets.push_back("QLineEdit");
    mPossibleWidgets.push_back("QSlider");
}

QList<QWidget*> XmlReader::load(QString pathToFile)
{
    QFile file(pathToFile);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
       QMessageBox msgBox;
       msgBox.setText("Can't load file");
       msgBox.exec();
       QList<QWidget*> empty;
       return empty;
    }
    readXml(&file);
    return mWidgestList;
}

void XmlReader::readXml(QFile *file)
{
    mXml.setDevice(file);

    while(!mXml.atEnd() && !mXml.hasError())
    {
        QXmlStreamReader::TokenType token = mXml.readNext();
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        if(token == QXmlStreamReader::StartElement)
        {
            processXml();
        }
    }
}

void XmlReader::processXml()
{
    if(mXml.name() == "menu")
    {
        return;
    }
    if(mPossibleWidgets.contains(mXml.name().toString()))
        processChild();
}

void XmlReader::processChild()
{
    QString widgetType = mXml.name().toString();
    mXml.readNext();
    QVector<std::pair<QString, QString>> parametersVector;
    MenuWidgetFabric widgetsFabric;

    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == keyName))
    {
        if(mXml.tokenType() == QXmlStreamReader::StartElement)
        {
            parametersVector.push_back(extractParameters());
        }
        mXml.readNext();
    }
    auto widget = widgetsFabric.createWidget(widgetType, parametersVector);
    mWidgestList.append(widget);
}

std::pair<QString, QString> XmlReader::extractParameters()
{
    auto name = mXml.name().toString();
    auto text = mXml.text().toString();
    return std::make_pair (name, text);
}

}
