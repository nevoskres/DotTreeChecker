#include "pch.h"
#include "graph_utils.h"
#include<set>
using namespace std;

void DFS(int start, vector<bool>& visited, vector<vector<int>>& adjMatrix, vector<pair<int, int>>& way)
{
	//Отмечаем текущую вершину как посещнную
	visited[start] = true;

	//Проходим по всем возможным соседям текущей вершины
	for (int neighbor = 0; neighbor < adjMatrix.size(); ++neighbor)
	{
		
		if (adjMatrix[start][neighbor] == 1 && !visited[neighbor])   //Если существует ребро от start к соседу и если сосед ещё не посещён
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

		
		if (visitedCount > maxVisited)   //Если количество посещенных вершин из текущей больше чем у предыдущей
		{
			//Записать новое количество вершин как максимально 
			maxVisited = visitedCount;
			//Записать новый путь как лучший остов
			skeleton = s;
			//Записать текущий корень 
			bestStartVertex = i;
		}
	}

	
	if (skeleton.empty() && bestStartVertex != -1)   // Если остов пуст (нет дуг), но вершина есть, добавить "псевдо-ребро"
	{
		//Добавить ребро из вершины в саму себя 
		skeleton.push_back({ bestStartVertex, bestStartVertex });
	}

	//Вернуть лучший остов (путь)
	return skeleton;
}

string trim(const string& s) 
{
	// Находим индекс первого непробельного символа с начала строки
	size_t start = 0;
	while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) {
		++start;
	}

	// Находим индекс последнего непробельного символа с конца строки
	size_t end = s.size();
	while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) {
		--end;
	}

	// Возвращаем подстроку без пробелов в начале и конце
	return s.substr(start, end - start);
}

vector<string> cleanLines(const vector<string>& lines) 
{
	vector<string> result;


	for (const auto& line : lines) // Для каждой строки
	{
		// Удаляем пробелы по краям строки
		string trimmed = trim(line);
		
		// Если строка не пустая после обрезки — добавляем в результат
		if (!trimmed.empty()) 
		{
			result.push_back(trimmed);
		}
	}

	// Возвращаем очищенный вектор строк
	return result;
}

string extractGraphName(const vector<string>& dotLines) 
{
	// Если входной вектор пуст — возвращаем имя по умолчанию
	if (dotLines.empty()) 
		return "G";

	// В первой строке ищем позицию "digraph"
	const string& line = dotLines.front();
	size_t pos = line.find("digraph");

	// Если "digraph" не найдено — вернуть "G"
	if (pos == string::npos) 
		return "G";

	// Переходим за слово "digraph"
	pos += 7;

	// Пропускаем пробелы после "digraph"
	while (pos < line.size() && isspace(static_cast<unsigned char>(line[pos]))) ++pos;

	// Считываем имя графа: допускаются буквы, цифры и подчёркивания
	string name;
	while (pos < line.size() && (isalnum(static_cast<unsigned char>(line[pos])) || line[pos] == '_')) {
		name += line[pos++];
	}

	// Если имя не найдено — вернуть "G" иначе вернуть найденное имя
	return name.empty() ? "G" : name;
}

Graph parseDotFile(const vector<string>& lines)
{

	Graph g;
	g.setDotStringGraph(lines);

	string graphName = extractGraphName(lines);

	map<int, int> vertexToIndex;        // отображение: имя вершины индекс
	vector<int> indexToVertex;          // обратное отображение: индекс имя вершины
	vector<pair<int, int>> edges;       // список дуг

	// Обрабатываем строки
	for (const string& line : lines)
	{
		if (line == "{" || line == "}") continue;
		if (line == "digraph " + graphName) continue;

		size_t arrowPos = line.find("->");
		if (arrowPos != string::npos)
		{
			// Обработка дуги вида "a->b"
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
			// Обработка изолированной вершины (без дуг)
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

	// Записываем данные в объект Graph
	g.setVertexToIndex(vertexToIndex);
	g.setIndexToVertex(indexToVertex);
	g.setAdjacencyMatrix(adjacencyMatrix);

	return g;
}

vector<string> writeDotFile(
	const vector<vector<int>>& adjacencyMatrix,
	const vector<int>& indexToVertex,
	const vector<pair<int, int>>& path,
	const vector<string>& dotStringGraph,
	const outMessForGraph& messages)
{
	set<pair<int, int>> pathEdges(path.begin(), path.end());
	set<int> pathVertices;
	for (const auto& edge : path) {
		int from = edge.first;
		int to = edge.second;
		pathVertices.insert(from);
		pathVertices.insert(to);
	}

	vector<string> dot;
	string graphName = extractGraphName(dotStringGraph);
	dot.push_back("digraph " + graphName);
	dot.push_back("{");

	int n = static_cast<int>(adjacencyMatrix.size());
	bool allInPath = true;

	bool isSingleVertexTree = false;
	if (n == 1 && pathEdges.size() == 1) {
		auto edge = *pathEdges.begin();
		if (edge.first == edge.second) {
			isSingleVertexTree = true;
		}
	}

	// Обработка изолированных вершин
	for (int i = 0; i < n; ++i) {
		bool hasOutgoing = false, hasIncoming = false;
		for (int j = 0; j < n; ++j) {
			if (adjacencyMatrix[i][j] != 0) hasOutgoing = true;
			if (adjacencyMatrix[j][i] != 0) hasIncoming = true;
			if (hasOutgoing && hasIncoming) break;
		}

		if (!hasOutgoing && !hasIncoming) {
			string line = "    " + to_string(indexToVertex[i]);
			if (pathVertices.count(i) == 0) {
				line += " " + messages.forRemove;
				allInPath = false;
			}
			line += ";";
			dot.push_back(line);
		}
	}

	// Обработка дуг
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (adjacencyMatrix[i][j] != 0) {
				string from = to_string(indexToVertex[i]);
				string to = to_string(indexToVertex[j]);
				string line = "    " + from + " -> " + to;

				if (pathEdges.count({ i, j }) == 0) {
					line += " " + messages.forRemove;
					allInPath = false;

					// Отметить вершины, если они ранее не были упомянуты
					if (pathVertices.count(i) == 0) {
						dot.push_back("    " + from + " " + messages.forRemove + ";");
						pathVertices.insert(i);
					}
					if (pathVertices.count(j) == 0) {
						dot.push_back("    " + to + " " + messages.forRemove + ";");
						pathVertices.insert(j);
					}
				}

				line += ";";
				dot.push_back(line);
			}
		}
	}

	// Добавляем финальное сообщение о том, является ли граф деревом
	if (isSingleVertexTree || allInPath) {
		dot.push_back("    " + messages.graphIsTree + ";");
	}
	else {
		dot.push_back("    " + messages.graphIsNotTree + ";");
	}

	dot.push_back("}");
	return dot;
}
