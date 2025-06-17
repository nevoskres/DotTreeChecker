#include "pch.h"
#include "graph_utils.h"
#include<set>
using namespace std;

void DFS(int start, vector<bool>& visited, vector<vector<int>>& adjMatrix, vector<pair<int, int>>& way)
{
	//�������� ������� ������� ��� ���������
	visited[start] = true;

	//�������� �� ���� ��������� ������� ������� �������
	for (int neighbor = 0; neighbor < adjMatrix.size(); ++neighbor)
	{
		//���� ���������� ����� �� start � ������ � ���� ����� ��� �� �������
		if (adjMatrix[start][neighbor] == 1 && !visited[neighbor])
		{
			//�������� ���� ��� ����� ������
			adjMatrix[start][neighbor] = 2;
			//��������� ��� ���� � ����  
			way.emplace_back(start, neighbor);
			//���������� �������� DFS ��� ������
			DFS(neighbor, visited, adjMatrix, way);
		}
	}
}

vector<pair<int, int>> findBestSkeleton(vector<vector<int>> matrixCopy)
{

	vector<pair<int, int>> skeleton;
	int maxVisited = -1;
	int bestStartVertex = -1;



	//��� ������ ������� �����
	for (int i = 0; i < matrixCopy.size(); ++i)
	{
		vector<pair<int, int>> s;
		std::vector<bool> visited(matrixCopy.size(), false);
		vector<vector<int>> matrixCopyCopy = matrixCopy;


		//����������� ����� � ������� �� ������� �������
		DFS(i, visited, matrixCopyCopy, s);

		int visitedCount = int(count(visited.begin(), visited.end(), true));

		//���� ���������� ���������� ������ �� ������� ������ ��� � ����������
		if (visitedCount > maxVisited)
		{
			//�������� ����� ���������� ������ ��� ����������� 
			maxVisited = visitedCount;
			//�������� ����� ���� ��� ������ �����
			skeleton = s;
			//�������� ������� ������ 
			bestStartVertex = i;
		}
	}

	// ���� ����� ���� (��� ���), �� ������� ����, �������� "������-�����"
	if (skeleton.empty() && bestStartVertex != -1)
	{
		//�������� ����� �� ������� � ���� ���� 
		skeleton.push_back({ bestStartVertex, bestStartVertex });
	}

	//������� ������ ����� (����)
	return skeleton;
}


Graph parseDotFile(const vector<string>& lines)
{

	Graph g;
	g.setDotStringGraph(lines);

	map<int, int> vertexToIndex;        // �����������: ��� ������� ������
	vector<int> indexToVertex;          // �������� �����������: ������ ��� �������
	vector<pair<int, int>> edges;       // ������ ���

	// ������������ ������
	for (const string& line : lines)
	{
		if (line == "digraph G" || line == "{" || line == "}") continue;

		size_t arrowPos = line.find("->");
		if (arrowPos != string::npos)
		{
			// ����: a->b
			int from = stoi(line.substr(0, arrowPos));
			int to = stoi(line.substr(arrowPos + 2));

			edges.emplace_back(from, to);

			// ������������ �������
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
			// ������������� �������
			int v = stoi(line);
			if (vertexToIndex.find(v) == vertexToIndex.end()) {
				vertexToIndex[v] = indexToVertex.size();
				indexToVertex.push_back(v);
			}
		}
	}

	// �������� ������� ���������
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


string extractGraphName(const vector<string>& dotLines) 
{
	if (dotLines.empty()) return "G";

	const string& line = dotLines.front();

	size_t pos = line.find("digraph");
	if (pos == string::npos) return "G";

	pos += 7;

	while (pos < line.size() && isspace(static_cast<unsigned char>(line[pos]))) ++pos;

	string name;
	while (pos < line.size() && (isalnum(static_cast<unsigned char>(line[pos])) || line[pos] == '_')) {
		name += line[pos++];
	}

	return name.empty() ? "G" : name;
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

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (adjacencyMatrix[i][j] != 0) {
				string from = to_string(indexToVertex[i]);
				string to = to_string(indexToVertex[j]);
				string line = "    " + from + " -> " + to;

				if (pathEdges.count({ i, j }) == 0) {
					line += " " + messages.forRemove;
					allInPath = false;

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

	if (isSingleVertexTree || allInPath) {
		dot.push_back("    " + messages.graphIsTree + ";");
	}
	else {
		dot.push_back("    " + messages.graphIsNotTree + ";");
	}

	dot.push_back("}");
	return dot;
}
