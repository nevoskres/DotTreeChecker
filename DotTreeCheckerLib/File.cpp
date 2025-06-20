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

	vector<string> lines;   // Вектор для хранения строк файла

	// Открываем файл для чтения
	ifstream file(filename);

	if (!file.is_open())   // Если не удалось открыть файл для чтения
	{
		// Выводим в консоль сообщение об ошибке 
		wcerr << L"Не удалось открыть файл: "<<filename<<"\n";
		// Устанавливаем флаг ошибки
		error = true;
		// Возвращаем пустой вектор
		return lines;
	}

	string line;

	while (getline(file, line))    // Считываем файл построчно, пока есть строки
	{
		// Добавляем строку в вектор
		lines.push_back(line);
	}

	// Закрываем файл
	file.close();   

	// Возвращаем считанные строки
	return lines;
}

pair<string, string> extractFilePaths(int argc, char* argv[])
{
	string inputFile;
	string outputFile;

	if (argc == 3)   // Если передано ровно два аргумента (имя программы + 2 параметра)
	{
		inputFile = argv[1];   // Первый аргумент — входной файл  
		outputFile = argv[2];   // Второй аргумент — выходной файл 
	}
	else if (argc == 1)    // Если аргументов нет (кроме имени программы)
	{
		// Запрашиваем пути у пользователя вручную
		wcout << L"Введите путь входного файла: ";
		getline(cin, inputFile);
		wcout << L"Введите путь выходного файла: ";
		getline(cin, outputFile);
	}
	else // Иначе 
	{
		// Выводим в консоль сообщение об ошибке и выводим подсказку
		wcerr << L"Ошибка: неверное количество аргументов\n" << L"Использование: " << (argc > 0 ? argv[0] : "program") << " <input_file> <output_file>" << endl;
		inputFile = "";
		outputFile = "";
	}

	// Возвращаем пару путей
	return make_pair(inputFile, outputFile);
}

bool writeLinesToFile(const vector<string>& lines, const wstring& filename)
{
	// Открываем файл для записи
	ofstream outFile(filename);

	if (!outFile.is_open())   // Если не удалось открыть файл для записи
	{
		// Выводим в консоль сообщение об ошибке 
		wcerr << L"Не удалось открыть файл для записи: " << filename << "\n";
		// Возвращаем false
		return false;
	}

	// Записываем каждую строку в файл с переводом строки
	for (const auto& line : lines)
	{
		outFile << line << '\n';
	}

	// Закрываем файл
	outFile.close();

	// Возвращаем true
	return true;
}