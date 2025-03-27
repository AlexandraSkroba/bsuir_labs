#include "pch.h"
#include"../static_libs/ststic_libs.h"

TEST(TestCase5, Test1) {
  EXPECT_EQ(findWordAmount(14, 1000, "cup", "russia"), 752);
  EXPECT_TRUE(true);
}
TEST(TestCase5, Test2) {
	EXPECT_EQ(findWordAmount(7, 123, "russian", "codecup"), -80);
	EXPECT_TRUE(true);
}
TEST(TestCase5, Test3) {
	EXPECT_EQ(findWordAmount(7, 15, "codec", "decup"), 1);
	EXPECT_TRUE(true);
}
TEST(TestCase5, Test4) {
	EXPECT_EQ(findWordAmount(132, 1000, "warm", "water"), -648);
	EXPECT_TRUE(true);
}
TEST(TestCase5, Test5) {
	EXPECT_EQ(findWordAmount(8, 1200, "apple", "cold"), -848);
	EXPECT_TRUE(true);
} 

TEST(TestCase6, Test1) {
	EXPECT_EQ(anagrams("solo"), 12);
	EXPECT_TRUE(true);
}
TEST(TestCase6, Test2) {
	EXPECT_EQ(anagrams("solo"), 12);
	EXPECT_TRUE(true);
}
TEST(TestCase6, Test3) {
	EXPECT_EQ(anagrams("apple"), 60);
	EXPECT_TRUE(true);
}
TEST(TestCase6, Test4) {
	EXPECT_EQ(anagrams("dad"), 3);
	EXPECT_TRUE(true);
}
TEST(TestCase6, Test5) {
	EXPECT_EQ(anagrams("fail"), 24);
	EXPECT_TRUE(true);
}

TEST(TestCase7, Test1) {
	EXPECT_EQ(anagrams("aba"), 3);
	EXPECT_TRUE(true);
}
TEST(TestCase7, Test2) {
	EXPECT_EQ(anagrams("aaaaaaaaa"), 1);
	EXPECT_TRUE(true);
}
TEST(TestCase7, Test3) {
	EXPECT_EQ(anagrams("asd"), 6);
	EXPECT_TRUE(true);
}
TEST(TestCase7, Test4) {
	EXPECT_EQ(anagrams("mam"), 3);
	EXPECT_TRUE(true);
}
TEST(TestCase7, Test5) {
	EXPECT_EQ(anagrams("ghghghgd"), 280);
	EXPECT_TRUE(true);
}

TEST(TestCase8, Test1) {
	EXPECT_EQ(result("abcdef", "cdedcb"), 89);
	EXPECT_TRUE(true);
}
TEST(TestCase8, Test2) {
	EXPECT_EQ(result("aaa", "aaaaa"), 89);
	EXPECT_TRUE(true);
}
TEST(TestCase8, Test3) {
	EXPECT_EQ(result("aab", "baaa"), 78);
	EXPECT_TRUE(true);
}
TEST(TestCase8, Test4) {
	EXPECT_EQ(result("ab", "b"), 89);
	EXPECT_TRUE(true);
}
TEST(TestCase8, Test5) {
	EXPECT_EQ(result("abcdef", "abcdef"), 89);
	EXPECT_TRUE(true);
}
TEST(TestCase8, Test6) {
	EXPECT_EQ(result("ba", "baa"), 78);
	EXPECT_TRUE(true);
}

TEST(TestCase9, Test1) {
	EXPECT_EQ(Sum("fghj2jhsdn2"), 4);
	EXPECT_TRUE(true);
}
TEST(TestCase9, Test2) {
	EXPECT_EQ(Sum("jgh23jh1"), 24);
	EXPECT_TRUE(true);
}
TEST(TestCase9, Test3) {
	EXPECT_EQ(Sum("vhs87sgj"), 87);
	EXPECT_TRUE(true);
}
TEST(TestCase9, Test4) {
	EXPECT_EQ(Sum("gghmda7v2vmbe3bmqv22"), 34);
	EXPECT_TRUE(true);
}
TEST(TestCase9, Test5) {
	EXPECT_EQ(Sum("ashg67as76"), 143);
	EXPECT_TRUE(true);
}
/*TEST(TestCase9, Test6) {
	EXPECT_EQ(Sum("1234.e-2.0"), 1234);
	EXPECT_TRUE(true);
}
TEST(TestCase9, Test7) {
	EXPECT_EQ(Sum("1234.e-2."), 1234);
	EXPECT_TRUE(true);
}
TEST(TestCase9, Test8) {
	EXPECT_EQ(Sum("1234.e-2.0e-2.1"), 0);
	EXPECT_TRUE(true);
}*/