#pragma once

#include <QTreeView>
#include <QStandardItemModel>
#include <QTableView>
#include <QScrollArea>
#include "common/MainWidget.h"
#include "scene/callbacks/StandardMouseEventHandler.h"

namespace common {

class UiWindowsCreator : public QObject {
 Q_OBJECT
 public:
  explicit UiWindowsCreator(QWidget* parent = nullptr);

 ~UiWindowsCreator() = default;

  QVBoxLayout* createNodeLayout(QTreeView* treeView, QWidget* parent);

  scene::callbacks::StandardMouseEventHandler* installEventFilterOnTreeView(
      QTreeView* treeView,
      QWidget* parent);

  QVBoxLayout* createInspectorViewLayout(QScrollArea* inspectorArea, QWidget* parent);

  QVBoxLayout* createObjectPropertiesLayout(QTreeView* propertiesTree, QWidget* parent);

};

}

