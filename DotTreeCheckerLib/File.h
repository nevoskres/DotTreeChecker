#pragma once
#include<vector>
#include<string>
#include "Export.h"


/**
 * @file File.h
 * @brief ������������ ���� � ��������� ��� ������ � �������.
 */


/**
 * @brief ��������� ������ �� ���������� ����� � ������ �����.
 *
 * @details ��������� ���� �� ��������� �����, ��������� ��������� ���������� � ���������
 * ������ ������ � ������. ���� ��� ����� ������ ��� ���� �� ������ �������,
 * ���������� ������ ������.
 *
 * @param filename ��� ����� ��� ������.
 * @return ������ �����, ��������� �� �����.
 */

MYLIB_API  std::vector<std::string> readFile(const std::string& filename,bool& error);


/**
 * @brief �������� ���� � �������� � ��������� ������ �� ���������� ��������� ������.
 *
 * @param argc ���������� ���������� ��������� ������.
 * @param argv ������ ���������� ��������� ������.
 *
 * @return ���� �����: <�������_����, ��������_����>.
 */

MYLIB_API std::pair<std::string, std::string> extractFilePaths(int argc, char* argv[]);