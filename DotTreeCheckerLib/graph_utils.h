#pragma once
#include"Graph.h"
#include<vector>
#include<string>


/**
* @file graph_utils.h
* @brief Заголовочный файл с функциями для обхода ориентированного графа в глубину и поиска остова.
*/


/**
* @brief Рекурсивный обход графа в глубину (DFS), начиная с вершины start.
*
* @param start Индекс начальной вершины.
* @param visited Вектор посещенных вершин (будет обновлен).
* @param adjMatrix Матрица смежности графа.
* @param way Вектор дуг, формирующих путь остова (будет заполнен).
*/

void DFS(int start, std::vector<bool>& visited, std::vector<std::vector<int>>& adjMatrix, std::vector<std::pair<int, int>>& way);


/**
* @brief Ищет остов, покрывающий максимальное число вершин.
* Использует обход в глубину (DFS) для каждой вершины в графе.
*
* @param matrixCopy Копия матрицы смежности графа.
* @return Вектор дуг, составляющих найденный остов.
*/

std::vector<std::pair<int, int>> findBestSkeleton(std::vector<std::vector<int>> matrixCopy);


/**
 * @brief Удаляет ведущие и завершающие пробельные символы из строки.
 *
 * @param s Входная строка, из которой нужно удалить пробелы по краям.
 * @return Новая строка без пробелов в начале и конце.
 */

std::string trim(const std::string& s);


/**
 * @brief Парсит граф, описанный в формате DOT, и строит его матрицу смежности.
 *
 * @param lines Вектор строк, содержащий DOT-описание ориентированного графа.
 * @return Структура Graph, содержащая:
 * - исходные строки DOT-кода,
 * - матрицу смежности графа,
 * - отображение имен вершин в индексы и обратно.
 */

Graph parseDotFile(const std::vector<std::string>& lines);