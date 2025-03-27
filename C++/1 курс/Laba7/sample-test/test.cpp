#include "pch.h"
#include"../static_libs/static_libs.h"

// task 1
TEST(TestCase1, Test1) {
	EXPECT_EQ(nine_to_sev(1234), -52);
	EXPECT_TRUE(true);
}
TEST(TestCase1, Test2) {
	EXPECT_EQ(nine_to_sev(12), -52);
	EXPECT_TRUE(true);
}
TEST(TestCase1, Test3) {
	EXPECT_EQ(nine_to_sev(45), -52);
	EXPECT_TRUE(true);
}
TEST(TestCase1, Test4) {
	EXPECT_EQ(nine_to_sev(765), -52);
	EXPECT_TRUE(true);
}
TEST(TestCase1, Test5) {
	EXPECT_EQ(nine_to_sev(394), -52);
	EXPECT_TRUE(true);
}

// task 2
TEST(TestCase2, Test1) {
	EXPECT_EQ(dop_code("00000000"), "00000001");
	EXPECT_TRUE(true);
}
TEST(TestCase2, Test2) {
	EXPECT_EQ(dop_code("01001101"), "01101100");
	EXPECT_TRUE(true);
}
TEST(TestCase2, Test3) {
	EXPECT_EQ(dop_code("11000110"), "11000111");
	EXPECT_TRUE(true);
}
TEST(TestCase2, Test4) {
	EXPECT_EQ(dop_code("10100011"), "10110000");
	EXPECT_TRUE(true);
}
TEST(TestCase2, Test5) {
	EXPECT_EQ(dop_code("00001111"), "00000100");
	EXPECT_TRUE(true);
}

// task 3
TEST(TestCase3, Test1) {
	EXPECT_EQ(sum("00000000", "000000101"), "00000010");
	EXPECT_TRUE(true);
}
TEST(TestCase3, Test2) {
	EXPECT_EQ(sum("00100100", "01001011"), "01101111");
	EXPECT_TRUE(true);
}
TEST(TestCase3, Test3) {
	EXPECT_EQ(sum("01101111", "011111000"), "10000011");
	EXPECT_TRUE(true);
}
TEST(TestCase3, Test4) {
	EXPECT_EQ(sum("10000011", "01101111"), "11110000");
	EXPECT_TRUE(true);
}
TEST(TestCase3, Test5) {
	EXPECT_EQ(sum("01001011", "000000101"), "01001101");
	EXPECT_TRUE(true);
}

// task 4
TEST(TestCase4, Test1) {
	EXPECT_EQ(sum("01001011", "000000101"), "01001101");
	EXPECT_TRUE(true);
}
TEST(TestCase4, Test2) {
	EXPECT_EQ(sum("01001101", "000000101"), "01001111");
	EXPECT_TRUE(true);
}
TEST(TestCase4, Test3) {
	EXPECT_EQ(sum("01001011", "01001101"), "10010110");
	EXPECT_TRUE(true);
}
TEST(TestCase4, Test4) {
	EXPECT_EQ(sum("10010110", "01001111"), "11010001");
	EXPECT_TRUE(true);
}
TEST(TestCase4, Test5) {
	EXPECT_EQ(sum("01001111", "01001101"), "10010010");
	EXPECT_TRUE(true);
}

// task 5
TEST(TestCase5, Test1) {
	EXPECT_EQ(convertToRomanian(5), "V");
	EXPECT_TRUE(true);
}
TEST(TestCase5, Test2) {
	EXPECT_EQ(convertToRomanian(32), "XXXII");
	EXPECT_TRUE(true);
}
TEST(TestCase5, Test3) {
	EXPECT_EQ(convertToRomanian(123), "CXXIII");
	EXPECT_TRUE(true);
}
TEST(TestCase5, Test4) {
	EXPECT_EQ(convertToRomanian(27), "XXVII");
	EXPECT_TRUE(true);
}
TEST(TestCase5, Test5) {
	EXPECT_EQ(convertToRomanian(50), "L");
	EXPECT_TRUE(true);
}

// task 6
TEST(TestCase6, Test1) {
	EXPECT_EQ(interesting_number(5), 0);
	EXPECT_TRUE(true);
}
TEST(TestCase6, Test2) {
	EXPECT_EQ(interesting_number(1), 0);
	EXPECT_TRUE(true);
}
TEST(TestCase6, Test3) {
	EXPECT_EQ(interesting_number(9), 1);
	EXPECT_TRUE(true);
}
TEST(TestCase6, Test4) {
	EXPECT_EQ(interesting_number(34), 3);
	EXPECT_TRUE(true);
}
TEST(TestCase6, Test5) {
	EXPECT_EQ(interesting_number(880055535), 88005553);
	EXPECT_TRUE(true);
}


// task 7
TEST(TestCase7, Test1) {
	EXPECT_EQ(multiplieByThree(10), 0);
	EXPECT_TRUE(true);
}
TEST(TestCase7, Test2) {
	EXPECT_EQ(multiplieByThree(33), 1);
	EXPECT_TRUE(true);
}
TEST(TestCase7, Test3) {
	EXPECT_EQ(multiplieByThree(1234), 0);
	EXPECT_TRUE(true);
}

TEST(TestCase7, Test4) {
	EXPECT_EQ(multiplieByFourtySeven(1735), 0);
	EXPECT_TRUE(true);
}
TEST(TestCase7, Test5) {
	EXPECT_EQ(multiplieByFourtySeven(47), 1);
	EXPECT_TRUE(true);
}
TEST(TestCase7, Test6) {
	EXPECT_EQ(multiplieByFourtySeven(1234), 0);
	EXPECT_TRUE(true);
}

TEST(TestCase7, Test7) {
	EXPECT_EQ(multiplieByBigValue(197), 1);
	EXPECT_TRUE(true);
}
TEST(TestCase7, Test8) {
	EXPECT_EQ(multiplieByBigValue(394), 1);
	EXPECT_TRUE(true);
}
TEST(TestCase7, Test9) {
	EXPECT_EQ(multiplieByBigValue(1970), 1);
	EXPECT_TRUE(true);
}

// task 8
TEST(TestCase8, Test1) {
	EXPECT_EQ(two_decimal(10), "1100");
	EXPECT_TRUE(true);
}
TEST(TestCase8, Test2) {
	EXPECT_EQ(two_decimal(10), "1100");
	EXPECT_TRUE(true);
}
TEST(TestCase8, Test3) {
	EXPECT_EQ(two_decimal(10), "1100");
	EXPECT_TRUE(true);
}
TEST(TestCase8, Test4) {
	EXPECT_EQ(two_decimal(10), "1100");
	EXPECT_TRUE(true);
}
TEST(TestCase8, Test5) {
	EXPECT_EQ(two_decimal(10), "1100");
	EXPECT_TRUE(true);
}

// task 9
TEST(TestCase9, Test1) {
  EXPECT_EQ(func(7), "21");
  EXPECT_TRUE(true);
}
TEST(TestCase9, Test2) {
	EXPECT_EQ(func(22), "211");
	EXPECT_TRUE(true);
}
TEST(TestCase9, Test3) {
	EXPECT_EQ(func(105), "10220");
	EXPECT_TRUE(true);
}
TEST(TestCase9, Test4) {
	EXPECT_EQ(func(341), "110122");
	EXPECT_TRUE(true);
}
TEST(TestCase9, Test5) {
	EXPECT_EQ(func(4), "11");
	EXPECT_TRUE(true);
}

// task 10
TEST(TestCase10, Test1) {
	EXPECT_EQ(bad_barrel(3, 56), 97);
	EXPECT_TRUE(true);
}
TEST(TestCase10, Test2) {
	EXPECT_EQ(bad_barrel(1, 1000), 33);
	EXPECT_TRUE(true);
}
TEST(TestCase10, Test3) {
	EXPECT_EQ(bad_barrel(4, 4), 144);
	EXPECT_TRUE(true);
}
TEST(TestCase10, Test4) {
	EXPECT_EQ(bad_barrel(3, 1440), 144);
	EXPECT_TRUE(true);
}
TEST(TestCase10, Test5) {
	EXPECT_EQ(bad_barrel(2, 138), 52);
	EXPECT_TRUE(true);
}