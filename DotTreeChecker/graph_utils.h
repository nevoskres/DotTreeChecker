#pragma once
#include<vector>


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

