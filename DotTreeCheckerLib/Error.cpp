#include "pch.h"
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <set>
#include "graph_utils.h"
#include "Error.h"
using namespace std;


namespace 
{
    size_t findCaseInsensitive(const std::string& haystack, const std::string& needle) {
        if (needle.empty()) return 0;
        for (size_t i = 0; i + needle.size() <= haystack.size(); ++i) {
            bool match = true;
            for (size_t j = 0; j < needle.size(); ++j) {
                if (tolower(static_cast<unsigned char>(haystack[i + j])) !=
                    tolower(static_cast<unsigned char>(needle[j]))) {
                    match = false;
                    break;
                }
            }
            if (match)
                return i;
        }
        return std::string::npos;
    }
}


Error::Error(ErrorType t, int n, const string& str) : type(t), numberStr(n), lineStr(str)
{
    message = "строка " + std::to_string(n + 1) + ": \"" + str + "\"";
}


string Error::generateErrorMessage(ErrorType type) const
{
    switch (type)
    {
    case noError: return "";
    case inFileNotExist: return "Ошибка: файл не найден";
    case outFileCreateFail: return "Ошибка: не удалось создать выходной файл";
    case emptyFile: return "Ошибка: пустой файл";
    case connectionsError: return "Ошибка: в строке больше одной связи — " + message;
    case notDiGraph: return "Ошибка: граф не является орграфом — " + message;
    case countConnectionsError: return "Ошибка: слишком много связей — " + message;
    case countVerticesError: return "Ошибка: слишком много вершин — " + message;
    case emptyGraph: return "Ошибка: граф пустой";
    case loopError: return "Ошибка: в графе есть петля — " + message;
    case multipleConnectionsError: return "Ошибка: в графе есть кратные связи — " + message;
    case nameVerticesError: return "Ошибка: некорректное имя вершины — " + message;
    case graphsNotationSyntaxError: return "Ошибка: неверное обозначение графа — " + message;
    case graphNameSyntaxError: return "Ошибка: неверное имя графа — " + message;
    case curlyBracketError: return "Ошибка: отсутствует фигурная скобка — " + message;
    case extraCharacterAfterGraphError: return "Ошибка: лишний символ после тела графа — " + message;
    case extraCharacterInGraphError: return "Ошибка: лишний символ внутри тела графа — " + message;
    case connectionsSyntaxError: return "Ошибка: неверное написание дуги — " + message;
    }
    return "Неизвестная ошибка — " + message;
}

ErrorType Error::getType() const
{
    return type;
}

int Error::getLineNumber() const
{
    return numberStr;
}

string Error::getLineString() const
{
    return lineStr;
}

const vector<Error>& Error::getErrors() const
{
    return errors;
}


void Error::findErrors(const vector<string>& lines)
{
    errors.clear();

    // Пропуск пустых строк в начале файла
    int nonEmpty = 0;
    while (nonEmpty < static_cast<int>(lines.size()) && trim(lines[nonEmpty]).empty())
        ++nonEmpty;

    // Проверка: если файл полностью пустой или только из пробелов
    if (nonEmpty == static_cast<int>(lines.size())) {
        errors.emplace_back(emptyFile, 0, "");
        return;
    }

    // Проверка первой непустой строки: корректность объявления графа и имени
    const string& firstLine = trim(lines[nonEmpty]);
    size_t pos = findCaseInsensitive(firstLine, "digraph");
    if (pos == string::npos) {
        if (findCaseInsensitive(firstLine, "graph") != string::npos) {
            errors.emplace_back(notDiGraph, nonEmpty + 1, firstLine);
        }
        else {
            errors.emplace_back(graphsNotationSyntaxError, nonEmpty + 1, firstLine);
        }
        pos = 0; // чтобы избежать использования в дальнейшем
    }
    else {
        pos += 7; // длина "digraph"
    }

    // Извлечение и проверка имени графа (пропускаем пробелы после digraph)
    while (pos < firstLine.size() && isspace(static_cast<unsigned char>(firstLine[pos]))) ++pos;
    string graphName = firstLine.substr(pos);
    graphName = trim(graphName);

    if (graphName.empty()) {
        errors.emplace_back(graphNameSyntaxError, nonEmpty + 1, firstLine);
    }
    else {
        for (char c : graphName) {
            if (!(isalnum(static_cast<unsigned char>(c)) || c == '_')) {
                errors.emplace_back(graphNameSyntaxError, nonEmpty + 1, firstLine);
                break;
            }
        }
    }

    // Пропуск пустых строк после заголовка
    ++nonEmpty;
    while (nonEmpty < static_cast<int>(lines.size()) && trim(lines[nonEmpty]).empty())
        ++nonEmpty;

    // Проверка наличия открывающей фигурной скобки '{'
    if (nonEmpty >= static_cast<int>(lines.size())) {
        errors.emplace_back(curlyBracketError, nonEmpty + 1, "нет строки с открывающей фигурной скобкой");
        return;
    }

    string openBraceLine = trim(lines[nonEmpty]);
    if (openBraceLine.find('{') == string::npos) {
        errors.emplace_back(curlyBracketError, nonEmpty + 1, lines[nonEmpty]);
    }
    else if (openBraceLine != "{") {
        errors.emplace_back(extraCharacterInGraphError, nonEmpty + 1, lines[nonEmpty]);
    }

    // Основной анализ тела графа
    set<pair<string, string>> edges;
    set<string> vertices;
    int edgeCount = 0;

    ++nonEmpty;
    for (; nonEmpty < static_cast<int>(lines.size()); ++nonEmpty) {
        string line = trim(lines[nonEmpty]);
        if (line.empty()) continue;

        // Завершение проверки при нахождении закрывающей скобки
        if (line == "}") break;

        // Проверка на множественные связи в одной строке
        size_t arrowCount = 0, searchPos = 0;
        while ((searchPos = line.find("->", searchPos)) != string::npos) {
            ++arrowCount;
            searchPos += 2;
        }
        if (arrowCount > 1) {
            errors.emplace_back(connectionsError, nonEmpty + 1, line);
            continue;
        }

        // Проверка синтаксиса дуги (->)
        size_t arrowPos = line.find("->");
        if (arrowPos == string::npos)
        {
            if (line.find("--") != string::npos)
            {
                errors.emplace_back(connectionsSyntaxError, nonEmpty + 1, line);
            }
            else if (line.find('>') != string::npos || line.find('<') != string::npos)
            {
                errors.emplace_back(connectionsSyntaxError, nonEmpty + 1, line);
            }
            continue;
        }

        // Извлечение вершин и их валидация
        string from = trim(line.substr(0, arrowPos));
        string to = trim(line.substr(arrowPos + 2));

        // Если в конце 'to' есть ';', убрать его
        if (!to.empty() && to.back() == ';') {
            to.pop_back();
            to = trim(to);
        }

        auto isNumber = [](const string& s)
            {
                return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
            };

        if (!isNumber(from))
        {
            errors.emplace_back(nameVerticesError, nonEmpty + 1, line);
        }
        else if (stoi(from) > 10)
        {
            errors.emplace_back(nameVerticesError, nonEmpty + 1, line);
        }

        if (!isNumber(to))
        {
            errors.emplace_back(nameVerticesError, nonEmpty + 1, line);
        }
        else if (stoi(to) > 10) {
            errors.emplace_back(nameVerticesError, nonEmpty + 1, line);
        }

        // Проверка наличия петли
        if (from == to)
        {
            errors.emplace_back(loopError, nonEmpty + 1, line);
        }

        // Проверка кратных связей
        pair<string, string> edge = { from, to };
        if (edges.count(edge))
        {
            errors.emplace_back(multipleConnectionsError, nonEmpty + 1, line);
        }
        else
        {
            edges.insert(edge);
        }

        // Учет вершин и количества дуг
        vertices.insert(from);
        vertices.insert(to);

        ++edgeCount;

        // Проверка на лишние символы (кроме допустимых: цифры, ->, пробелы, ;)
        // Лишние символы — все кроме: 0-9, '-', '>', ';', ' ', '\t'
        for (char ch : line) {
            if (!(isdigit(static_cast<unsigned char>(ch)) || ch == '-' || ch == '>' || ch == ';' || isspace(static_cast<unsigned char>(ch)))) {
                errors.emplace_back(extraCharacterInGraphError, nonEmpty + 1, line);
                break;
            }
        }
    }

    // Проверка на пустой граф (нет вершин)
    if (vertices.empty())
    {
        errors.emplace_back(emptyGraph, nonEmpty + 1, "{");
    }
    else if (vertices.size() > 10)
    {
        errors.emplace_back(countVerticesError, nonEmpty + 1, "");
    }

    // Проверка на превышение допустимого числа дуг
    if (edgeCount > 110)
    {
        errors.emplace_back(countConnectionsError, nonEmpty + 1, "");
    }

    // Проверка лишних строк после закрытия тела графа
    for (int i = nonEmpty + 1; i < static_cast<int>(lines.size()); ++i) {
        string line = trim(lines[i]);
        if (!line.empty()) {
            errors.emplace_back(extraCharacterAfterGraphError, i + 1, lines[i]);
        }
    }
}

























//void Error::findErrors(const vector<string>& lines)
//{
//    errors.clear();
//
//    //Пропускаем "пустые" строки
//    int nonEmpty = 0;
//    while (nonEmpty < static_cast<int>(lines.size()) && trim(lines[nonEmpty]).empty())
//        ++nonEmpty;
//
//    //Проверка что файл не пустой или не заполнен только пробелами
//    if (nonEmpty == static_cast<int>(lines.size()))
//    {
//        errors.emplace_back(emptyFile, 0, "");
//        return;
//    }
//
//    //Проверка первой не пустой строки (объявление графа и его имя)
//    const string& firstLine = lines[nonEmpty];
//    size_t pos = findCaseInsensitive(firstLine,"digraph");
//    if (pos == string::npos)
//    {
//        errors.emplace_back(graphsNotationSyntaxError, nonEmpty, firstLine);
//    }
//    else
//    {
//        string afterDigraph = firstLine.substr(pos+7);
//        size_t start = afterDigraph.find_first_not_of(" \t");
//        if (start == string::npos)
//        {
//            errors.emplace_back(graphNameSyntaxError, nonEmpty, firstLine);
//        }
//
//        string graphName = afterDigraph.substr(start);
//        for (char c : graphName)
//        {
//            if (!(isalnum(static_cast<unsigned char>(c)) || c == '_'))
//            {
//                errors.emplace_back(graphNameSyntaxError, nonEmpty, firstLine);
//            }
//        }
//    }
//
//    //Пропускаем "пустые" строки
//    ++nonEmpty;
//    while (nonEmpty < static_cast<int>(lines.size()) && trim(lines[nonEmpty]).empty())
//        ++nonEmpty;
//
//    // Проверка на открывающую фигурную скобку
//    if (nonEmpty >= static_cast<int>(lines.size()))
//    {
//        errors.emplace_back(curlyBracketError, nonEmpty + 1, "нет строки с открывающей фигурной скобкой (это последняя строка файла)");
//        return;
//    }
//    else
//    {
//        string line = trim(lines[nonEmpty]);
//
//        if (line.empty() || line.find('{') == string::npos)
//        {
//            errors.emplace_back(curlyBracketError, nonEmpty + 1, lines[nonEmpty]);
//        }
//        else if (line != "{")
//        {
//            errors.emplace_back(extraCharacterInGraphError, nonEmpty + 1, lines[nonEmpty]);
//        }
//    }
//
//
//
//    //Пропускаем "пустые" строки
//    ++nonEmpty;
//    while (nonEmpty < static_cast<int>(lines.size()) && trim(lines[nonEmpty]).empty())
//        ++nonEmpty;
//
//    //Проверка правильности написания связей и вершин
//    for (int i = nonEmpty; i < static_cast<int>(lines.size()); ++i)
//    {
//        const string& line = lines[i];
//        if (trim(line).empty()) continue;
//
//        size_t arrowPos = line.find("->");
//        if (arrowPos == string::npos)
//        {
//            errors.emplace_back(connectionsSyntaxError, i, line);
//            continue;
//        }
//
//
//
//        //string from = line.substr(0, arrowPos);
//        //string to = line.substr(arrowPos + 2);
//
//        //auto isNumber = [](const string& s) {
//        //    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
//        //};
//
//        //if (!isNumber(from) || !isNumber(to))
//        //{
//        //    errors.emplace_back(nameVerticesError, i, line);
//        //    continue;
//        //}
//
//        //if (to.find_first_not_of("0123456789") != string::npos)
//        //{
//        //    errors.emplace_back(extraCharacterInGraphError, i, line);
//        //    continue;
//        //}
//
//        //if (line.find("->", arrowPos + 2) != string::npos)
//        //{
//        //    errors.emplace_back(connectionsError, i, line);
//        //}
//    }
//
//}
//

