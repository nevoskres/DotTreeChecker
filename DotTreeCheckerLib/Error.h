#pragma once

#include <string>
#include <vector>
#include "Export.h"

/**
 * @file Error.h
 * @brief Класс и функции для обработки и хранения ошибок при проверке файла с описанием графа.
 *
 * @details Файл содержит определение класса Error, предназначенного для представления различных типов ошибок,
 * возникающих при валидации графа, а также методы для их поиска и хранения.
 */



/**
 * @enum ErrorType
 * @brief Типы ошибок, которые могут возникать при обработке графа.
 */
enum MYLIB_API ErrorType {
    noError,                   /**< Ошибок нет */
    emptyFile,                 /**< Пустой файл */
    connectionsError,          /**< В строке больше одной связи */
    notDiGraph,                /**< Граф не является орграфом */
    countConnectionsError,     /**< Слишком много связей */
    countVerticesError,        /**< Слишком много вершин */
    emptyGraph,                /**< Пустой граф */
    loopError,                 /**< В графе есть петля */
    multipleConnectionsError,  /**< В графе есть кратные связи */
    nameVerticesError,         /**< Некорректное имя вершины */
    graphsNotationSyntaxError, /**< Неверное обозначение графа */
    graphNameSyntaxError,      /**< Неверное имя графа */
    curlyBracketError,         /**< Отсутствует фигурная скобка */
    extraCharacterAfterGraphError, /**< Лишний символ после тела графа */
    extraCharacterInGraphError,     /**< Лишний символ внутри тела графа */
    connectionsSyntaxError          /**< Неверное написание дуги */
};

/**
 * @class Error
 * @brief Класс для хранения информации об ошибках при парсинге графа.
 *
 * @details Хранит тип ошибки, номер строки, текст строки с ошибкой и сообщение об ошибке.
 * Также содержит контейнер для накопления нескольких ошибок.
 */
class MYLIB_API Error
{
private:
    

    ErrorType type = noError;             ///< Тип ошибки (по умолчанию noError)
    int numberStr = -1;                   ///< Номер строки с ошибкой
    std::string lineStr;                  ///< Строка с ошибкой
    std::string message;                  ///< Текст сообщения об ошибке
    std::vector<Error> errors;            ///< Контейнер для накопления ошибок

public:

    /**
     * @brief Генерирует текст сообщения об ошибке на основе типа ошибки
     * @param type Тип ошибки
     * @return Текст сообщения
     */
    std::string generateErrorMessage(ErrorType type) const;

    /**
     * @brief Конструктор по умолчанию
     */
    Error() = default;

    /**
     * @brief Конструктор с инициализацией ошибки
     * @param t Тип ошибки
     * @param n Номер строки с ошибкой
     * @param str Строка, в которой обнаружена ошибка
     */
    Error(ErrorType t, int n, const std::string& str);

    /**
     * @brief Возвращает тип ошибки
     * @return Тип ошибки
     */
    ErrorType getType() const;

    /**
     * @brief Возвращает номер строки с ошибкой
     * @return Номер строки
     */
    int getLineNumber() const;

    /**
     * @brief Возвращает строку, в которой обнаружена ошибка
     * @return Строка с ошибкой
     */
    std::string getLineString() const;

    /**
     * @brief Возвращает текст сообщения об ошибке
     * @return Сообщение об ошибке
     */
    std::string getMessage() const;

    /**
     * @brief Возвращает контейнер с найденными ошибками
     * @return Вектор ошибок
     */
    const std::vector<Error>& getErrors() const;

    /**
     * @brief Выполняет проверку строк графа на ошибки и заполняет контейнер errors
     * @param lines Вектор строк, содержащих описание графа
     */
    void findErrors(const std::vector<std::string>& lines);

};

