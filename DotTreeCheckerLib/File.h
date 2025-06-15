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

MYLIB_API  std::vector<std::string> readFile(const std::wstring& filename,bool& error);


/**
 * @brief �������� ���� � �������� � ��������� ������ �� ���������� ��������� ������.
 *
 * @param argc ���������� ���������� ��������� ������.
 * @param argv ������ ���������� ��������� ������.
 *
 * @return ���� �����: <�������_����, ��������_����>.
 */

MYLIB_API std::pair<std::string, std::string> extractFilePaths(int argc, char* argv[]);


/**
 * @brief ���������� ������ � ��������� ���� ���������.
 *
 * @param lines ������ �����, ������� ���������� �������� � ����.
 * @param filename ��� ����� (� ����), � ������� ����� ������������� ������.
 * @return true ���� ���� ������� ������ � ������ ��������.
 * @return false ���� �� ������� ������� ���� ��� ������.
 */

MYLIB_API bool writeLinesToFile(const std::vector<std::string>& lines, const std::wstring& filename);
