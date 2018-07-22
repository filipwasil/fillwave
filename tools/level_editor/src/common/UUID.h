#pragma once

#include <QUuid>

namespace common {
class UUID {
 public:
  QByteArray getId();
  bool compareQByteArrays(const QByteArray* array1, const QByteArray* array2);
};

}