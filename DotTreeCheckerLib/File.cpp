#include "pch.h"
#include"File.h"
#include <string>
#include<vector>
#include <iostream>
#include<fstream>
#include "Error.h"
  
using namespace std;

vector<string> readFile(const string& filename, bool& error)
{

	vector<string> lines;

	ifstream file(filename);

	if (!file.is_open())
	{
		cerr << "�� ������� ������� ����: "<<filename<<"\n";
		error = true;
		return lines;
	}

	string line;
	while (getline(file, line))
	{
		lines.push_back(line);
	}

	file.close();
	return lines;
}

pair<string, string> extractFilePaths(int argc, char* argv[])
{
	string inputFile;
	string outputFile;

	if (argc == 3) 
	{
		inputFile = argv[1];   
		outputFile = argv[2];  
	}
	else if (argc == 1)
	{

		cout << "������� ���� �������� �����: ";
		getline(cin, inputFile);
		cout << "������� ���� ��������� �����: ";
		getline(cin, outputFile);
	}
	else
	{
		cerr << "������: �������� ���������� ����������\n" << "�������������: " << (argc > 0 ? argv[0] : "program") << " <input_file> <output_file>" << endl;
		inputFile = "";
		outputFile = "";
	}

	return make_pair(inputFile, outputFile);
}

bool writeLinesToFile(const std::vector<std::string>& lines, const std::string& filename)
{
	std::ofstream outFile(filename);
	if (!outFile.is_open())
	{
		cerr << "�� ������� ������� ���� ��� ������: " << filename << "\n";
		return false;
	}

	for (const auto& line : lines)
	{
		outFile << line << '\n';
	}
	outFile.close();
	return true;
}