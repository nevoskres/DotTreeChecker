#include "pch.h"
#include "CppUnitTest.h"
#include "../DotTreeChecker/graph_utils.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


/**
 * @file test_DFS.cpp
 * @brief Набор модульных тестов для функции DFS из graph_utils.h
 */


namespace DFSTests
{
	TEST_CLASS(DFSTests)
	{
	public:

		/// @brief Тест DFS: граф из одной вершины без дуг
		TEST_METHOD(DFS_singleVertex)
		{
			vector<vector<int>> adjMatrix = { {0} };
			vector<bool> visited(1, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			Assert::IsTrue(visited[0]);
			Assert::IsTrue(way.empty());
		}

		/// @brief Тест DFS: две изолированные вершины
		TEST_METHOD(DFS_twoNotConnectedVertex)
		{
			vector<vector<int>> adjMatrix = { {0,0}, {0,0} };
			vector<bool> visited(2, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			Assert::IsTrue(visited[0]);
			Assert::IsFalse(visited[1]);

			Assert::IsTrue(way.empty());

		}

		/// @brief Тест DFS: две вершины, соединенные дугой
		TEST_METHOD(DFS_twoConnectedVertex)
		{
			vector<vector<int>> adjMatrix = { {0,1}, {0,0} };
			vector<bool> visited(2, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			Assert::IsTrue(visited[0]);
			Assert::IsTrue(visited[1]);

			Assert::AreEqual(size_t(1), way.size());
			Assert::IsTrue(way[0] == make_pair(0, 1));

			Assert::AreEqual(2, adjMatrix[0][1]);
		}

		/// @brief Тест DFS: две связанные и одна изолированная вершина
		TEST_METHOD(DFS_twoConnectedVertex_oneIsolated) 
		{
			vector<vector<int>> adjMatrix = { {0,1,0},{0,0,0},{0,0,0} };
			vector<bool> visited(3, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			Assert::IsTrue(visited[0]);
			Assert::IsTrue(visited[1]);
			Assert::IsFalse(visited[2]);

			Assert::AreEqual(size_t(1), way.size());
			Assert::IsTrue(way[0] == make_pair(0, 1));

			Assert::AreEqual(2, adjMatrix[0][1]);
		}

		/// @brief Тест DFS: цикл из трех вершин
		TEST_METHOD(DFS_threeVerticesCycle)
		{
			vector<vector<int>> adjMatrix = { {0,1,0},{0,0,1},{1,0,0} };
			vector<bool> visited(3, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			Assert::IsTrue(visited[0]&&visited[1]&&visited[2]);

			Assert::AreEqual(size_t(2), way.size());
			Assert::IsTrue((way[0] == make_pair(0, 1))&&(way[1] == make_pair(1, 2)));

			Assert::AreEqual(2, adjMatrix[0][1]);
			Assert::AreEqual(2, adjMatrix[1][2]);
			Assert::AreEqual(1, adjMatrix[2][0]);

		}

		/// @brief Тест DFS: две слабо связанные компоненты
		TEST_METHOD(DFS_twoWeaklyConnectedComponents)
		{
			vector<vector<int>> adjMatrix = { {0,1,1,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,1},{0,0,0,0,0} };
			vector<bool> visited(5, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			Assert::IsTrue(visited[0]&&visited[1]&&visited[2]&&!visited[3]&&!visited[4]);

			Assert::AreEqual(size_t(2), way.size());
			Assert::IsTrue((way[0] == make_pair(0, 1)) && (way[1] == make_pair(0, 2)));

			Assert::AreEqual(2, adjMatrix[0][1]);
			Assert::AreEqual(2, adjMatrix[0][2]);
			Assert::AreEqual(1, adjMatrix[3][4]);
		}

		/// @brief Тест DFS: полный граф из трех вершин
		TEST_METHOD(DFS_completeGraphThreeVertices)
		{
			vector<vector<int>> adjMatrix = { {0,1,1},{1,0,1},{1,1,0} };
			vector<bool> visited(3, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			Assert::IsTrue(visited[0] && visited[1] && visited[2]);

			Assert::AreEqual(size_t(2), way.size());
			Assert::IsTrue((way[0] == make_pair(0, 1)) && (way[1] == make_pair(1, 2)));

			vector<vector<int>> correctAdjMatrix = {{0,2,1},{1,0,2},{1,1,0} };
			Assert::IsTrue(adjMatrix == correctAdjMatrix);
		}

		/// @brief Тест DFS: вершина без входящих дуг (не корень)
		TEST_METHOD(DFS_vertexWithoutIncoming_notRoot)
		{
			vector<vector<int>> adjMatrix = { {0,1,1,0},{0,0,0,0},{0,0,0,0},{0,0,1,0} };
			vector<bool> visited(4, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			Assert::IsTrue(visited[0] && visited[1] && visited[2]);
			Assert::IsFalse(visited[3]);

			Assert::AreEqual(size_t(2), way.size());
			Assert::IsTrue((way[0] == make_pair(0, 1)) && (way[1] == make_pair(0, 2)));

			vector<vector<int>> correctAdjMatrix = {{0,2,2,0},{0,0,0,0},{0,0,0,0},{0,0,1,0}};
			Assert::IsTrue(adjMatrix == correctAdjMatrix);
		}

		/// @brief Тест DFS: линейный граф из четырех вершин
		TEST_METHOD(DFS_linearGraphFourVertices)
		{
			vector<vector<int>> adjMatrix = { {0,1,0,0},{0,0,1,0},{0,0,0,1},{0,0,0,0} };
			vector<bool> visited(4, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			Assert::IsTrue(visited[0] && visited[1] && visited[2]&& visited[3]);

			Assert::AreEqual(size_t(3), way.size());
			Assert::IsTrue((way[0] == make_pair(0, 1)) && (way[1] == make_pair(1, 2))&&(way[2] == make_pair(2, 3)));

			vector<vector<int>> correctAdjMatrix = { {0,2,0,0},{0,0,2,0},{0,0,0,2},{0,0,0,0} };
			Assert::IsTrue(adjMatrix == correctAdjMatrix);
		}

		/// @brief Тест DFS: дерево из 11 вершин
		TEST_METHOD(DFS_treeElevenVertices)
		{
			vector<vector<int>> adjMatrix = { {0,1,0,0,1,1,0,0,0,0,0},
				{0,0,1,0,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,1,1,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,1,0,0},
				{0,0,0,0,0,0,0,0,0,1,0},{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0} };
			vector<bool> visited(11, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			for (bool v : visited) Assert::IsTrue(v);

			Assert::AreEqual(size_t(10), way.size());
			Assert::IsTrue((way[0] == make_pair(0, 1)) && (way[1] == make_pair(1, 2)) && (way[2] == make_pair(2, 3))
				&&(way[3] == make_pair(0, 4))&&(way[4] == make_pair(4, 6))&&(way[5] == make_pair(6, 8))
				&&(way[6] == make_pair(4, 7))&&(way[7] == make_pair(7, 9))&&(way[8] == make_pair(0, 5))
				&&(way[9] == make_pair(5, 10)));

			vector<vector<int>> correctAdjMatrix = { {0,2,0,0,2,2,0,0,0,0,0},
				{0,0,2,0,0,0,0,0,0,0,0},{0,0,0,2,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,2,2,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,2},{0,0,0,0,0,0,0,0,2,0,0},
				{0,0,0,0,0,0,0,0,0,2,0},{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0} };
			Assert::IsTrue(adjMatrix == correctAdjMatrix);
		}

	};
}
