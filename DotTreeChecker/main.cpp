#include <locale> 
#include <windows.h> 
#include <iostream>
#include <fstream>

#include "../DotTreeCheckerlib/DotTreeCheckerlib.h"

using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setlocale(LC_ALL, "ru_RU.UTF-8");

	//Считать из параметров командной строки путь ко входному файлу
	auto filePaths = extractFilePaths(argc,argv);
	string inputFP = filePaths.first;
	//Считать из параметров командной строки путь для выходного файла
	string outputFP = filePaths.second;

	
	if (inputFP.empty())
	{
		cerr << "Не указан входной файл\n";
		return 1;
	}
	else if (outputFP.empty())
	{
		cerr << "Не указан выходной файл\n";
		return 1;
	}

	bool errorOpenInputFile = false;
	auto lines = readFile(inputFP, errorOpenInputFile);

	if (errorOpenInputFile) return 1;

	Error errorOb;

	errorOb.findErrors(lines);
	
	if (!errorOb.getErrors().empty())
	{
		const auto& errors = errorOb.getErrors();
		for (const auto& err : errors)
			std::cerr << err.generateErrorMessage() << std::endl;
		return 1;  
	}
	
	Graph g = parseDotFile(cleanLines(lines));

	vector<pair<int, int>> bestSkeleton = findBestSkeleton(g.getAdjacencyMatrix());

	outMessForGraph message;

	vector<string> checkedDotGraph = writeDotFile(g.getAdjacencyMatrix(),g.getIndexToVertex(),
		bestSkeleton,g.getDotStringGraph(),message);
		
	bool openOutputFile = writeLinesToFile(checkedDotGraph, outputFP);
			
	if (!openOutputFile)
	{
		return 1;
	}

	return 0;
}
