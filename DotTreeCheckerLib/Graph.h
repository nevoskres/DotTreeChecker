#pragma once

#include<vector>
#include<map>
#include <string>


/**
* @brief Класс для хранения графа, заданного в формате DOT, и его представлений.
*/
class Graph
{
private:
	/**
	 * @brief Исходное DOT-описание графа в виде строк.
	 */
	std::vector<std::string> dotStringGraph;

	/**
	 * @brief Отображение: имя вершины -> индекс в матрице смежности.
	 */
	std::map<int, int> vertexToIndex;

	/**
	 * @brief Обратное отображение: индекс -> имя вершины.
	 */
	std::vector<int> indexToVertex;

	/**
	 * @brief Матрица смежности графа.
	 */
	std::vector<std::vector<int>> adjacencyMatrix;

public:
	/**
	 * @brief Конструктор по умолчанию.
	 */
	Graph();

	/**
	 * @brief Устанавливает строки DOT-описания графа.
	 * @param lines Вектор строк с DOT-описанием.
	 */
	void setDotStringGraph(const std::vector<std::string>& lines);

	/**
	 * @brief Возвращает строки DOT-описания графа.
	 * @return Вектор строк с DOT-описанием.
	 */
	const std::vector<std::string>& getDotStringGraph() const;

	/**
	 * @brief Устанавливает отображение "вершина → индекс".
	 * @param v2i Map соответствия имени вершины и её индекса.
	 */
	void setVertexToIndex(const std::map<int, int>& v2i);

	/**
	 * @brief Возвращает отображение "вершина → индекс".
	 * @return Map соответствия имени вершины и её индекса.
	 */
	const std::map<int, int>& getVertexToIndex() const;

	/**
	 * @brief Устанавливает отображение "индекс → вершина".
	 * @param i2v Вектор, сопоставляющий индекс с именем вершины.
	 */
	void setIndexToVertex(const std::vector<int>& i2v);

	/**
	 * @brief Возвращает отображение "индекс → вершина".
	 * @return Вектор, сопоставляющий индекс с именем вершины.
	 */
	const std::vector<int>& getIndexToVertex() const;

	/**
	 * @brief Устанавливает матрицу смежности графа.
	 * @param matrix Матрица смежности.
	 */
	void setAdjacencyMatrix(const std::vector<std::vector<int>>& matrix);

	/**
	 * @brief Возвращает матрицу смежности графа.
	 * @return Матрица смежности.
	 */
	const std::vector<std::vector<int>>& getAdjacencyMatrix() const;

};

