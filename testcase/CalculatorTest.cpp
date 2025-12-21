#include <gtest/gtest.h>

class CalculatorTest: public ::testing::Test {
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

TEST_F(CalculatorTest, simple_add_function_ok) {
    EXPECT_EQ(2 + 2, 4);
    EXPECT_NE(1, 0);
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}

TEST_F(CalculatorTest, simple_sub_function_ok) {
    ASSERT_EQ(5 - 3, 2);
    ASSERT_NE(10, 5);
    ASSERT_TRUE(1);
    ASSERT_FALSE(0);
    ASSERT_FALSE(false);
}
