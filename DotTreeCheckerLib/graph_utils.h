#pragma once
#include"Graph.h"
#include<vector>
#include<string>


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

void DFS(int start, std::vector<bool>& visited, std::vector<std::vector<int>>& adjMatrix, std::vector<std::pair<int, int>>& way);


/**
* @brief ���� �����, ����������� ������������ ����� ������.
* ���������� ����� � ������� (DFS) ��� ������ ������� � �����.
*
* @param matrixCopy ����� ������� ��������� �����.
* @return ������ ���, ������������ ��������� �����.
*/

std::vector<std::pair<int, int>> findBestSkeleton(std::vector<std::vector<int>> matrixCopy);


/**
 * @brief ������� ������� � ����������� ���������� ������� �� ������.
 *
 * @param s ������� ������, �� ������� ����� ������� ������� �� �����.
 * @return ����� ������ ��� �������� � ������ � �����.
 */

std::string trim(const std::string& s);


/**
 * @brief ������ ����, ��������� � ������� DOT, � ������ ��� ������� ���������.
 *
 * @param lines ������ �����, ���������� DOT-�������� ���������������� �����.
 * @return ��������� Graph, ����������:
 * - �������� ������ DOT-����,
 * - ������� ��������� �����,
 * - ����������� ���� ������ � ������� � �������.
 */

Graph parseDotFile(const std::vector<std::string>& lines);