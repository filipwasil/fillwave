/*
 * PtrShared.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: filip
 */

#include <fillwave/Log.h>
#include <fillwave/common/PtrShared.h>
#include <fillwave/common/Finishable.h>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

FLOGINIT_DEFAULT()

//void foo1(fillwave::framework::PtrShared<fillwave::framework::Finishable>& a) {
//	auto b = a;
//	(void)b;
//	EXPECT_EQ (*b.mRefs, 2);
//}
//
//void foo2(fillwave::framework::PtrShared<fillwave::framework::Finishable> a) {
//	EXPECT_EQ (*a.mRefs, 2);
//}
//
//void foo3(fillwave::framework::PtrShared<fillwave::framework::Finishable>& a) {
//	EXPECT_EQ (*a.mRefs, 1);
//}
//
//TEST (PtrShared, simple) {
//	auto a = fillwave::framework::make_shared<fillwave::framework::Finishable> (0.1f);
//	EXPECT_EQ (*a.mRefs, 1);
//}
//
//TEST (PtrShared, copy) { //crashing
//	auto a = fillwave::framework::make_shared<fillwave::framework::Finishable> (0.1f);
//	fillwave::framework::PtrShared<fillwave::framework::Finishable> b = a;
//	EXPECT_EQ (*a.mRefs, 2);
//}
//
//TEST (PtrShared, foo_ref) {
//	auto a = fillwave::framework::make_shared<fillwave::framework::Finishable> (0.1f);
//	foo1(a);
//	EXPECT_EQ (*a.mRefs, 1);
//}
//
//TEST (PtrShared, foo_copy) {
//	auto a = fillwave::framework::make_shared<fillwave::framework::Finishable> (0.1f);
//	foo2(a);
//	EXPECT_EQ (*a.mRefs, 1);
//}
//
//TEST (PtrShared, foo_ref_check) {
//	auto a = fillwave::framework::make_shared<fillwave::framework::Finishable> (0.1f);
//	foo3(a);
//	EXPECT_EQ (*a.mRefs, 1);
//}

