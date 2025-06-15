#pragma once

#include <string>
#include <vector>
#include "Export.h"

/**
 * @file Error.h
 * @brief ����� � ������� ��� ��������� � �������� ������ ��� �������� ����� � ��������� �����.
 *
 * @details ���� �������� ����������� ������ Error, ���������������� ��� ������������� ��������� ����� ������,
 * ����������� ��� ��������� �����, � ����� ������ ��� �� ������ � ��������.
 */



/**
 * @enum ErrorType
 * @brief ���� ������, ������� ����� ��������� ��� ��������� �����.
 */
enum MYLIB_API ErrorType {
    noError,                   /**< ������ ��� */
    inFileNotExist,            /**< ���� �� ������ */
    outFileCreateFail,         /**< �� ������� ������� �������� ���� */
    emptyFile,                 /**< ������ ���� */
    connectionsError,          /**< � ������ ������ ����� ����� */
    notDiGraph,                /**< ���� �� �������� �������� */
    countConnectionsError,     /**< ������� ����� ������ */
    countVerticesError,        /**< ������� ����� ������ */
    emptyGraph,                /**< ������ ���� */
    loopError,                 /**< � ����� ���� ����� */
    multipleConnectionsError,  /**< � ����� ���� ������� ����� */
    nameVerticesError,         /**< ������������ ��� ������� */
    graphsNotationSyntaxError, /**< �������� ����������� ����� */
    graphNameSyntaxError,      /**< �������� ��� ����� */
    curlyBracketError,         /**< ����������� �������� ������ */
    extraCharacterAfterGraphError, /**< ������ ������ ����� ���� ����� */
    extraCharacterInGraphError,     /**< ������ ������ ������ ���� ����� */
    connectionsSyntaxError          /**< �������� ��������� ���� */
};

/**
 * @class Error
 * @brief ����� ��� �������� ���������� �� ������� ��� �������� �����.
 *
 * @details ������ ��� ������, ����� ������, ����� ������ � ������� � ��������� �� ������.
 * ����� �������� ��������� ��� ���������� ���������� ������.
 */
class MYLIB_API Error
{
private:
    /**
     * @brief ���������� ����� ��������� �� ������ �� ������ ���� ������
     * @param type ��� ������
     * @return ����� ���������
     */
    std::string generateErrorMessage(ErrorType type) const;

    ErrorType type = noError;             ///< ��� ������ (�� ��������� noError)
    int numberStr = -1;                   ///< ����� ������ � �������
    std::string lineStr;                  ///< ������ � �������
    std::string message;                  ///< ����� ��������� �� ������
    std::vector<Error> errors;            ///< ��������� ��� ���������� ������

public:
    /**
     * @brief ����������� �� ���������
     */
    Error() = default;

    /**
     * @brief ����������� � �������������� ������
     * @param t ��� ������
     * @param n ����� ������ � �������
     * @param str ������, � ������� ���������� ������
     */
    Error(ErrorType t, int n, const std::string& str);

    /**
     * @brief ���������� ��� ������
     * @return ��� ������
     */
    ErrorType getType() const;

    /**
     * @brief ���������� ����� ������ � �������
     * @return ����� ������
     */
    int getLineNumber() const;

    /**
     * @brief ���������� ������, � ������� ���������� ������
     * @return ������ � �������
     */
    std::string getLineString() const;

    /**
     * @brief ���������� ����� ��������� �� ������
     * @return ��������� �� ������
     */
    std::string getMessage() const;

    /**
     * @brief ���������� ��������� � ���������� ��������
     * @return ������ ������
     */
    const std::vector<Error>& getErrors() const;

    /**
     * @brief ��������� �������� ����� ����� �� ������ � ��������� ��������� errors
     * @param lines ������ �����, ���������� �������� �����
     */
    void findErrors(const std::vector<std::string>& lines);
};

