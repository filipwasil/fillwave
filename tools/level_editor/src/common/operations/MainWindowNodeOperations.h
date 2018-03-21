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
  MainWindowNodeOperations(QWidget* parent = nullptr);

  virtual ~MainWindowNodeOperations();

  MainWindowNodeOperations(const MainWindowNodeOperations& mE) = default;

  MainWindowNodeOperations(MainWindowNodeOperations&& mE) = default;

  MainWindowNodeOperations& operator=(const MainWindowNodeOperations& mE) = default;

  MainWindowNodeOperations& operator=(MainWindowNodeOperations&& mE) = default;

  QVBoxLayout* createNodeLayout(QWidget* parent);

  QVBoxLayout* createInspectorViewLayout(QWidget* parent);

  QVBoxLayout* createObjectPropertiesLayout(QWidget* parent);

 private:
  scene::callbacks::StandardMouseEventHandler* eventFilterMouse;
};

}

