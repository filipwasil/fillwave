#pragma once

#include <QTreeView>
#include <QStandardItemModel>
#include <QTableView>
#include <QScrollArea>
#include "common/MainWidget.h"
#include "scene/callbacks/StandardMouseEventHandler.h"

namespace common {

class MainWindowNodeOperations : public QObject {
 Q_OBJECT
 public:
  explicit MainWindowNodeOperations(QWidget* parent = nullptr);

 ~MainWindowNodeOperations();

  QVBoxLayout* createNodeLayout(QWidget* parent);

  QVBoxLayout* createInspectorViewLayout(QWidget* parent);

  QVBoxLayout* createObjectPropertiesLayout(QWidget* parent);

 private:
  scene::callbacks::StandardMouseEventHandler* eventFilterMouse;
};

}

