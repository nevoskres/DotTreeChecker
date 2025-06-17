#include "pch.h"
#include "CppUnitTest.h"
#include "../DotTreeCheckerlib/DotTreeCheckerlib.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


/**
 * @file test_writeDotFile.cpp
 * @brief Набор модульных тестов для функции writeDotFile из graph_utils.h
 */

namespace writeDotFileTests
{
	TEST_CLASS(writeDotFileTests)
	{
	public:

		/// @brief Тест writeDotFile: граф с двумя изолированными вершинами
		TEST_METHOD(writeDotFile_twoIsolatedVertex)
		{
			vector<vector<int>> matrix = {
				{0, 0},
				{0, 0}
			};
			vector<int> indexToVertex = { 1, 3 };
			vector<pair<int, int>> path = { {0,0} };
			vector<string> dotStringGraph = { "digraph G","{" ,"1;","3;","}"};
			outMessForGraph msg = { "c[green]", "[red]", "c[red]" };

			auto dot = writeDotFile(matrix, indexToVertex, path, dotStringGraph, msg);

			Assert::IsTrue(find(dot.begin(), dot.end(), "    1;") != dot.end());
			Assert::IsTrue(find(dot.begin(), dot.end(), "    3 [red];") != dot.end());
			Assert::IsTrue(find(dot.begin(), dot.end(), "    c[red];") != dot.end());
		}

		/// @brief Тест writeDotFile: граф с одной изолированной вершиной
		TEST_METHOD(writeDotFile_singleVertex)
		{
			vector<vector<int>> matrix = {
				{0}
			};
			vector<int> indexToVertex = { 7 };
			vector<pair<int, int>> path = { {0,0} };
			vector<string> dotStringGraph = { "digraph G","{" ,"7;","}" };
			outMessForGraph msg = { "c[green]", "[red]", "c[red]" };

			auto dot = writeDotFile(matrix, indexToVertex, path, dotStringGraph, msg);

			Assert::IsTrue(find(dot.begin(), dot.end(), "    7;") != dot.end());
			Assert::IsTrue(find(dot.begin(), dot.end(), "    c[green];") != dot.end());
		}

		/// @brief Тест writeDotFile: граф с дугами вне пути 
		TEST_METHOD(writeDotFile_notWay)
		{
			vector<vector<int>> matrix = {
				{0, 1, 1},
				{0, 0, 1},
				{0, 0, 0}
			};
			vector<int> indexToVertex = { 1, 2, 3 };
			vector<pair<int, int>> path = { {0,1},{1,2} };
			vector<string> dotStringGraph = { "digraph G","{" ,"}" };
			outMessForGraph msg = { "c[green]", "[red]", "c[red]" };

			auto dot = writeDotFile(matrix, indexToVertex, path, dotStringGraph, msg);

			Assert::IsTrue(find(dot.begin(), dot.end(), "    1 -> 2;") != dot.end());
			Assert::IsTrue(find(dot.begin(), dot.end(), "    1 -> 3 [red];") != dot.end());
			Assert::IsTrue(find(dot.begin(), dot.end(), "    2 -> 3;") != dot.end());
			Assert::IsTrue(find(dot.begin(), dot.end(), "    c[red];") != dot.end());
		}

		/// @brief Тест writeDotFile: граф, где все дуги входят в путь  
		TEST_METHOD(writeDotFile_onlyWay)
		{
			vector<vector<int>> matrix = {
				{0, 1, 0},
				{0, 0, 1},
				{0, 0, 0}
			};
			vector<int> indexToVertex = { 1, 2, 3 };
			vector<pair<int, int>> path = { {0, 1}, {1, 2} };
			vector<string> dotStringGraph = {};
			outMessForGraph msg = { "c[green]", "[red]", "c[red]" };

			auto dot = writeDotFile(matrix, indexToVertex, path, dotStringGraph, msg);

			Assert::IsTrue(find(dot.begin(), dot.end(), "    1 -> 2;") != dot.end());
			Assert::IsTrue(find(dot.begin(), dot.end(), "    2 -> 3;") != dot.end());
			Assert::IsTrue(find(dot.begin(), dot.end(), "    c[green];") != dot.end());
		}

		/// @brief Тест writeDotFile: граф с вершиной без входящих дуг, которая не входит в путь 
		TEST_METHOD(writeDotFile_orphanVertexNotInPath)
		{
			vector<vector<int>> matrix = {
				{0, 0, 1},
				{0, 0, 1},
				{0, 0, 0}
			};
			vector<int> indexToVertex = { 1, 2, 3 };
			vector<pair<int, int>> path = { {0, 2} }; 
			vector<string> dotStringGraph = {};
			outMessForGraph msg = { "c[green]", "[red]", "c[red]" };

			auto dot = writeDotFile(matrix, indexToVertex, path, dotStringGraph, msg);

		
			Assert::IsTrue(find(dot.begin(), dot.end(), "    1 -> 3;") != dot.end());
			Assert::IsTrue(find(dot.begin(), dot.end(), "    2 -> 3 [red];") != dot.end());
			Assert::IsTrue(find(dot.begin(), dot.end(), "    c[red];") != dot.end());
		}


	};
}