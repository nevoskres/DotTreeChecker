#include <locale> 
#include <windows.h> 
#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>

#include "../DotTreeCheckerlib/DotTreeCheckerlib.h"

using namespace std;


std::wstring utf8ToUtf16(const std::string& utf8)
{

	if (utf8.empty()) return L"";
	int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), (int)utf8.size(), nullptr, 0);
	std::wstring wstrTo(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, utf8.data(), (int)utf8.size(), &wstrTo[0], sizeNeeded);
	return wstrTo;
}

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setlocale(LC_ALL, "ru_RU.UTF-8");

	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	auto filePaths = extractFilePaths(argc,argv);
	string inputFP = filePaths.first;
	string outputFP = filePaths.second;

	
	if (inputFP.empty())
	{
		wcerr << L"Не указан входной файл\n";
		return 1;
	}
	else if (outputFP.empty())
	{
		wcerr << L"Не указан выходной файл\n";
		return 1;
	}

	bool errorOpenInputFile = false;
	auto lines = readFile(utf8ToUtf16(inputFP), errorOpenInputFile);

	if (errorOpenInputFile) return 1;

	Error errorOb;

	errorOb.findErrors(lines);
	
	if (!errorOb.getErrors().empty())
	{
		const auto& errors = errorOb.getErrors();
		for (const auto& err : errors)
			wcerr << utf8ToUtf16(err.generateErrorMessage() ) << endl;
		return 1;  
	}
	
	Graph g = parseDotFile(cleanLines(lines));

	vector<pair<int, int>> bestSkeleton = findBestSkeleton(g.getAdjacencyMatrix());

	outMessForGraph message;

	vector<string> checkedDotGraph = writeDotFile(g.getAdjacencyMatrix(),g.getIndexToVertex(),
		bestSkeleton,g.getDotStringGraph(),message);
		
	bool openOutputFile = writeLinesToFile(checkedDotGraph, utf8ToUtf16(outputFP));
			
	if (!openOutputFile)
	{
		return 1;
	}

	return 0;
}
