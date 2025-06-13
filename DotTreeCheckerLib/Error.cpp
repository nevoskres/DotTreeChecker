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
    message = "������ " + std::to_string(n + 1) + ": \"" + str + "\"";
}


string Error::generateErrorMessage(ErrorType type) const
{
    switch (type)
    {
    case noError: return "";
    case inFileNotExist: return "������: ���� �� ������";
    case outFileCreateFail: return "������: �� ������� ������� �������� ����";
    case emptyFile: return "������: ������ ����";
    case connectionsError: return "������: � ������ ������ ����� ����� � " + message;
    case notDiGraph: return "������: ���� �� �������� �������� � " + message;
    case countConnectionsError: return "������: ������� ����� ������ � " + message;
    case countVerticesError: return "������: ������� ����� ������ � " + message;
    case emptyGraph: return "������: ���� ������";
    case loopError: return "������: � ����� ���� ����� � " + message;
    case multipleConnectionsError: return "������: � ����� ���� ������� ����� � " + message;
    case nameVerticesError: return "������: ������������ ��� ������� � " + message;
    case graphsNotationSyntaxError: return "������: �������� ����������� ����� � " + message;
    case graphNameSyntaxError: return "������: �������� ��� ����� � " + message;
    case curlyBracketError: return "������: ����������� �������� ������ � " + message;
    case extraCharacterAfterGraphError: return "������: ������ ������ ����� ���� ����� � " + message;
    case extraCharacterInGraphError: return "������: ������ ������ ������ ���� ����� � " + message;
    case connectionsSyntaxError: return "������: �������� ��������� ���� � " + message;
    }
    return "����������� ������ � " + message;
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

    // ������� ������ ����� � ������ �����
    int nonEmpty = 0;
    while (nonEmpty < static_cast<int>(lines.size()) && trim(lines[nonEmpty]).empty())
        ++nonEmpty;

    // ��������: ���� ���� ��������� ������ ��� ������ �� ��������
    if (nonEmpty == static_cast<int>(lines.size())) {
        errors.emplace_back(emptyFile, 0, "");
        return;
    }

    // �������� ������ �������� ������: ������������ ���������� ����� � �����
    const string& firstLine = trim(lines[nonEmpty]);
    size_t pos = findCaseInsensitive(firstLine, "digraph");
    if (pos == string::npos) {
        if (findCaseInsensitive(firstLine, "graph") != string::npos) {
            errors.emplace_back(notDiGraph, nonEmpty + 1, firstLine);
        }
        else {
            errors.emplace_back(graphsNotationSyntaxError, nonEmpty + 1, firstLine);
        }
        pos = 0; // ����� �������� ������������� � ����������
    }
    else {
        pos += 7; // ����� "digraph"
    }

    // ���������� � �������� ����� ����� (���������� ������� ����� digraph)
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

    // ������� ������ ����� ����� ���������
    ++nonEmpty;
    while (nonEmpty < static_cast<int>(lines.size()) && trim(lines[nonEmpty]).empty())
        ++nonEmpty;

    // �������� ������� ����������� �������� ������ '{'
    if (nonEmpty >= static_cast<int>(lines.size())) {
        errors.emplace_back(curlyBracketError, nonEmpty + 1, "��� ������ � ����������� �������� �������");
        return;
    }

    string openBraceLine = trim(lines[nonEmpty]);
    if (openBraceLine.find('{') == string::npos) {
        errors.emplace_back(curlyBracketError, nonEmpty + 1, lines[nonEmpty]);
    }
    else if (openBraceLine != "{") {
        errors.emplace_back(extraCharacterInGraphError, nonEmpty + 1, lines[nonEmpty]);
    }

    // �������� ������ ���� �����
    set<pair<string, string>> edges;
    set<string> vertices;
    int edgeCount = 0;

    ++nonEmpty;
    for (; nonEmpty < static_cast<int>(lines.size()); ++nonEmpty) {
        string line = trim(lines[nonEmpty]);
        if (line.empty()) continue;

        // ���������� �������� ��� ���������� ����������� ������
        if (line == "}") break;

        // �������� �� ������������� ����� � ����� ������
        size_t arrowCount = 0, searchPos = 0;
        while ((searchPos = line.find("->", searchPos)) != string::npos) {
            ++arrowCount;
            searchPos += 2;
        }
        if (arrowCount > 1) {
            errors.emplace_back(connectionsError, nonEmpty + 1, line);
            continue;
        }

        // �������� ���������� ���� (->)
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

        // ���������� ������ � �� ���������
        string from = trim(line.substr(0, arrowPos));
        string to = trim(line.substr(arrowPos + 2));

        // ���� � ����� 'to' ���� ';', ������ ���
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

        // �������� ������� �����
        if (from == to)
        {
            errors.emplace_back(loopError, nonEmpty + 1, line);
        }

        // �������� ������� ������
        pair<string, string> edge = { from, to };
        if (edges.count(edge))
        {
            errors.emplace_back(multipleConnectionsError, nonEmpty + 1, line);
        }
        else
        {
            edges.insert(edge);
        }

        // ���� ������ � ���������� ���
        vertices.insert(from);
        vertices.insert(to);

        ++edgeCount;

        // �������� �� ������ ������� (����� ����������: �����, ->, �������, ;)
        // ������ ������� � ��� �����: 0-9, '-', '>', ';', ' ', '\t'
        for (char ch : line) {
            if (!(isdigit(static_cast<unsigned char>(ch)) || ch == '-' || ch == '>' || ch == ';' || isspace(static_cast<unsigned char>(ch)))) {
                errors.emplace_back(extraCharacterInGraphError, nonEmpty + 1, line);
                break;
            }
        }
    }

    // �������� �� ������ ���� (��� ������)
    if (vertices.empty())
    {
        errors.emplace_back(emptyGraph, nonEmpty + 1, "{");
    }
    else if (vertices.size() > 10)
    {
        errors.emplace_back(countVerticesError, nonEmpty + 1, "");
    }

    // �������� �� ���������� ����������� ����� ���
    if (edgeCount > 110)
    {
        errors.emplace_back(countConnectionsError, nonEmpty + 1, "");
    }

    // �������� ������ ����� ����� �������� ���� �����
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
//    //���������� "������" ������
//    int nonEmpty = 0;
//    while (nonEmpty < static_cast<int>(lines.size()) && trim(lines[nonEmpty]).empty())
//        ++nonEmpty;
//
//    //�������� ��� ���� �� ������ ��� �� �������� ������ ���������
//    if (nonEmpty == static_cast<int>(lines.size()))
//    {
//        errors.emplace_back(emptyFile, 0, "");
//        return;
//    }
//
//    //�������� ������ �� ������ ������ (���������� ����� � ��� ���)
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
//    //���������� "������" ������
//    ++nonEmpty;
//    while (nonEmpty < static_cast<int>(lines.size()) && trim(lines[nonEmpty]).empty())
//        ++nonEmpty;
//
//    // �������� �� ����������� �������� ������
//    if (nonEmpty >= static_cast<int>(lines.size()))
//    {
//        errors.emplace_back(curlyBracketError, nonEmpty + 1, "��� ������ � ����������� �������� ������� (��� ��������� ������ �����)");
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
//    //���������� "������" ������
//    ++nonEmpty;
//    while (nonEmpty < static_cast<int>(lines.size()) && trim(lines[nonEmpty]).empty())
//        ++nonEmpty;
//
//    //�������� ������������ ��������� ������ � ������
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

