
/**
 * @file Export.h
 * @brief ����������� ������� ��������/������� �������� ��� ����������.
 *
 * @details ���� ���� �������� ������ `MYLIB_API`, ������� ��������� ��������� � ��������
 * �������, ������� � ���������� ����� ����������� � �������� ���������.
 */

#pragma once

#ifdef MYLIBRARY_EXPORTS
#define MYLIB_API __declspec(dllexport)
#else
#define MYLIB_API __declspec(dllimport)
#endif
