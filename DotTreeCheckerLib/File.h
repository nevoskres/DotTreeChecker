#pragma once
#include<vector>
#include<string>
#include "Export.h"


/**
 * @file File.h
 * @brief Заголовочный файл с функциями для работы с файлами.
 */


/**
 * @brief Считывает строки из текстового файла в вектор строк.
 *
 * @details Открывает файл по заданному имени, построчно считывает содержимое и сохраняет
 * каждую строку в вектор. Если имя файла пустое или файл не удаётся открыть,
 * возвращает пустой вектор.
 *
 * @param filename Имя файла для чтения.
 * @return Вектор строк, считанных из файла.
 */

MYLIB_API  std::vector<std::string> readFile(const std::string& filename,bool& error);


/**
 * @brief Получает пути к входному и выходному файлам из аргументов командной строки.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 *
 * @return Пара путей: <входной_файл, выходной_файл>.
 */

MYLIB_API std::pair<std::string, std::string> extractFilePaths(int argc, char* argv[]);