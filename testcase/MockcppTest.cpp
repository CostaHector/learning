#include "TestHelper.h"

USING_MOCKCPP_NS;
class MockcppTest: public TestHelper {
public:
    static void SetUpTestSuite() {
        printf("set up MockcppTest\n");
    };
    static void TearDownTestSuite() {
        printf("tear down MockcppTest\n");
    };
};

#include <random>
#include <vector>
#include <numeric>
namespace PlainFunction {
bool isServiceReady() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(generator) == 1;
}

static int g_callCount = 0;
bool invokeIsServiceReady() {
    ++g_callCount;
    return true;
}

int DoCalculate(const std::vector<int>& data) {
    if (!isServiceReady()) {
        return -1;
    }
    return std::accumulate(data.cbegin(), data.cend(), 0);
}
}

// 自由函数 & 静态函数
TEST_F(MockcppTest, willReturn_ok) {
    using PlainFunction::isServiceReady;
    using PlainFunction::DoCalculate;
    MOCKER(isServiceReady).stubs().will(returnValue(true)).then(returnValue(false));
    EXPECT_EQ(DoCalculate({1,2,3,4}), 10);
    EXPECT_EQ(DoCalculate({1,2,3,4}), -1);
    EXPECT_EQ(DoCalculate({1,2,3,4}), -1);
    EXPECT_FALSE(isServiceReady());
}

// Stubs, invoke其他
TEST_F(MockcppTest, invoke_ok) {
    using PlainFunction::isServiceReady;
    using PlainFunction::invokeIsServiceReady;
    MOCKER(isServiceReady).stubs().will(invoke(invokeIsServiceReady));
    const int beforeCnt = PlainFunction::g_callCount;
    isServiceReady();
    isServiceReady();
    const int afterCnt = PlainFunction::g_callCount;
    EXPECT_EQ(afterCnt, beforeCnt + 2);
}

// 约束(入参, 出参)
bool CreateArray(int** pOutArr, int size) {
    if (size < 0) {
        return false;
    }
    if (pOutArr == nullptr) {
        return false;
    }
    *pOutArr = new (std::nothrow) int[size]{0};
    return *pOutArr != nullptr;
}

TEST_F(MockcppTest, constraint_input_output_ok) {
    int* p = nullptr;
    EXPECT_TRUE(CreateArray(&p, 2));
    EXPECT_EQ(p[0], 0);
    EXPECT_EQ(p[1], 0);
    delete[] p;
    p = nullptr;


    int arr[10] = {10, 9, 8, 7};
    int* pArr0 = &arr[0];
    int* pArr1 = &arr[1];
    MOCKER(CreateArray).stubs().with(outBoundP(&pArr0, sizeof(pArr0)), eq(2)).will(returnValue(true));
    MOCKER(CreateArray).stubs().with(outBoundP(&pArr1, sizeof(pArr1)), eq(9)).will(ignoreReturnValue());

    int* p0 = nullptr;
    EXPECT_TRUE(CreateArray(&p0, 2));
    EXPECT_EQ(p0[0], 10);
    EXPECT_EQ(p0[1], 9);

    int* p1 = nullptr;
    CreateArray(&p1, 9);
    EXPECT_EQ(p1[0], 9);
    EXPECT_EQ(p1[1], 8);
}

void ProcessSomethingCore(int timeout)
{
}
void ProcessSomething()
{
    int timeout = 10;
    ProcessSomethingCore(timeout);
}

TEST_F(MockcppTest, constraint_spy) {
    int param = -1;
    MOCKER(ProcessSomethingCore).stubs().with(spy(param));
    ProcessSomething();
    EXPECT_EQ(param, 10);
}

struct Score {
    int chinese;
    int math;
    int english;
};

struct ScoreChecker {
    explicit ScoreChecker(int threshold) : mthreshold{threshold} {}
    bool operator()(const Score& sc) const {
        return sc.math >= 85;
    }
private:
    const int mthreshold;
};

#include <vector>
using std::vector;

void PrintScore(const Score& sc) {

}
void DoScoresFilter() {
    vector<Score> rawScores{{100,99,98}, {88,80,70}, {80, 80, 80}};
    // .... filter ...
    Score excellentAtMathScores = rawScores[0];
    PrintScore(excellentAtMathScores);
}

TEST_F(MockcppTest, constraint_checkwith) {
    MOCKER(PrintScore).stubs().with(checkWith(ScoreChecker(85))).will(ignoreReturnValue());
    DoScoresFilter();
}