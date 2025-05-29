#pragma once
#include<vector>


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

