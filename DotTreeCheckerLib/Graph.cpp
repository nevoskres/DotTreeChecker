#include "pch.h"
#include"Graph.h"
#include<string>

Graph::Graph() {}

void Graph::setDotStringGraph(const std::vector<std::string>& lines)
{ 
	dotStringGraph = lines;
}


const std::vector<std::string>& Graph::getDotStringGraph() const
{
	return dotStringGraph;
}


void Graph::setVertexToIndex(const std::map<int, int>& v2i)
{
	vertexToIndex = v2i;
}


const std::map<int, int>& Graph::getVertexToIndex() const
{
	return vertexToIndex;
}


void Graph::setIndexToVertex(const std::vector<int>& i2v)
{
	indexToVertex = i2v;
}


const std::vector<int>& Graph::getIndexToVertex() const
{
	return indexToVertex;
}


void Graph::setAdjacencyMatrix(const std::vector<std::vector<int>>& matrix)
{ 
	adjacencyMatrix = matrix;
}

const std::vector<std::vector<int>>& Graph::getAdjacencyMatrix() const
{
	return adjacencyMatrix;
}

std::string Graph::extractGraphName() const 
{
    if (dotStringGraph.empty()) return "G";

    const std::string& line = dotStringGraph.front();

    size_t pos = line.find("digraph");
    if (pos == std::string::npos) return "G";

    pos += 7; 

    while (pos < line.size() && isspace(static_cast<unsigned char>(line[pos]))) ++pos;

    std::string name;
    while (pos < line.size() && (isalnum(static_cast<unsigned char>(line[pos])) || line[pos] == '_')) {
        name += line[pos++];
    }

    return name.empty() ? "G" : name;
}
