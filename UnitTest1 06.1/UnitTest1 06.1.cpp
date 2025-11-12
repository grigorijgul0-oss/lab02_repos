#include "pch.h"
#include "CppUnitTest.h"
#include "../pr-06.1/pr-06.1.cpp"  // шлях до твоєї програми

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestIterative
{
	TEST_CLASS(UnitTestIterative)
	{
	public:

		TEST_METHOD(TestCountPositiveEven)
		{
			int arr[] = { -3, 2, 4, 5, 6, 0, -8 };
			int result = CountPositiveEven(arr, 7);
			Assert::AreEqual(3, result); // 2,4,6
		}

		TEST_METHOD(TestSumPositiveEven)
		{
			int arr[] = { -3, 2, 4, 5, 6, 0, -8 };
			int result = SumPositiveEven(arr, 7);
			Assert::AreEqual(12, result); // 2+4+6
		}

		TEST_METHOD(TestReplacePositiveEvenWithZero)
		{
			int arr[] = { -3, 2, 4, 5, 6, 0, -8 };
			ReplacePositiveEvenWithZero(arr, 7);
			int expected[] = { -3, 0, 0, 5, 0, 0, -8 };
			for (int i = 0; i < 7; i++)
				Assert::AreEqual(expected[i], arr[i]);
		}
	};
}
