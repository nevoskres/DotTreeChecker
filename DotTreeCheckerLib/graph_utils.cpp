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


Graph parseDotFile(const vector<string>& lines)
{

	Graph g;
	g.setDotStringGraph(lines);

	map<int, int> vertexToIndex;        // отображение: имя вершины индекс
	vector<int> indexToVertex;          // обратное отображение: индекс имя вершины
	vector<pair<int, int>> edges;       // список дуг

	// Обрабатываем строки
	for (const string& line : lines)
	{
		if (line == "digraph G" || line == "{" || line == "}") continue;

		size_t arrowPos = line.find("->");
		if (arrowPos != string::npos)
		{
			// Дуга: a->b
			int from = stoi(line.substr(0, arrowPos));
			int to = stoi(line.substr(arrowPos + 2));

			edges.emplace_back(from, to);

			// Регистрируем вершины
			if (vertexToIndex.find(from) == vertexToIndex.end()) {
				vertexToIndex[from] = indexToVertex.size();
				indexToVertex.push_back(from);
			}
			if (vertexToIndex.find(to) == vertexToIndex.end()) {
				vertexToIndex[to] = indexToVertex.size();
				indexToVertex.push_back(to);
			}
		}
		else
		{
			// Изолированная вершина
			int v = stoi(line);
			if (vertexToIndex.find(v) == vertexToIndex.end()) {
				vertexToIndex[v] = indexToVertex.size();
				indexToVertex.push_back(v);
			}
		}
	}

	// Создание матрицы смежности
	int n = indexToVertex.size();
	vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0));

	for (const auto& edge : edges)
	{
		int i = vertexToIndex[edge.first];
		int j = vertexToIndex[edge.second];
		adjacencyMatrix[i][j] = 1;
	}

	g.setVertexToIndex(vertexToIndex);
	g.setIndexToVertex(indexToVertex);
	g.setAdjacencyMatrix(adjacencyMatrix);

	return g;
}


string trim(const string& s) 
{
	size_t start = 0;
	while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) {
		++start;
	}
	size_t end = s.size();
	while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) {
		--end;
	}
	return s.substr(start, end - start);
}

vector<string> cleanLines(const vector<string>& lines) 
{
	vector<string> result;
	for (const auto& line : lines) {
		
		string trimmed = trim(line);
		
		if (!trimmed.empty()) 
		{
			result.push_back(trimmed);
		}
	}
	return result;
}