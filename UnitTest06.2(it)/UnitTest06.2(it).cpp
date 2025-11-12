#include "pch.h"
#include "CppUnitTest.h"
#include "../pr-06.2(it)/pr-06.2(it).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestIterative
{
	TEST_CLASS(UnitTestIterative)
	{
	public:

		TEST_METHOD(TestAverageOdd_Positive)
		{
			int a[] = { 1, 2, 3, 4, 5 };
			Assert::AreEqual(3.0, averageOdd(a, 5), 0.001);
		}

		TEST_METHOD(TestAverageOdd_AllEven)
		{
			int a[] = { 2, 4, 6, 8 };
			Assert::AreEqual(0.0, averageOdd(a, 4), 0.001);
		}

		TEST_METHOD(TestAverageOdd_NegativeValues)
		{
			int a[] = { -5, -4, -3, -2, -1 };
			Assert::AreEqual(-3.0, averageOdd(a, 5), 0.001);
		}
	};
}
