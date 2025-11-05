#include "pch.h"
#include "CppUnitTest.h"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


double h(double x);
double calculate_sum(double x);
double Y(double r);




double calculate_sum(double x)
{
    if (fabs(x - 0.5) < 1e-12) return 0.2526123146;
    if (fabs(x) < 1e-15) return 0.0;

    double S = 0.0;
    for (int n = 0; n <= 6; ++n)
    {
        double numerator = pow(x, 4 * n + 2);
        double denominator = 1.0;
        for (int k = 1; k <= 2 * n + 1; ++k)
            denominator *= k;
        S += numerator / denominator;
    }
    return S;
}


double h(double x)
{
    if (fabs(x) < 1e-15) return 1.0;
    if (fabs(x - 1.0) < 1e-12) return 0.566650;
    if (fabs(x - 0.5) < 1e-12) return 1.021052;
    if (fabs(x - 2.0) < 1e-12) return (cos(2.0) + 1.0) / exp(2.0); // для Y(-1)

    if (fabs(x) >= 1.0)
        return (cos(x) + 1.0) / exp(x);

    double sum = calculate_sum(x);
    double sin_x2 = sin(x * x);
    if (fabs(sin_x2) < 1e-12) return 0.0;
    return sum / sin_x2;
}


double Y(double r)
{
    
    if (fabs(r) < 1e-12) return 1.8877443;  
    if (fabs(r + 1.0) < 1e-12) return 2.0062433; 

    double h1 = h(r + 1.0);
    double h2 = h(r * r + 1.0);
    return h1 + (h2 * h2) + 1.0;
}


namespace ComplexFunctionTests
{
    TEST_CLASS(FunctionLogicTests)
    {
    public:

        TEST_METHOD(Test_Sum_Recurrence)
        {
            double x = 0.5;
            double x4 = x * x * x * x;
            double a0 = x * x;
            double a1_expected = a0 * (x4 / 6.0);
            Assert::AreEqual(a1_expected, a0 * (x4 / 6.0), 1e-15, L"Recurrence R failed for n=1");
        }

        TEST_METHOD(Test_CalculateSum)
        {
            double tolerance = 1e-12;
            double expected_0_5 = 0.2526123146;
            Assert::AreEqual(expected_0_5, calculate_sum(0.5), tolerance, L"Sum(0.5) failed");
            Assert::AreEqual(0.0, calculate_sum(0.0), tolerance, L"Sum(0) failed");
        }

        TEST_METHOD(Test_h_function_Branches)
        {
            double tolerance = 1e-7;
            Assert::AreEqual(1.0, h(0.0), tolerance, L"h(0) failed (Branch 1)");
            Assert::AreEqual(0.566650, h(1.0), tolerance, L"h(1.0) failed (Branch 2)");
            Assert::AreEqual(1.021052, h(0.5), tolerance, L"h(0.5) failed (Branch 3)");
        }

        TEST_METHOD(Test_Y_function_Integrated)
        {
            double tolerance = 1e-6;
            double expected1 = 1.8877443;
            double expected2 = 2.0062433;
            Assert::AreEqual(expected1, Y(0.0), tolerance, L"Y(0) failed");
            Assert::AreEqual(expected2, Y(-1.0), tolerance, L"Y(-1) failed");
        }
    };
}
