#include "pch.h"
#include "CppUnitTest.h"
#include "../DotTreeCheckerLib/Error.h"

#include <vector>
#include <string>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework {

            template<>
            inline std::wstring ToString<ErrorType>(const ErrorType& e)
            {
                switch (e)
                {
                case noError: return L"noError";
                case inFileNotExist: return L"inFileNotExist";
                case outFileCreateFail: return L"outFileCreateFail";
                case emptyFile: return L"emptyFile";
                case connectionsError: return L"connectionsError";
                case notDiGraph: return L"notDiGraph";
                case countConnectionsError: return L"countConnectionsError";
                case countVerticesError: return L"countVerticesError";
                case emptyGraph: return L"emptyGraph";
                case loopError: return L"loopError";
                case multipleConnectionsError: return L"multipleConnectionsError";
                case nameVerticesError: return L"nameVerticesError";
                case graphsNotationSyntaxError: return L"graphsNotationSyntaxError";
                case graphNameSyntaxError: return L"graphNameSyntaxError";
                case curlyBracketError: return L"curlyBracketError";
                case extraCharacterAfterGraphError: return L"extraCharacterAfterGraphError";
                case extraCharacterInGraphError: return L"extraCharacterInGraphError";
                case connectionsSyntaxError: return L"connectionsSyntaxError";
                default: return L"UnknownErrorType";
                }
            }

        } 
    } 
} 


using namespace std;

/**
 * @file test_findErrors.cpp
 * @brief Набор модульных тестов для функции findErrors из Error.h
 */




namespace findErrorsTests
{
	TEST_CLASS(findErrorsTests)
	{
	public:

		/// @brief Тест findErrors: линейный граф из трех вершин без ошибок
		TEST_METHOD(findErrors_correctLinearGraph)
		{
            Error errorObj;
            vector<string> input =
            {
                "digraph G",
                "{",
                "1->2;",
                "2->3",
                "}"
            };

            errorObj.findErrors(input);

            Assert::IsTrue(errorObj.getErrors().empty());
		}

        /// @brief Тест findErrors: циклический граф из четырех вершин без ошибок
        TEST_METHOD(findErrors_correctCycleGraph)
        {
            Error errorObj;
            vector<string> input =
            {
                "digraph G",
                "{",
                "1->2",
                "2->3",
                "3->4",
                "4->2",
                "}"
            };

            errorObj.findErrors(input);

            Assert::IsTrue(errorObj.getErrors().empty());
        }

        /// @brief Тест findErrors: ошибка - пустой файл 
        TEST_METHOD(findErrors_emptyFile)
        {
            Error errorObj;
            vector<string> input = {}; // пустой файл

            errorObj.findErrors(input);

        
            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(emptyFile, errorObj.getErrors()[0].getType());
            Assert::AreEqual(0, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка - пустой файл тоолько с пробелами 
        TEST_METHOD(findErrors_spaceFile)
        {
            Error errorObj;
            vector<string> input = {"   ","   ","      "}; // пустой файл с пробелами

            errorObj.findErrors(input);


            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(emptyFile, errorObj.getErrors()[0].getType());
            Assert::AreEqual(0, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка - в строке больше одной связи
        TEST_METHOD(findErrors_twoConnectionsInStr)
        {
            Error errorObj;
            vector<string> input =
            {
                "digraph G",
                "{",
                "1->2->5",
                "2->3",            
                "}"
            };

            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(connectionsError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(3, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка - указан неориентированный граф и ошибка связи
        TEST_METHOD(findErrors_notDiGraph)
        {
            Error errorObj;
            vector<string> input =
            {
                "graph G",
                "{",
                "1--2",
                "}"
            };

            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(notDiGraph, errorObj.getErrors()[0].getType());
            Assert::AreEqual(1, errorObj.getErrors()[0].getLineNumber());
            
        }

        /// @brief Тест findErrors: ошибка - в графе есть петля
        TEST_METHOD(findErrors_loopConnection)
        {
            Error errorObj;
            vector<string> input =
            {
                "digraph G",
                "{",
                "3->2",
                "1->1",
                "}"
            };

            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(loopError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(4, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка - пустой граф
        TEST_METHOD(findErrors_emptyGraph)
        {
            Error errorObj;
            vector<string> input =
            {
                "digraph G",
                "{",
                "}"
            };

            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(emptyGraph, errorObj.getErrors()[0].getType());
            Assert::AreEqual(3, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка - количество вершин превышает допустимое
        TEST_METHOD(findErrors_overCountVertices)
        {
            Error errorObj;
            vector<string> input = {
    "digraph G",
    "{",
    "1->2",
    "2->3",
    "2->4",
    "4->5",
    "4->6",
    "4->7",
    "6->8",
    "3->9",
    "9->10",
    "5->11",
    "1->12",
    "}"
            };

            errorObj.findErrors(input);

            Assert::AreEqual(size_t(3), errorObj.getErrors().size());

            Assert::AreEqual(nameVerticesError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(12, errorObj.getErrors()[0].getLineNumber());
            Assert::AreEqual(nameVerticesError, errorObj.getErrors()[1].getType());
            Assert::AreEqual(13, errorObj.getErrors()[1].getLineNumber());

            Assert::AreEqual(countVerticesError, errorObj.getErrors()[2].getType());
            Assert::AreEqual(14, errorObj.getErrors()[2].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка - в графе есть кратные связи
        TEST_METHOD(findErrors_multipleEdges)
        {
            Error errorObj;
            vector<string> input = {
    "digraph G",
    "{",
    "1->2",
    "2->3",
    "1->2",
    "}"
            };


            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(multipleConnectionsError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(5, errorObj.getErrors()[0].getLineNumber());
        }


        /// @brief Тест findErrors:  ошибка имени графа (буква)
        TEST_METHOD(findErrors_invalidVertexName)
        {
            Error errorObj;
            vector<string> input = {
     "digraph G",
    "{",
    "2->a",
    "}"
            };


            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(nameVerticesError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(3, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка имени графа (цифра больше 9)
        TEST_METHOD(findErrors_vertexNameOutOfRange)
        {
            Error errorObj;
            vector<string> input = {
     "digraph G",
    "{",
    "2->22",
    "}"
            };


            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(nameVerticesError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(3, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка обозначения графа 
        TEST_METHOD(findErrors_invalidGraphNotation)
        {
            Error errorObj;
            vector<string> input = {
     "digrph G",
    "{",
    "1->2",
    "}"
            };


            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(graphsNotationSyntaxError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(1, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка имени графа 
        TEST_METHOD(findErrors_invalidGraphName)
        {
            Error errorObj;
            vector<string> input = {
    "digraph G%%",
    "{",
    "1->2",
    "}"
            };


            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(graphNameSyntaxError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(1, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка - отсутствует закрывающая фигурная скобка
        TEST_METHOD(findErrors_missingClosingBrace)
        {
            Error errorObj;
            vector<string> input = {
   "digraph G",
    "{",
    "1->2",
    "2->3",
    "2->4"
            };


            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(curlyBracketError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(6, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка - лишний символ псле тела графа 
        TEST_METHOD(findErrors_extraClosingBrace)
        {
            Error errorObj;
            vector<string> input = {

    "digraph G",
    "{",
    "1->2",
    "2->3",
    "2->4",
    "}}"
};


            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(extraCharacterAfterGraphError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(6, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка — лишний символ в теле графа
        TEST_METHOD(findErrors_extraSymbolInGraphBody)
        {
            Error errorObj;
            vector<string> input = {
                "digraph G",
                "{",
                "1->2",
                "2->3 %",
                "2->4;",
                "}"
            };

            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(extraCharacterInGraphError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(4, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка — синтаксис дуги нарушен (2>4)
        TEST_METHOD(findErrors_invalidEdgeSyntax)
        {
            Error errorObj;
            vector<string> input = {
                "digraph G",
                "{",
                "2->3",
                "2>4",
                "}"
            };

            errorObj.findErrors(input);

            Assert::AreEqual(size_t(1), errorObj.getErrors().size());
            Assert::AreEqual(connectionsSyntaxError, errorObj.getErrors()[0].getType());
            Assert::AreEqual(4, errorObj.getErrors()[0].getLineNumber());
        }

        /// @brief Тест findErrors: ошибка — превышено допустимое количество связей (>110)
        TEST_METHOD(findErrors_tooManyConnections)
        {
            Error errorObj;
            std::vector<std::string> input = {
                "digraph G",
                "{"
            };

            for (int i = 0; i <= 110; ++i) {
                input.push_back(to_string(i % 10) + "->" + to_string((i + 1) % 10));
            }

            input.push_back("}");

            errorObj.findErrors(input);

            bool hasCountConnectionsError = any_of(
                errorObj.getErrors().begin(),
                errorObj.getErrors().end(),
                [](const auto& e) {
                    return e.getType() == countConnectionsError;
                }
            );

            Assert::IsTrue(hasCountConnectionsError);
        }

        /// @brief Тест findErrors: несколько ошибок в одном файле
        TEST_METHOD(findErrors_multipleErrorsInFile)
        {
            Error errorObj;
            std::vector<std::string> input = {
                "digrph G",
                "{",
                "1->2",
                "2->3 %",
                "1->4",
                "2>4",
                "}"
            };

            errorObj.findErrors(input);

            const auto& errs = errorObj.getErrors();
            Assert::AreEqual(size_t(3), errs.size());

            Assert::AreEqual(graphsNotationSyntaxError, errs[0].getType());
            Assert::AreEqual(1, errs[0].getLineNumber());

            Assert::AreEqual(extraCharacterInGraphError, errs[1].getType());
            Assert::AreEqual(4, errs[1].getLineNumber());

            Assert::AreEqual(connectionsSyntaxError, errs[2].getType());
            Assert::AreEqual(6, errs[2].getLineNumber());
        }


	};
}
