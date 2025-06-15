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

MYLIB_API  std::vector<std::string> readFile(const std::wstring& filename,bool& error);


/**
 * @brief Получает пути к входному и выходному файлам из аргументов командной строки.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 *
 * @return Пара путей: <входной_файл, выходной_файл>.
 */

MYLIB_API std::pair<std::string, std::string> extractFilePaths(int argc, char* argv[]);


/**
 * @brief Записывает строки в указанный файл построчно.
 *
 * @param lines Вектор строк, который необходимо записать в файл.
 * @param filename Имя файла (с путём), в который будет производиться запись.
 * @return true Если файл успешно открыт и данные записаны.
 * @return false Если не удалось открыть файл для записи.
 */

MYLIB_API bool writeLinesToFile(const std::vector<std::string>& lines, const std::wstring& filename);
