#include "pch.h"
#include "CppUnitTest.h"
#include <cmath>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


double P0(const int K, const int N) {
    double p = 1;
    for (int i = K; i <= N; i++)
        p *= (pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / (i * i);
    return p;
}

double P1(const int K, const int N, const int i) {
    if (i > N)
        return 1;
    else
        return ((pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / (i * i)) * P1(K, N, i + 1);
}

double P2(const int K, const int N, const int i) {
    if (i < K)
        return 1;
    else
        return ((pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / (i * i)) * P2(K, N, i - 1);
}

double P3(const int K, const int N, const int i, double t) {
    t *= (pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / (i * i);
    if (i >= N)
        return t;
    else
        return P3(K, N, i + 1, t);
}

double P4(const int K, const int N, const int i, double t) {
    t *= (pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / (i * i);
    if (i <= K)
        return t;
    else
        return P4(K, N, i - 1, t);
}


namespace RecursionProductTests
{
    TEST_CLASS(ProductTests)
    {
    public:

        const int K = 1;
        const int N = 13;
        const double eps = 1e-10;

        
        TEST_METHOD(TestIterative)
        {
            double result = P0(K, N);
            Logger::WriteMessage("Ітераційне обчислення завершено.");
            Assert::IsTrue(result > 0);
        }

        
        TEST_METHOD(TestRecursiveDownIncrease)
        {
            double expected = P0(K, N);
            double actual = P1(K, N, K);
            Assert::IsTrue(fabs(expected - actual) < eps, L"P1 не збігається з P0");
        }

        
        TEST_METHOD(TestRecursiveDownDecrease)
        {
            double expected = P0(K, N);
            double actual = P2(K, N, N);
            Assert::IsTrue(fabs(expected - actual) < eps, L"P2 не збігається з P0");
        }

        
        TEST_METHOD(TestRecursiveUpIncrease)
        {
            double expected = P0(K, N);
            double actual = P3(K, N, K, 1);
            Assert::IsTrue(fabs(expected - actual) < eps, L"P3 не збігається з P0");
        }

        
        TEST_METHOD(TestRecursiveUpDecrease)
        {
            double expected = P0(K, N);
            double actual = P4(K, N, N, 1);
            Assert::IsTrue(fabs(expected - actual) < eps, L"P4 не збігається з P0");
        }
    };
}
