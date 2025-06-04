#include "pch.h"
#include "graph_utils.h"
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
