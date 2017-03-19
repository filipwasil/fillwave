#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

FLOGINIT_DEFAULT()

using namespace testing;

TEST(TGetterTests, security_tests
)
{
std::string s = "test";
auto fun = [&]() -> TGetter<std::string> && {
  return TGetter<std::string> (&s);
};
//ASSERT_THAT(fun()->substr(1), Eq("est")); // it is working - good!

// error: ‘TGetter<TWrapped>::TGetter(TGetter<TWrapped>&&) [with TWrapped = std::__cxx11::basic_string<char>]’ is private
// auto good1 = fun();

// error: ‘TGetter<TWrapped>::TGetter(TGetter<TWrapped>&&) [with TWrapped = std::__cxx11::basic_string<char>]’ is private
// const auto good2 = fun();

// error: ‘std::__cxx11::basic_string<char>* TGetter<std::__cxx11::basic_string<char> >::mWrapped’ is private
// auto* wrong = fun().mWrapped;

// error: invalid initialization of non-const reference
// auto& wrong3 = fun();

const auto &wrong2 = fun ();
// error: passing ‘const TGetter<std::__cxx11::basic_string<char> >’ as ‘this’ argument discards qualifiers [-fpermissive]
// ASSERT_THAT(wrong2->substr(1), Eq("est"));

// only one at the time from below will work - if two are running SEH exception is thrown

// error: passing ‘TGetter<std::__cxx11::basic_string<char> >’ as ‘this’ argument discards qualifiers [-fpermissive]
// ASSERT_THAT(const_cast<TGetter<std::string>&>(wrong2)->substr(1), Eq("est"));

// Non valid case
// ASSERT_THAT(const_cast<TGetter<std::string>&&>(wrong2)->substr(1), Eq("est"));

}