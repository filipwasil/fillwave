#include "../common.h"

#include <flw/cmn/allocators/AllocatorHeap.h>

using namespace flw;

struct DualIntStructure {
  int a;
  int b;
};

bool operator == (DualIntStructure const& lhs, DualIntStructure const& rhs) {
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

bool operator != (DualIntStructure const& lhs, DualIntStructure const& rhs) {
  return lhs.a != rhs.a || lhs.b != rhs.b;
}

TEST (AllocatorHeap, definingIntVector) {
  std::vector<int, AllocatorHeap<int>> sut;
  EXPECT_EQ (1, 1);
}

TEST (AllocatorHeap, SizeEqualZeroWhenDefiningAContainer) {
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut;
  EXPECT_EQ (sut.size(), 0);
}

TEST (AllocatorHeap, SizeEqualOneWhenPushingOneValueToContainer) {
  DualIntStructure value {
    111111,
    999990
  };
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut;
  sut.push_back(value);
  EXPECT_EQ (sut.size(), 1);
}

TEST (AllocatorHeap, ValueSizeWhenPushingOneElementToDualIntStructureVector) {
  DualIntStructure value {
    111111,
    999990
  };
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut;
  sut.push_back(value);
  EXPECT_EQ (sizeof(sut[0]), sizeof(value));
}

TEST (AllocatorHeap, ValueEqualsWhenPushingOneElementToContainer) {
  DualIntStructure value {
    111111,
    999990
  };
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut;
  sut.push_back(value);
  EXPECT_EQ (sut[0], value);
}

TEST (AllocatorHeap, ValueNotEqualsWhenPushingOneElementToContainerAndChangingItOutside) {
  DualIntStructure value {
    111111,
    999990
  };
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut;
  sut.push_back(value);
  value.a = 5;
  EXPECT_NE (sut[0], value);
}

// todo potential optimization. Use paramtric tests
TEST (AllocatorHeap, ElementsOrderWhenWhenPushingManyElementsToContainer) {
  DualIntStructure v1 {
    1,
    2
  };
  DualIntStructure v2 {
    3,
    4
  };
  DualIntStructure v3 {
    5,
    6
  };
  DualIntStructure v4 {
    7,
    8
  };
  DualIntStructure v5 {
    9,
    0
  };
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut;
  sut.push_back(v1);
  sut.push_back(v2);
  sut.push_back(v3);
  sut.push_back(v4);
  sut.push_back(v5);
  EXPECT_EQ (sut[0], v1);
  EXPECT_EQ (sut[1], v2);
  EXPECT_EQ (sut[2], v3);
  EXPECT_EQ (sut[3], v4);
  EXPECT_EQ (sut[4], v5);
}

TEST (AllocatorHeap, SizeEqualOneAfterAddingClearingAndAddingElementToContainer) {
  DualIntStructure v {
    1,
    2
  };
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut;
  sut.push_back(v);
  sut.clear();
  sut.push_back(v);
  EXPECT_EQ (sut.size(), 1);
}

TEST (AllocatorHeap, ValueDifferentOneAfterAddingClearingAndAddingDifferentElementsToContainer) {
  DualIntStructure v1 {
    1,
    2
  };
  DualIntStructure v2 {
    3,
    4
  };
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut;
  sut.push_back(v1);
  sut.clear();
  sut.push_back(v2);
  EXPECT_EQ (sut[0], v2);
  EXPECT_NE (sut[0], v1);
}

TEST (AllocatorHeap, AllocateFullMemory) {
  auto maxElements = AllocatorHeap<DualIntStructure>().max_size();
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut;

  for (size_t i = 0; i < maxElements; ++i) {
    DualIntStructure v = {
      static_cast<int>(2*i),
      static_cast<int>(2*i+1)
    };
    sut.push_back( v );
  }

  const int lastIdx = static_cast<int>(maxElements-1);
  DualIntStructure lastValue {
    2*lastIdx,
    2*lastIdx+1
  };
  EXPECT_EQ (sut[lastIdx], lastValue);
}

TEST (AllocatorHeap, AllocateFullMemoryNextClearingAndAllocateFullMemoryAgain) {
  auto maxElements = AllocatorHeap<DualIntStructure>().max_size();
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut;

  for (size_t i = 0; i < maxElements; ++i) {
    DualIntStructure v = {
      static_cast<int>(2*i),
      static_cast<int>(2*i+1)
    };
    sut.push_back( v );
  }

  sut.clear();

  for (size_t i = 0; i < maxElements; ++i) {
    DualIntStructure v = {
      static_cast<int>(2*i),
      static_cast<int>(2*i+1)
    };
    sut.push_back( v );
  }

  const int lastIdx = static_cast<int>(maxElements-1);
  DualIntStructure lastValue {
    2*lastIdx,
    2*lastIdx+1
  };

  EXPECT_EQ (sut[lastIdx], lastValue);
}

TEST (AllocatorHeap, VectorEqualityCheck) {
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut1;
  std::vector<DualIntStructure, AllocatorHeap<DualIntStructure>> sut2;
  EXPECT_EQ (sut1, sut2);
}

TEST (AllocatorHeap, AllocatorEqualityCheck) {
  AllocatorHeap<DualIntStructure> sut;
}

TEST (AllocatorHeap, NestAllocator) {
  // nothing
}