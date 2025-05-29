#include "pch.h"
#include "CppUnitTest.h"
#include "../DotTreeChecker/graph_utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace DFSTests
{
	TEST_CLASS(DFSTests)
	{
	public:

		TEST_METHOD(DFS_singleVertex)
		{
			vector<vector<int>> adjMatrix = { {0} };
			vector<bool> visited(1, false);
			vector<pair<int, int>> way;

			DFS(0, visited, adjMatrix, way);

			Assert::IsTrue(visited[0]);
			Assert::IsTrue(way.empty());
		}

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

	};
}
