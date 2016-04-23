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

void foo1(fillwave::framework::PtrShared<fillwave::framework::Finishable>& a) {
	auto b = a;
	(void)b;
	EXPECT_EQ (b.m->mRefs, 2);
}

TEST (PtrShared, ref1) {
	auto a = fillwave::framework::make_shared<fillwave::framework::Finishable> (0.1f);
	EXPECT_EQ (a.m->mRefs, 1);
}

TEST (PtrShared, ref2) {
	auto a = fillwave::framework::make_shared<fillwave::framework::Finishable> (0.1f);
	auto b = a;
	EXPECT_EQ (a.m->mRefs, 2);
}

TEST (PtrShared, ref3) {
	auto a = fillwave::framework::make_shared<fillwave::framework::Finishable> (0.1f);
	foo1(a);
	EXPECT_EQ (a.m->mRefs, 1);
}
