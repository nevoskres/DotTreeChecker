
/**
 * @file Export.h
 * @brief Определение макроса экспорта/импорта символов для библиотеки.
 *
 * @details Этот файл содержит макрос `MYLIB_API`, который управляет экспортом и импортом
 * функций, классов и переменных между библиотекой и внешними проектами.
 */

#pragma once

#define MYLIB_API

//#ifdef MYLIBRARY_EXPORTS
//#define MYLIB_API __declspec(dllexport)
//#else
//#define MYLIB_API __declspec(dllimport)
//#endif
