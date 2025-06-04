#include "pch.h"
#include "CppUnitTest.h"
#include "../DotTreeCheckerLib/graph_utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

/**
 * @file test_findBestSkeleton.cpp
 * @brief Набор модульных тестов для функции findBestSkeleton из graph_utils.h
 */

namespace findBestSkeletonTests
{
	TEST_CLASS(findBestSkeletonTests)
	{
	public:

		/// @brief Тест findBestSkeleton: граф из одной вершины
		TEST_METHOD(findBestSkeleton_singleVertex)
		{
			vector<vector<int>> adjMatrix = { {0} };
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(1), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 0));
		}

		/// @brief Тест findBestSkeleton: две изолированные вершины
		TEST_METHOD(findBestSkeleton_twoDisconnectedVertices)
		{
			vector<vector<int>> adjMatrix = {{0,0},{0,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(1), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 0));
		}

		/// @brief Тест findBestSkeleton: две соединённые вершины
		TEST_METHOD(findBestSkeleton_twoConnectedVertices)
		{
			vector<vector<int>> adjMatrix = {{0,1},{0,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(1), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
		}

		/// @brief Тест findBestSkeleton: три соединённые вершины и одна изолированная
		TEST_METHOD(findBestSkeleton_twoConnectedVertices_oneIsolated)
		{
			vector<vector<int>> adjMatrix = {{0,1,0,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(2), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
			Assert::IsTrue(skeleton[1] == make_pair(1, 2));
		}

		/// @brief Тест findBestSkeleton: две вершины без входящих дуг
		TEST_METHOD(findBestSkeleton_twoVerticesWithoutIncoming)
		{
			vector<vector<int>> adjMatrix = {{0,1,0},{0,0,0},{0,1,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(1), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
		}

		/// @brief Тест findBestSkeleton: две вершины без входящих дуг (с разной достижимостью из них)
		TEST_METHOD(findBestSkeleton_unequalSizeTwoVerticesWithoutIncoming)
		{
			vector<vector<int>> adjMatrix = { {0,1,0,0},{0,0,0,0},{0,1,0,1},{0,0,0,0} };
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(2), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(2, 1));
			Assert::IsTrue(skeleton[1] == make_pair(2, 3));
		}

		/// @brief Тест findBestSkeleton: линейный граф из четырёх вершин
		TEST_METHOD(findBestSkeleton_linearGraphFourVertices)
		{
			vector<vector<int>> adjMatrix = {{0,1,0,0},{0,0,1,0},{0,0,0,1},{0,0,0,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(3), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
			Assert::IsTrue(skeleton[1] == make_pair(1, 2));
			Assert::IsTrue(skeleton[2] == make_pair(2, 3));
		}

		/// @brief Тест findBestSkeleton: цикл из трёх вершин
		TEST_METHOD(findBestSkeleton_cycleGraph)
		{
			vector<vector<int>> adjMatrix = {{0,1,0},{0,0,1},{1,0,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(2), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
			Assert::IsTrue(skeleton[1] == make_pair(1, 2));
		}

		/// @brief Тест findBestSkeleton: две компоненты одинакового размера и две изолированные вершины
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

		/// @brief Тест findBestSkeleton: две компоненты разного размера
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

		/// @brief Тест findBestSkeleton: полный граф из трёх вершин
		TEST_METHOD(findBestSkeleton_completeGraphThreeVertices)
		{
			vector<vector<int>> adjMatrix = {{0,1,1},{1,0,1},{1,1,0}};
			auto skeleton = findBestSkeleton(adjMatrix);
			Assert::AreEqual(size_t(2), skeleton.size());
			Assert::IsTrue(skeleton[0] == make_pair(0, 1));
			Assert::IsTrue(skeleton[1] == make_pair(1, 2));
		}

		/// @brief Тест findBestSkeleton: дерево из 11 вершин
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

