#pragma once

#include <QMap>
#include <QString>
namespace common {
enum class EItemType {
  none,
  threeDObject,
  object
};

extern QMap<EItemType, QString> ItemTypeString;

}