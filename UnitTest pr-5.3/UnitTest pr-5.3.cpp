#include "pch.h"
#include "CppUnitTest.h"
#include <cmath> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;





double A(const double x, const int n, double a)
{

    double R = (x * x) * (2.0 * n - 1.0) / (2.0 * n + 1.0);
    a *= R;
    return a;
}


double S(const double x, const double eps, int& n)
{
    
    if (abs(x) >= 1.0) return 0.0;

    n = 0;
    
    double a = 2 * x;
    double s = a;

    do {
        n++;
        a = A(x, n, a);
        s += a;
    } while (abs(a) >= eps);

    return s;
}


double Exact_ln(double x)
{
   
    return log((1.0 + x) / (1.0 - x));
}


namespace Task5Tests
{
    TEST_CLASS(LogSeriesTests)
    {
    public:

       
        TEST_METHOD(Test_S_vs_Exact)
        {
           
            double eps = 1e-5;
            int n_terms = 0;

            
            double tolerance = 5e-5;

            
            double x1 = 0.5;
            double expected1 = Exact_ln(x1); 
            double actual1 = S(x1, eps, n_terms);
            Assert::AreEqual(expected1, actual1, tolerance, L"Test failed for x=0.5");

            
            double x2 = 0.9;
            double expected2 = Exact_ln(x2);
            
            double actual2 = S(x2, eps, n_terms);
            Assert::AreEqual(expected2, actual2, tolerance, L"Test failed for x=0.9");

            
            double x3 = 0.0;
            double expected3 = Exact_ln(x3); 
            double actual3 = S(x3, eps, n_terms);
            Assert::AreEqual(expected3, actual3, tolerance, L"Test failed for x=0.0");
        }

        
        TEST_METHOD(Test_Recurrence_A)
        {
            double x = 0.5;
            
            double a0 = 2 * x;
            double a1_expected = 1.0 / 12.0;
            double a1_actual = A(x, 1, a0);

            
            Assert::AreEqual(a1_expected, a1_actual, 1e-10, L"Test failed for A(x, n=1)");
        }
    };
}
