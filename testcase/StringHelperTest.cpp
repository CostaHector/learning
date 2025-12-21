#include <gtest/gtest.h>
#include "StringHelper.h"

class StringHelperTest: public ::testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    
protected:
    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST_F(StringHelperTest, basic_strip_function_ok) {
    using namespace StringHelper;
    str test1 = "   Hello, World!  \n";
    str test2 = "\t\tTest String\t";
    str test3 = "NoWhitespace";
    str test4 = "     \n\t   ";

    EXPECT_EQ(strip(test1), "Hello, World!");
    EXPECT_EQ(strip(test2), "Test String");
    EXPECT_EQ(strip(test3), "NoWhitespace");
    EXPECT_EQ(strip(test4), "");
}