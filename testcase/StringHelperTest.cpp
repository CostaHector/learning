#include "TestHelper.h"
#include "StringHelper.h"
#include <string>
#include <cstring>
using std::string;

class StringHelperTest: public TestHelper {
public:
    static void SetUpTestSuite() {
        printf("set up StringHelperTest\n");
    };
    static void TearDownTestSuite() {
        printf("tear down StringHelperTest\n");
    };
};

TEST_F(StringHelperTest, basic_strip_function_ok) {
    using namespace StringHelper;
    string test1 = "   Hello, World!  \n";
    string test2 = "\t\tTest String\t";
    string test3 = "NoWhitespace";
    string test4 = "     \n\t   ";

    EXPECT_EQ(strip(test1), "Hello, World!");
    EXPECT_EQ(strip(test2), "Test String");
    EXPECT_EQ(strip(test3), "NoWhitespace");
    EXPECT_EQ(strip(test4), "");
}

TEST_F(StringHelperTest, string_basic) {
    string s = "Hello";
    EXPECT_EQ(s, "Hello");
    EXPECT_EQ(s.size(), 5);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.substr(1, 3), "ell");
    EXPECT_EQ(s.find_first_of('x'), string::npos);

    s.clear();
    EXPECT_TRUE(s.empty());

    const char arr[] = "world";
    EXPECT_EQ(strlen(arr), 5);
    s.assign(arr);
    EXPECT_EQ(s, "world");
    EXPECT_EQ(s.size(), 5);
}