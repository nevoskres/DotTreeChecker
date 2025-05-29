#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//#include "../DotTreeChecker/GraphChecker.h" // Проверь и поправь путь, если надо

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

