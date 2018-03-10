#include "../common.h"

#include <fillwave/Fillwave.h>
#include <fillwave/allocators/AllocatorStack.h>

using namespace flw;
using namespace flw::flf;

struct DualIntStruct {
  int a;
  int b;
};

bool operator == (DualIntStruct const& lhs, DualIntStruct const& rhs) {
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

bool operator != (DualIntStruct const& lhs, DualIntStruct const& rhs) {
  return lhs.a != rhs.a || lhs.b != rhs.b;
}

TEST (StackAllocator, definingIntVector) {
  std::vector<int, AllocatorStack<int>> sut;
  EXPECT_EQ (1, 1);
}

TEST (StackAllocator, SizeEqualZeroWhenDefiningAContainer) {
  std::vector<DualIntStruct, AllocatorStack<DualIntStruct>> sut;
  EXPECT_EQ (sut.size(), 0);
}

TEST (StackAllocator, SizeEqualOneWhenPushingOneValueToContainer) {
  DualIntStruct value {
    111111,
    999990
  };
  std::vector<DualIntStruct, AllocatorStack<DualIntStruct>> sut;
  sut.push_back(value);
  EXPECT_EQ (sut.size(), 1);
}

TEST (StackAllocator, ValueSizeWhenPushingOneElementToDualIntStructVector) {
  DualIntStruct value {
    111111,
    999990
  };
  std::vector<DualIntStruct, AllocatorStack<DualIntStruct>> sut;
  sut.push_back(value);
  EXPECT_EQ (sizeof(sut[0]), sizeof(value));
}

TEST (StackAllocator, ValueEqualsWhenPushingOneElementToContainer) {
  DualIntStruct value {
    111111,
    999990
  };
  std::vector<DualIntStruct, AllocatorStack<DualIntStruct>> sut;
  sut.push_back(value);
  EXPECT_EQ (sut[0], value);
}

TEST (StackAllocator, ValueNotEqualsWhenPushingOneElementToContainerAndChangingItOutside) {
  DualIntStruct value {
    111111,
    999990
  };
  std::vector<DualIntStruct, AllocatorStack<DualIntStruct>> sut;
  sut.push_back(value);
  value.a = 5;
  EXPECT_NE (sut[0], value);
}

// todo potential optimization. Use paramtric tests
TEST (StackAllocator, ElementsOrderWhenWhenPushingManyElementsToContainer) {
  DualIntStruct v1 {
    1,
    2
  };
  DualIntStruct v2 {
    3,
    4
  };
  DualIntStruct v3 {
    5,
    6
  };
  DualIntStruct v4 {
    7,
    8
  };
  DualIntStruct v5 {
    9,
    0
  };
  std::vector<DualIntStruct, AllocatorStack<DualIntStruct>> sut;
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

TEST (StackAllocator, SizeEqualOneAfterAddingClearingAndAddingElementToContainer) {
  DualIntStruct v {
    1,
    2
  };
  std::vector<DualIntStruct, AllocatorStack<DualIntStruct>> sut;
  sut.push_back(v);
  sut.clear();
  sut.push_back(v);
  EXPECT_EQ (sut.size(), 1);
}

TEST (StackAllocator, ValueDifferentOneAfterAddingClearingAndAddingDifferentElementsToContainer) {
  DualIntStruct v1 {
    1,
    2
  };
  DualIntStruct v2 {
    3,
    4
  };
  std::vector<DualIntStruct, AllocatorStack<DualIntStruct>> sut;
  sut.push_back(v1);
  sut.clear();
  sut.push_back(v2);
  EXPECT_EQ (sut[0], v2);
  EXPECT_NE (sut[0], v1);
}

TEST (StackAllocator, AllocateFullMemory) {
  auto maxElements = AllocatorStack<DualIntStruct>().max_size();
  std::vector<DualIntStruct, AllocatorStack<DualIntStruct>> sut;

  for (size_t i = 0; i < maxElements; ++i) {
    DualIntStruct v = {
      static_cast<int>(2*i),
      static_cast<int>(2*i+1)
    };
    sut.push_back( v );
  }

  const int lastIdx = static_cast<int>(maxElements-1);
  DualIntStruct lastValue {
    2*lastIdx,
    2*lastIdx+1
  };
  EXPECT_EQ (sut[lastIdx], lastValue);
}

TEST (StackAllocator, AllocateFullMemoryNextClearingAndAllocateFullMemoryAgain) {
  auto maxElements = AllocatorStack<DualIntStruct>().max_size();
  std::vector<DualIntStruct, AllocatorStack<DualIntStruct>> sut;

  for (size_t i = 0; i < maxElements; ++i) {
    DualIntStruct v = {
      static_cast<int>(2*i),
      static_cast<int>(2*i+1)
    };
    sut.push_back( v );
  }

  sut.clear();

  for (size_t i = 0; i < maxElements; ++i) {
    DualIntStruct v = {
      static_cast<int>(2*i),
      static_cast<int>(2*i+1)
    };
    sut.push_back( v );
  }

  const int lastIdx = static_cast<int>(maxElements-1);
  DualIntStruct lastValue {
    2*lastIdx,
    2*lastIdx+1
  };

  EXPECT_EQ (sut[lastIdx], lastValue);
}