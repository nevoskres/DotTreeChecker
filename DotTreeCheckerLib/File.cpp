#include "pch.h"
#include"File.h"
#include <string>
#include<vector>
#include <iostream>
#include<fstream>
#include <io.h>
#include <fcntl.h>
#include "Error.h"
  
using namespace std;


vector<string> readFile(const wstring& filename, bool& error)
{

	vector<string> lines;   // ������ ��� �������� ����� �����

	// ��������� ���� ��� ������
	ifstream file(filename);

	if (!file.is_open())   // ���� �� ������� ������� ���� ��� ������
	{
		// ������� � ������� ��������� �� ������ 
		wcerr << L"�� ������� ������� ����: "<<filename<<"\n";
		// ������������� ���� ������
		error = true;
		// ���������� ������ ������
		return lines;
	}

	string line;

	while (getline(file, line))    // ��������� ���� ���������, ���� ���� ������
	{
		// ��������� ������ � ������
		lines.push_back(line);
	}

	// ��������� ����
	file.close();   

	// ���������� ��������� ������
	return lines;
}

pair<string, string> extractFilePaths(int argc, char* argv[])
{
	string inputFile;
	string outputFile;

	if (argc == 3)   // ���� �������� ����� ��� ��������� (��� ��������� + 2 ���������)
	{
		inputFile = argv[1];   // ������ �������� � ������� ����  
		outputFile = argv[2];   // ������ �������� � �������� ���� 
	}
	else if (argc == 1)    // ���� ���������� ��� (����� ����� ���������)
	{
		// ����������� ���� � ������������ �������
		wcout << L"������� ���� �������� �����: ";
		getline(cin, inputFile);
		wcout << L"������� ���� ��������� �����: ";
		getline(cin, outputFile);
	}
	else // ����� 
	{
		// ������� � ������� ��������� �� ������ � ������� ���������
		wcerr << L"������: �������� ���������� ����������\n" << L"�������������: " << (argc > 0 ? argv[0] : "program") << " <input_file> <output_file>" << endl;
		inputFile = "";
		outputFile = "";
	}

	// ���������� ���� �����
	return make_pair(inputFile, outputFile);
}

bool writeLinesToFile(const vector<string>& lines, const wstring& filename)
{
	// ��������� ���� ��� ������
	ofstream outFile(filename);

	if (!outFile.is_open())   // ���� �� ������� ������� ���� ��� ������
	{
		// ������� � ������� ��������� �� ������ 
		wcerr << L"�� ������� ������� ���� ��� ������: " << filename << "\n";
		// ���������� false
		return false;
	}

	// ���������� ������ ������ � ���� � ��������� ������
	for (const auto& line : lines)
	{
		outFile << line << '\n';
	}

	// ��������� ����
	outFile.close();

	// ���������� true
	return true;
}