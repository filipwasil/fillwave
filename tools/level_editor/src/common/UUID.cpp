#include "UUID.h"

namespace common {
QByteArray UUID::getId() {
  return QUuid::createUuid().toByteArray();
}

bool UUID::compareQByteArrays(const QByteArray* array1, const QByteArray* array2) {
  if (array1->size() != array2->size()) {
    return false;
  }
  for (int i = 0; i < array1->size(); i++) {
    if (array1[i] != array2[i]) {
      return false;
    }
  }
  return true;
}
}