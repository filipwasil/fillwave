#include "xmlreader.h"
#include <QMessageBox>

namespace databaseperation
{

XmlReader::XmlReader()
{
    //Should be loading from some asset file
    mWidgetList.push_back("QLineEdit");
    mWidgetList.push_back("QSlider");
}

elementsData XmlReader::load(QString pathToFile)
{
    QFile file(pathToFile);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
       QMessageBox msgBox;
       msgBox.setText("Can't load file");
       msgBox.exec();
       elementsData empty;
       return empty;
    }
    readXml(&file);
    return mRetrivedData;
}

void XmlReader::readXml(QFile *file)
{
    xml.setDevice(file);

    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument)
            continue;
        if(token == QXmlStreamReader::StartElement)
            processXml();
    }
}

void XmlReader::processXml()
{
    if(xml.name() == "menu")
    {
        return;
    }
    if(mWidgetList.contains(xml.name().toString()))
        procesChild();
}

void XmlReader::procesChild()
{
    QString keyName = xml.name().toString();
    xml.readNext();
    QVector<std::pair<QString, QString>> vector;

    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == keyName))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            vector.push_back(extractChilds());
        }
        xml.readNext();
    }
    mRetrivedData.push_back(std::make_pair(keyName, vector));
}

std::pair<QString, QString> XmlReader::extractChilds()
{
    auto name = xml.name().toString();
    auto text = xml.text().toString();
    return std::make_pair (name, text);
}

}
