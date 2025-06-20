#pragma once
#include<vector>
#include<string>
#include"Graph.h"
#include "Export.h"


/**
* @file graph_utils.h
* @brief ������������ ���� � ��������� ��� ������ ���������������� ����� � ������� � ������ ������.
*/


/**
* @brief ����������� ����� ����� � ������� (DFS), ������� � ������� start.
*
* @param start ������ ��������� �������.
* @param visited ������ ���������� ������ (����� ��������).
* @param adjMatrix ������� ��������� �����.
* @param way ������ ���, ����������� ���� ������ (����� ��������).
*/

MYLIB_API void DFS(int start, std::vector<bool>& visited, std::vector<std::vector<int>>& adjMatrix, std::vector<std::pair<int, int>>& way);


/**
* @brief ���� �����, ����������� ������������ ����� ������.
* @details ���������� ����� � ������� (DFS) ��� ������ ������� � �����.
*
* @param matrixCopy ����� ������� ��������� �����.
* @return ������ ���, ������������ ��������� �����.
*/

MYLIB_API  std::vector<std::pair<int, int>> findBestSkeleton(std::vector<std::vector<int>> matrixCopy);


/**
 * @brief ������� ������� � ����������� ���������� ������� �� ������.
 *
 * @param s ������� ������, �� ������� ����� ������� ������� �� �����.
 * @return ����� ������ ��� �������� � ������ � �����.
 */

MYLIB_API  std::string trim(const std::string& s);


/**
 * @brief ������� ������ ������ � �������� ������� �� ����� � ������ ������.
 * @details ������������ ��� ��������������� ������� ������� ������ ����� ����� ���������.
 * ������ ����������� ������� trim ��� �������� ��������.
 *
 * @param lines ������ �����, �������� ���������� ������ ������.
 * @return ����� ������ ����� ��� ������ � � ����������� ���������.
 */

MYLIB_API  std::vector<std::string> cleanLines(const std::vector<std::string>& lines);


/**
 * @brief ������ ����, ��������� � ������� DOT, � ������ ��� ������� ���������.
 *
 * @param lines ������ �����, ���������� DOT-�������� ���������������� �����.
 * @return ��������� Graph, ����������:
 * - �������� ������ DOT-����,
 * - ������� ��������� �����,
 * - ����������� ���� ������ � ������� � �������.
 */

MYLIB_API  Graph parseDotFile(const std::vector<std::string>& lines);


/**
 * @brief ��������� ��� �������� ��������� � ������� DOT, ������������ ��� ������������ ����������� �������� ����� �� ������.
 * 
 * @details ��������� `outMessForGraph` �������� ��������������� ������, �������������� ��������� ��������� � ������������ ��� ������� ����� �� ������� ��� ������������ ������.
 * ��� ������ ����� �������������� � ����������� ������������ (��������, � ������� Graphviz).
 */

struct MYLIB_API outMessForGraph
{
    /// ������ DOT-��������� ���� ��� ����������� ��������� � ���, ��� ���� �������� �������.
    /// ������� ���� ������������ ��� ��������� �������������� ����������.
    const std::string graphIsTree = "c[color = green label = \"���� �������� �������\", fontcolor = green]";

    /// ������ DOT-��������� ����, ����������� � ������ ��� ��������, ������� ������������� �������,
    /// ����� ���� ���� �������. ���������� ������� ������.
    const std::string forRemove = "[color=red]";

    /// ������ DOT-��������� ���� � ���������� � ���, ��� ���� �� �������� �������,
    /// � ������������� �� �������� ������������� ������ ����� �������� ���.
    const std::string graphIsNotTree = "c[color = red label = \"���� ��� �������� ������������� ���� �������� ������������� �������, ����� ������� ������� �������\"]";
};


/**
 * @brief ��������� ��� ����� �� ������ ������ DOT-��������.
 * @param dotLines ������ �����, �������������� DOT-�������� �����. ������ ������ ������ ��������� ���������� �����.
 * @return ��� �����.
 */

MYLIB_API std::string extractGraphName(const std::vector<std::string>& dotLines);


/**
 * @brief ���������� DOT-���� �� ������� ��������� � ����.
 *
 * @details ������� � ����, �� �������� � ����, ���������� ������� ������.
 * � ����� ����������� ����������� ������� c[...] � ����������:
 * - ���� ��� ������� � ���� ������ � ���� � ���� ������.
 * - ����� � ������� �� ������������� �������� ��� �������� ���.
 *
 * @param adjacencyMatrix ������� ���������.
 * @param indexToVertex �������� �����������: ������ -> ��� �������.
 * @param dotStringGraph ����������� DOT-�������� �����
 * @param path ���� � ���� ��� (������, ����), �� ������ ��������.
 * @return ������ ����� � DOT-�������� �����.
 */

MYLIB_API  std::vector<std::string> writeDotFile(
    const std::vector<std::vector<int>>& adjacencyMatrix,
    const std::vector<int>& indexToVertex,
    const std::vector<std::pair<int, int>>& path,
    const std::vector<std::string>& dotStringGraph,
    const outMessForGraph& messages);