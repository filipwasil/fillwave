#pragma once

#include <QUuid>

namespace common {
class UUID {
 public:
  QByteArray getId();
  bool comapreQByteArrays(const QByteArray* array1, const QByteArray* array2);
};

}

