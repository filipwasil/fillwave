#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

struct Fool {
  Fool () : a (0) {

  }

  void fooConst() const {
    std::cout << "\nValue: " << a <<  std::endl;
  }

  void foo() {
    std::cout << "\nValue: " << a <<  std::endl;
  }

private:
  int a;
};

template <class Used>
class User {
  Used used;
public:
  flw::TGetter<Used> get() {
    auto fun = [&]() -> flw::TGetter<Used> {
      return &used;
    };
    return fun();
  }
};

TEST(TGetterTests, security_tests_when_copy_enabled
)
{
  // Error field private
//  User<Fool> sut;
//  sut.get()->foo();

  // Error use of deleted function
//  auto u = sut.get();
//  u->foo();
//  u->fooConst();

  // Error use of deleted function
//  auto&& u = sut.get();
//  u->foo();
//  u->fooConst();

  // Error field private
//  auto* wrong = sut.get().mWrapped;

  // Error argument discards qualifiers, and deleted function
// const auto u = sut.get();
//  const auto&& u = sut.get();
//  u->foo();
//  u->fooConst();

  // Error invalid initialization of non-const reference
  // auto& wrong = sut.get();

//  auto&& u = sut.get();
//  std::move(u)->foo();
//  std::move(u)->fooConst();
}