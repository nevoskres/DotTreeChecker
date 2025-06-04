#include "pch.h"
#include "graph_utils.h"
using namespace std;

void DFS(int start, vector<bool>& visited, vector<vector<int>>& adjMatrix, vector<pair<int, int>>& way)
{
	//Отмечаем текущую вершину как посещнную
	visited[start] = true;

	//Проходим по всем возможным соседям текущей вершины
	for (int neighbor = 0; neighbor < adjMatrix.size(); ++neighbor)
	{
		//Если существует ребро от start к соседу и если сосед ещё не посещён
		if (adjMatrix[start][neighbor] == 1 && !visited[neighbor])
		{
			//Помечаем дугу как часть остова
			adjMatrix[start][neighbor] = 2;
			//Добавляем эту дугу в путь  
			way.emplace_back(start, neighbor);
			//Рекурсивно вызываем DFS для соседа
			DFS(neighbor, visited, adjMatrix, way);
		}
	}
}

vector<pair<int, int>> findBestSkeleton(vector<vector<int>> matrixCopy)
{

	vector<pair<int, int>> skeleton;
	int maxVisited = -1;
	int bestStartVertex = -1;



	//Для каждой вершины графа
	for (int i = 0; i < matrixCopy.size(); ++i)
	{
		vector<pair<int, int>> s;
		std::vector<bool> visited(matrixCopy.size(), false);
		vector<vector<int>> matrixCopyCopy = matrixCopy;


		//Осуществить поиск в глубину от текущей вершины
		DFS(i, visited, matrixCopyCopy, s);

		int visitedCount = int(count(visited.begin(), visited.end(), true));

		//Если количество посещенных вершин из текущей больше чем у предыдущей
		if (visitedCount > maxVisited)
		{
			//Записать новое количество вершин как максимально 
			maxVisited = visitedCount;
			//Записать новый путь как лучший остов
			skeleton = s;
			//Записать текущий корень 
			bestStartVertex = i;
		}
	}

	// Если остов пуст (нет дуг), но вершина есть, добавить "псевдо-ребро"
	if (skeleton.empty() && bestStartVertex != -1)
	{
		//Добавить ребро из вершины в саму себя 
		skeleton.push_back({ bestStartVertex, bestStartVertex });
	}

	//Вернуть лучший остов (путь)
	return skeleton;
}
