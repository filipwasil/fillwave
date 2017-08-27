#pragma once

#include <QDialog>
#include <QTreeView>
#include <QPushButton>
#include <QMap>
#include <QStandardItemModel>
#include "common/ENodeType.hpp"

namespace common {
namespace windows {
namespace basic {

class NewNode : public QDialog {
 public:
  NewNode(QWidget* parent = Q_NULLPTR);

  ENodeType getSelectedNode() const;

 public slots:

  void setNodeData();

  const QString& getName() const;

 private:
  void init();

  QTreeView* mNodeList;
  QStandardItemModel* mNodeModel;
  QPushButton* mOk;
  QPushButton* mCancel;
  QMap<QString, ENodeType> mTypeMap;
  ENodeType mSelectedNode;
  QString mName;
};

}
}
}


