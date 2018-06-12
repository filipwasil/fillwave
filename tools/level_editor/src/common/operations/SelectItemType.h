#pragma once

#include <QStandardItemModel>
#include <QtWidgets/QTreeView>
#include "objects/items/BaseItem.h"
#include "common/InternalTypes.h"

namespace common {

class SelectItemType : public QObject {
 Q_OBJECT
 public:
  bool show();

  virtual ~SelectItemType();

  SelectItemType();

  EItemType getItemType() const;

  const QString& getItemName() const;

 public slots:

  void selectedType();

 private:
  QStandardItemModel* mItemListModel;
  EItemType mItemType{EItemType::none};
  QTreeView* mItemListTreeView;
  QDialog* mMainWidget;
  std::map<QString, EItemType> mItemTypes;
  QString mItemName;
  bool mOperationStatus;
};

}


