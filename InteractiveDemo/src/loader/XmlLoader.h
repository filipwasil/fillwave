#pragma once

#include <QXmlStreamReader>
#include <QXmlStreamAttributes>
#include <QFile>
#include <QList>
#include <QWidget>
#include "IDataLoader.h"
#include "loader/IWidgetFabric.h"

namespace loader {
class XmlLoader : public IDataLoader {
public:
  XmlLoader(IWidgetFabric *WidgetFabric);

  virtual ~XmlLoader();

  QList<QWidget *> load(QString pathToFile) override;

  const QVector<std::pair<QString, QString>> getParameters();

private:
  bool init();

  void readXml(QFile *file);

  void processXml();

  void processChild();

  std::pair<QString, QString> extractParameter();

  QVector<std::pair<QString, QString>> parametersVector;
  QVector<QString> mPossibleWidgets;
  QList<QWidget *> mWidgetsList;
  QXmlStreamReader mXml;
  IWidgetFabric *mWidgetFabric;
};
}
