#include "pch.h"
#include "../../../Libs for add/StaticLib_add1/StaticLib_add1/StaticLib_1.h"
#include "../../../Libs for add/StaticLib_add1/StaticLib_add2/StaticLib_add2.h"
#include "../../../Libs for add/StaticLib_add1/StaticLib_add3/StaticLib_add3.h"

TEST(TestCase1, Test1) {
  EXPECT_EQ(sum(1, 10), 46);
  EXPECT_TRUE(true);
}
TEST(TestCase1, Test2) {
	EXPECT_EQ(sum(10, 20), 48);
	EXPECT_TRUE(true);
}
TEST(TestCase1, Test3) {
	EXPECT_EQ(sum(30, 40), 52);
	EXPECT_TRUE(true);
}
TEST(TestCase1, Test4) {
	EXPECT_EQ(sum(INT16_MAX, INT16_MAX), 7);
	EXPECT_TRUE(true);
}

TEST(TestCase2, Test1) {
	EXPECT_EQ(calculations(1234, 1234, power(4)), 736);
	EXPECT_TRUE(true);
}
TEST(TestCase2, Test2) {
	EXPECT_EQ(calculations(2323, 99999999999, power(8)), 39087387);
	EXPECT_TRUE(true);
}
TEST(TestCase2, Test3) {
	EXPECT_EQ(calculations(4, 99999, power(9)), 494777344);
	EXPECT_TRUE(true);
}
TEST(TestCase2, Test4) {
	EXPECT_EQ(calculations(888, 888, power(8)), 91255296);
	EXPECT_TRUE(true);
}

TEST(TestCase3, Test1) {
	EXPECT_EQ(function(7), 21);
	EXPECT_TRUE(true);
}
TEST(TestCase3, Test2) {
	EXPECT_EQ(function(1), 1);
	EXPECT_TRUE(true);
}
TEST(TestCase3, Test3) {
	EXPECT_EQ(function(777), 201537);
	EXPECT_TRUE(true);
}
TEST(TestCase3, Test4) {
	EXPECT_EQ(function(INT16_MAX), 357913941);
	EXPECT_TRUE(true);
}