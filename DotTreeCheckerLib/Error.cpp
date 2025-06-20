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

    string toLowerCopy(const string& s) {
        string res = s;
        transform(res.begin(), res.end(), res.begin(), [](unsigned char c) { return tolower(c); });
        return res;
    }

    string getFirstWord(const string& s) {
        size_t pos = s.find_first_of(" \t");
        if (pos == string::npos)
            return s;
        return s.substr(0, pos);
    }
}


Error::Error(ErrorType t, int n, const string& str) : type(t), numberStr(n), lineStr(str)
{
    message = "строка " + std::to_string(n) + ": \"" + str + "\"";
}


std::string Error::generateErrorMessage() const 
{
    switch (type) 
    {
    case noError: return "";
    case emptyFile: return "Ошибка: пустой файл";
    case connectionsError: return "Ошибка: в строке больше одной связи — " + message;
    case notDiGraph: return "Ошибка: граф не является орграфом — " + message;
    case countConnectionsError: return "Ошибка: слишком много связей — " + message;
    case countVerticesError: return "Ошибка: слишком много вершин — " + message;
    case emptyGraph: return "Ошибка: граф пустой";
    case loopError: return "Ошибка: в графе есть петля — " + message;
    case multipleConnectionsError: return "Ошибка: в графе есть кратные связи — " + message;
    case nameVerticesError: return "Ошибка: некорректное имя вершины (допустимое имя - числа в диапазоне [0;10])— " + message;
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

    const string& firstLineRaw = trim(lines[nonEmpty]);
    string firstWord = getFirstWord(firstLineRaw);
    string firstWordLower = toLowerCopy(firstWord);

    if (firstWordLower != "digraph") {
        if (firstWordLower == "graph") {
            errors.emplace_back(notDiGraph, nonEmpty + 1, firstLineRaw);
            return;
        }
        else {
            errors.emplace_back(graphsNotationSyntaxError, nonEmpty + 1, firstLineRaw);
        }
    }

    // Если слово digraph корректно, дальше извлекаем имя
    if (firstWordLower == "digraph") {
        size_t posAfterFirstWord = firstLineRaw.find_first_not_of(" \t", firstWord.size());
        string graphName;
        if (posAfterFirstWord == string::npos)
            graphName = "";
        else
            graphName = trim(firstLineRaw.substr(posAfterFirstWord));

        if (graphName.empty()) {
            errors.emplace_back(graphNameSyntaxError, nonEmpty + 1, firstLineRaw);
        }
        else {
            for (char c : graphName) {
                if (!(isalnum(static_cast<unsigned char>(c)) || c == '_')) {
                    errors.emplace_back(graphNameSyntaxError, nonEmpty + 1, firstLineRaw);
                    break;
                }
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
        if (!line.empty() && line[0] == '}') {
            if (line.size() > 1) {
                errors.emplace_back(extraCharacterAfterGraphError, nonEmpty + 1, line);
            }
            break; // закрывающая скобка найдена — заканчиваем анализ тела графа
        }

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

        size_t arrowPos = line.find("->");
        if (arrowPos == string::npos) {
            // Нет ребра — возможно, изолированная вершина
            // Проверим строку на корректное число с точкой с запятой
            string vertexStr = line;
            if (!vertexStr.empty() && vertexStr.back() == ';') {
                vertexStr.pop_back();
                vertexStr = trim(vertexStr);
            }

            auto isNumber = [](const string& s) {
                return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
                };

            if (isNumber(vertexStr)) {
                // Корректная изолированная вершина
                vertices.insert(vertexStr);
            }
            else if (line.find("--") != string::npos || line.find('>') != string::npos || line.find('<') != string::npos) {
                errors.emplace_back(connectionsSyntaxError, nonEmpty + 1, line);
            }
            continue;
        }

        // Извлечение вершин и их валидация
        string from = trim(line.substr(0, arrowPos));
        string toPart = trim(line.substr(arrowPos + 2));

        // Если в конце 'toPart' есть ';', убрать его
        if (!toPart.empty() && toPart.back() == ';') {
            toPart.pop_back();
            toPart = trim(toPart);
        }

        // Выделяем число в 'to' и возможные лишние символы
        size_t posNum = 0;
        while (posNum < toPart.size() && isdigit(static_cast<unsigned char>(toPart[posNum]))) {
            ++posNum;
        }

        string toNumber = toPart.substr(0, posNum);
        string extra = toPart.substr(posNum);

        auto isNumber = [](const string& s)
            {
                return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
            };

        bool vertexNameErrorFound = false;

        // Проверка from
        if (!isNumber(from))
        {
            errors.emplace_back(nameVerticesError, nonEmpty + 1, line);
            vertexNameErrorFound = true;
        }
        else if (from.size() > 2 || stoi(from) > 10)
        {
            errors.emplace_back(nameVerticesError, nonEmpty + 1, line);
            vertexNameErrorFound = true;
        }

        // Проверка toNumber
        if (!isNumber(toNumber))
        {
            errors.emplace_back(nameVerticesError, nonEmpty + 1, line);
            vertexNameErrorFound = true;
        }
        else if (toNumber.size() > 2 || stoi(toNumber) > 10)
        {
            errors.emplace_back(nameVerticesError, nonEmpty + 1, line);
            vertexNameErrorFound = true;
        }

        // Проверка наличия петли
        if (from == toNumber)
        {
            errors.emplace_back(loopError, nonEmpty + 1, line);
        }

        // Проверка кратных связей
        pair<string, string> edge = { from, toNumber };
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
        vertices.insert(toNumber);

        ++edgeCount;

        if (!vertexNameErrorFound) {
            for (char ch : line) {
                if (!(isdigit(static_cast<unsigned char>(ch)) || ch == '-' || ch == '>' || ch == ';' || isspace(static_cast<unsigned char>(ch)))) {
                    errors.emplace_back(extraCharacterInGraphError, nonEmpty + 1, line);
                    break;
                }
            }
        }
    }

    if (nonEmpty == static_cast<int>(lines.size())) {
        // Закрывающая скобка не найдена
        errors.emplace_back(curlyBracketError, nonEmpty + 1, "отсутствует закрывающая фигурная скобка");
    }
    else {
        // Проверка лишних строк после закрывающей скобки
        for (int i = nonEmpty + 1; i < static_cast<int>(lines.size()); ++i) {
            if (!trim(lines[i]).empty()) {
                errors.emplace_back(extraCharacterAfterGraphError, i + 1, lines[i]);
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
}
