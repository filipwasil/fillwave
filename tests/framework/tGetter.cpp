#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

TEST(TGetterTests, security_tests
)
{
//  std::string s = "test";
//  auto fun = [&]() -> TGetter<std::string> {
//    return &s;
//  };

//ASSERT_THAT(fun()->substr(1), Eq("est")); // it is working - good!

// error: ‘TGetter<TWrapped>::TGetter(TGetter<TWrapped>&&) [with TWrapped = std::__cxx11::basic_string<char>]’ is private
   //auto good1 = fun()->c_str();

// error: ‘TGetter<TWrapped>::TGetter(TGetter<TWrapped>&&) [with TWrapped = std::__cxx11::basic_string<char>]’ is private
   //const auto good2 = fun();

// error: ‘std::__cxx11::basic_string<char>* TGetter<std::__cxx11::basic_string<char> >::mWrapped’ is private
// auto* wrong = fun().mWrapped;

// error: invalid initialization of non-const reference
// auto& wrong3 = fun();

//const auto &wrong2 = fun();
// error: passing ‘const TGetter<std::__cxx11::basic_string<char> >’ as ‘this’ argument discards qualifiers [-fpermissive]
// ASSERT_THAT(wrong2->substr(1), Eq("est"));

// only one at the time from below will work - if two are running SEH exception is thrown

// error: passing ‘TGetter<std::__cxx11::basic_string<char> >’ as ‘this’ argument discards qualifiers [-fpermissive]
// ASSERT_THAT(const_cast<TGetter<std::string>&>(wrong2)->substr(1), Eq("est"));

// Non valid case
// ASSERT_THAT(const_cast<TGetter<std::string>&&>(wrong2)->substr(1), Eq("est"));

}

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
  User<std::string> sut;
  sut.get()->c_str();

  // Error function private
  //auto u = ss.use();

  auto&& u = sut.get();
  // Error use of deleted function
  // u->c_str();

  // Error field private
  // auto* wrong = ss.use().mWrapped;

  // Error function private
  // const auto good2 = ss.use();
}