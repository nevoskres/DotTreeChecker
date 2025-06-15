#include "pch.h"
#include "CppUnitTest.h"
#include "../DotTreeCheckerlib/DotTreeCheckerlib.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


/**
 * @file test_parseDotFile.cpp
 * @brief Набор модульных тестов для функции parseDotFile из graph_utils.h
 */

namespace parseDotFileTests
{
	TEST_CLASS(parseDotFileTests)
	{
	public:

		/// @brief Тест parseDotFile: граф с одной изолированной вершиной
		TEST_METHOD(parseDotFile_singleVertex)
		{
			vector<string> input = {
				"digraph G",
				"{",
				"5",
				"}"
			};

			Graph g = parseDotFile(input);

			Assert::AreEqual(input.size(), g.getDotStringGraph().size());
			for (size_t i = 0; i < input.size(); i++) 
			{
				Assert::AreEqual(input[i], g.getDotStringGraph()[i]);
			}

			Assert::AreEqual(size_t(1), g.getVertexToIndex().size());
			Assert::AreEqual(size_t(1), g.getIndexToVertex().size());

			int idx5 = g.getVertexToIndex().at(5); 
			Assert::AreEqual(0, idx5);

			Assert::AreEqual(size_t(1), g.getAdjacencyMatrix().size());
			Assert::AreEqual(size_t(1), g.getAdjacencyMatrix()[0].size());

			vector<vector<int>> expectedMatrix = { {0} };

			for (size_t i = 0; i < expectedMatrix.size(); i++) 
			{
				for (size_t j = 0; j < expectedMatrix[i].size(); j++) 
				{
					Assert::AreEqual(expectedMatrix[i][j], g.getAdjacencyMatrix()[i][j]);
				}
			}
		}


		/// @brief Тест parseDotFile: линейный граф из четырёх вершин
		TEST_METHOD(parseDotFile_linearGraphFourVertices)
		{
			vector<string> input = {
				"digraph G",
				"{",
				"0->1",
				"1->2",
				"2->3",
				"}"
			};

			Graph g = parseDotFile(input);

			Assert::AreEqual(input.size(), g.getDotStringGraph().size());
			for (size_t i = 0; i < input.size(); i++)
			{
				Assert::AreEqual(input[i], g.getDotStringGraph()[i]);
			}

			Assert::AreEqual(size_t(4), g.getVertexToIndex().size());
			Assert::AreEqual(size_t(4), g.getIndexToVertex().size());

			int idx0 = g.getVertexToIndex().at(0);
			Assert::AreEqual(0, idx0);
			int idx1 = g.getVertexToIndex().at(1);
			Assert::AreEqual(1, idx1);
			int idx2 = g.getVertexToIndex().at(2);
			Assert::AreEqual(2, idx2);
			int idx3 = g.getVertexToIndex().at(3);
			Assert::AreEqual(3, idx3);

			Assert::AreEqual(size_t(4), g.getAdjacencyMatrix().size());
			Assert::AreEqual(size_t(4), g.getAdjacencyMatrix()[0].size());

			vector<vector<int>> expectedMatrix = { {0,1,0,0},{0,0,1,0},{0,0,0,1},{0,0,0,0} };

			for (size_t i = 0; i < expectedMatrix.size(); i++)
			{
				for (size_t j = 0; j < expectedMatrix[i].size(); j++)
				{
					Assert::AreEqual(expectedMatrix[i][j], g.getAdjacencyMatrix()[i][j]);
				}
			}
		}

		/// @brief Тест parseDotFile: цикл из трёх вершин
		TEST_METHOD(parseDotFile_cycleGraph)
		{
			vector<string> input = {
				"digraph G",
				"{",
				"0->1",
				"1->2",
				"2->0",
				"}"
			};

			Graph g = parseDotFile(input);

			Assert::AreEqual(input.size(), g.getDotStringGraph().size());
			for (size_t i = 0; i < input.size(); i++)
			{
				Assert::AreEqual(input[i], g.getDotStringGraph()[i]);
			}

			Assert::AreEqual(size_t(3), g.getVertexToIndex().size());
			Assert::AreEqual(size_t(3), g.getIndexToVertex().size());

			int idx0 = g.getVertexToIndex().at(0);
			Assert::AreEqual(0, idx0);
			int idx1 = g.getVertexToIndex().at(1);
			Assert::AreEqual(1, idx1);
			int idx2 = g.getVertexToIndex().at(2);
			Assert::AreEqual(2, idx2);

			Assert::AreEqual(size_t(3), g.getAdjacencyMatrix().size());
			Assert::AreEqual(size_t(3), g.getAdjacencyMatrix()[0].size());

			vector<vector<int>> expectedMatrix = { {0,1,0},{0,0,1},{1,0,0} };

			for (size_t i = 0; i < expectedMatrix.size(); i++)
			{
				for (size_t j = 0; j < expectedMatrix[i].size(); j++)
				{
					Assert::AreEqual(expectedMatrix[i][j], g.getAdjacencyMatrix()[i][j]);
				}
			}
		}

		/// @brief Тест parseDotFile: полный граф из трёх вершин
		TEST_METHOD(parseDotFile_completeGraphThreeVertices)
		{
			vector<string> input = {
				"digraph G",
				"{",
				"0->1",
				"0->2",
				"1->0",
				"1->2",
				"2->0",
				"2->1",
				"}"
			};

			Graph g = parseDotFile(input);

			Assert::AreEqual(input.size(), g.getDotStringGraph().size());
			for (size_t i = 0; i < input.size(); i++)
			{
				Assert::AreEqual(input[i], g.getDotStringGraph()[i]);
			}

			Assert::AreEqual(size_t(3), g.getVertexToIndex().size());
			Assert::AreEqual(size_t(3), g.getIndexToVertex().size());

			int idx0 = g.getVertexToIndex().at(0);
			Assert::AreEqual(0, idx0);
			int idx1 = g.getVertexToIndex().at(1);
			Assert::AreEqual(1, idx1);
			int idx2 = g.getVertexToIndex().at(2);
			Assert::AreEqual(2, idx2);

			Assert::AreEqual(size_t(3), g.getAdjacencyMatrix().size());
			Assert::AreEqual(size_t(3), g.getAdjacencyMatrix()[0].size());

			vector<vector<int>> expectedMatrix = { {0,1,1},{1,0,1},{1,1,0} };

			for (size_t i = 0; i < expectedMatrix.size(); i++)
			{
				for (size_t j = 0; j < expectedMatrix[i].size(); j++)
				{
					Assert::AreEqual(expectedMatrix[i][j], g.getAdjacencyMatrix()[i][j]);
				}
			}
		}

		/// @brief Тест parseDotFile: дерево из 11 вершин
		TEST_METHOD(parseDotFile_treeElevenVertices)
		{
			vector<string> input = {
			"digraph G",
			"{",
			"0->1",
			"1->2",
			"2->3",
			"0->4",
			"0->5",
			"4->6",
			"4->7",
			"6->8",
			"7->9",
			"5->10",
			"}"
			};

			Graph g = parseDotFile(input);

			Assert::AreEqual(input.size(), g.getDotStringGraph().size());
			for (size_t i = 0; i < input.size(); i++)
			{
				Assert::AreEqual(input[i], g.getDotStringGraph()[i]);
			}

			Assert::AreEqual(size_t(11), g.getVertexToIndex().size());
			Assert::AreEqual(size_t(11), g.getIndexToVertex().size());

			int idx0 = g.getVertexToIndex().at(0);
			Assert::AreEqual(0, idx0);
			int idx1 = g.getVertexToIndex().at(1);
			Assert::AreEqual(1, idx1);
			int idx2 = g.getVertexToIndex().at(2);
			Assert::AreEqual(2, idx2);
			int idx3 = g.getVertexToIndex().at(3);
			Assert::AreEqual(3, idx3);
			int idx4 = g.getVertexToIndex().at(4);
			Assert::AreEqual(4, idx4);
			int idx5 = g.getVertexToIndex().at(5);
			Assert::AreEqual(5, idx5);
			int idx6 = g.getVertexToIndex().at(6);
			Assert::AreEqual(6, idx6);
			int idx7 = g.getVertexToIndex().at(7);
			Assert::AreEqual(7, idx7);
			int idx8 = g.getVertexToIndex().at(8);
			Assert::AreEqual(8, idx8);
			int idx9 = g.getVertexToIndex().at(9);
			Assert::AreEqual(9, idx9);
			int idx10 = g.getVertexToIndex().at(10);
			Assert::AreEqual(10, idx10);

			Assert::AreEqual(size_t(11), g.getAdjacencyMatrix().size());
			Assert::AreEqual(size_t(11), g.getAdjacencyMatrix()[0].size());

			vector<vector<int>> expectedMatrix = {{0,1,0,0,1,1,0,0,0,0,0},
													{0,0,1,0,0,0,0,0,0,0,0},
													{0,0,0,1,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,1,1,0,0,0},
													{0,0,0,0,0,0,0,0,0,0,1},
													{0,0,0,0,0,0,0,0,1,0,0},
													{0,0,0,0,0,0,0,0,0,1,0},
													{0,0,0,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0,0,0,0}};

			for (size_t i = 0; i < expectedMatrix.size(); i++)
			{
				for (size_t j = 0; j < expectedMatrix[i].size(); j++)
				{
					Assert::AreEqual(expectedMatrix[i][j], g.getAdjacencyMatrix()[i][j]);
				}
			}

		}

		/// @brief Тест parseDotFile: три соединённые вершины и одна изолированная
		TEST_METHOD(parseDotFile_threeConnectedVerticesOneIsolated)
		{
			vector<string> input = {
			"digraph G",
			"{",
			"0->1",
			"1->2",
			"3",
			"}"
			};

			Graph g = parseDotFile(input);

			Assert::AreEqual(input.size(), g.getDotStringGraph().size());
			for (size_t i = 0; i < input.size(); i++)
			{
				Assert::AreEqual(input[i], g.getDotStringGraph()[i]);
			}

			Assert::AreEqual(size_t(4), g.getVertexToIndex().size());
			Assert::AreEqual(size_t(4), g.getIndexToVertex().size());

			int idx0 = g.getVertexToIndex().at(0);
			Assert::AreEqual(0, idx0);
			int idx1 = g.getVertexToIndex().at(1);
			Assert::AreEqual(1, idx1);
			int idx2 = g.getVertexToIndex().at(2);
			Assert::AreEqual(2, idx2);
			int idx3 = g.getVertexToIndex().at(3);
			Assert::AreEqual(3, idx3);

			Assert::AreEqual(size_t(4), g.getAdjacencyMatrix().size());
			Assert::AreEqual(size_t(4), g.getAdjacencyMatrix()[0].size());

			vector<vector<int>> expectedMatrix = { {0,1,0,0},{0,0,1,0},{0,0,0,0},{0,0,0,0} };

			for (size_t i = 0; i < expectedMatrix.size(); i++)
			{
				for (size_t j = 0; j < expectedMatrix[i].size(); j++)
				{
					Assert::AreEqual(expectedMatrix[i][j], g.getAdjacencyMatrix()[i][j]);
				}
			}
		}

		/// @brief Тест parseDotFile: две компоненты разного размера
		TEST_METHOD(parseDotFile_disconnectedComponents)
		{
			vector<string> input = {
			"digraph G",
			"{",
			"0->1",
			"2->3",
			"0->4",
			"}"
			};

			Graph g = parseDotFile(input);

			Assert::AreEqual(input.size(), g.getDotStringGraph().size());
			for (size_t i = 0; i < input.size(); i++)
			{
				Assert::AreEqual(input[i], g.getDotStringGraph()[i]);
			}

			Assert::AreEqual(size_t(5), g.getVertexToIndex().size());
			Assert::AreEqual(size_t(5), g.getIndexToVertex().size());

			int idx0 = g.getVertexToIndex().at(0);
			Assert::AreEqual(0, idx0);
			int idx1 = g.getVertexToIndex().at(1);
			Assert::AreEqual(1, idx1);
			int idx2 = g.getVertexToIndex().at(2);
			Assert::AreEqual(2, idx2);
			int idx3 = g.getVertexToIndex().at(3);
			Assert::AreEqual(3, idx3);
			int idx4 = g.getVertexToIndex().at(4);
			Assert::AreEqual(4, idx4);

			Assert::AreEqual(size_t(5), g.getAdjacencyMatrix().size());
			Assert::AreEqual(size_t(5), g.getAdjacencyMatrix()[0].size());

			vector<vector<int>> expectedMatrix = { {0,1,0,0,1},{0,0,0,0,0},{0,0,0,1,0},{0,0,0,0,0},{0,0,0,0,0} };

			for (size_t i = 0; i < expectedMatrix.size(); i++)
			{
				for (size_t j = 0; j < expectedMatrix[i].size(); j++)
				{
					Assert::AreEqual(expectedMatrix[i][j], g.getAdjacencyMatrix()[i][j]);
				}
			}
		}

		/// @brief Тест parseDotFile: проверка отсутствия обратных рёбер
		TEST_METHOD(parseDotFile_directionality)
		{
			vector<string> input = {
				"digraph G",
				"{",
				"1->2",
				"}"
			};

			Graph g = parseDotFile(input);

			Assert::AreEqual(1, g.getAdjacencyMatrix()[0][1]);
			Assert::AreEqual(0, g.getAdjacencyMatrix()[1][0]);
		}



	};
}