#include "pch.h"
#include "CppUnitTest.h"
#include "../DotTreeChecker/graph_utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace findBestSkeletonTests
{
	TEST_CLASS(findBestSkeletonTests)
	{
	public:

		TEST_METHOD(findBestSkeleton_singleVertex)
		{
			vector<vector<int>> adjMatrix = { {0} };
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(1), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 0));
		}

		TEST_METHOD(findBestSkeleton_twoDisconnectedVertices)
		{
			vector<vector<int>> adjMatrix = {{0,0},{0,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(1), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 0));
		}

		TEST_METHOD(findBestSkeleton_twoConnectedVertices)
		{
			vector<vector<int>> adjMatrix = {{0,1},{0,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(1), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
		}

		TEST_METHOD(findBestSkeleton_twoConnectedVertices_oneIsolated)
		{
			vector<vector<int>> adjMatrix = {{0,1,0,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(2), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
			Assert::IsTrue(skeleton[1] == make_pair(1, 2));
		}

		TEST_METHOD(findBestSkeleton_twoVerticesWithoutIncoming)
		{
			vector<vector<int>> adjMatrix = {{0,1,0},{0,0,0},{0,1,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(1), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
		}

		TEST_METHOD(findBestSkeleton_unequalSizeTwoVerticesWithoutIncoming)
		{
			vector<vector<int>> adjMatrix = { {0,1,0,0},{0,0,0,0},{0,1,0,1},{0,0,0,0} };
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(2), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(2, 1));
			Assert::IsTrue(skeleton[1] == make_pair(2, 3));
		}

		TEST_METHOD(findBestSkeleton_linearGraphFourVertices)
		{
			vector<vector<int>> adjMatrix = {{0,1,0,0},{0,0,1,0},{0,0,0,1},{0,0,0,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(3), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
			Assert::IsTrue(skeleton[1] == make_pair(1, 2));
			Assert::IsTrue(skeleton[2] == make_pair(2, 3));
		}

		TEST_METHOD(findBestSkeleton_cycleGraph)
		{
			vector<vector<int>> adjMatrix = {{0,1,0},{0,0,1},{1,0,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(2), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
			Assert::IsTrue(skeleton[1] == make_pair(1, 2));
		}

		TEST_METHOD(findBestSkeleton_equalSizeComponents)
		{
			vector<vector<int>> adjMatrix = {
				{0,1,0,0,0,0},
				{0,0,0,0,0,0},
				{0,0,0,0,0,0},
				{0,0,0,0,1,0},
				{0,0,0,0,0,0},
				{0,0,0,0,0,0}
			};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(1), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
		}

		TEST_METHOD(findBestSkeleton_disconnectedComponents)
		{
			vector<vector<int>> adjMatrix = {
				{0,1,0,0,1},
				{0,0,0,0,0},
				{0,0,0,1,0},
				{0,0,0,0,0},
				{0,0,0,0,0}
			};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(1), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
		}

		TEST_METHOD(findBestSkeleton_completeGraphThreeVertices)
		{
			vector<vector<int>> adjMatrix = {{0,1,1},{1,0,1},{1,1,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(2), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
			Assert::IsTrue(skeleton[1] == make_pair(1, 2));
		}

		TEST_METHOD(findBestSkeleton_treeElevenVertices)
		{
			vector<vector<int>> adjMatrix = { {0,0,0,0,0,0,1,1,0,0,0},
				{0,0,1,0,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,0,1,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,1,0,0},
				{0,0,0,0,0,0,0,0,0,1,0},{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0} 
			};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(10), skeleton.size());
			Assert::IsTrue((skeleton[0] == make_pair(4, 1)) && (skeleton[1] == make_pair(1, 2)) && (skeleton[2] == make_pair(2, 3))
				&& (skeleton[3] == make_pair(4, 0)) && (skeleton[4] == make_pair(0, 6)) && (skeleton[5] == make_pair(6, 8))
				&& (skeleton[6] == make_pair(0, 7)) && (skeleton[7] == make_pair(7, 9)) && (skeleton[8] == make_pair(4, 5))
				&& (skeleton[9] == make_pair(5, 10)));
		}

	};
}