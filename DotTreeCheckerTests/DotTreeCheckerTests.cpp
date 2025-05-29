#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace DotTreeCheckerTests
{
	TEST_CLASS(SanityCheck)
	{
	public:
		TEST_METHOD(TestAlwaysPasses)
		{
			Assert::IsTrue(true);
		}
	};
}

