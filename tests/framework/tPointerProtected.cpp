#include "../common.h"

#include <flw/Fillwave.h>

using namespace testing;

struct Fool {
  Fool () : a (0) {
    //nothing
  }

  void fooConst() const {
    std::cout << "\nValueC: " << a <<  std::endl;
  }

  void foo() {
    std::cout << "\nValue: " << a <<  std::endl;
  }

private:
  int a;
};


TEST(ppTests, security_tests_when_copy_enabled) {
 //User<Fool> sut;

  // Error field private
//  sut.used->foo();

  // Error use of deleted function
  //auto u = sut.get();
  //u->foo();
  //u->fooConst();

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